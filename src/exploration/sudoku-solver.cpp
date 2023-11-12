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
template<unsigned size>
struct AddEvent {
  AddEvent(Stack<size>* stack_, const std::function<void(std::unique_ptr<exploration::Event<size>>)>& add_event_)
    : stack(stack_), add_event(add_event_) {}

  void operator()(std::unique_ptr<exploration::Event<size>> event) const {
    event->apply(stack);
    add_event(std::move(event));
  }

 private:
  Stack<size>* stack;
  const std::function<void(std::unique_ptr<exploration::Event<size>>)>& add_event;
};


// Make sure a closing event is added, however the scope is exited
template<unsigned size>
struct EventsPairGuard {
  EventsPairGuard(
    const AddEvent<size>& add_event_,
    std::unique_ptr<exploration::Event<size>> in,
    std::unique_ptr<exploration::Event<size>> out_
  ) :  // NOLINT(whitespace/parens)
    add_event(add_event_),
    out(std::move(out_))
  {  // NOLINT(whitespace/braces)
    add_event(std::move(in));
  }

  ~EventsPairGuard() {
    add_event(std::move(out));
  }

  const AddEvent<size>& add_event;
  std::unique_ptr<exploration::Event<size>> out;
};


template<unsigned size>
void propagate(
  const Stack<size>& stack,
  const std::set<Coordinates>& todo_,
  const AddEvent<size>& add_event
) {
  UniqueQueue<Coordinates> todo;
  for (const auto cell : todo_) {
    todo.add(cell);
  }

  EventsPairGuard<size> guard(
    add_event,
    std::make_unique<exploration::PropagationStartsForSudoku<size>>(),
    std::make_unique<exploration::PropagationIsDoneForSudoku<size>>());

  while (!todo.empty()) {
    const auto source_cell = todo.get();
    assert(stack.current().cell_at(source_cell).is_set());
    const unsigned value = stack.current().cell_at(source_cell).get();

    EventsPairGuard<size> guard(
      add_event,
      std::make_unique<exploration::PropagationStartsForCell<size>>(source_cell, value),
      std::make_unique<exploration::PropagationIsDoneForCell<size>>(source_cell, value));

    const auto [row, col] = source_cell;
    for (const auto region : SudokuConstants<size>::regions_of[row][col]) {
      for (const auto target_cell : SudokuConstants<size>::regions[region]) {
        if (target_cell != source_cell) {
          if (stack.current().cell_at(target_cell).is_set()) {
            if (stack.current().cell_at(target_cell).get() == value) {
              throw NeedsBacktracking();
            }
          } else {
            assert(stack.current().cell_at(target_cell).allowed_count() > 1);
            if (stack.current().cell_at(target_cell).is_allowed(value)) {
              add_event(std::make_unique<exploration::CellPropagates<size>>(source_cell, target_cell, value));

              if (stack.current().cell_at(target_cell).allowed_count() == 1) {
                for (unsigned value : SudokuConstants<size>::values) {
                  if (stack.current().cell_at(target_cell).is_allowed(value)) {
                    add_event(std::make_unique<exploration::CellIsDeducedFromSingleAllowedValue<size>>(
                      target_cell, value));
                    todo.add(target_cell);
                    break;
                  }
                }
              }

              for (unsigned region : SudokuConstants<size>::regions_of[target_cell.first][target_cell.second]) {
                unsigned count = 0;
                Coordinates single_cell;
                for (auto cell : SudokuConstants<size>::regions[region]) {
                  if (stack.current().cell_at(cell).is_allowed(value)) {
                    ++count;
                    single_cell = cell;
                  }
                }
                if (count == 1 && !stack.current().cell_at(single_cell).is_set()) {
                  add_event(std::make_unique<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>>(
                    single_cell, value, region));
                  todo.add(single_cell);
                }
              }

              // 'AnnotatedSudoku::is_solved' is currently O(AnnotatedSudoku::size^2),
              // which we could optimize easily with additional book-keeping,
              // but the *whole* solving algorithm still executes in less than 100ms for size 9,
              // so it's not worth it yet.
              if (stack.current().is_solved()) {
                add_event(std::make_unique<exploration::SudokuIsSolved<size>>());
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


template<unsigned size>
Coordinates get_most_constrained_cell(const AnnotatedSudoku<size>& sudoku) {
  Coordinates best_cell;
  unsigned best_count = size + 1;

  for (const auto cell : SudokuConstants<size>::cells) {
    if (sudoku.cell_at(cell).is_set()) {
      continue;
    }
    unsigned count = sudoku.cell_at(cell).allowed_count();
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


template<unsigned size>
void propagate_and_explore(
  const Stack<size>&,
  const std::set<Coordinates>& todo,
  const AddEvent<size>&
);


template<unsigned size>
void explore(const Stack<size>& stack, const AddEvent<size>& add_event) {
  assert(!stack.current().is_solved());

  const auto cell = get_most_constrained_cell(stack.current());
  std::vector<unsigned> allowed_values;
  for (unsigned val : SudokuConstants<size>::values) {
    if (stack.current().cell_at(cell).is_allowed(val)) {
      allowed_values.push_back(val);
    }
  }

  EventsPairGuard<size> guard(
    add_event,
    std::make_unique<exploration::ExplorationStarts<size>>(cell, allowed_values),
    std::make_unique<exploration::ExplorationIsDone<size>>(cell));

  // @todo Artificially favor values without solution to demonstrate and visualize backtracking
  for (unsigned val : allowed_values) {
    auto hypothesis_ = std::make_unique<exploration::HypothesisIsMade<size>>(cell, val);
    exploration::HypothesisIsMade<size>* hypothesis = hypothesis_.get();
    add_event(std::move(hypothesis_));
    try {
      propagate_and_explore(stack, {cell}, add_event);
      if (stack.current().is_solved()) {
        add_event(std::make_unique<exploration::HypothesisIsAccepted<size>>(cell, val));
        break;
      } else {
        throw NeedsBacktracking();
      }
    } catch (NeedsBacktracking&) {
      add_event(std::make_unique<exploration::HypothesisIsRejected<size>>(cell, val));
    }
  }
}


template<unsigned size>
void propagate_and_explore(
  const Stack<size>& stack,
  const std::set<Coordinates>& todo,
  const AddEvent<size>& add_event
) {
  propagate(stack, todo, add_event);
  if (!stack.current().is_solved()) {
    explore(stack, add_event);
  }
}


template<unsigned size>
Sudoku<ValueCell, size> solve_using_exploration(
  Sudoku<ValueCell, size> sudoku,
  const std::function<void(std::unique_ptr<exploration::Event<size>>)>& add_event_
) {
  Stack<size> stack;
  AddEvent<size> add_event(&stack, add_event_);
  std::set<Coordinates> todo;
  for (auto cell : SudokuConstants<size>::cells) {
    const auto val = sudoku.cell_at(cell).get();
    if (val) {
      add_event(std::make_unique<exploration::CellIsSetInInput<size>>(cell, *val));
      todo.insert(cell);
    }
  }

  add_event(std::make_unique<exploration::InputsAreDone<size>>());

  try {
    propagate_and_explore(stack, std::move(todo), add_event);
  } catch (NeedsBacktracking&) {
    // Nothing to do, just return the unsolved Sudoku
  }

  for (auto cell : SudokuConstants<size>::cells) {
    if (stack.current().cell_at(cell).is_set()) {
      sudoku.cell_at(cell).set(stack.current().cell_at(cell).get());
    }
  }
  return sudoku;
}

template Sudoku<ValueCell, 4> solve_using_exploration(
  Sudoku<ValueCell, 4>,
  const std::function<void(std::unique_ptr<exploration::Event<4>>)>&);

template Sudoku<ValueCell, 9> solve_using_exploration(
  Sudoku<ValueCell, 9>,
  const std::function<void(std::unique_ptr<exploration::Event<9>>)>&);
