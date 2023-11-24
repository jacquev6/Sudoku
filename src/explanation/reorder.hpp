// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_REORDER_HPP_
#define EXPLANATION_REORDER_HPP_

#include <vector>

#include "../exploration/events.hpp"


template<unsigned size>
class Reorder {
 public:
  explicit Reorder(const std::function<void(const exploration::Event<size>&)>& process_event_) :
    process_event(process_event_)
  {}

 public:
  void operator()(const exploration::CellIsSetInInput<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::InputsAreDone<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::PropagationStartsForSudoku<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::PropagationStartsForCell<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::CellPropagates<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
    pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }

  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
    pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }

  void operator()(const exploration::PropagationIsDoneForCell<size>& event) {
    process_event(event);
    flush_pending_events();
  }

  void operator()(const exploration::PropagationIsDoneForSudoku<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::ExplorationStarts<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::HypothesisIsMade<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::HypothesisIsRejected<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::SudokuIsSolved<size>& event) {
    flush_pending_events();
    process_event(event);
  }

  void operator()(const exploration::HypothesisIsAccepted<size>& event) {
    process_event(event);
  }

  void operator()(const exploration::ExplorationIsDone<size>& event) {
    process_event(event);
  }

 private:
  void flush_pending_events() {
    for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
      process_event(event);
    }
    for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
      process_event(event);
    }
    pending_cell_is_deduced_from_single_allowed_value_events.clear();
    pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }

 private:
  std::function<void(const exploration::Event<size>&)> process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size>>
    pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>>
    pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};

#endif  // EXPLANATION_REORDER_HPP_
