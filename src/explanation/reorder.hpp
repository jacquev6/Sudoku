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
  void operator()(const exploration::CellIsSetInInput<size>&);
  void operator()(const exploration::InputsAreDone<size>&);
  void operator()(const exploration::PropagationStartsForSudoku<size>&);
  void operator()(const exploration::PropagationStartsForCell<size>&);
  void operator()(const exploration::CellPropagates<size>&);
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>&);
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>&);
  void operator()(const exploration::PropagationIsDoneForCell<size>&);
  void operator()(const exploration::PropagationIsDoneForSudoku<size>&);
  void operator()(const exploration::ExplorationStarts<size>&);
  void operator()(const exploration::HypothesisIsMade<size>&);
  void operator()(const exploration::HypothesisIsRejected<size>&);
  void operator()(const exploration::SudokuIsSolved<size>&);
  void operator()(const exploration::HypothesisIsAccepted<size>&);
  void operator()(const exploration::ExplorationIsDone<size>&);
  void flush_pending_events();

 private:
  std::function<void(const exploration::Event<size>&)> process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size>>
    pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>>
    pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};

#endif  // EXPLANATION_REORDER_HPP_
