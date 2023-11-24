// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <variant>
#include <vector>

#include "annotations.hpp"


namespace exploration {

// Name events like affirmative sentences in present tense

template<unsigned size>
struct CellIsSetInInput {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct InputsAreDone {
  void apply(Stack<size>*) const;
};

template<unsigned size>
struct PropagationStartsForSudoku {
  void apply(Stack<size>*) const;
};

template<unsigned size>
struct PropagationStartsForCell {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct CellPropagates {
  void apply(Stack<size>*) const;

  Coordinates source_cell;
  Coordinates target_cell;
  unsigned value;
};

template<unsigned size>
struct CellIsDeducedFromSingleAllowedValue {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct CellIsDeducedAsSinglePlaceForValueInRegion {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
  unsigned region;
};

template<unsigned size>
struct PropagationIsDoneForCell {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct PropagationIsDoneForSudoku {
  void apply(Stack<size>*) const;
};

template<unsigned size>
struct ExplorationStarts {
  void apply(Stack<size>*) const;

  Coordinates cell;
  std::vector<unsigned> allowed_values;
};

template<unsigned size>
struct HypothesisIsMade {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct HypothesisIsRejected {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct SudokuIsSolved {
  void apply(Stack<size>*) const;
};

template<unsigned size>
struct HypothesisIsAccepted {
  void apply(Stack<size>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct ExplorationIsDone {
  void apply(Stack<size>*) const;

  Coordinates cell;
};

template<unsigned size>
using Event = std::variant<
  CellIsSetInInput<size>,
  InputsAreDone<size>,
  PropagationStartsForSudoku<size>,
  PropagationStartsForCell<size>,
  CellPropagates<size>,
  CellIsDeducedFromSingleAllowedValue<size>,
  CellIsDeducedAsSinglePlaceForValueInRegion<size>,
  PropagationIsDoneForCell<size>,
  PropagationIsDoneForSudoku<size>,
  ExplorationStarts<size>,
  HypothesisIsMade<size>,
  HypothesisIsRejected<size>,
  SudokuIsSolved<size>,
  HypothesisIsAccepted<size>,
  ExplorationIsDone<size>>;

}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
