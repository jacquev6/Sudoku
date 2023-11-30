// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <vector>

#include "../puzzle/sudoku.hpp"


// Name events like affirmative sentences in present tense

template<unsigned size>
struct CellIsSetInInput {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct InputsAreDone {};

template<unsigned size>
struct PropagationStartsForSudoku {};

template<unsigned size>
struct PropagationStartsForCell {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct CellPropagates {
  Coordinates source_cell;
  Coordinates target_cell;
  unsigned value;
};

template<unsigned size>
struct CellIsDeducedFromSingleAllowedValue {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct CellIsDeducedAsSinglePlaceForValueInRegion {
  Coordinates cell;
  unsigned value;
  unsigned region;
};

template<unsigned size>
struct PropagationIsDoneForCell {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct PropagationIsDoneForSudoku {};

template<unsigned size>
struct ExplorationStarts {
  Coordinates cell;
  std::vector<unsigned> allowed_values;
};

template<unsigned size>
struct HypothesisIsMade {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct HypothesisIsRejected {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct SudokuIsSolved {};

template<unsigned size>
struct HypothesisIsAccepted {
  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct ExplorationIsDone {
  Coordinates cell;
};

#endif  // EXPLORATION_EVENTS_HPP_
