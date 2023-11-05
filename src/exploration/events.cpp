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

template struct CellIsSetInInput<4>;
template struct CellIsSetInInput<9>;
template struct CellIsSetInInput<16>;
template struct CellIsSetInInput<25>;
template struct CellIsSetInInput<36>;

template struct InputsAreDone<4>;
template struct InputsAreDone<9>;
template struct InputsAreDone<16>;
template struct InputsAreDone<25>;
template struct InputsAreDone<36>;

template struct PropagationStartsForSudoku<4>;
template struct PropagationStartsForSudoku<9>;
template struct PropagationStartsForSudoku<16>;
template struct PropagationStartsForSudoku<25>;
template struct PropagationStartsForSudoku<36>;

template struct PropagationStartsForCell<4>;
template struct PropagationStartsForCell<9>;
template struct PropagationStartsForCell<16>;
template struct PropagationStartsForCell<25>;
template struct PropagationStartsForCell<36>;

template struct CellPropagates<4>;
template struct CellPropagates<9>;
template struct CellPropagates<16>;
template struct CellPropagates<25>;
template struct CellPropagates<36>;

template struct CellIsDeducedFromSingleAllowedValue<4>;
template struct CellIsDeducedFromSingleAllowedValue<9>;
template struct CellIsDeducedFromSingleAllowedValue<16>;
template struct CellIsDeducedFromSingleAllowedValue<25>;
template struct CellIsDeducedFromSingleAllowedValue<36>;

template struct CellIsDeducedAsSinglePlaceForValueInRegion<4>;
template struct CellIsDeducedAsSinglePlaceForValueInRegion<9>;
template struct CellIsDeducedAsSinglePlaceForValueInRegion<16>;
template struct CellIsDeducedAsSinglePlaceForValueInRegion<25>;
template struct CellIsDeducedAsSinglePlaceForValueInRegion<36>;

template struct PropagationIsDoneForCell<4>;
template struct PropagationIsDoneForCell<9>;
template struct PropagationIsDoneForCell<16>;
template struct PropagationIsDoneForCell<25>;
template struct PropagationIsDoneForCell<36>;

template struct PropagationIsDoneForSudoku<4>;
template struct PropagationIsDoneForSudoku<9>;
template struct PropagationIsDoneForSudoku<16>;
template struct PropagationIsDoneForSudoku<25>;
template struct PropagationIsDoneForSudoku<36>;

template struct ExplorationStarts<4>;
template struct ExplorationStarts<9>;
template struct ExplorationStarts<16>;
template struct ExplorationStarts<25>;
template struct ExplorationStarts<36>;

template struct HypothesisIsMade<4>;
template struct HypothesisIsMade<9>;
template struct HypothesisIsMade<16>;
template struct HypothesisIsMade<25>;
template struct HypothesisIsMade<36>;

template struct HypothesisIsRejected<4>;
template struct HypothesisIsRejected<9>;
template struct HypothesisIsRejected<16>;
template struct HypothesisIsRejected<25>;
template struct HypothesisIsRejected<36>;

template struct SudokuIsSolved<4>;
template struct SudokuIsSolved<9>;
template struct SudokuIsSolved<16>;
template struct SudokuIsSolved<25>;
template struct SudokuIsSolved<36>;

template struct HypothesisIsAccepted<4>;
template struct HypothesisIsAccepted<9>;
template struct HypothesisIsAccepted<16>;
template struct HypothesisIsAccepted<25>;
template struct HypothesisIsAccepted<36>;

template struct ExplorationIsDone<4>;
template struct ExplorationIsDone<9>;
template struct ExplorationIsDone<16>;
template struct ExplorationIsDone<25>;
template struct ExplorationIsDone<36>;


}  // namespace exploration
