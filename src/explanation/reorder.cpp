// Copyright 2023 Vincent Jacques

#include "reorder.hpp"


template<unsigned size>
void Reorder<size>::operator()(const exploration::CellIsSetInInput<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::InputsAreDone<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::PropagationStartsForSudoku<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::PropagationStartsForCell<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::CellPropagates<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::PropagationIsDoneForCell<size>& event) {
  process_event(event);
  flush_pending_events();
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::PropagationIsDoneForSudoku<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::ExplorationStarts<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::HypothesisIsMade<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::HypothesisIsRejected<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::SudokuIsSolved<size>& event) {
  flush_pending_events();
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::HypothesisIsAccepted<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::operator()(const exploration::ExplorationIsDone<size>& event) {
  process_event(event);
}

template<unsigned size>
void Reorder<size>::flush_pending_events() {
  for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
    process_event(event);
  }
  for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
    process_event(event);
  }
  pending_cell_is_deduced_from_single_allowed_value_events.clear();
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
}

template class Reorder<4>;
template class Reorder<9>;
