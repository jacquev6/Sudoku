// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_REORDER_HPP_
#define EXPLANATION_REORDER_HPP_

#include <vector>

#include "../exploration/events.hpp"


template<unsigned size>
class Reorder : public exploration::EventVisitor<size> {
 public:
  explicit Reorder(const std::function<void(const exploration::Event<size>&)>& process_event_) :
    process_event(process_event_)
  {}

 private:
  void visit(const exploration::CellIsSetInInput<size>&) override;
  void visit(const exploration::InputsAreDone<size>&) override;
  void visit(const exploration::PropagationStartsForSudoku<size>&) override;
  void visit(const exploration::PropagationStartsForCell<size>&) override;
  void visit(const exploration::CellPropagates<size>&) override;
  void visit(const exploration::CellIsDeducedFromSingleAllowedValue<size>&) override;
  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>&) override;
  void visit(const exploration::PropagationIsDoneForCell<size>&) override;
  void visit(const exploration::PropagationIsDoneForSudoku<size>&) override;
  void visit(const exploration::ExplorationStarts<size>&) override;
  void visit(const exploration::HypothesisIsMade<size>&) override;
  void visit(const exploration::HypothesisIsRejected<size>&) override;
  void visit(const exploration::SudokuIsSolved<size>&) override;
  void visit(const exploration::HypothesisIsAccepted<size>&) override;
  void visit(const exploration::ExplorationIsDone<size>&) override;
  void flush_pending_events();

 private:
  std::function<void(const exploration::Event<size>&)> process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size>>
    pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>>
    pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};

#endif  // EXPLANATION_REORDER_HPP_
