// Copyright 2023 Vincent Jacques

#include "html-explainer.hpp"

#include <cairomm/cairomm.h>

#include <string>

#include <boost/format.hpp>

#include "art.hpp"


struct Image {
  static constexpr unsigned frame_width = 480;
  static constexpr unsigned frame_height = 320;
  static constexpr unsigned margin = 10;
  static constexpr unsigned viewport_width = frame_width - 2 * margin;
  static constexpr unsigned viewport_height = frame_height - 2 * margin;

  explicit Image(const std::filesystem::path& path_) :
    path(path_),
    surface(Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, frame_width, frame_height)),
    cr(Cairo::Context::create(surface))
  {  // NOLINT(whitespace/braces)
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr->save();
    cr->translate(margin, margin);
  }

  ~Image() {
    cr->restore();
    // @todo Remove the margin visualisation
    cr->rectangle(0, 0, frame_width, frame_height);
    cr->rectangle(margin, margin, viewport_width, viewport_height);
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(1, 0.5, 0.5, 0.5);
    cr->fill();

    surface->write_to_png(path.string());
  }

 private:
  std::filesystem::path path;
  Cairo::RefPtr<Cairo::ImageSurface> surface;

 public:
  Cairo::RefPtr<Cairo::Context> cr;
};


template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::CellIsSetInInput<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::InputsAreDone<size>& event) {
  event.apply(&stack);

  index_file << "<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n";
  index_file << "<h1>Input grid</h1>\n";
  Image input(directory_path / "input.png");
  const double grid_size = art::round_grid_size<size>(input.viewport_height);
  input.cr->translate((input.viewport_width - grid_size) / 2, (input.viewport_height - grid_size) / 2);
  art::draw(input.cr, current(), {.grid_size = grid_size});
  index_file << "<p><img src=\"input.png\"/></p>\n";

  index_file << "<h1>Possible values</h1>\n";
  Image possible(directory_path / "initial-possible.png");
  possible.cr->translate((possible.viewport_width - grid_size) / 2, (possible.viewport_height - grid_size) / 2);
  art::draw(possible.cr, current(), {.grid_size = grid_size, .possible = true});
  index_file << "<p><img src=\"initial-possible.png\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::PropagationStartsForSudoku<size>& event) {
  index_file << "<h1>Propagation</h1>\n";

  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::PropagationStartsForCell<size>& event) {
  const auto [row, col] = event.cell;
  index_file << "<h2>Propagation from (" << row << ", " << col << ")</h2>\n";

  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::CellPropagates<size>& event) {
  event.apply(&stack);

  const auto [src_row, src_col] = event.source_cell;
  const auto [tgt_row, tgt_col] = event.target_cell;
  const std::string image_name =
    str(boost::format("propagation-%1%-%2%--%3%-%4%.png") % src_row % src_col % tgt_row % tgt_col);
  Image propagation(directory_path / image_name);
  const double grid_size = art::round_grid_size<size>(propagation.viewport_height);
  propagation.cr->translate(
    (propagation.viewport_width - grid_size) / 2,
    (propagation.viewport_height - grid_size) / 2);
  art::draw(
    propagation.cr,
    current(),
    {
      .grid_size = grid_size,
      .possible = true,
      .bold_todo = true,
      .circled_cells = {event.source_cell},
      .circled_values = {{event.target_cell, event.value}},
      .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
    });
  index_file << "<p><img src=\"" << image_name << "\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::PropagationIsDoneForCell<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::PropagationIsDoneForSudoku<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::ExplorationStarts<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::HypothesisIsMade<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::HypothesisIsRejected<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::SudokuIsSolved<size>& event) {
  event.apply(&stack);

  index_file << "<h1>Solved grid</h1>\n";
  Image solved(directory_path / "solved.png");
  const double grid_size = art::round_grid_size<size>(solved.viewport_height);
  solved.cr->translate((solved.viewport_width - grid_size) / 2, (solved.viewport_height - grid_size) / 2);
  art::draw(
    solved.cr,
    current(),
    {
      .grid_size = grid_size,
    });
  index_file << "<p><img src=\"solved.png\"/></p>\n";
  index_file << "</body></html>\n";
}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::HypothesisIsAccepted<size>& event) {}

template<unsigned size>
void HtmlExplainer<size>::visit(const exploration::ExplorationIsDone<size>& event) {}

template class HtmlExplainer<9>;
