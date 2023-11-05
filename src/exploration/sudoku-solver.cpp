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


// This is the only way to modify the Stack (everywhere else, it's manipulated through const references).
// This design ensures that the events returned to the client can replicate exactly the evolution of the
// stack that happened during the exploration, because the stack actually evolved only through said events.
// (I think this is brilliant, but I *may* biased as I'm the author of this code).
struct AddEvent {
  AddEvent(Stack* stack_, const std::function<void(std::unique_ptr<exploration::Event>)>& add_event_)
    : stack(stack_), add_event(add_event_) {}

  void operator()(std::unique_ptr<exploration::Event> event) const {
    event->apply(stack);
    add_event(std::move(event));
  }

 private:
  Stack* stack;
  const std::function<void(std::unique_ptr<exploration::Event>)>& add_event;
};


// Make sure a closing event is added, however the scope is exited
struct EventsPairGuard {
  EventsPairGuard(
    const AddEvent& add_event_,
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

  const AddEvent& add_event;
  std::unique_ptr<exploration::Event> out;
};


void propagate(
  const Stack& stack,
  const std::set<AnnotatedSudoku::Coordinates>& todo_,
  const AddEvent& add_event
) {
  UniqueQueue<AnnotatedSudoku::Coordinates> todo;
  for (const auto cell : todo_) {
    todo.add(cell);
  }

  EventsPairGuard guard(
    add_event,
    std::make_unique<exploration::PropagationStartsForSudoku>(),
    std::make_unique<exploration::PropagationIsDoneForSudoku>());

  while (!todo.empty()) {
    const auto source_cell = todo.get();
    assert(stack.current().is_set(source_cell));
    const unsigned value = stack.current().get(source_cell);

    EventsPairGuard guard(
      add_event,
      std::make_unique<exploration::PropagationStartsForCell>(source_cell, value),
      std::make_unique<exploration::PropagationIsDoneForCell>(source_cell, value));

    const auto [row, col] = source_cell;
    for (const auto region : AnnotatedSudoku::regions_of[row][col]) {
      for (const auto target_cell : AnnotatedSudoku::regions[region]) {
        if (target_cell != source_cell) {
          if (stack.current().is_set(target_cell)) {
            if (stack.current().get(target_cell) == value) {
              throw NeedsBacktracking();
            }
          } else {
            assert(stack.current().allowed_count(target_cell) > 1);
            if (stack.current().is_allowed(target_cell, value)) {
              add_event(std::make_unique<exploration::CellPropagates>(source_cell, target_cell, value));

              if (stack.current().allowed_count(target_cell) == 1) {
                for (unsigned value : AnnotatedSudoku::values) {
                  if (stack.current().is_allowed(target_cell, value)) {
                    add_event(std::make_unique<exploration::CellIsDeducedFromSingleAllowedValue>(
                      target_cell, value));
                    todo.add(target_cell);
                    break;
                  }
                }
              }

              for (unsigned region : AnnotatedSudoku::regions_of[target_cell.first][target_cell.second]) {
                unsigned count = 0;
                AnnotatedSudoku::Coordinates single_cell;
                for (auto cell : AnnotatedSudoku::regions[region]) {
                  if (stack.current().is_allowed(cell, value)) {
                    ++count;
                    single_cell = cell;
                  }
                }
                if (count == 1 && !stack.current().is_set(single_cell)) {
                  add_event(std::make_unique<exploration::CellIsDeducedAsSinglePlaceForValueInRegion>(
                    single_cell, value, region));
                  todo.add(single_cell);
                }
              }

              // 'AnnotatedSudoku::is_solved' is currently O(AnnotatedSudoku::size^2),
              // which we could optimize easily with additional book-keeping,
              // but the *whole* solving algorithm still executes in less than 100ms for size 9,
              // so it's not worth it yet.
              if (stack.current().is_solved()) {
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


AnnotatedSudoku::Coordinates get_most_constrained_cell(const AnnotatedSudoku& sudoku) {
  AnnotatedSudoku::Coordinates best_cell;
  unsigned best_count = AnnotatedSudoku::size + 1;

  for (const auto cell : AnnotatedSudoku::cells) {
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
  const Stack&,
  const std::set<AnnotatedSudoku::Coordinates>& todo,
  const AddEvent&
);


void explore(const Stack& stack, const AddEvent& add_event) {
  assert(!stack.current().is_solved());

  const auto cell = get_most_constrained_cell(stack.current());
  std::vector<unsigned> allowed_values;
  for (unsigned val : AnnotatedSudoku::values) {
    if (stack.current().is_allowed(cell, val)) {
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
      propagate_and_explore(stack, {cell}, add_event);
      if (stack.current().is_solved()) {
        hypothesis->spoiler = true;
        add_event(std::make_unique<exploration::HypothesisIsAccepted>(cell, val));
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
  const Stack& stack,
  const std::set<AnnotatedSudoku::Coordinates>& todo,
  const AddEvent& add_event
) {
  propagate(stack, todo, add_event);
  if (!stack.current().is_solved()) {
    explore(stack, add_event);
  }
}


io::Sudoku solve_using_exploration(
  io::Sudoku sudoku,
  const std::function<void(std::unique_ptr<exploration::Event>)>& add_event_
) {
  Stack stack;
  AddEvent add_event(&stack, add_event_);
  std::set<AnnotatedSudoku::Coordinates> todo;
  for (auto cell : AnnotatedSudoku::cells) {
    const auto val = sudoku.get(cell);
    if (val) {
      add_event(std::make_unique<exploration::CellIsSetInInput>(cell, *val));
      todo.insert(cell);
    }
  }

  add_event(std::make_unique<exploration::InputsAreDone>());

  try {
    propagate_and_explore(stack, std::move(todo), add_event);
  } catch (NeedsBacktracking&) {
    // Nothing to do, just return the unsolved Sudoku
  }

  for (auto cell : AnnotatedSudoku::cells) {
    if (stack.current().is_set(cell)) {
      sudoku.set(cell, stack.current().get(cell));
    }
  }
  return sudoku;
}
