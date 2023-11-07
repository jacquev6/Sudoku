// Copyright 2023 Vincent Jacques

#include "video-explainer.hpp"

#include <tuple>
#include <vector>

#include "../art.hpp"


template<unsigned size>
void VideoExplainer<size>::visit(const exploration::CellIsSetInInput<size>& event) {
  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::InputsAreDone<size>& event) {
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
void VideoExplainer<size>::visit(const exploration::PropagationStartsForSudoku<size>& event) {
  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::PropagationStartsForCell<size>& event) {
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
void VideoExplainer<size>::visit(const exploration::CellPropagates<size>& event) {
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
void VideoExplainer<size>::visit(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::PropagationIsDoneForCell<size>& event) {
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
void VideoExplainer<size>::visit(const exploration::PropagationIsDoneForSudoku<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::ExplorationStarts<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::HypothesisIsMade<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::HypothesisIsRejected<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::SudokuIsSolved<size>& event) {
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
void VideoExplainer<size>::visit(const exploration::HypothesisIsAccepted<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::visit(const exploration::ExplorationIsDone<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_events() {
  flush_pending_cell_propagates_events();
  flush_pending_cell_is_deduced_from_single_allowed_value_events();
  flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
}

template class VideoExplainer<4>;
template class VideoExplainer<9>;
