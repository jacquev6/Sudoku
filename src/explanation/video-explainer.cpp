// Copyright 2023 Vincent Jacques

#include "video-explainer.hpp"

#include <ranges>
#include <string>
#include <tuple>
#include <vector>

#include "art.hpp"


template<unsigned size>
class VideoExplainer {
  static constexpr unsigned margin_pixels = 10;
  static constexpr unsigned thick_line_width = 4;
  static constexpr unsigned thin_line_width = 2;

 public:
  VideoExplainer(
    const Explanation<size>& explanation_,
    video::Serializer* serializer_,
    bool quick_,
    unsigned frame_width_,
    unsigned frame_height_
  ) :  // NOLINT(whitespace/parens)
    explanation(explanation_),
    serializer(serializer_),
    quick(quick_),
    frame_width_pixels(frame_width_),
    frame_height_pixels(frame_height_),
    viewport_height_pixels(frame_height_pixels - 2 * margin_pixels),
    viewport_width_pixels(frame_width_pixels - 2 * margin_pixels),
    stack()
  {}

 public:
  void explain() {
    for (const auto& cell : explanation.inputs.cells()) {
      const std::optional<unsigned> value = cell.get();
      if (value) {
        stack.current().cell(cell.coordinates()).set_input(*value);
      }
    }

    Layout title{
      .above = {
        {"How to solve this Sudoku?", 40, Text::Bold},
        {"An automated explanation by @jacquev6", 20},
        {"https://github.com/jacquev6/Sudoku", 20},
      },
    };

    for (unsigned index = 0; index != quicken(75); ++index) {
      make_frame(title, {});
    }

    Layout propagate{.below = {{"Propagate constraints", 20}}};

    const unsigned transition_duration = quicken(12);
    for (unsigned index = 0; index != transition_duration; ++index) {
      make_frame(title, propagate, index, transition_duration, {});
    }

    for (unsigned index = 0; index != quicken(12); ++index) {
      make_frame(propagate, {});
    }

    for (unsigned index = 0; index != quicken(12); ++index) {
      make_frame(propagate, { .possible = true, .bold_todo = true });
    }

    explain(explanation.propagations);
    explain(explanation.exploration);
  }

 private:
  void explain(const std::vector<typename Explanation<size>::Propagation>& propagations) {
    for (const auto& propagation : propagations) {
      explain(propagation);
    }
  }

  void explain(const typename Explanation<size>::Propagation& propagation) {
    Layout propagate{.below = {{"Propagate constraints", 20}}};
    const double widths[] = {2, 4, 5, 3, 2};
    const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

    if (cell_propagations_handled < quicken(3)) {
      for (unsigned index = 0; index != quicken(3) * widths_count; ++index) {
        make_frame(
          propagate,
          {
            .possible = true,
            .bold_todo = true,
            .circled_cells = {propagation.source},
            .circled_cells_line_width = widths[index % widths_count],
          });
      }

      for (const auto& target : propagation.targets) {
        if (single_propagations_handled < quicken(6)) {
          for (unsigned index = 0; index != quicken(3) * widths_count; ++index) {
            make_frame(propagate, {
              .possible = true,
              .bold_todo = true,
              .circled_cells = {propagation.source},
              .circled_values = {{target.cell, propagation.value}},
              .circled_values_line_width = widths[index % widths_count],
              .links_from_cell_to_value = {{propagation.source, target.cell, propagation.value}},
              .links_from_cell_to_value_line_width = widths[index % widths_count],
            });
          }

          stack.current().cell(target.cell).forbid(propagation.value);

          for (unsigned index = 0; index != quicken(6); ++index) {
            make_frame(propagate, {
              .possible = true,
              .bold_todo = true,
              .circled_cells = {propagation.source},
            });
          }
        } else {
          for (unsigned index = 0; index != quicken(1) * widths_count; ++index) {
            make_frame(propagate, {
              .possible = true,
              .bold_todo = true,
              .circled_cells = {propagation.source},
              .circled_values = {{target.cell, propagation.value}},
              .circled_values_line_width = widths[index % widths_count],
              .links_from_cell_to_value = {{propagation.source, target.cell, propagation.value}},
              .links_from_cell_to_value_line_width = widths[index % widths_count],
            });
          }

          stack.current().cell(target.cell).forbid(propagation.value);

          for (unsigned index = 0; index != quicken(4); ++index) {
            make_frame(propagate, {
              .possible = true,
              .bold_todo = true,
              .circled_cells = {propagation.source},
              .circled_values = {{target.cell, propagation.value}},
              .links_from_cell_to_value = {{propagation.source, target.cell, propagation.value}},
            });
          }
        }

        ++single_propagations_handled;
      }
    } else {
      std::vector<std::tuple<Coordinates, unsigned>> circled_values;
      circled_values.reserve(propagation.targets.size());
      std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
      links_from_cell_to_value.reserve(propagation.targets.size());
      for (const auto& target : propagation.targets) {
        circled_values.emplace_back(target.cell, propagation.value);
        links_from_cell_to_value.emplace_back(propagation.source, target.cell, propagation.value);
      }

      if (!circled_values.empty()) {
        for (unsigned index = 0; index != quicken(1) * widths_count; ++index) {
          make_frame(propagate, {
            .possible = true,
            .bold_todo = true,
            .circled_cells = {propagation.source},
            .circled_cells_line_width = widths[index % widths_count],
            .circled_values = circled_values,
            .circled_values_line_width = widths[index % widths_count],
            .links_from_cell_to_value = links_from_cell_to_value,
            .links_from_cell_to_value_line_width = widths[index % widths_count],
          });
        }
      }

      for (const auto& target : propagation.targets) {
        stack.current().cell(target.cell).forbid(propagation.value);
      }

      if (!circled_values.empty()) {
        for (unsigned index = 0; index != quicken(4); ++index) {
          make_frame(propagate, {
            .possible = true,
            .bold_todo = true,
            .circled_cells = {propagation.source},
            .circled_values = circled_values,
            .links_from_cell_to_value = links_from_cell_to_value,
          });
        }

        for (unsigned index = 0; index != quicken(4); ++index) {
          make_frame(propagate, {
            .possible = true,
            .bold_todo = true,
            .circled_cells = {propagation.source},
          });
        }
      }
    }

    bool solved = false;
    for (const auto& target : propagation.targets) {
      for (const auto& deduction : target.single_value_deductions) {
        if (deduction.solved) {
          solved = true;
        }
      }
      for (const auto& deduction : target.single_place_deductions) {
        if (deduction.solved) {
          solved = true;
        }
      }
    }
    if (!solved) {
      stack.current().cell(propagation.source).set_propagated();
    }

    if (deductions_handled < quicken(4)) {
      for (const auto& target : propagation.targets) {
        for (const auto& deduction : target.single_value_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          ++deductions_handled;

          for (unsigned index = 0; index != quicken(6) * widths_count; ++index) {
            make_frame(propagate, {
              .possible = true,
              .bold_todo = true,
              .circled_cells = {deduction.cell},
              .circled_cells_line_width = widths[index % widths_count],
              .circled_cells_color = {0, 1, 0},
            });
          }
        }

        for (const auto& deduction : target.single_place_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          ++deductions_handled;

          for (unsigned index = 0; index != quicken(6) * widths_count; ++index) {
            make_frame(propagate, {
              .possible = true,
              .bold_todo = true,
              .boxed_cells = {deduction.cell},
              .boxed_cells_line_width = widths[index % widths_count],
              .boxed_cells_color = {0, 1, 0},
            });
          }
        }
      }
    } else {
      std::vector<Coordinates> circled_cells;
      for (const auto& target : propagation.targets) {
        for (const auto& deduction : target.single_value_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          ++deductions_handled;

          circled_cells.emplace_back(deduction.cell);
        }
      }
      if (!circled_cells.empty()) {
        for (unsigned index = 0; index != quicken(2) * widths_count; ++index) {
          make_frame(propagate, {
            .possible = true,
            .bold_todo = true,
            .circled_cells = circled_cells,
            .circled_cells_line_width = widths[index % widths_count],
            .circled_cells_color = {0, 1, 0},
          });
        }
      }

      std::vector<Coordinates> boxed_cells;
      for (const auto& target : propagation.targets) {
        for (const auto& deduction : target.single_place_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          ++deductions_handled;

          boxed_cells.emplace_back(deduction.cell);
        }
      }
      if (!boxed_cells.empty()) {
        for (unsigned index = 0; index != quicken(2) * widths_count; ++index) {
          make_frame(propagate, {
            .possible = true,
            .bold_todo = true,
            .boxed_cells = boxed_cells,
            .boxed_cells_line_width = widths[index % widths_count],
            .boxed_cells_color = {0, 1, 0},
          });
        }
      }
    }

    if (solved) {
      for (unsigned index = 0; index != quicken(75); ++index) {
        make_frame({.below = {{"Solved!", 20}}}, {});
      }
    }

    ++cell_propagations_handled;
  }

  void explain(const std::optional<typename Explanation<size>::Exploration>& exploration) {
    if (exploration.has_value()) {
      explain(*exploration);
    }
  }

  void explain(const typename Explanation<size>::Exploration& exploration) {
    for (const auto& hypothesis : exploration.explored_hypotheses) {
      stack.push();
      stack.current().cell(exploration.cell).set_hypothesis(hypothesis.value);

      explain(hypothesis.propagations);
      explain(hypothesis.exploration);

      stack.pop();
    }
  }

 private:
  unsigned quicken(unsigned n) {
    if (quick) {
      return 1;
    } else {
      return n;
    }
  }

 private:
  struct Text {
    std::string text;
    double font_size;
    enum { Normal, Bold } weight;
  };

  struct Layout {
    std::vector<Text> above = {};
    std::vector<Text> below = {};
  };

  void make_frame(const Layout& layout, art::DrawOptions draw_options) {
    auto surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, frame_width_pixels, frame_height_pixels);
    auto cr = Cairo::Context::create(surface);
    cr->set_source_rgb(1.0, 0.8, 0.8);
    cr->paint();
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
    cr->fill();
    cr->save();
    cr->translate(margin_pixels, margin_pixels);
    cr->set_source_rgb(0, 0, 0);

    const auto [grid_x, grid_y, grid_size] = draw_layout(cr, layout);
    cr->translate(grid_x, grid_y);
    draw_options.grid_size = grid_size;
    art::draw(cr, stack.current(), draw_options);

    cr->restore();
    // @todo Remove the margin visualisation
    cr->rectangle(0, 0, frame_width_pixels, frame_height_pixels);
    cr->rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(0.5, 0.5, 0.5, 0.5);
    cr->fill();

    serializer->serialize(surface);
  }

  void make_frame(
    const Layout& before,
    const Layout& after,
    const unsigned index,
    const unsigned duration,
    art::DrawOptions draw_options
  ) {
    auto surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, frame_width_pixels, frame_height_pixels);
    auto cr = Cairo::Context::create(surface);
    cr->set_source_rgb(1.0, 0.8, 0.8);
    cr->paint();
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
    cr->fill();
    cr->save();
    cr->translate(margin_pixels, margin_pixels);
    cr->set_source_rgb(0, 0, 0);

    const double ratio = (index + 1.) / (duration + 1);
    const auto [grid_x, grid_y, grid_size] = draw_layout_transition(cr, before, after, ratio);
    cr->translate(grid_x, grid_y);
    draw_options.grid_size = grid_size;
    art::draw(cr, stack.current(), draw_options);

    cr->restore();
    // @todo Remove the margin visualisation
    cr->rectangle(0, 0, frame_width_pixels, frame_height_pixels);
    cr->rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(0.5, 0.5, 0.5, 0.5);
    cr->fill();

    serializer->serialize(surface);
  }

 private:
  std::tuple<double, double, double> draw_layout(Cairo::RefPtr<Cairo::Context> cr, const Layout& layout) {
    Cairo::SaveGuard saver(cr);

    double above_height = 0;
    for (const auto& text : layout.above) {
      cr->set_font_size(text.font_size);
      switch (text.weight) {
        case Text::Normal:
          cr->select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
        case Text::Bold:
          cr->select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
      }
      Cairo::TextExtents extents;
      cr->get_text_extents(text.text, extents);
      cr->move_to(
        (viewport_width_pixels - extents.width) / 2 - extents.x_bearing,
        above_height - extents.y_bearing);
      cr->show_text(text.text);
      above_height += extents.height;
    }
    // assert(above_height == compute_text_height(layout.above));

    double below_height = 0;
    for (const auto& text : layout.below | std::views::reverse) {
      cr->set_font_size(text.font_size);
      switch (text.weight) {
        case Text::Normal:
          cr->select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
        case Text::Bold:
          cr->select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
      }
      Cairo::TextExtents extents;
      cr->get_text_extents(text.text, extents);
      below_height += extents.height;
      cr->move_to(
        (viewport_width_pixels - extents.width) / 2 - extents.x_bearing,
        viewport_height_pixels - below_height - extents.y_bearing);
      cr->show_text(text.text);
    }
    // assert(below_height == compute_text_height(layout.below));

    // Use integer to ensure no aliasing occurs on the grid
    const unsigned available_height = viewport_height_pixels - above_height - below_height;
    // @todo Use 'art::round_grid_size' instead of this custom code
    const unsigned grid_size =
      (available_height - thick_line_width) / size * size + thick_line_width;
    const unsigned grid_x = (viewport_width_pixels - grid_size) / 2;
    const unsigned grid_y = above_height + (available_height - grid_size) / 2;

    return std::make_tuple(grid_x, grid_y, grid_size);
  }

  std::tuple<double, double, double> draw_layout_transition(
    Cairo::RefPtr<Cairo::Context> cr,
    const Layout& before,
    const Layout& after,
    const double ratio
  ) {
    Cairo::SaveGuard saver(cr);

    const double above_height_before = compute_text_height(cr, before.above);
    const double below_height_before = compute_text_height(cr, before.below);
    const unsigned available_height_before = viewport_height_pixels - above_height_before - below_height_before;
    const unsigned grid_size_before =
      (available_height_before - thick_line_width) / size * size + thick_line_width;
    const double grid_x_before = (viewport_width_pixels - grid_size_before) / 2;
    const double grid_y_before = above_height_before + (available_height_before - grid_size_before) / 2;

    const double above_height_after = compute_text_height(cr, after.above);
    const double below_height_after = compute_text_height(cr, after.below);
    const unsigned available_height_after = viewport_height_pixels - above_height_after - below_height_after;
    const unsigned grid_size_after =
      (available_height_after - thick_line_width) / size * size + thick_line_width;
    const double grid_x_after = (viewport_width_pixels - grid_size_after) / 2;
    const double grid_y_after = above_height_after + (available_height_after - grid_size_after) / 2;

    const double grid_size = grid_size_before + ratio * (grid_size_after - grid_size_before);
    const double grid_x = grid_x_before + ratio * (grid_x_after - grid_x_before);
    const double grid_y = grid_y_before + ratio * (grid_y_after - grid_y_before);

    return std::make_tuple(grid_x, grid_y, grid_size);
  }

  double compute_text_height(Cairo::RefPtr<Cairo::Context> cr, const std::vector<Text>& texts) const {
    Cairo::SaveGuard saver(cr);

    double height = 0;

    for (const auto& text : texts) {
      cr->set_font_size(text.font_size);
      switch (text.weight) {
        case Text::Normal:
          cr->select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
        case Text::Bold:
          cr->select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
      }
      Cairo::TextExtents extents;
      cr->get_text_extents(text.text, extents);
      height += extents.height;
    }

    return height;
  }

 private:
  const Explanation<size>& explanation;
  video::Serializer* serializer;
  bool quick;
  unsigned frame_width_pixels;
  unsigned frame_height_pixels;
  unsigned viewport_height_pixels;
  unsigned viewport_width_pixels;
  Stack<size> stack;

 private:
  unsigned single_propagations_handled = 0;
  unsigned cell_propagations_handled = 0;
  unsigned deductions_handled = 0;
};

template<unsigned size>
void explain_as_video(
  const Explanation<size>& explanation,
  video::Serializer* serializer,
  bool quick,
  unsigned frame_width,
  unsigned frame_height
) {
  VideoExplainer<size>(explanation, serializer, quick, frame_width, frame_height).explain();
}

template void explain_as_video<4>(const Explanation<4>&, video::Serializer*, bool, unsigned, unsigned);
template void explain_as_video<9>(const Explanation<9>&, video::Serializer*, bool, unsigned, unsigned);
