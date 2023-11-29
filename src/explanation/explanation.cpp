// Copyright 2023 Vincent Jacques

#include "explanation.hpp"

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::CellIsSetInInput<size>& event) {
  explanation.inputs.cell(event.cell).set(event.value);
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::InputsAreDone<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationStartsForSudoku<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationStartsForCell<size>& event) {
  assert(!stack.empty());
  assert(stack.back().propagations != nullptr);
  stack.back().propagations->push_back({event.cell, event.value});
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::CellPropagates<size>& event) {
  assert(!stack.empty());
  assert(stack.back().propagations != nullptr);
  assert(!stack.back().propagations->empty());
  assert(stack.back().propagations->back().source == event.source_cell);
  assert(stack.back().propagations->back().value == event.value);
  stack.back().propagations->back().targets.push_back({event.target_cell});
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  stack.back().propagations->back().targets.back().single_value_deductions.push_back({event.cell, event.value});
  stack.back().sudoku_is_solved =
    &stack.back().propagations->back().targets.back().single_value_deductions.back().solved;
}

template<unsigned size>
void Explanation<size>::Builder::operator()(
  const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event
) {
  stack.back().propagations->back().targets.back().single_place_deductions.push_back(
    {event.region, event.cell, event.value});
  stack.back().sudoku_is_solved =
    &stack.back().propagations->back().targets.back().single_place_deductions.back().solved;
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationIsDoneForCell<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationIsDoneForSudoku<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::ExplorationStarts<size>& event) {
  assert(stack.back().exploration != nullptr);
  assert(!stack.back().exploration->has_value());
  stack.back().exploration->emplace(Exploration{event.cell, event.allowed_values, {}});
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::HypothesisIsMade<size>& event) {
  assert(stack.back().exploration != nullptr);
  assert(stack.back().exploration->has_value());
  Exploration& exploration = **stack.back().exploration;
  Hypothesis& hypothesis = exploration.explored_hypotheses.emplace_back(Hypothesis{event.value});
  stack.push_back({&hypothesis.propagations, &hypothesis.exploration, &hypothesis });
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::HypothesisIsRejected<size>&) {
  assert(stack.back().hypothesis != nullptr);
  stack.back().hypothesis->successful = false;
  stack.pop_back();
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::SudokuIsSolved<size>&) {
  *stack.back().sudoku_is_solved = true;
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::HypothesisIsAccepted<size>&) {
  assert(stack.back().hypothesis != nullptr);
  stack.back().hypothesis->successful = true;
  stack.pop_back();
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::ExplorationIsDone<size>&) {
}

template class Explanation<4>;
template class Explanation<9>;
