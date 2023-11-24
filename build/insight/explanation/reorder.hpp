// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_REORDER_HPP_
#define EXPLANATION_REORDER_HPP_

#include <functional>
#include <vector>

#include "../exploration/events.hpp"


template<unsigned int size>
class Reorder
{
  
  public: 
  inline explicit Reorder(const std::function<void (const exploration::Event<size> &)> & process_event_)
  : process_event{process_event_}
  {
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::InputsAreDone<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::CellPropagates<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<size> & event)
  {
    this->process_event(event);
    this->flush_pending_events();
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::ExplorationStarts<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::HypothesisIsMade<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::SudokuIsSolved<size> & event)
  {
    this->flush_pending_events();
    this->process_event(event);
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::ExplorationIsDone<size> & event)
  {
    this->process_event(event);
  }
  
  
  private: 
  inline void flush_pending_events()
  {
    {
      auto && __range2 = this->pending_cell_is_deduced_from_single_allowed_value_events;
      for(; ; ) {
        const auto & event;
        this->process_event(event);
      }
      
    }
    {
      auto && __range2 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
      for(; ; ) {
        const auto & event;
        this->process_event(event);
      }
      
    }
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  
  private: 
  std::function<void (const exploration::Event<size> &)> process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size> > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};



#endif  // EXPLANATION_REORDER_HPP_
