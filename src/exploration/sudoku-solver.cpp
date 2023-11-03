// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <cassert>
#include <functional>
#include <list>
#include <set>
#include <utility>
#include <vector>


// FIFO with unique elements
template<typename T>
class UniqueQueue {
 public:
  void add(const T& t) {
    if (set.insert(t).second) {
      list.push_back(t);
    }
  }

  bool empty() const {
    assert(list.empty() == set.empty());
    return list.empty();
  }

  bool has(const T& t) const {
    return set.count(t);
  }

  T get() {
    assert(!empty());
    const T t = list.front();
    list.pop_front();
    set.erase(t);
    return t;
  }

 private:
  std::list<T> list;
  std::set<T> set;
};


struct NeedsBacktracking {};


// Make sure a closing event is added, however the scope is exited
struct EventsPairGuard {
  EventsPairGuard(
    const std::function<void(std::unique_ptr<exploration::Event>)>& add_event_,
    std::unique_ptr<exploration::Event> in,
    std::unique_ptr<exploration::Event> out_
  ) :  // NOLINT(whitespace/parens)
    add_event(add_event_),
    out(std::move(out_))
  {  // NOLINT(whitespace/braces)
    add_event(std::move(in));
  }

  ~EventsPairGuard() {
    add_event(std::move(out));
  }

  const std::function<void(std::unique_ptr<exploration::Event>)>& add_event;
  std::unique_ptr<exploration::Event> out;
};


void propagate(
  Sudoku* sudoku,
  const std::set<Sudoku::Coordinates>& todo_,
  const std::function<void(std::unique_ptr<exploration::Event>)>& add_event
) {
  UniqueQueue<Sudoku::Coordinates> todo;
  for (const auto cell : todo_) {
    todo.add(cell);
  }

  EventsPairGuard guard(
    add_event,
    std::make_unique<exploration::PropagationStartsForSudoku>(),
    std::make_unique<exploration::PropagationIsDoneForSudoku>());

  while (!todo.empty()) {
    const auto source_cell = todo.get();
    assert(sudoku->is_set(source_cell));
    const unsigned value = sudoku->get(source_cell);

    EventsPairGuard guard(
      add_event,
      std::make_unique<exploration::PropagationStartsForCell>(source_cell, value),
      std::make_unique<exploration::PropagationIsDoneForCell>(source_cell, value));

    const auto [row, col] = source_cell;
    for (const auto region : Sudoku::regions_of[row][col]) {
      for (const auto target_cell : Sudoku::regions[region]) {
        if (target_cell != source_cell) {
          if (sudoku->is_set(target_cell)) {
            if (sudoku->get(target_cell) == value) {
              throw NeedsBacktracking();
            }
          } else {
            assert(sudoku->allowed_count(target_cell) > 1);
            if (sudoku->is_allowed(target_cell, value)) {
              add_event(std::make_unique<exploration::CellPropagates>(source_cell, target_cell, value));
              sudoku->forbid(target_cell, value);

              if (sudoku->allowed_count(target_cell) == 1) {
                for (unsigned value : Sudoku::values) {
                  if (sudoku->is_allowed(target_cell, value)) {
                    sudoku->set(target_cell, value);
                    break;
                  }
                }
                add_event(std::make_unique<exploration::CellIsDeducedFromSingleAllowedValue>(
                  target_cell, sudoku->get(target_cell)));
                todo.add(target_cell);
              }

              for (unsigned region : Sudoku::regions_of[target_cell.first][target_cell.second]) {
                unsigned count = 0;
                Sudoku::Coordinates single_cell;
                for (auto cell : Sudoku::regions[region]) {
                  if (sudoku->is_allowed(cell, value)) {
                    ++count;
                    single_cell = cell;
                  }
                }
                if (count == 1 && !sudoku->is_set(single_cell)) {
                  sudoku->set(single_cell, value);
                  add_event(std::make_unique<exploration::CellIsDeducedAsSinglePlaceForValueInRegion>(
                    single_cell, value, region));
                  todo.add(single_cell);
                }
              }

              // 'Sudoku::is_solved' is currently O(Sudoku::size^2),
              // which we could optimize easily with additional book-keeping,
              // but the *whole* solving algorithm still executes in less than 100ms for size 9,
              // so it's not worth it yet.
              if (sudoku->is_solved()) {
                add_event(std::make_unique<exploration::SudokuIsSolved>());
              }
            } else {
              // Nothing to do: this is old news
            }
          }
        }
      }
    }
  }
}


Sudoku::Coordinates get_most_constrained_cell(const Sudoku& sudoku) {
  Sudoku::Coordinates best_cell;
  unsigned best_count = Sudoku::size + 1;

  for (const auto cell : Sudoku::cells) {
    if (sudoku.is_set(cell)) {
      continue;
    }
    unsigned count = sudoku.allowed_count(cell);
    if (count < best_count) {
      best_cell = cell;
      best_count = count;
    }
    if (best_count == 2) {
      break;
    }
  }

  return best_cell;
}


void propagate_and_explore(
  Sudoku* sudoku,
  const std::set<Sudoku::Coordinates>& todo,
  const std::function<void(std::unique_ptr<exploration::Event>)>&
);


void explore(Sudoku* sudoku, const std::function<void(std::unique_ptr<exploration::Event>)>& add_event) {
  assert(!sudoku->is_solved());

  const auto cell = get_most_constrained_cell(*sudoku);
  std::vector<unsigned> allowed_values;
  for (unsigned val : Sudoku::values) {
    if (sudoku->is_allowed(cell, val)) {
      allowed_values.push_back(val);
    }
  }

  EventsPairGuard guard(
    add_event,
    std::make_unique<exploration::ExplorationStarts>(cell, allowed_values),
    std::make_unique<exploration::ExplorationIsDone>(cell));

  // @todo Artificially favor values without solution to demonstrate and visualize backtracking
  for (unsigned val : allowed_values) {
    auto hypothesis_ = std::make_unique<exploration::HypothesisIsMade>(cell, val);
    exploration::HypothesisIsMade* hypothesis = hypothesis_.get();
    add_event(std::move(hypothesis_));
    try {
      Sudoku copy = *sudoku;
      copy.set(cell, val);
      propagate_and_explore(&copy, {cell}, add_event);
      if (copy.is_solved()) {
        hypothesis->spoiler = true;
        add_event(std::make_unique<exploration::HypothesisIsAccepted>(cell, val));
        *sudoku = copy;
        break;
      } else {
        throw NeedsBacktracking();
      }
    } catch (NeedsBacktracking&) {
      hypothesis->spoiler = false;
      add_event(std::make_unique<exploration::HypothesisIsRejected>(cell, val));
    }
  }
}


void propagate_and_explore(
  Sudoku* sudoku, const std::set<Sudoku::Coordinates>& todo,
  const std::function<void(std::unique_ptr<exploration::Event>)>& add_event
) {
  propagate(sudoku, todo, add_event);
  if (!sudoku->is_solved()) {
    explore(sudoku, add_event);
  }
}


Sudoku solve_using_exploration(
  Sudoku sudoku,
  const std::function<void(std::unique_ptr<exploration::Event>)>& add_event
) {
  std::set<Sudoku::Coordinates> todo;
  for (auto cell : Sudoku::cells) {
    if (sudoku.is_set(cell)) {
      todo.insert(cell);
      add_event(std::make_unique<exploration::CellIsSetInInput>(cell, sudoku.get(cell)));
    }
  }
  add_event(std::make_unique<exploration::InputsAreDone>());
  try {
    propagate_and_explore(&sudoku, std::move(todo), add_event);
  } catch (NeedsBacktracking&) {
    // Nothing to do, just return the unsolved Sudoku
  }

  return sudoku;
}
