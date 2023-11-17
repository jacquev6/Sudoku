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


// This is the only way to modify the Stack (everywhere else, it's manipulated through const references).
// This design ensures that the events returned to the client can replicate exactly the evolution of the
// stack that happened during the exploration, because the stack actually evolved only through said events.
// (I think this is brilliant, but I *may* biased as I'm the author of this code).
template<unsigned size>
struct EventAdder {
  EventAdder(Stack<size>* stack_, const std::function<void(std::unique_ptr<exploration::Event<size>>)>& add_event_)
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
    const EventAdder<size>& add_event_,
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

  const EventAdder<size>& add_event;
  std::unique_ptr<exploration::Event<size>> out;
};


template<unsigned size>
bool propagate(
  const Stack<size>& stack,
  const std::set<Coordinates>& todo_,
  const EventAdder<size>& add_event
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
    const auto source_coords = todo.get();
    const auto& source_cell = stack.current().cell(source_coords);
    assert(source_cell.is_set());
    const unsigned value = source_cell.get();

    EventsPairGuard<size> guard(
      add_event,
      std::make_unique<exploration::PropagationStartsForCell<size>>(source_coords, value),
      std::make_unique<exploration::PropagationIsDoneForCell<size>>(source_coords, value));

    const auto [row, col] = source_coords;
    for (const auto& source_region : source_cell.regions()) {
      for (const auto& target_cell : source_region.cells()) {
        const auto target_coords = target_cell.coordinates();
        if (target_cell != source_cell) {
          if (target_cell.is_set()) {
            if (target_cell.get() == value) {
              return false;
            }
          } else {
            assert(target_cell.allowed_count() > 1);
            if (target_cell.is_allowed(value)) {
              add_event(std::make_unique<exploration::CellPropagates<size>>(source_coords, target_coords, value));

              if (target_cell.allowed_count() == 1) {
                for (unsigned value : SudokuConstants<size>::values) {
                  if (target_cell.is_allowed(value)) {
                    add_event(std::make_unique<exploration::CellIsDeducedFromSingleAllowedValue<size>>(
                      target_coords, value));
                    todo.add(target_coords);
                    break;
                  }
                }
              }

              for (const auto& target_region : target_cell.regions()) {
                unsigned count = 0;
                const typename AnnotatedSudoku<size>::Cell* single_cell;
                for (const auto& cell : target_region.cells()) {
                  if (cell.is_allowed(value)) {
                    ++count;
                    single_cell = &cell;
                  }
                }
                if (count == 1 && !single_cell->is_set()) {
                  const Coordinates single_coords = single_cell->coordinates();
                  add_event(std::make_unique<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>>(
                    single_coords, value, target_region.index()));
                  todo.add(single_coords);
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

  return true;
}


template<unsigned size>
Coordinates get_most_constrained_cell(const AnnotatedSudoku<size>& sudoku) {
  Coordinates best_coords;
  unsigned best_count = size + 1;

  for (const auto& cell : sudoku.cells()) {
    if (cell.is_set()) {
      continue;
    }
    unsigned count = cell.allowed_count();
    if (count < best_count) {
      best_coords = cell.coordinates();
      best_count = count;
    }
    if (best_count == 2) {
      break;
    }
  }

  return best_coords;
}


template<unsigned size>
bool propagate_and_explore(
  const Stack<size>&,
  const std::set<Coordinates>& todo,
  const EventAdder<size>&
);


template<unsigned size>
bool explore(const Stack<size>& stack, const EventAdder<size>& add_event) {
  assert(!stack.current().is_solved());

  const auto& cell = stack.current().cell(get_most_constrained_cell(stack.current()));
  const Coordinates coords = cell.coordinates();
  std::vector<unsigned> allowed_values;
  for (unsigned val : SudokuConstants<size>::values) {
    if (cell.is_allowed(val)) {
      allowed_values.push_back(val);
    }
  }

  EventsPairGuard<size> guard(
    add_event,
    std::make_unique<exploration::ExplorationStarts<size>>(coords, allowed_values),
    std::make_unique<exploration::ExplorationIsDone<size>>(coords));

  // @todo Artificially favor values without solution to demonstrate and visualize backtracking
  for (unsigned val : allowed_values) {
    auto hypothesis_ = std::make_unique<exploration::HypothesisIsMade<size>>(coords, val);
    exploration::HypothesisIsMade<size>* hypothesis = hypothesis_.get();
    add_event(std::move(hypothesis_));
    if (propagate_and_explore(stack, {coords}, add_event)) {
      add_event(std::make_unique<exploration::HypothesisIsAccepted<size>>(coords, val));
      return true;
    } else {
      add_event(std::make_unique<exploration::HypothesisIsRejected<size>>(coords, val));
    }
  }

  return false;
}


template<unsigned size>
bool propagate_and_explore(
  const Stack<size>& stack,
  const std::set<Coordinates>& todo,
  const EventAdder<size>& add_event
) {
  if (propagate(stack, todo, add_event)) {
    if (stack.current().is_solved()) {
      return true;
    } else {
      return explore(stack, add_event);
    }
  } else {
    return false;
  }
}


template<unsigned size>
Sudoku<ValueCell, size> solve_using_exploration(
  Sudoku<ValueCell, size> sudoku,
  const std::function<void(std::unique_ptr<exploration::Event<size>>)>& add_event_
) {
  Stack<size> stack;
  EventAdder<size> add_event(&stack, add_event_);
  std::set<Coordinates> todo;
  for (const auto& cell : sudoku.cells()) {
    const auto val = cell.get();
    if (val) {
      const Coordinates coords = cell.coordinates();
      add_event(std::make_unique<exploration::CellIsSetInInput<size>>(coords, *val));
      todo.insert(coords);
    }
  }

  add_event(std::make_unique<exploration::InputsAreDone<size>>());

  propagate_and_explore(stack, std::move(todo), add_event);

  for (const auto& cell : stack.current().cells()) {
    if (cell.is_set()) {
      sudoku.cell(cell.coordinates()).set(cell.get());
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
