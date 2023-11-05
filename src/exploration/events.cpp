// Copyright 2023 Vincent Jacques

#include "events.hpp"

namespace exploration {

template<unsigned size>
void CellIsSetInInput<size>::apply(Stack<size>* stack) const {
  stack->current().set_input(cell, value);
}

template<unsigned size>
void InputsAreDone<size>::apply(Stack<size>* stack) const {
}

template<unsigned size>
void PropagationStartsForSudoku<size>::apply(Stack<size>* stack) const {
}

template<unsigned size>
void PropagationStartsForCell<size>::apply(Stack<size>* stack) const {
  assert(stack->current().is_set(cell));
  assert(stack->current().get(cell) == value);
  assert(!stack->current().is_propagated(cell));
}

template<unsigned size>
void CellPropagates<size>::apply(Stack<size>* stack) const {
  assert(stack->current().is_set(source_cell));
  assert(stack->current().get(source_cell) == value);
  assert(!stack->current().is_set(target_cell));
  assert(stack->current().is_allowed(target_cell, value));
  assert(!stack->current().is_propagated(source_cell));

  stack->current().forbid(target_cell, value);
}

template<unsigned size>
void CellIsDeducedFromSingleAllowedValue<size>::apply(Stack<size>* stack) const {
  assert(!stack->current().is_set(cell));
  assert(!stack->current().is_propagated(cell));

  stack->current().set_deduced(cell, value);
}

template<unsigned size>
void CellIsDeducedAsSinglePlaceForValueInRegion<size>::apply(Stack<size>* stack) const {
  assert(!stack->current().is_set(cell));
  assert(!stack->current().is_propagated(cell));

  stack->current().set_deduced(cell, value);
}

template<unsigned size>
void PropagationIsDoneForCell<size>::apply(Stack<size>* stack) const {
  assert(stack->current().is_set(cell));
  assert(stack->current().get(cell) == value);
  assert(!stack->current().is_propagated(cell));

  stack->current().set_propagated(cell);
}

template<unsigned size>
void PropagationIsDoneForSudoku<size>::apply(Stack<size>* stack) const {
}

template<unsigned size>
void ExplorationStarts<size>::apply(Stack<size>* stack) const {
}

template<unsigned size>
void HypothesisIsMade<size>::apply(Stack<size>* stack) const {
  assert(!stack->current().is_set(cell));
  assert(stack->current().is_allowed(cell, value));
  assert(!stack->current().is_propagated(cell));

  stack->push();
  stack->current().set_deduced(cell, value);
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
void HypothesisIsAccepted<size>::apply(Stack<size>* stack) const {
}

template<unsigned size>
void ExplorationIsDone<size>::apply(Stack<size>* stack) const {
}

template struct CellIsSetInInput<9>;
template struct InputsAreDone<9>;
template struct PropagationStartsForSudoku<9>;
template struct PropagationStartsForCell<9>;
template struct CellPropagates<9>;
template struct CellIsDeducedFromSingleAllowedValue<9>;
template struct CellIsDeducedAsSinglePlaceForValueInRegion<9>;
template struct PropagationIsDoneForCell<9>;
template struct PropagationIsDoneForSudoku<9>;
template struct ExplorationStarts<9>;
template struct HypothesisIsMade<9>;
template struct HypothesisIsRejected<9>;
template struct SudokuIsSolved<9>;
template struct HypothesisIsAccepted<9>;
template struct ExplorationIsDone<9>;

}  // namespace exploration
