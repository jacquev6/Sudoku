// Copyright 2023 Vincent Jacques

#include "reorder.hpp"


template<unsigned size>
void Reorder<size>::visit(const exploration::CellIsSetInInput<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::InputsAreDone<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::PropagationStartsForSudoku<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::PropagationStartsForCell<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::CellPropagates<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::PropagationIsDoneForCell<size>& event) {
  event.accept(visitor);
  flush_pending_events();
}

template<unsigned size>
void Reorder<size>::visit(const exploration::PropagationIsDoneForSudoku<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::ExplorationStarts<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::HypothesisIsMade<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::HypothesisIsRejected<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::SudokuIsSolved<size>& event) {
  flush_pending_events();
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::HypothesisIsAccepted<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::visit(const exploration::ExplorationIsDone<size>& event) {
  event.accept(visitor);
}

template<unsigned size>
void Reorder<size>::flush_pending_events() {
  for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
    event.accept(visitor);
  }
  for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
    event.accept(visitor);
  }
  pending_cell_is_deduced_from_single_allowed_value_events.clear();
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
}

template class Reorder<4>;
template class Reorder<9>;
