// Copyright 2023 Vincent Jacques

#include "video-explainer.hpp"

#include <tuple>
#include <vector>

#include "art.hpp"


template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellIsSetInInput<size>& event) {
  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::InputsAreDone<size>& event) {
  VisitEventsGuard visit(this, event);

  Layout title{.above = {
    {"How to solve this Sudoku?", 40, Text::Bold},
    {"An automated explanation by @jacquev6", 20},
    {"https://github.com/jacquev6/Sudoku", 20},
  }};

  for (unsigned index = 0; index != quicken(75); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(title);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size
      });
  }

  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const unsigned transition_duration = quicken(12);
  for (unsigned index = 0; index != transition_duration; ++index) {
    const double ratio = (index + 1.) / (transition_duration + 1);

    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout_transition(title, propagate, ratio);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size
      });
  }

  for (unsigned index = 0; index != quicken(12); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size
      });
  }

  for (unsigned index = 0; index != quicken(12); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size,
        .possible = true,
        .bold_todo = true
      });
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationStartsForSudoku<size>& event) {
  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationStartsForCell<size>& event) {
  flush_pending_cell_is_deduced_from_single_allowed_value_events();
  flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  VisitEventsGuard visit(this, event);

  Layout propagate{.below = {{"Propagate constraints", 20}}};

  if (cell_propagations_handled < quicken(3)) {
    const double widths[] = {2, 4, 5, 3, 2};
    const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);
    for (unsigned index = 0; index != quicken(3) * widths_count; ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);
      art::draw(
        context,
        visit.before.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {event.cell},
          .circled_cells_line_width = widths[index % widths_count],
        });
    }
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellPropagates<size>& event) {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (cell_propagations_handled < quicken(3)) {
    VisitEventsGuard visit(this, event);

    if (single_propagations_handled < quicken(6)) {
      for (unsigned index = 0; index != quicken(3) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.before.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
            .circled_values = {{event.target_cell, event.value}},
            .circled_values_line_width = widths[index % widths_count],
            .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
            .links_from_cell_to_value_line_width = widths[index % widths_count],
          });
      }

      for (unsigned index = 0; index != quicken(6); ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
          });
      }
    } else {
      for (unsigned index = 0; index != quicken(1) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.before.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
            .circled_values = {{event.target_cell, event.value}},
            .circled_values_line_width = widths[index % widths_count],
            .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
            .links_from_cell_to_value_line_width = widths[index % widths_count],
          });
      }

      for (unsigned index = 0; index != quicken(4); ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
            .circled_values = {{event.target_cell, event.value}},
            .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
          });
      }
    }
    ++single_propagations_handled;
  } else {
    pending_cell_propagates_events.push_back(event);
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationIsDoneForCell<size>& event) {
  flush_pending_cell_propagates_events();

  VisitEventsGuard visit(this, event);

  ++cell_propagations_handled;
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_cell_propagates_events() {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (!pending_cell_propagates_events.empty()) {
    VisitEventsGuard visit(this, pending_cell_propagates_events);

    for (unsigned index = 0; index != quicken(1) * widths_count; ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);

      const Coordinates source_cell = pending_cell_propagates_events.front().source_cell;
      std::vector<std::tuple<Coordinates, unsigned>> circled_values;
      std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
      for (const auto& event : pending_cell_propagates_events) {
        assert(event.source_cell == source_cell);
        circled_values.push_back({event.target_cell, event.value});
        links_from_cell_to_value.push_back({event.source_cell, event.target_cell, event.value});
      }

      art::draw(
        context,
        visit.before.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source_cell},
          .circled_cells_line_width = widths[index % widths_count],
          .circled_values = circled_values,
          .circled_values_line_width = widths[index % widths_count],
          .links_from_cell_to_value = links_from_cell_to_value,
          .links_from_cell_to_value_line_width = widths[index % widths_count],
        });
    }

    for (unsigned index = 0; index != quicken(4); ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);

      const Coordinates source_cell = pending_cell_propagates_events.front().source_cell;
      std::vector<std::tuple<Coordinates, unsigned>> circled_values;
      std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
      for (const auto& event : pending_cell_propagates_events) {
        assert(event.source_cell == source_cell);
        circled_values.push_back({event.target_cell, event.value});
        links_from_cell_to_value.push_back({event.source_cell, event.target_cell, event.value});
      }

      art::draw(
        context,
        visit.after.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source_cell},
          .circled_values = circled_values,
          .links_from_cell_to_value = links_from_cell_to_value,
        });
    }

    for (unsigned index = 0; index != quicken(4); ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);
      art::draw(
        context,
        visit.after.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {pending_cell_propagates_events.front().source_cell},
        });
    }
  }
  pending_cell_propagates_events.clear();
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_cell_is_deduced_from_single_allowed_value_events() {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (!pending_cell_is_deduced_from_single_allowed_value_events.empty()) {
    VisitEventsGuard visit(this, pending_cell_is_deduced_from_single_allowed_value_events);

    if (deductions_handled < quicken(4)) {
      for (unsigned index = 0; index != quicken(6) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> circled_cells;
        for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
          circled_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = circled_cells,
            .circled_cells_line_width = widths[index % widths_count],
            .circled_cells_color = {0, 1, 0},
          });
      }
    } else {
      for (unsigned index = 0; index != quicken(2) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> circled_cells;
        for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
          circled_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = circled_cells,
            .circled_cells_line_width = widths[index % widths_count],
            .circled_cells_color = {0, 1, 0},
          });
      }
    }
    ++deductions_handled;
  }
  pending_cell_is_deduced_from_single_allowed_value_events.clear();
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events() {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (!pending_cell_is_deduced_as_single_place_for_value_in_region_events.empty()) {
    VisitEventsGuard visit(this, pending_cell_is_deduced_as_single_place_for_value_in_region_events);

    if (deductions_handled < quicken(4)) {
      for (unsigned index = 0; index != quicken(6) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> boxed_cells;
        for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
          boxed_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .boxed_cells = boxed_cells,
            .boxed_cells_line_width = widths[index % widths_count],
            .boxed_cells_color = {0, 1, 0},
          });
      }
    } else {
      for (unsigned index = 0; index != quicken(2) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> boxed_cells;
        for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
          boxed_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .boxed_cells = boxed_cells,
            .boxed_cells_line_width = widths[index % widths_count],
            .boxed_cells_color = {0, 1, 0},
          });
      }
    }
    ++deductions_handled;
  }
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationIsDoneForSudoku<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::ExplorationStarts<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::HypothesisIsMade<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::HypothesisIsRejected<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::SudokuIsSolved<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);

  Layout done{.below = {{"Solved!", 20}}};

  for (unsigned index = 0; index != quicken(75); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(done);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.after.current(),
      {
        .grid_size = grid_size,
      });
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::HypothesisIsAccepted<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::ExplorationIsDone<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_events() {
  flush_pending_cell_propagates_events();
  flush_pending_cell_is_deduced_from_single_allowed_value_events();
  flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
}



template<>
class VideoExplainer<static_cast<unsigned int>(4)>
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  inline static constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  inline static constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  
  public: 
  inline VideoExplainer(video::Serializer * video_serializer_, const bool quick_, unsigned int frame_width_, unsigned int frame_height_)
  : before{Stack<4>()}
  , after{Stack<4>()}
  , frame_width_pixels{frame_width_}
  , frame_height_pixels{frame_height_}
  , viewport_height_pixels{this->frame_height_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , viewport_width_pixels{this->frame_width_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width_pixels), static_cast<int>(this->frame_height_pixels))}
  , context{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  , cr{static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->context).operator*()}
  , video_serializer{video_serializer_}
  , quick{quick_}
  , single_propagations_handled{static_cast<unsigned int>(0)}
  , cell_propagations_handled{static_cast<unsigned int>(0)}
  , deductions_handled{static_cast<unsigned int>(0)}
  , pending_cell_propagates_events{std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >()}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >()}
  {
  }
  
  
  private: 
  class VisitEventsGuard
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > & event)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
            
      class __lambda_64_18
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
        {
          e.apply(&__this->explainer.after);
        }
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        private: 
        VideoExplainer<4>::VisitEventsGuard * __this;
        
        public:
        __lambda_64_18(VideoExplainer<4>::VisitEventsGuard * _this)
        : __this{_this}
        {}
        
      };
      
      std::visit<__lambda_64_18, const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(__lambda_64_18{this}, event);
      this->events.push_back(event);
    }
    
    template<typename T>
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<T> & events_);
    
    
    /* First instantiated from: video-explainer.cpp:230 */
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline VisitEventsGuard<exploration::CellPropagates<4> >(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range3 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin0 = __range3.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end0 = __range3.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end0)); __begin0.operator++()) {
          const exploration::CellPropagates<4> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin0).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event));
        }
        
      }
    }
    #endif
    
    
    
    /* First instantiated from: video-explainer.cpp:315 */
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> >(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range3 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin0 = __range3.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end0 = __range3.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end0)); __begin0.operator++()) {
          const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event));
        }
        
      }
    }
    #endif
    
    
    
    /* First instantiated from: video-explainer.cpp:377 */
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range3 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin0 = __range3.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end0 = __range3.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end0)); __begin0.operator++()) {
          const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event));
        }
        
      }
    }
    #endif
    
    
    // inline VisitEventsGuard(const VisitEventsGuard &) = delete;
    // inline VisitEventsGuard & operator=(const VisitEventsGuard &) = delete;
    // inline VisitEventsGuard(VisitEventsGuard &&) = delete;
    // inline VisitEventsGuard & operator=(VisitEventsGuard &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > & __range2 = this->events;
        __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > *, std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > > __begin0 = __range2.begin();
        __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > *, std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > > __end0 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > *, std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > *, std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > >>(__end0)); __begin0.operator++()) {
          const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > & event = static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(static_cast<const __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > *, std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > >>(__begin0).operator*());
                    
          class __lambda_88_20
          {
            public: 
            template<class type_parameter_0_0>
            inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
            {
              e.apply(&__this->explainer.before);
            }
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            private: 
            VideoExplainer<4>::VisitEventsGuard * __this;
            
            public:
            __lambda_88_20(VideoExplainer<4>::VisitEventsGuard * _this)
            : __this{_this}
            {}
            
          };
          
          std::visit<__lambda_88_20, const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(__lambda_88_20{this}, event);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >, std::allocator<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  class FrameGuard
  {
    
    public: 
    inline explicit FrameGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_)
    : explainer{*explainer_}
    , cr{this->explainer.cr}
    {
      {
        CairoSaveGuard saver = CairoSaveGuard(this->cr);
        this->cr.set_source_rgb(1.0, 0.80000000000000004, 0.80000000000000004);
        this->cr.paint();
        this->cr.set_source_rgb(1.0, 1.0, 1.0);
        this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
        this->cr.fill();
      };
      this->cr.save();
      this->cr.translate(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels));
    }
    
    // inline FrameGuard(const FrameGuard &) = delete;
    // inline FrameGuard & operator=(const FrameGuard &) = delete;
    // inline FrameGuard(FrameGuard &&) = delete;
    // inline FrameGuard & operator=(FrameGuard &&) = delete;
    inline ~FrameGuard() noexcept
    {
      this->cr.restore();
      CairoSaveGuard saver = CairoSaveGuard(this->cr);
      this->cr.rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->explainer.frame_width_pixels), static_cast<double>(this->explainer.frame_height_pixels));
      this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
      this->cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      this->cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      this->cr.fill();
      this->explainer.video_serializer->serialize(std::shared_ptr<Cairo::ImageSurface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->explainer.surface)));
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    Cairo::Context & cr;
  };
  
  struct Text
  {
    std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
    double font_size;
    enum 
    {
      Normal, 
      Bold
    };
    
    VideoExplainer<4>::Text::(unnamed) weight;
    // inline constexpr Text(const Text &) noexcept(false) = default;
    // inline constexpr ~Text() noexcept = default;
  };
  
  struct Layout
  {
    std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > above = std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{};
    std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > below = std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{};
    // inline constexpr ~Layout() noexcept = default;
  };
  
  
  private: 
  inline unsigned int quicken(unsigned int n)
  {
    if(this->quick) {
      return static_cast<unsigned int>(1);
    } else {
      return n;
    } 
    
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<4> & event)
  {
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::InputsAreDone<4> & event)
  {
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
    VideoExplainer<4>::Layout title = {std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("How to solve this Sudoku?"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(40), Text::Bold}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("An automated explanation by @jacquev6"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("https://github.com/jacquev6/Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}, {std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __title28 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(title)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title28));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title28));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title28));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const unsigned int transition_duration = this->quicken(static_cast<unsigned int>(12));
    for(unsigned int index = static_cast<unsigned int>(0); index != transition_duration; ++index) {
      const double ratio = (static_cast<double>(index) + 1.0) / static_cast<double>((transition_duration + static_cast<unsigned int>(1)));
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __title45 = static_cast<const std::tuple<double, double, double>>(this->draw_layout_transition(static_cast<const VideoExplainer<4>::Layout>(title), static_cast<const VideoExplainer<4>::Layout>(propagate), ratio));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title45));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title45));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title45));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate57 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate57));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate57));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate57));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate69 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate69));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate69));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate69));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::PropagationStartsForSudoku<4> & event)
  {
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::PropagationStartsForCell<4> & event)
  {
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
      const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate100 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate100));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate100));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate100));
        this->cr.translate(grid_x, grid_y);
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
  }
  
  void operator()(const exploration::CellPropagates<4> & event)
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
      if(this->single_propagations_handled < this->quicken(static_cast<unsigned int>(6))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate129 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate129));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate129));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate129));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(6)); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate148 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate148));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate148));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate148));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate163 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate163));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate163));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate163));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate182 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate182));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate182));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate182));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->single_propagations_handled;
    } else {
      this->pending_cell_propagates_events.push_back(event);
    } 
    
  }
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  void operator()(const exploration::PropagationIsDoneForCell<4> & event)
  {
    this->flush_pending_cell_propagates_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
    ++this->cell_propagations_handled;
  }
  
  void operator()(const exploration::PropagationIsDoneForSudoku<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::ExplorationStarts<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::HypothesisIsMade<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::HypothesisIsRejected<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::SudokuIsSolved<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
    VideoExplainer<4>::Layout done = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Solved!"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __done469 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(done)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__done469));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__done469));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__done469));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::HypothesisIsAccepted<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void operator()(const exploration::ExplorationIsDone<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >>(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(event)));
  }
  
  void flush_pending_cell_propagates_events()
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >>(this->pending_cell_propagates_events).empty()) {
      VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >>(this->pending_cell_propagates_events));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate234 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate234));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate234));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate234));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range3 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin0 = __range3.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end0 = __range3.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end0)); __begin0.operator++()) {
            const exploration::CellPropagates<4> & event = static_cast<const exploration::CellPropagates<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin0).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("/wd/src/explanation/video-explainer.cpp"), static_cast<unsigned int>(241), static_cast<const char *>(__extension__"void VideoExplainer<4>::flush_pending_cell_propagates_events() [size = 4]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate264 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate264));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate264));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate264));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range3 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin0 = __range3.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end0 = __range3.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end0)); __begin0.operator++()) {
            const exploration::CellPropagates<4> & event = static_cast<const exploration::CellPropagates<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin0).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("/wd/src/explanation/video-explainer.cpp"), static_cast<unsigned int>(271), static_cast<const char *>(__extension__"void VideoExplainer<4>::flush_pending_cell_propagates_events() [size = 4]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate291 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate291));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate291));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate291));
        this->cr.translate(grid_x, grid_y);
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
    this->pending_cell_propagates_events.clear();
  }
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events()
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events).empty()) {
      VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate320 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate320));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate320));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate320));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range4 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate343 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate343));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate343));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate343));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range4 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
  }
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events()
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events).empty()) {
      VideoExplainer<4>::VisitEventsGuard visit = VideoExplainer<4>::VisitEventsGuard(this, static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate382 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate382));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate382));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate382));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range4 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate405 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate405));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate405));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate405));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range4 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  void flush_pending_events()
  {
    this->flush_pending_cell_propagates_events();
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  }
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double above_height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > & __range2 = layout.above;
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __begin0 = __range2.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __end0 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__end0)); __begin0.operator++()) {
        const VideoExplainer<4>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin0).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, above_height - extents.y_bearing);
        this->cr.show_text(text.text);
        above_height = above_height + extents.height;
      }
      
    }
    double below_height = static_cast<double>(0);
    {
      std::ranges::reverse_view<std::ranges::ref_view<const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > > && __range2 = operator|(layout.below, std::ranges::views::reverse);
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > > __begin0 = __range2.begin();
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > > __end0 = __range2.end();
      for(; !std::operator==(static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > >>(__begin0), static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > >>(__end0)); __begin0.operator++()) {
        const VideoExplainer<4>::Text & text = static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > >>(__begin0).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        below_height = below_height + extents.height;
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, (static_cast<double>(this->viewport_height_pixels) - below_height) - extents.y_bearing);
        this->cr.show_text(text.text);
      }
      
    }
    const unsigned int available_height = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height) - below_height);
    const unsigned int grid_size = (((available_height - thick_line_width) / 4U) * 4U) + thick_line_width;
    const unsigned int grid_x = (this->viewport_width_pixels - grid_size) / static_cast<unsigned int>(2);
    const unsigned int grid_y = static_cast<const unsigned int>(above_height + (static_cast<double>((available_height - grid_size) / static_cast<unsigned int>(2))));
    return std::tuple<double, double, double>(std::make_tuple<const unsigned int &, const unsigned int &, const unsigned int &>(grid_x, grid_y, grid_size));
  }
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    const double above_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(before.above);
    const double below_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(before.below);
    const unsigned int available_height_before = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_before) - below_height_before);
    const unsigned int grid_size_before = (((available_height_before - thick_line_width) / 4U) * 4U) + thick_line_width;
    const double grid_x_before = static_cast<const double>((this->viewport_width_pixels - grid_size_before) / static_cast<unsigned int>(2));
    const double grid_y_before = above_height_before + (static_cast<double>((available_height_before - grid_size_before) / static_cast<unsigned int>(2)));
    const double above_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(after.above);
    const double below_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(after.below);
    const unsigned int available_height_after = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_after) - below_height_after);
    const unsigned int grid_size_after = (((available_height_after - thick_line_width) / 4U) * 4U) + thick_line_width;
    const double grid_x_after = static_cast<const double>((this->viewport_width_pixels - grid_size_after) / static_cast<unsigned int>(2));
    const double grid_y_after = above_height_after + (static_cast<double>((available_height_after - grid_size_after) / static_cast<unsigned int>(2)));
    const double grid_size = static_cast<double>(grid_size_before) + (ratio * static_cast<double>((grid_size_after - grid_size_before)));
    const double grid_x = grid_x_before + (ratio * (grid_x_after - grid_x_before));
    const double grid_y = grid_y_before + (ratio * (grid_y_after - grid_y_before));
    return std::make_tuple<const double &, const double &, const double &>(grid_x, grid_y, grid_size);
  }
  
  inline double compute_text_height(const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > & texts) const
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > & __range2 = texts;
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __begin0 = __range2.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __end0 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__end0)); __begin0.operator++()) {
        const VideoExplainer<4>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin0).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        height = height + extents.height;
      }
      
    }
    return height;
  }
  
  
  private: 
  Stack<4> before;
  Stack<4> after;
  unsigned int frame_width_pixels;
  unsigned int frame_height_pixels;
  unsigned int viewport_height_pixels;
  unsigned int viewport_width_pixels;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> context;
  Cairo::Context & cr;
  video::Serializer * video_serializer;
  const bool quick;
  
  private: 
  unsigned int single_propagations_handled;
  unsigned int cell_propagations_handled;
  unsigned int deductions_handled;
  std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline VideoExplainer<static_cast<unsigned int>(4)> & operator=(const VideoExplainer<static_cast<unsigned int>(4)> &) /* noexcept */ = delete;
  // inline VideoExplainer<static_cast<unsigned int>(4)> & operator=(VideoExplainer<static_cast<unsigned int>(4)> &&) /* noexcept */ = delete;
};





template<>
class VideoExplainer<static_cast<unsigned int>(9)>
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  inline static constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  inline static constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  
  public: 
  inline VideoExplainer(video::Serializer * video_serializer_, const bool quick_, unsigned int frame_width_, unsigned int frame_height_)
  : before{Stack<9>()}
  , after{Stack<9>()}
  , frame_width_pixels{frame_width_}
  , frame_height_pixels{frame_height_}
  , viewport_height_pixels{this->frame_height_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , viewport_width_pixels{this->frame_width_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width_pixels), static_cast<int>(this->frame_height_pixels))}
  , context{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  , cr{static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->context).operator*()}
  , video_serializer{video_serializer_}
  , quick{quick_}
  , single_propagations_handled{static_cast<unsigned int>(0)}
  , cell_propagations_handled{static_cast<unsigned int>(0)}
  , deductions_handled{static_cast<unsigned int>(0)}
  , pending_cell_propagates_events{std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >()}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >()}
  {
  }
  
  
  private: 
  class VisitEventsGuard
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > & event)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
            
      class __lambda_64_18
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
        {
          e.apply(&__this->explainer.after);
        }
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & e) const
        {
          e.apply(&__this->explainer.after);
        }
        #endif
        
        private: 
        VideoExplainer<9>::VisitEventsGuard * __this;
        
        public:
        __lambda_64_18(VideoExplainer<9>::VisitEventsGuard * _this)
        : __this{_this}
        {}
        
      };
      
      std::visit<__lambda_64_18, const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(__lambda_64_18{this}, event);
      this->events.push_back(event);
    }
    
    template<typename T>
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<T> & events_);
    
    
    /* First instantiated from: video-explainer.cpp:230 */
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline VisitEventsGuard<exploration::CellPropagates<9> >(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range3 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin0 = __range3.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end0 = __range3.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end0)); __begin0.operator++()) {
          const exploration::CellPropagates<9> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin0).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event));
        }
        
      }
    }
    #endif
    
    
    
    /* First instantiated from: video-explainer.cpp:315 */
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> >(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range3 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin0 = __range3.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end0 = __range3.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end0)); __begin0.operator++()) {
          const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event));
        }
        
      }
    }
    #endif
    
    
    
    /* First instantiated from: video-explainer.cpp:377 */
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range3 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin0 = __range3.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end0 = __range3.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end0)); __begin0.operator++()) {
          const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event));
        }
        
      }
    }
    #endif
    
    
    // inline VisitEventsGuard(const VisitEventsGuard &) = delete;
    // inline VisitEventsGuard & operator=(const VisitEventsGuard &) = delete;
    // inline VisitEventsGuard(VisitEventsGuard &&) = delete;
    // inline VisitEventsGuard & operator=(VisitEventsGuard &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > & __range2 = this->events;
        __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > *, std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > > __begin0 = __range2.begin();
        __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > *, std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > > __end0 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > *, std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > *, std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > >>(__end0)); __begin0.operator++()) {
          const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > & event = static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(static_cast<const __gnu_cxx::__normal_iterator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > *, std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > >>(__begin0).operator*());
                    
          class __lambda_88_20
          {
            public: 
            template<class type_parameter_0_0>
            inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
            {
              e.apply(&__this->explainer.before);
            }
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            
            #ifdef INSIGHTS_USE_TEMPLATE
            template<>
            inline /*constexpr */ void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & e) const
            {
              e.apply(&__this->explainer.before);
            }
            #endif
            
            private: 
            VideoExplainer<9>::VisitEventsGuard * __this;
            
            public:
            __lambda_88_20(VideoExplainer<9>::VisitEventsGuard * _this)
            : __this{_this}
            {}
            
          };
          
          std::visit<__lambda_88_20, const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(__lambda_88_20{this}, event);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >, std::allocator<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  class FrameGuard
  {
    
    public: 
    inline explicit FrameGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_)
    : explainer{*explainer_}
    , cr{this->explainer.cr}
    {
      {
        CairoSaveGuard saver = CairoSaveGuard(this->cr);
        this->cr.set_source_rgb(1.0, 0.80000000000000004, 0.80000000000000004);
        this->cr.paint();
        this->cr.set_source_rgb(1.0, 1.0, 1.0);
        this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
        this->cr.fill();
      };
      this->cr.save();
      this->cr.translate(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels));
    }
    
    // inline FrameGuard(const FrameGuard &) = delete;
    // inline FrameGuard & operator=(const FrameGuard &) = delete;
    // inline FrameGuard(FrameGuard &&) = delete;
    // inline FrameGuard & operator=(FrameGuard &&) = delete;
    inline ~FrameGuard() noexcept
    {
      this->cr.restore();
      CairoSaveGuard saver = CairoSaveGuard(this->cr);
      this->cr.rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->explainer.frame_width_pixels), static_cast<double>(this->explainer.frame_height_pixels));
      this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
      this->cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      this->cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      this->cr.fill();
      this->explainer.video_serializer->serialize(std::shared_ptr<Cairo::ImageSurface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->explainer.surface)));
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    Cairo::Context & cr;
  };
  
  struct Text
  {
    std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
    double font_size;
    enum 
    {
      Normal, 
      Bold
    };
    
    VideoExplainer<9>::Text::(unnamed) weight;
    // inline constexpr Text(const Text &) noexcept(false) = default;
    // inline constexpr ~Text() noexcept = default;
  };
  
  struct Layout
  {
    std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > above = std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{};
    std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > below = std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{};
    // inline constexpr ~Layout() noexcept = default;
  };
  
  
  private: 
  inline unsigned int quicken(unsigned int n)
  {
    if(this->quick) {
      return static_cast<unsigned int>(1);
    } else {
      return n;
    } 
    
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<9> & event)
  {
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::InputsAreDone<9> & event)
  {
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
    VideoExplainer<9>::Layout title = {std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("How to solve this Sudoku?"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(40), Text::Bold}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("An automated explanation by @jacquev6"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("https://github.com/jacquev6/Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}, {std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __title28 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(title)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title28));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title28));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title28));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const unsigned int transition_duration = this->quicken(static_cast<unsigned int>(12));
    for(unsigned int index = static_cast<unsigned int>(0); index != transition_duration; ++index) {
      const double ratio = (static_cast<double>(index) + 1.0) / static_cast<double>((transition_duration + static_cast<unsigned int>(1)));
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __title45 = static_cast<const std::tuple<double, double, double>>(this->draw_layout_transition(static_cast<const VideoExplainer<9>::Layout>(title), static_cast<const VideoExplainer<9>::Layout>(propagate), ratio));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title45));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title45));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title45));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate57 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate57));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate57));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate57));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate69 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate69));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate69));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate69));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::PropagationStartsForSudoku<9> & event)
  {
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::PropagationStartsForCell<9> & event)
  {
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
      const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate100 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate100));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate100));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate100));
        this->cr.translate(grid_x, grid_y);
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
  }
  
  void operator()(const exploration::CellPropagates<9> & event)
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
      if(this->single_propagations_handled < this->quicken(static_cast<unsigned int>(6))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate129 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate129));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate129));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate129));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(6)); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate148 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate148));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate148));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate148));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate163 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate163));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate163));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate163));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate182 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate182));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate182));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate182));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->single_propagations_handled;
    } else {
      this->pending_cell_propagates_events.push_back(event);
    } 
    
  }
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  void operator()(const exploration::PropagationIsDoneForCell<9> & event)
  {
    this->flush_pending_cell_propagates_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
    ++this->cell_propagations_handled;
  }
  
  void operator()(const exploration::PropagationIsDoneForSudoku<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::ExplorationStarts<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::HypothesisIsMade<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::HypothesisIsRejected<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::SudokuIsSolved<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
    VideoExplainer<9>::Layout done = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Solved!"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __done469 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(done)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__done469));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__done469));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__done469));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::HypothesisIsAccepted<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void operator()(const exploration::ExplorationIsDone<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >>(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(event)));
  }
  
  void flush_pending_cell_propagates_events()
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >>(this->pending_cell_propagates_events).empty()) {
      VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >>(this->pending_cell_propagates_events));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate234 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate234));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate234));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate234));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range3 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin0 = __range3.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end0 = __range3.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end0)); __begin0.operator++()) {
            const exploration::CellPropagates<9> & event = static_cast<const exploration::CellPropagates<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin0).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("/wd/src/explanation/video-explainer.cpp"), static_cast<unsigned int>(241), static_cast<const char *>(__extension__"void VideoExplainer<9>::flush_pending_cell_propagates_events() [size = 9]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate264 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate264));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate264));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate264));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range3 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin0 = __range3.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end0 = __range3.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end0)); __begin0.operator++()) {
            const exploration::CellPropagates<9> & event = static_cast<const exploration::CellPropagates<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin0).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("/wd/src/explanation/video-explainer.cpp"), static_cast<unsigned int>(271), static_cast<const char *>(__extension__"void VideoExplainer<9>::flush_pending_cell_propagates_events() [size = 9]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate291 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate291));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate291));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate291));
        this->cr.translate(grid_x, grid_y);
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
    this->pending_cell_propagates_events.clear();
  }
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events()
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events).empty()) {
      VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate320 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate320));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate320));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate320));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range4 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate343 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate343));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate343));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate343));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range4 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
  }
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events()
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events).empty()) {
      VideoExplainer<9>::VisitEventsGuard visit = VideoExplainer<9>::VisitEventsGuard(this, static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate382 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate382));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate382));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate382));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range4 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate405 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate405));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate405));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate405));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range4 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin0 = __range4.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end0 = __range4.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end0)); __begin0.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  void flush_pending_events()
  {
    this->flush_pending_cell_propagates_events();
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  }
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double above_height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > & __range2 = layout.above;
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __begin0 = __range2.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __end0 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__end0)); __begin0.operator++()) {
        const VideoExplainer<9>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin0).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, above_height - extents.y_bearing);
        this->cr.show_text(text.text);
        above_height = above_height + extents.height;
      }
      
    }
    double below_height = static_cast<double>(0);
    {
      std::ranges::reverse_view<std::ranges::ref_view<const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > > && __range2 = operator|(layout.below, std::ranges::views::reverse);
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > > __begin0 = __range2.begin();
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > > __end0 = __range2.end();
      for(; !std::operator==(static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > >>(__begin0), static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > >>(__end0)); __begin0.operator++()) {
        const VideoExplainer<9>::Text & text = static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > >>(__begin0).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        below_height = below_height + extents.height;
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, (static_cast<double>(this->viewport_height_pixels) - below_height) - extents.y_bearing);
        this->cr.show_text(text.text);
      }
      
    }
    const unsigned int available_height = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height) - below_height);
    const unsigned int grid_size = (((available_height - thick_line_width) / 9U) * 9U) + thick_line_width;
    const unsigned int grid_x = (this->viewport_width_pixels - grid_size) / static_cast<unsigned int>(2);
    const unsigned int grid_y = static_cast<const unsigned int>(above_height + (static_cast<double>((available_height - grid_size) / static_cast<unsigned int>(2))));
    return std::tuple<double, double, double>(std::make_tuple<const unsigned int &, const unsigned int &, const unsigned int &>(grid_x, grid_y, grid_size));
  }
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    const double above_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(before.above);
    const double below_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(before.below);
    const unsigned int available_height_before = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_before) - below_height_before);
    const unsigned int grid_size_before = (((available_height_before - thick_line_width) / 9U) * 9U) + thick_line_width;
    const double grid_x_before = static_cast<const double>((this->viewport_width_pixels - grid_size_before) / static_cast<unsigned int>(2));
    const double grid_y_before = above_height_before + (static_cast<double>((available_height_before - grid_size_before) / static_cast<unsigned int>(2)));
    const double above_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(after.above);
    const double below_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(after.below);
    const unsigned int available_height_after = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_after) - below_height_after);
    const unsigned int grid_size_after = (((available_height_after - thick_line_width) / 9U) * 9U) + thick_line_width;
    const double grid_x_after = static_cast<const double>((this->viewport_width_pixels - grid_size_after) / static_cast<unsigned int>(2));
    const double grid_y_after = above_height_after + (static_cast<double>((available_height_after - grid_size_after) / static_cast<unsigned int>(2)));
    const double grid_size = static_cast<double>(grid_size_before) + (ratio * static_cast<double>((grid_size_after - grid_size_before)));
    const double grid_x = grid_x_before + (ratio * (grid_x_after - grid_x_before));
    const double grid_y = grid_y_before + (ratio * (grid_y_after - grid_y_before));
    return std::make_tuple<const double &, const double &, const double &>(grid_x, grid_y, grid_size);
  }
  
  inline double compute_text_height(const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > & texts) const
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > & __range2 = texts;
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __begin0 = __range2.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __end0 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__end0)); __begin0.operator++()) {
        const VideoExplainer<9>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin0).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        height = height + extents.height;
      }
      
    }
    return height;
  }
  
  
  private: 
  Stack<9> before;
  Stack<9> after;
  unsigned int frame_width_pixels;
  unsigned int frame_height_pixels;
  unsigned int viewport_height_pixels;
  unsigned int viewport_width_pixels;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> context;
  Cairo::Context & cr;
  video::Serializer * video_serializer;
  const bool quick;
  
  private: 
  unsigned int single_propagations_handled;
  unsigned int cell_propagations_handled;
  unsigned int deductions_handled;
  std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline VideoExplainer<static_cast<unsigned int>(9)> & operator=(const VideoExplainer<static_cast<unsigned int>(9)> &) /* noexcept */ = delete;
  // inline VideoExplainer<static_cast<unsigned int>(9)> & operator=(VideoExplainer<static_cast<unsigned int>(9)> &&) /* noexcept */ = delete;
};



