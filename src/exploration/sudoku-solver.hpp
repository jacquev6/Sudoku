// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <deque>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "../puzzle/sudoku.hpp"
#include "events.hpp"


// This is the only way to modify the Stack (everywhere else, it's manipulated through const references).
// This design ensures that the events returned to the client can replicate exactly the evolution of the
// stack that happened during the exploration, because the stack actually evolved only through said events.
// (I think this is brilliant, but I *may* biased as I'm the author of this code).
template<unsigned size>
struct EventAdder {
  EventAdder(Stack<size>* stack_, const std::function<void(exploration::Event<size>&&)>& add_event_)
    : stack(stack_), add_event(add_event_) {}

  void operator()(exploration::Event<size>&& event) const {
    std::visit([this](const auto& e) { e.apply(stack); }, event);
    add_event(std::move(event));
  }

 private:
  Stack<size>* stack;
  const std::function<void(exploration::Event<size>&&)>& add_event;
};


// Make sure a closing event is added, however the scope is exited
template<unsigned size>
struct EventsPairGuard {
  EventsPairGuard(
    const EventAdder<size>& add_event_,
    exploration::Event<size>&& in,
    exploration::Event<size>&& out_
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
  exploration::Event<size> out;
};




template<unsigned size>
bool propagate(
  const Stack<size>& stack,
  std::deque<Coordinates> todo,
  const EventAdder<size>& add_event
) {
  for (const auto& coords : todo) {
    assert(std::count(todo.begin(), todo.end(), coords) == 1);
  }

  EventsPairGuard<size> guard(
    add_event,
    exploration::PropagationStartsForSudoku<size>(),
    exploration::PropagationIsDoneForSudoku<size>());

  while (!todo.empty()) {
    const auto source_coords = todo.front();
    todo.pop_front();
    const auto& source_cell = stack.current().cell(source_coords);
    assert(source_cell.is_set());
    const unsigned value = source_cell.get();

    EventsPairGuard<size> guard(
      add_event,
      exploration::PropagationStartsForCell<size>(source_coords, value),
      exploration::PropagationIsDoneForCell<size>(source_coords, value));

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
              add_event(exploration::CellPropagates<size>(source_coords, target_coords, value));

              if (target_cell.allowed_count() == 1) {
                for (unsigned value : SudokuConstants<size>::values) {
                  if (target_cell.is_allowed(value)) {
                    add_event(exploration::CellIsDeducedFromSingleAllowedValue<size>(
                      target_coords, value));
                    assert(std::count(todo.begin(), todo.end(), target_coords) == 0);
                    todo.push_back(target_coords);
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
                  add_event(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>(
                    single_coords, value, target_region.index()));
                  assert(std::count(todo.begin(), todo.end(), single_coords) == 0);
                  todo.push_back(single_coords);
                }
              }

              // 'AnnotatedSudoku::is_solved' is currently O(AnnotatedSudoku::size^2),
              // which we could optimize easily with additional book-keeping,
              // but the *whole* solving algorithm still executes in less than 100ms for size 9,
              // so it's not worth it yet.
              if (stack.current().is_solved()) {
                add_event(exploration::SudokuIsSolved<size>());
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
  const std::deque<Coordinates>& todo,
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
    exploration::ExplorationStarts<size>(coords, allowed_values),
    exploration::ExplorationIsDone<size>(coords));

  // @todo Artificially favor values without solution to demonstrate and visualize backtracking
  for (unsigned val : allowed_values) {
    add_event(exploration::HypothesisIsMade<size>(coords, val));
    if (propagate_and_explore(stack, {coords}, add_event)) {
      add_event(exploration::HypothesisIsAccepted<size>(coords, val));
      return true;
    } else {
      add_event(exploration::HypothesisIsRejected<size>(coords, val));
    }
  }

  return false;
}


template<unsigned size>
bool propagate_and_explore(
  const Stack<size>& stack,
  const std::deque<Coordinates>& todo,
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
  const std::function<void(exploration::Event<size>&&)>& add_event_ = [](exploration::Event<size>&&) {}
) {
  Stack<size> stack;
  EventAdder<size> add_event(&stack, add_event_);
  std::deque<Coordinates> todo;
  for (const auto& cell : sudoku.cells()) {
    const auto val = cell.get();
    if (val) {
      const Coordinates coords = cell.coordinates();
      add_event(exploration::CellIsSetInInput<size>(coords, *val));
      todo.push_back(coords);
    }
  }

  add_event(exploration::InputsAreDone<size>());

  propagate_and_explore(stack, std::move(todo), add_event);

  for (const auto& cell : stack.current().cells()) {
    if (cell.is_set()) {
      sudoku.cell(cell.coordinates()).set(cell.get());
    }
  }
  return sudoku;
}

#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
