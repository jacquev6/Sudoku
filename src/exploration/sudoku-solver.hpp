// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <array>
#include <bitset>
#include <cassert>
#include <deque>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "../puzzle/sudoku.hpp"
#include "events.hpp"


template<unsigned size>
class ExplorableCell {
 public:
  ExplorableCell() :
    allowed_values(),
    set_value()
  {  // NOLINT(whitespace/braces)
    allowed_values.set();
    assert_invariants();
  }

  ExplorableCell(const ExplorableCell&) = default;
  ExplorableCell& operator=(const ExplorableCell&) = default;
  ExplorableCell(ExplorableCell&&) = default;
  ExplorableCell& operator=(ExplorableCell&&) = default;

 public:
  bool is_set() const {
    assert_invariants();
    return set_value.has_value();
  }

  unsigned get() const {
    assert_invariants();
    assert(is_set());

    return set_value.value();
  }

  bool is_allowed(const unsigned value) const {
    assert_invariants();
    assert(value < size);

    return allowed_values.test(value);
  }

  unsigned allowed_count() const {
    assert_invariants();

    return allowed_values.count();
  }

  unsigned get_single_allowed_value() const {
    assert_invariants();
    assert(allowed_count() == 1);

    for (unsigned value : SudokuConstants<size>::values) {
      if (is_allowed(value)) {
        return value;
      }
    }
    __builtin_unreachable();
  }

  void set(const unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(value));
    assert(!is_set());

    allowed_values.reset();
    allowed_values.set(value);
    set_value = value;

    assert_invariants();
  }

  void forbid(const unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(value));

    allowed_values.reset(value);

    assert_invariants();
  }

 private:
  void assert_invariants() const {
    // At least one value is always allowed
    assert(allowed_values.any());

    // 'set_value' forces 'allowed_values'
    if (set_value.has_value()) {
      assert(allowed_values.count() == 1);
      assert(allowed_values.test(set_value.value()));
    }
  }

 private:
  std::bitset<size> allowed_values;
  std::optional<unsigned> set_value;
};

template<unsigned size>
class Sudoku<ExplorableCell<size>, size> : public SudokuBase<ExplorableCell<size>, size> {
 public:
  bool is_solved() const {
    for (const auto& cell : this->cells()) {
      if (!cell.is_set()) {
        return false;
      }
    }
    return true;
  }
};

// Make sure a closing event is added, however the scope is exited
template<typename EventSink, typename EventIn, typename EventOut>
struct EventsPairGuard {
  EventsPairGuard(
    EventSink& sink_event_,  // NOLINT(runtime/references)
    const EventIn& in,
    const EventOut& out_
  ) :  // NOLINT(whitespace/parens)
    sink_event(sink_event_),
    out(out_)
  {  // NOLINT(whitespace/braces)
    sink_event(in);
  }

  ~EventsPairGuard() {
    sink_event(out);
  }

  EventSink& sink_event;
  EventOut out;
};


template<unsigned size, typename EventSink>
class ExplorationSolver {
 public:
  ExplorationSolver(
    const Sudoku<ValueCell, size>& input_sudoku_,
    EventSink& sink_event_
  ) :  // NOLINT(whitespace/parens)
    input_sudoku(input_sudoku_),
    sink_event(sink_event_)
  {}

 public:
  std::optional<Sudoku<ValueCell, size>> solve() {
    Sudoku<ExplorableCell<size>, size> sudoku;
    std::deque<Coordinates> to_propagate;
    for (const auto& cell : input_sudoku.cells()) {
      const auto value = cell.get();
      if (value) {
        const Coordinates coords = cell.coordinates();
        sink_event(CellIsSetInInput<size>(coords, *value));
        sudoku.cell(coords).set(*value);
        to_propagate.push_back(coords);
      }
    }

    sink_event(InputsAreDone<size>());

    for (const auto& cell : input_sudoku.cells()) {
      if (cell.get()) {
        deduce_after_set(&sudoku, cell.coordinates(), &to_propagate);
      }
    }

    if (sudoku.is_solved()) {
      sink_event(SudokuIsSolved<size>());
    }

    switch (propagate_and_explore(&sudoku, std::move(to_propagate))) {
      case ExplorationResult::solved: {
        std::optional<Sudoku<ValueCell, size>> solved(std::in_place);
        for (const auto& cell : sudoku.cells()) {
          if (cell.is_set()) {
            solved->cell(cell.coordinates()).set(cell.get());
          }
        }
        return solved;
      }
      case ExplorationResult::unsolvable:
        return std::nullopt;
    }
    __builtin_unreachable();
  }

 private:
  enum class PropagationResult { solved, unsolvable, requires_exploration };

  PropagationResult propagate(Sudoku<ExplorableCell<size>, size>* sudoku, std::deque<Coordinates>&& to_propagate) {
    for (const auto& coords : to_propagate) {
      assert(std::count(to_propagate.begin(), to_propagate.end(), coords) == 1);
    }

    EventsPairGuard guard(
      sink_event,
      PropagationStartsForSudoku<size>(),
      PropagationIsDoneForSudoku<size>());

    while (!to_propagate.empty()) {
      const auto source_coords = to_propagate.front();
      to_propagate.pop_front();
      auto& source_cell = sudoku->cell(source_coords);
      assert(source_cell.is_set());
      const unsigned source_value = source_cell.get();

      EventsPairGuard guard(
        sink_event,
        PropagationStartsForCell<size>(source_coords, source_value),
        PropagationIsDoneForCell<size>(source_coords, source_value));

      for (auto& source_region : source_cell.regions()) {
        for (auto& target_cell : source_region.cells()) {
          const auto target_coords = target_cell.coordinates();
          if (target_cell != source_cell) {
            if (target_cell.is_set()) {
              if (target_cell.get() == source_value) {
                return PropagationResult::unsolvable;
              }
            } else {
              assert(target_cell.allowed_count() > 1);
              if (target_cell.is_allowed(source_value)) {
                sink_event(CellPropagates<size>(source_coords, target_coords, source_value));
                target_cell.forbid(source_value);

                if (target_cell.allowed_count() == 1) {
                  const unsigned set_value = target_cell.get_single_allowed_value();
                  sink_event(CellIsDeducedFromSingleAllowedValue<size>(target_coords, set_value));
                  target_cell.set(set_value);

                  assert(std::count(to_propagate.begin(), to_propagate.end(), target_coords) == 0);
                  to_propagate.push_back(target_coords);

                  deduce_after_set(sudoku, target_coords, &to_propagate);
                } else {
                  deduce_after_forbid(sudoku, target_coords, source_value, &to_propagate);
                }

                #ifndef NDEBUG
                // All single-value deductions have been applied
                for (const auto& cell : sudoku->cells()) {
                  assert(cell.is_set() || cell.allowed_count() > 1);
                }
                // All single-place deductions have been applied
                for (const auto& region : sudoku->regions()) {
                  for (const unsigned value : SudokuConstants<size>::values) {
                    unsigned count = 0;
                    const typename Sudoku<ExplorableCell<size>, size>::Cell* single_cell = nullptr;
                    for (const auto& cell : region.cells()) {
                      if (cell.is_allowed(value)) {
                        ++count;
                        single_cell = &cell;
                      }
                    }
                    assert(!(count == 1 && !single_cell->is_set()));
                  }
                }
                #endif

                // 'is_solved' is currently O(size^2),
                // which we could optimize easily with additional book-keeping,
                // but the *whole* solving algorithm still executes in less than 100ms for size 9,
                // so it's not worth it yet.
                if (sudoku->is_solved()) {
                  sink_event(SudokuIsSolved<size>());
                  // @todo return solved;
                }
              } else {
                // Nothing to do: this is old news
              }
            }
          }
        }
      }
    }

    // @todo Remove the test, always return requires_exploration
    if (sudoku->is_solved()) {
      return PropagationResult::solved;
    } else {
      return PropagationResult::requires_exploration;
    }
  }

  void deduce_after_set(
    Sudoku<ExplorableCell<size>, size>* sudoku,
    const Coordinates& coords,
    std::deque<Coordinates>* to_propagate
  ) {
    auto& set_cell = sudoku->cell(coords);
    assert(set_cell.is_set());

    // @todo Iterate on fewer values: only the ones that were allowed before the cell was set
    for (unsigned value : SudokuConstants<size>::values) {
      if (value != set_cell.get()) {
        deduce_after_forbid(sudoku, coords, value, to_propagate);
      }
    }
  }

  void deduce_after_forbid(
    Sudoku<ExplorableCell<size>, size>* sudoku,
    const Coordinates& coords,
    const unsigned value,
    std::deque<Coordinates>* to_propagate
  ) {
    for (auto& region : sudoku->cell(coords).regions()) {
      unsigned count = 0;
      typename Sudoku<ExplorableCell<size>, size>::Cell* single_cell = nullptr;
      for (auto& cell : region.cells()) {
        if (cell.is_allowed(value)) {
          ++count;
          single_cell = &cell;
        }
      }
      if (count == 1 && !single_cell->is_set()) {
        const Coordinates single_coords = single_cell->coordinates();
        sink_event(CellIsDeducedAsSinglePlaceForValueInRegion<size>(
          single_coords, value, region.index()));
        single_cell->set(value);

        assert(std::count(to_propagate->begin(), to_propagate->end(), single_coords) == 0);
        to_propagate->push_back(single_coords);

        deduce_after_set(sudoku, single_coords, to_propagate);
      }
    }
  }

  Coordinates get_most_constrained_cell(Sudoku<ExplorableCell<size>, size>* sudoku) {
    Coordinates best_coords;
    unsigned best_count = size + 1;

    for (const auto& cell : sudoku->cells()) {
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

  enum class ExplorationResult { solved, unsolvable };

  ExplorationResult explore(Sudoku<ExplorableCell<size>, size>* sudoku) {
    assert(!sudoku->is_solved());

    const Coordinates coords = get_most_constrained_cell(sudoku);
    const auto& cell = sudoku->cell(coords);
    std::vector<unsigned> allowed_values;
    for (unsigned value : SudokuConstants<size>::values) {
      if (cell.is_allowed(value)) {
        allowed_values.push_back(value);
      }
    }

    EventsPairGuard guard(
      sink_event,
      ExplorationStarts<size>(coords, allowed_values),
      ExplorationIsDone<size>(coords));

    for (unsigned value : allowed_values) {
      sink_event(HypothesisIsMade<size>(coords, value));
      Sudoku<ExplorableCell<size>, size> copied_sudoku(*sudoku);
      copied_sudoku.cell(coords).set(value);

      std::deque<Coordinates> to_propagate(1, {coords});
      deduce_after_set(&copied_sudoku, coords, &to_propagate);

      if (copied_sudoku.is_solved()) {
        sink_event(SudokuIsSolved<size>());
      }

      switch (propagate_and_explore(&copied_sudoku, std::move(to_propagate))) {
        case ExplorationResult::solved:
          sink_event(HypothesisIsAccepted<size>(coords, value));
          *sudoku = copied_sudoku;
          return ExplorationResult::solved;
        case ExplorationResult::unsolvable:
          sink_event(HypothesisIsRejected<size>(coords, value));
          break;
      }
    }

    return ExplorationResult::unsolvable;
  }

  ExplorationResult propagate_and_explore(Sudoku<ExplorableCell<size>, size>* sudoku, std::deque<Coordinates>&& todo) {
    switch (propagate(sudoku, std::move(todo))) {
      case PropagationResult::solved:
        return ExplorationResult::solved;
      case PropagationResult::unsolvable:
        return ExplorationResult::unsolvable;
      case PropagationResult::requires_exploration:
        return explore(sudoku);
    }
    __builtin_unreachable();
  }

 private:
  Sudoku<ValueCell, size> input_sudoku;
  EventSink& sink_event;
};

template<unsigned size, typename EventSink>
std::optional<Sudoku<ValueCell, size>> solve_using_exploration(
  Sudoku<ValueCell, size> sudoku,
  EventSink& sink_event
) {
  return ExplorationSolver(sudoku, sink_event).solve();
}

template<unsigned size, typename EventSink>
std::optional<Sudoku<ValueCell, size>> solve_using_exploration(
  Sudoku<ValueCell, size> sudoku,
  const EventSink& sink_event
) {
  return ExplorationSolver(sudoku, sink_event).solve();
}

template<unsigned size>
std::optional<Sudoku<ValueCell, size>> solve_using_exploration(Sudoku<ValueCell, size> sudoku) {
  return solve_using_exploration(sudoku, [](const auto&) {});
}

#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
