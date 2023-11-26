// Copyright 2023 Vincent Jacques

#include "html-explainer.hpp"

#include <cairomm/cairomm.h>

#include <string>

#include <boost/format.hpp>


template<unsigned size>
void HtmlExplainer<size>::make_image(
  const std::string& name,
  art::DrawOptions draw_options,
  const MakeImageOptions& options
) const {
  #ifndef NDEBUG
  assert(generated_image_names.count(name) == 0);
  generated_image_names.insert(name);
  #endif

  auto surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, frame_width, frame_height);
  auto cr = Cairo::Context::create(surface);
  const unsigned margin = 10;
  const unsigned viewport_width = frame_width - 2 * margin;
  const unsigned viewport_height = frame_height - 2 * margin;

  cr->set_source_rgb(1, 1, 1);
  cr->paint();
  cr->save();
  cr->translate(margin, margin);

  const double grid_size = art::round_grid_size<size>(viewport_height);
  if (options.draw_stack && stack.height() > 1) {
    {
      Cairo::SaveGuard guard(cr);
      const double small_grid_size = art::round_grid_size<size>(viewport_width - grid_size - 3 * margin);
      for (const auto& saved : stack.saved()) {
        art::draw(cr, saved, {.grid_size = small_grid_size});
        cr->translate(0, small_grid_size + margin);
      }
    }
    cr->translate(
      (viewport_width - grid_size),
      (viewport_height - grid_size) / 2);
  } else {
    cr->translate(
      (viewport_width - grid_size) / 2,
      (viewport_height - grid_size) / 2);
  }
  draw_options.grid_size = grid_size;
  art::draw(cr, stack.current(), draw_options);

  cr->restore();
  // @todo Remove the margin visualisation
  cr->rectangle(0, 0, frame_width, frame_height);
  cr->rectangle(margin, margin, viewport_width, viewport_height);
  cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
  cr->set_source_rgba(1, 0.5, 0.5, 0.5);
  cr->fill();

  surface->write_to_png((directory_path / name).string());
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellIsSetInInput<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::InputsAreDone<size>& event) {
  event.apply(&stack);

  index_file << "<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n";
  index_file << "<h1>Input grid</h1>\n";
  make_image("input.png", {});
  index_file << "<p><img src=\"input.png\"/></p>\n";

  index_file << "<h1>Possible values</h1>\n";
  make_image("initial-possible.png", { .possible = true});
  index_file << "<p><img src=\"initial-possible.png\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationStartsForSudoku<size>& event) {
  event.apply(&stack);

  index_file << "<h1>Propagation</h1>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationStartsForCell<size>& event) {
  event.apply(&stack);

  const auto [row, col] = event.cell;
  index_file << "<h2>Propagation from (" << row + 1 << ", " << col + 1 << ")</h2>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellPropagates<size>& event) {
  event.apply(&stack);

  const auto [src_row, src_col] = event.source_cell;
  const auto [tgt_row, tgt_col] = event.target_cell;
  const std::string image_name =
    str(boost::format("propagation-%1%-%2%--%3%-%4%.png")
    % (src_row + 1) % (src_col + 1) % (tgt_row + 1) % (tgt_col + 1));
  make_image(
    image_name,
    {
      .possible = true,
      .bold_todo = true,
      .circled_cells = {event.source_cell},
      .circled_values = {{event.target_cell, event.value}},
      .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
    });
  index_file << "<p><img src=\"" << image_name << "\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationIsDoneForCell<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationIsDoneForSudoku<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::ExplorationStarts<size>& event) {
  event.apply(&stack);

  const auto [row, col] = event.cell;
  index_file << "<h1>Exploration for (" << row + 1 << ", " << col + 1 << ")</h1>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::HypothesisIsMade<size>& event) {
  event.apply(&stack);

  const auto [row, col] = event.cell;
  index_file << "<h2>Trying " << event.value + 1 << " for (" << row + 1 << ", " << col + 1 << ")</h2>\n";

  const std::string image_name =
    str(boost::format("exploration-%1%-%2%--%3%.png") % (row + 1) % (col + 1) % (event.value + 1));
  make_image(
    image_name,
    {
      .possible = true,
      .bold_todo = true,
      .circled_cells = {event.cell},
    });
  index_file << "<p><img src=\"" << image_name << "\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::HypothesisIsRejected<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::SudokuIsSolved<size>& event) {
  event.apply(&stack);

  index_file << "<h1>Solved grid</h1>\n";
  make_image("solved.png", {}, { .draw_stack = false });
  index_file << "<p><img src=\"solved.png\"/></p>\n";
  index_file << "</body></html>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::HypothesisIsAccepted<size>&) {}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::ExplorationIsDone<size>&) {}

template class HtmlExplainer<4>;
template class HtmlExplainer<9>;
