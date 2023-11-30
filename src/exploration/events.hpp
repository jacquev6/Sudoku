// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <vector>

#include "annotations.hpp"


// Name events like affirmative sentences in present tense

template<unsigned size>
struct CellIsSetInInput {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct InputsAreDone {
  void apply(Stack<ExplorableSudoku<size>>*) const;
};

template<unsigned size>
struct PropagationStartsForSudoku {
  void apply(Stack<ExplorableSudoku<size>>*) const;
};

template<unsigned size>
struct PropagationStartsForCell {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct CellPropagates {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates source_cell;
  Coordinates target_cell;
  unsigned value;
};

template<unsigned size>
struct CellIsDeducedFromSingleAllowedValue {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct CellIsDeducedAsSinglePlaceForValueInRegion {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
  unsigned region;
};

template<unsigned size>
struct PropagationIsDoneForCell {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct PropagationIsDoneForSudoku {
  void apply(Stack<ExplorableSudoku<size>>*) const;
};

template<unsigned size>
struct ExplorationStarts {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  std::vector<unsigned> allowed_values;
};

template<unsigned size>
struct HypothesisIsMade {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct HypothesisIsRejected {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct SudokuIsSolved {
  void apply(Stack<ExplorableSudoku<size>>*) const;
};

template<unsigned size>
struct HypothesisIsAccepted {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
  unsigned value;
};

template<unsigned size>
struct ExplorationIsDone {
  void apply(Stack<ExplorableSudoku<size>>*) const;

  Coordinates cell;
};

#endif  // EXPLORATION_EVENTS_HPP_
