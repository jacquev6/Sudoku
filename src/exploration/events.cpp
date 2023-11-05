// Copyright 2023 Vincent Jacques

#include "events.hpp"

namespace exploration {

void CellIsSetInInput::apply(Stack* stack) const {
  stack->current().set_input(cell, value);
}

void InputsAreDone::apply(Stack* stack) const {
}

void PropagationStartsForSudoku::apply(Stack* stack) const {
}

void PropagationStartsForCell::apply(Stack* stack) const {
}

void CellPropagates::apply(Stack* stack) const {
  assert(stack->current().is_set(source_cell));
  assert(stack->current().get(source_cell) == value);
  assert(!stack->current().is_set(target_cell));
  assert(stack->current().is_allowed(target_cell, value));
  assert(!stack->current().is_propagated(source_cell));

  stack->current().forbid(target_cell, value);
}

void CellIsDeducedFromSingleAllowedValue::apply(Stack* stack) const {
  assert(!stack->current().is_set(cell));
  assert(!stack->current().is_propagated(cell));

  stack->current().set_deduced(cell, value);
}

void CellIsDeducedAsSinglePlaceForValueInRegion::apply(Stack* stack) const {
  assert(!stack->current().is_set(cell));
  assert(!stack->current().is_propagated(cell));

  stack->current().set_deduced(cell, value);
}

void PropagationIsDoneForCell::apply(Stack* stack) const {
  assert(stack->current().is_set(cell));
  assert(stack->current().get(cell) == value);
  assert(!stack->current().is_propagated(cell));

  stack->current().set_propagated(cell);
}

void PropagationIsDoneForSudoku::apply(Stack* stack) const {
}

void ExplorationStarts::apply(Stack* stack) const {
}

void HypothesisIsMade::apply(Stack* stack) const {
  assert(!stack->current().is_set(cell));
  assert(stack->current().is_allowed(cell, value));
  assert(!stack->current().is_propagated(cell));

  stack->push();
  stack->current().set_deduced(cell, value);
}

void HypothesisIsRejected::apply(Stack* stack) const {
  stack->pop();
}

void SudokuIsSolved::apply(Stack* stack) const {
  assert(stack->current().is_solved());
}

void HypothesisIsAccepted::apply(Stack* stack) const {
}

void ExplorationIsDone::apply(Stack* stack) const {
}

}  // namespace exploration
