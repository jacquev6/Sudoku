// Copyright 2023 Vincent Jacques

#include "video-explainer.hpp"

#include <ranges>
#include <string>
#include <tuple>
#include <vector>

#include "art.hpp"
#include "video/frames-serializer.hpp"  // Only for tests

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


using std::literals::operator""s;


template<unsigned size>
class Animator {
  static constexpr unsigned margin_pixels = 10;
  static constexpr unsigned thick_line_width = 4;
  static constexpr unsigned thin_line_width = 2;
  static constexpr double widths[] = {2, 4, 5, 3, 2};
  static constexpr unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

 public:
  Animator(
    video::Serializer* serializer_,
    unsigned frame_width_,
    unsigned frame_height_
  ) :  // NOLINT(whitespace/parens)
    serializer(serializer_),
    frame_width_pixels(frame_width_),
    frame_height_pixels(frame_height_),
    viewport_height_pixels(frame_height_pixels - 2 * margin_pixels),
    viewport_width_pixels(frame_width_pixels - 2 * margin_pixels)
  {}

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

  // @todo Make these layouts 'static constexpr' members instead of methods
  // (This currently fails with a weird compile error, and I'm procrastinating investigation)
  Layout title() {
    return {
      .above = {
        Text{"How to solve this Sudoku?"s, 40, Text::Bold},
        Text{"An automated explanation by @jacquev6"s, 20},
        Text{"https://github.com/jacquev6/Sudoku"s, 20},
      }
    };
  }

  Layout propagate() { return {.below = {{"Propagate constraints", 20}}}; }

 public:
  void make_title_sequence(const AnnotatedSudoku<size>& state, const unsigned duration) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame(title(), state, {});
    }
  }

  void make_title_to_propagate_sequence(const AnnotatedSudoku<size>& state, const unsigned duration) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame(title(), propagate(), index, duration, state, {});
    }
  }

  void make_introduce_propagation_sequence(const AnnotatedSudoku<size>& state, const unsigned duration) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame(propagate(), state, {});
    }
  }

  void make_setup_propagation_sequence(const AnnotatedSudoku<size>& state, const unsigned duration) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame(propagate(), state, { .possible = true, .bold_todo = true });
    }
  }

  void make_start_cell_propagation_sequence(
    const AnnotatedSudoku<size>& state,
    const Coordinates& source,
    const unsigned duration
  ) {
    for (unsigned index = 0; index != duration * widths_count; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
          .circled_cells_line_width = widths[index % widths_count],
        });
    }
  }

  void make_propagate_cell_to_target_sequence(
    const AnnotatedSudoku<size>& state,
    const Coordinates& source,
    const Coordinates& target,
    const unsigned value,
    const unsigned duration
  ) {
    for (unsigned index = 0; index != duration * widths_count; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
          .circled_values = {{target, value}},
          .circled_values_line_width = widths[index % widths_count],
          .links_from_cell_to_value = {{source, target, value}},
          .links_from_cell_to_value_line_width = widths[index % widths_count],
        });
    }
  }

  void make_continue_cell_propagation_1_sequence(
    const AnnotatedSudoku<size>& state,
    const Coordinates& source,
    const unsigned duration
  ) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
        });
    }
  }

  void make_continue_cell_propagation_2_sequence(
    const AnnotatedSudoku<size>& state,
    const Coordinates& source,
    const Coordinates& target,
    const unsigned value,
    const unsigned duration
  ) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
          .circled_values = {{target, value}},
          .links_from_cell_to_value = {{source, target, value}},
        });
    }
  }

  void make_quick_propagation_sequence_begin(
    const AnnotatedSudoku<size>& state,
    const Coordinates& source,
    const std::vector<Coordinates>& targets,
    const unsigned value,
    const unsigned duration
  ) {
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    circled_values.reserve(targets.size());
    std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
    links_from_cell_to_value.reserve(targets.size());
    for (const auto& target : targets) {
      circled_values.emplace_back(target, value);
      links_from_cell_to_value.emplace_back(source, target, value);
    }

    for (unsigned index = 0; index != duration * widths_count; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
          .circled_cells_line_width = widths[index % widths_count],
          .circled_values = circled_values,
          .circled_values_line_width = widths[index % widths_count],
          .links_from_cell_to_value = links_from_cell_to_value,
          .links_from_cell_to_value_line_width = widths[index % widths_count],
        });
    }
  }

  void make_quick_propagation_sequence_end(
    const AnnotatedSudoku<size>& state,
    const Coordinates& source,
    const std::vector<Coordinates>& targets,
    const unsigned value,
    const unsigned duration
  ) {
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    circled_values.reserve(targets.size());
    std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
    links_from_cell_to_value.reserve(targets.size());
    for (const auto& target : targets) {
      circled_values.emplace_back(target, value);
      links_from_cell_to_value.emplace_back(source, target, value);
    }

    for (unsigned index = 0; index != duration; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
          .circled_values = circled_values,
          .links_from_cell_to_value = links_from_cell_to_value,
        });
    }

    for (unsigned index = 0; index != duration; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source},
        });
    }
  }

  void make_single_value_deduction_sequence(
    const AnnotatedSudoku<size>& state,
    const std::vector<Coordinates>& cells,
    const unsigned duration
  ) {
    for (unsigned index = 0; index != duration * widths_count; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = cells,
          .circled_cells_line_width = widths[index % widths_count],
          .circled_cells_color = {0, 1, 0},
        });
    }
  }

  void make_single_place_deduction_sequence(
    const AnnotatedSudoku<size>& state,
    const std::vector<Coordinates>& cells,
    const unsigned duration
  ) {
    for (unsigned index = 0; index != duration * widths_count; ++index) {
      make_frame(
        propagate(),
        state,
        {
          .possible = true,
          .bold_todo = true,
          .boxed_cells = cells,
          .boxed_cells_line_width = widths[index % widths_count],
          .boxed_cells_color = {0, 1, 0},
        });
    }
  }

  void make_solved_sequence(const AnnotatedSudoku<size>& state, const unsigned duration) {
    for (unsigned index = 0; index != duration; ++index) {
      make_frame({.below = {{"Solved!", 20}}}, state, {});
    }
  }

 private:
  void make_frame(const Layout& layout, const AnnotatedSudoku<size>& state, art::DrawOptions draw_options) {
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
    art::draw(cr, state, draw_options);

    cr->restore();
    // @todo Remove the margin visualisation
    cr->rectangle(0, 0, frame_width_pixels, frame_height_pixels);
    cr->rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(0.5, 0.5, 0.5, 0.5);
    cr->fill();

    serializer->serialize(surface);
  }

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

 private:
  void make_frame(
    const Layout& before,
    const Layout& after,
    const unsigned index,
    const unsigned duration,
    const AnnotatedSudoku<size>& state,
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
    art::draw(cr, state, draw_options);

    cr->restore();
    // @todo Remove the margin visualisation
    cr->rectangle(0, 0, frame_width_pixels, frame_height_pixels);
    cr->rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(0.5, 0.5, 0.5, 0.5);
    cr->fill();

    serializer->serialize(surface);
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
  video::Serializer* const serializer;
  const unsigned frame_width_pixels;
  const unsigned frame_height_pixels;
  const unsigned viewport_height_pixels;
  const unsigned viewport_width_pixels;
};


// LCOV_EXCL_START

// These tests must be validated visually e.g. using 'git diff-image tests/unit' before commit
TEST_CASE("Animator::make_title_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "010-title-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_title_sequence(state, 1);
}

TEST_CASE("Animator::make_title_to_propagate_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "020-title_to_propagate-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_title_to_propagate_sequence(state, 4);
}

TEST_CASE("Animator::make_introduce_propagation_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "030-introduce_propagation-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_introduce_propagation_sequence(state, 1);
}

TEST_CASE("Animator::make_setup_propagation_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "040-setup_propagation-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_setup_propagation_sequence(state, 1);
}

TEST_CASE("Animator::make_start_cell_propagation_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "050-start_cell_propagation-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_start_cell_propagation_sequence(state, {0, 0}, 1);
}

TEST_CASE("Animator::make_propagate_cell_to_target_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "060-propagate_cell_to_target-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_propagate_cell_to_target_sequence(state, {0, 0}, {1, 0}, 0, 1);
}

TEST_CASE("Animator::make_continue_cell_propagation_1_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "070-continue_cell_propagation_1-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  state.cell({1, 0}).forbid(0);
  Animator<4>(&serializer, 640, 480).make_continue_cell_propagation_1_sequence(state, {0, 0}, 1);
}

TEST_CASE("Animator::make_continue_cell_propagation_2_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "080-continue_cell_propagation_2-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({0, 1}).set_input(1);
  state.cell({0, 2}).set_input(2);
  state.cell({0, 3}).set_input(3);
  state.cell({1, 0}).forbid(0);
  Animator<4>(&serializer, 640, 480).make_continue_cell_propagation_2_sequence(state, {0, 0}, {1, 0}, 0, 1);
}

TEST_CASE("Animator::make_quick_propagation_sequence_begin") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "090-quick_propagation_begin-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({1, 0}).set_input(1);
  state.cell({2, 0}).set_input(2);
  state.cell({3, 0}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_quick_propagation_sequence_begin(
    state, {0, 0}, {{0, 1}, {0, 2}, {0, 3}}, 0, 1);
}

TEST_CASE("Animator::make_quick_propagation_sequence_end") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "100-quick_propagation_end-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({1, 0}).set_input(1);
  state.cell({2, 0}).set_input(2);
  state.cell({3, 0}).set_input(3);
  state.cell({0, 1}).forbid(0);
  state.cell({0, 2}).forbid(0);
  state.cell({0, 3}).forbid(0);
  Animator<4>(&serializer, 640, 480).make_quick_propagation_sequence_end(state, {0, 0}, {{0, 1}, {0, 2}, {0, 3}}, 0, 1);
}

TEST_CASE("Animator::make_single_value_deduction_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "110-single_value_deduction-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({1, 0}).set_input(1);
  state.cell({2, 0}).set_input(2);
  state.cell({3, 0}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_single_value_deduction_sequence(state, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 1);
}

TEST_CASE("Animator::make_single_place_deduction_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "120-single_place_deduction-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({1, 0}).set_input(1);
  state.cell({2, 0}).set_input(2);
  state.cell({3, 0}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_single_place_deduction_sequence(state, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 1);
}

TEST_CASE("Animator::make_solved_sequence") {
  video::FramesSerializer serializer("tests/unit/explanation/video-explainer", "130-solved-");
  AnnotatedSudoku<4> state;
  state.cell({0, 0}).set_input(0);
  state.cell({1, 0}).set_input(1);
  state.cell({2, 0}).set_input(2);
  state.cell({3, 0}).set_input(3);
  Animator<4>(&serializer, 640, 480).make_solved_sequence(state, 1);
}

// LCOV_EXCL_STOP


template<unsigned size>
class VideoExplainer {
 public:
  VideoExplainer(
    const Explanation<size>& explanation_,
    video::Serializer* serializer_,
    bool quick_,
    unsigned frame_width_,
    unsigned frame_height_
  ) :  // NOLINT(whitespace/parens)
    explanation(explanation_),
    animator(serializer_, frame_width_, frame_height_),
    quick(quick_),
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

    animator.make_title_sequence(stack.current(), quicken(75));
    animator.make_title_to_propagate_sequence(stack.current(), quicken(12));
    animator.make_introduce_propagation_sequence(stack.current(), quicken(12));
    animator.make_setup_propagation_sequence(stack.current(), quicken(12));

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
    if (cell_propagations_handled < quicken(3)) {
      animator.make_start_cell_propagation_sequence(stack.current(), propagation.source, quicken(3));

      for (const auto& target : propagation.targets) {
        if (single_propagations_handled < quicken(6)) {
          animator.make_propagate_cell_to_target_sequence(
            stack.current(),
            propagation.source,
            target.cell,
            propagation.value,
            quicken(3));

          stack.current().cell(target.cell).forbid(propagation.value);

          animator.make_continue_cell_propagation_1_sequence(stack.current(), propagation.source, quicken(6));
        } else {
          animator.make_propagate_cell_to_target_sequence(
            stack.current(),
            propagation.source,
            target.cell,
            propagation.value,
            quicken(1));

          stack.current().cell(target.cell).forbid(propagation.value);

          animator.make_continue_cell_propagation_2_sequence(
            stack.current(),
            propagation.source,
            target.cell,
            propagation.value,
            quicken(4));
        }

        ++single_propagations_handled;
      }
    } else {
      if (!propagation.targets.empty()) {
        std::vector<Coordinates> targets;
        targets.reserve(propagation.targets.size());
        for (const auto& target : propagation.targets) {
          targets.emplace_back(target.cell);
        }

        animator.make_quick_propagation_sequence_begin(
          stack.current(),
          propagation.source,
          targets,
          propagation.value,
          quicken(1));

        for (const auto& target : propagation.targets) {
          stack.current().cell(target.cell).forbid(propagation.value);
        }

        animator.make_quick_propagation_sequence_end(
          stack.current(),
          propagation.source,
          targets,
          propagation.value,
          quicken(4));
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
          animator.make_single_value_deduction_sequence(stack.current(), {deduction.cell}, quicken(6));
        }

        for (const auto& deduction : target.single_place_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          ++deductions_handled;
          animator.make_single_place_deduction_sequence(stack.current(), {deduction.cell}, quicken(6));
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
        animator.make_single_value_deduction_sequence(stack.current(), circled_cells, quicken(2));
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
        animator.make_single_place_deduction_sequence(stack.current(), boxed_cells, quicken(2));
      }
    }

    if (solved) {
      animator.make_solved_sequence(stack.current(), quicken(75));
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
  const Explanation<size>& explanation;
  Animator<size> animator;
  bool quick;
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
