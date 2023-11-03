// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_VIDEO_EXPLAINER_HPP_
#define EXPLANATION_VIDEO_VIDEO_EXPLAINER_HPP_

#include <cairomm/cairomm.h>

#include <filesystem>
#include <iomanip>
#include <ranges>  // NOLINT(build/include_order)
#include <string>
#include <tuple>
#include <vector>

#include "../../exploration/events.hpp"
#include "../follower.hpp"
#include "video-serializer.hpp"


// Like Cairo::SaveGuard
class CairoSaveGuard {
 public:
  explicit CairoSaveGuard(Cairo::Context& cr_) : cr(cr_) { cr.save(); }
  ~CairoSaveGuard() { cr.restore(); }

 private:
  Cairo::Context& cr;
};


class VideoExplainer : public exploration::EventVisitor {
  // Keep consistent with 'VideoVideoSerializer'
  static constexpr unsigned frame_width_pixels = 640;
  static constexpr unsigned frame_height_pixels = 480;
  static constexpr unsigned margin_pixels = 10;
  static constexpr unsigned viewport_height_pixels = frame_height_pixels - 2 * margin_pixels;
  static constexpr unsigned viewport_width_pixels = frame_width_pixels - 2 * margin_pixels;
  static constexpr unsigned thick_line_width = 4;
  static constexpr unsigned thin_line_width = 2;

 public:
  VideoExplainer(VideoSerializer* video_serializer_, exploration::EventVisitor* printer_, const bool quick_) :
    before(),
    after(),
    surface(Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, frame_width_pixels, frame_height_pixels)),
    context(Cairo::Context::create(surface)),
    cr(*context),
    video_serializer(video_serializer_),
    printer(printer_),
    quick(quick_)
  {}

 private:
  class VisitEventsGuard {
   public:
    VisitEventsGuard(VideoExplainer* explainer_, const exploration::Event& event) :
      explainer(*explainer_),
      events(),
      before(explainer.before),
      after(explainer.after)
    {  // NOLINT(whitespace/braces)
      event.accept(explainer.after);
      event.accept(*explainer.printer);
      events.push_back(&event);
    }

    template<typename T>
    VisitEventsGuard(VideoExplainer* explainer_, const std::vector<T>& events_) :
      explainer(*explainer_),
      events(),
      before(explainer.before),
      after(explainer.after)
    {  // NOLINT(whitespace/braces)
      for (const T& event : events_) {
        event.accept(explainer.after);
        event.accept(*explainer.printer);
        events.push_back(static_cast<const exploration::Event*>(&event));
      }
    }

    VisitEventsGuard(const VisitEventsGuard&) = delete;
    VisitEventsGuard& operator=(const VisitEventsGuard&) = delete;
    VisitEventsGuard(VisitEventsGuard&&) = delete;
    VisitEventsGuard& operator=(VisitEventsGuard&&) = delete;

    ~VisitEventsGuard() {
      for (const exploration::Event* const event : events) {
        event->accept(explainer.before);
      }
    }

   private:
    VideoExplainer& explainer;
    std::vector<const exploration::Event*> events;

   public:
    const Follower& before;
    const Follower& after;
  };

  class FrameGuard {
   public:
    explicit FrameGuard(VideoExplainer* explainer_) : explainer(*explainer_), cr(explainer.cr) {
      {
        CairoSaveGuard saver(cr);

        cr.set_source_rgb(1.0, 0.8, 0.8);
        cr.paint();
        cr.set_source_rgb(1.0, 1.0, 1.0);
        cr.rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
        cr.fill();
      }

      cr.save();
      cr.translate(margin_pixels, margin_pixels);
    }

    FrameGuard(const FrameGuard&) = delete;
    FrameGuard& operator=(const FrameGuard&) = delete;
    FrameGuard(FrameGuard&&) = delete;
    FrameGuard& operator=(FrameGuard&&) = delete;

    ~FrameGuard() {
      cr.restore();

      CairoSaveGuard saver(cr);
      cr.rectangle(0, 0, frame_width_pixels, frame_height_pixels);
      cr.rectangle(margin_pixels, margin_pixels, viewport_width_pixels, viewport_height_pixels);
      cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      cr.fill();

      explainer.video_serializer->serialize(explainer.surface);
    }

   private:
    VideoExplainer& explainer;
    Cairo::Context& cr;
  };

  struct Text {
    std::string text;
    double font_size;
    enum { Normal, Bold } weight;
  };

  struct Layout {
    std::vector<Text> above = {};
    std::vector<Text> below = {};
  };

 private:
  unsigned quicken(unsigned n) {
    if (quick) {
      return 1;
    } else {
      return n;
    }
  }

 private:
  void visit(const exploration::CellIsSetInInput&) override;
  void visit(const exploration::InputsAreDone&) override;
  void visit(const exploration::PropagationStartsForSudoku&) override;
  void visit(const exploration::PropagationStartsForCell&) override;
  void visit(const exploration::CellPropagates&) override;
  void visit(const exploration::CellIsDeducedFromSingleAllowedValue&) override;
  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion&) override;
  void visit(const exploration::PropagationIsDoneForCell&) override;
  void visit(const exploration::PropagationIsDoneForSudoku&) override;
  void visit(const exploration::ExplorationStarts&) override;
  void visit(const exploration::HypothesisIsMade&) override;
  void visit(const exploration::HypothesisIsRejected&) override;
  void visit(const exploration::SudokuIsSolved&) override;
  void visit(const exploration::HypothesisIsAccepted&) override;
  void visit(const exploration::ExplorationIsDone&) override;

  void flush_pending_cell_propagates_events();
  void flush_pending_cell_is_deduced_from_single_allowed_value_events();
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  void flush_pending_events();

 private:
  std::tuple<double, double, double> draw_layout(const Layout& layout) {
    CairoSaveGuard saver(cr);

    double above_height = 0;
    for (const auto& text : layout.above) {
      cr.set_font_size(text.font_size);
      switch (text.weight) {
        case Text::Normal:
          cr.select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
        case Text::Bold:
          cr.select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
      }
      Cairo::TextExtents extents;
      cr.get_text_extents(text.text, extents);
      cr.move_to(
        (viewport_width_pixels - extents.width) / 2 - extents.x_bearing,
        above_height - extents.y_bearing);
      cr.show_text(text.text);
      above_height += extents.height;
    }
    // assert(above_height == compute_text_height(layout.above));

    double below_height = 0;
    for (const auto& text : layout.below | std::views::reverse) {
      cr.set_font_size(text.font_size);
      switch (text.weight) {
        case Text::Normal:
          cr.select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
        case Text::Bold:
          cr.select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
      }
      Cairo::TextExtents extents;
      cr.get_text_extents(text.text, extents);
      below_height += extents.height;
      cr.move_to(
        (viewport_width_pixels - extents.width) / 2 - extents.x_bearing,
        viewport_height_pixels - below_height - extents.y_bearing);
      cr.show_text(text.text);
    }
    // assert(below_height == compute_text_height(layout.below));

    // Use integer to ensure no aliasing occurs on the grid
    const unsigned available_height = viewport_height_pixels - above_height - below_height;
    const unsigned grid_size = (available_height - thick_line_width) / Sudoku::size * Sudoku::size + thick_line_width;
    const unsigned grid_x = (viewport_width_pixels - grid_size) / 2;
    const unsigned grid_y = above_height + (available_height - grid_size) / 2;

    return std::make_tuple(grid_x, grid_y, grid_size);
  }

  std::tuple<double, double, double> draw_layout_transition(
    const Layout& before,
    const Layout& after,
    const double ratio
  ) {
    CairoSaveGuard saver(cr);

    const double above_height_before = compute_text_height(before.above);
    const double below_height_before = compute_text_height(before.below);
    const unsigned available_height_before = viewport_height_pixels - above_height_before - below_height_before;
    const unsigned grid_size_before =
      (available_height_before - thick_line_width) / Sudoku::size * Sudoku::size + thick_line_width;
    const double grid_x_before = (viewport_width_pixels - grid_size_before) / 2;
    const double grid_y_before = above_height_before + (available_height_before - grid_size_before) / 2;

    const double above_height_after = compute_text_height(after.above);
    const double below_height_after = compute_text_height(after.below);
    const unsigned available_height_after = viewport_height_pixels - above_height_after - below_height_after;
    const unsigned grid_size_after =
      (available_height_after - thick_line_width) / Sudoku::size * Sudoku::size + thick_line_width;
    const double grid_x_after = (viewport_width_pixels - grid_size_after) / 2;
    const double grid_y_after = above_height_after + (available_height_after - grid_size_after) / 2;

    const double grid_size = grid_size_before + ratio * (grid_size_after - grid_size_before);
    const double grid_x = grid_x_before + ratio * (grid_x_after - grid_x_before);
    const double grid_y = grid_y_before + ratio * (grid_y_after - grid_y_before);

    return std::make_tuple(grid_x, grid_y, grid_size);
  }

  double compute_text_height(const std::vector<Text>& texts) const {
    CairoSaveGuard saver(cr);

    double height = 0;

    for (const auto& text : texts) {
      cr.set_font_size(text.font_size);
      switch (text.weight) {
        case Text::Normal:
          cr.select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
        case Text::Bold:
          cr.select_font_face("sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
      }
      Cairo::TextExtents extents;
      cr.get_text_extents(text.text, extents);
      height += extents.height;
    }

    return height;
  }

 private:
  Follower before;
  Follower after;
  Cairo::RefPtr<Cairo::ImageSurface> surface;
  Cairo::RefPtr<Cairo::Context> context;
  Cairo::Context& cr;
  VideoSerializer* video_serializer;
  exploration::EventVisitor* printer;
  const bool quick;

 private:
  unsigned single_propagations_handled = 0;
  unsigned cell_propagations_handled = 0;
  unsigned deductions_handled = 0;
  std::vector<exploration::CellPropagates> pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue>
    pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion>
    pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};

#endif  // EXPLANATION_VIDEO_VIDEO_EXPLAINER_HPP_
