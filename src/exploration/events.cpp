// Copyright 2023 Vincent Jacques

#include "events.hpp"


template<unsigned size>
void CellIsSetInInput<size>::apply(Stack<size>* stack) const {
  stack->current().cell(cell).set_input(value);
}

template<unsigned size>
void InputsAreDone<size>::apply(Stack<size>*) const {}

template<unsigned size>
void PropagationStartsForSudoku<size>::apply(Stack<size>*) const {}

template<unsigned size>
void PropagationStartsForCell<size>::apply(Stack<size>* stack) const {
  assert(stack->current().cell(cell).is_set());
  assert(stack->current().cell(cell).get() == value);
  assert(!stack->current().cell(cell).is_propagated());
}

template<unsigned size>
void CellPropagates<size>::apply(Stack<size>* stack) const {
  assert(stack->current().cell(source_cell).is_set());
  assert(stack->current().cell(source_cell).get() == value);
  assert(!stack->current().cell(target_cell).is_set());
  assert(stack->current().cell(target_cell).is_allowed(value));
  assert(!stack->current().cell(source_cell).is_propagated());

  stack->current().cell(target_cell).forbid(value);
}

template<unsigned size>
void CellIsDeducedFromSingleAllowedValue<size>::apply(Stack<size>* stack) const {
  assert(!stack->current().cell(cell).is_set());
  assert(!stack->current().cell(cell).is_propagated());

  stack->current().cell(cell).set_deduced(value);
}

template<unsigned size>
void CellIsDeducedAsSinglePlaceForValueInRegion<size>::apply(Stack<size>* stack) const {
  assert(!stack->current().cell(cell).is_set());
  assert(!stack->current().cell(cell).is_propagated());

  stack->current().cell(cell).set_deduced(value);
}

template<unsigned size>
void PropagationIsDoneForCell<size>::apply(Stack<size>* stack) const {
  assert(stack->current().cell(cell).is_set());
  assert(stack->current().cell(cell).get() == value);
  assert(!stack->current().cell(cell).is_propagated());

  stack->current().cell(cell).set_propagated();
}

template<unsigned size>
void PropagationIsDoneForSudoku<size>::apply(Stack<size>*) const {}

template<unsigned size>
void ExplorationStarts<size>::apply(Stack<size>*) const {}

template<unsigned size>
void HypothesisIsMade<size>::apply(Stack<size>* stack) const {
  assert(!stack->current().cell(cell).is_set());
  assert(stack->current().cell(cell).is_allowed(value));
  assert(!stack->current().cell(cell).is_propagated());

  stack->push();
  stack->current().cell(cell).set_hypothesis(value);
}

template<unsigned size>
void HypothesisIsRejected<size>::apply(Stack<size>* stack) const {
  stack->pop();
}

template<unsigned size>
void SudokuIsSolved<size>::apply(Stack<size>* stack) const {
  assert(stack->current().is_solved());
}

template<unsigned size>
void HypothesisIsAccepted<size>::apply(Stack<size>*) const {}

template<unsigned size>
void ExplorationIsDone<size>::apply(Stack<size>*) const {}

template struct CellIsSetInInput<4>;
template struct CellIsSetInInput<9>;

template struct InputsAreDone<4>;
template struct InputsAreDone<9>;

template struct PropagationStartsForSudoku<4>;
template struct PropagationStartsForSudoku<9>;

template struct PropagationStartsForCell<4>;
template struct PropagationStartsForCell<9>;

template struct CellPropagates<4>;
template struct CellPropagates<9>;

template struct CellIsDeducedFromSingleAllowedValue<4>;
template struct CellIsDeducedFromSingleAllowedValue<9>;

template struct CellIsDeducedAsSinglePlaceForValueInRegion<4>;
template struct CellIsDeducedAsSinglePlaceForValueInRegion<9>;

template struct PropagationIsDoneForCell<4>;
template struct PropagationIsDoneForCell<9>;

template struct PropagationIsDoneForSudoku<4>;
template struct PropagationIsDoneForSudoku<9>;

template struct ExplorationStarts<4>;
template struct ExplorationStarts<9>;

template struct HypothesisIsMade<4>;
template struct HypothesisIsMade<9>;

template struct HypothesisIsRejected<4>;
template struct HypothesisIsRejected<9>;

template struct SudokuIsSolved<4>;
template struct SudokuIsSolved<9>;

template struct HypothesisIsAccepted<4>;
template struct HypothesisIsAccepted<9>;

template struct ExplorationIsDone<4>;
template struct ExplorationIsDone<9>;
