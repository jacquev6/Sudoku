// Copyright 2023 Vincent Jacques

#include "art.hpp"

#include <filesystem>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../puzzle/sudoku-alphabet.hpp"

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


namespace art {

constexpr unsigned thick_line_width = 4;
constexpr unsigned thin_line_width = 2;

template<unsigned size>
double round_grid_size(unsigned available_size) {
  return (available_size - thick_line_width) / size * size + thick_line_width;
}

template<unsigned size>
void draw(Cairo::RefPtr<Cairo::Context> cr, const ExplainableSudoku<size>& sudoku, const DrawOptions& options) {
  Cairo::SaveGuard saver(cr);

  cr->translate(thick_line_width / 2, thick_line_width / 2);

  const double cell_size = (options.grid_size - thick_line_width) / size;
  const double cell_interior_size = cell_size - thick_line_width;

  const auto cell_center = [cell_size](const Coordinates& cell) {
    const auto [row, col] = cell;
    return std::make_pair((col + 0.5) * cell_size, (row + 0.5) * cell_size);
  };

  const auto value_center = [cell_size](const Coordinates& cell, unsigned value) {
    const auto [row, col] = cell;
    const unsigned value_x = value % SudokuConstants<size>::sqrt_size;
    const unsigned value_y = value / SudokuConstants<size>::sqrt_size;
    return std::make_pair(
      col * cell_size + (value_x + 0.5) * cell_size / SudokuConstants<size>::sqrt_size,
      row * cell_size + (value_y + 0.5) * cell_size / SudokuConstants<size>::sqrt_size);
  };

  // Known values
  cr->set_font_size(3 * cell_interior_size / 4);
  cr->set_source_rgb(0.0, 0.0, 0.0);
  for (const auto& cell : sudoku.cells()) {
    if (cell.is_set()) {
      const std::string text(1, SudokuAlphabet<size>::get_symbol(cell.get()));

      if (options.bold_todo && !cell.is_propagated()) {
        cr->select_font_face("sans-serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
      } else {
        cr->select_font_face("sans-serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      }

      if (options.inputs && cell.is_input()) {
        Cairo::SaveGuard saver(cr);

        const auto [x, y] = cell_center(cell.coordinates());
        cr->rectangle(x - cell_size / 2, y - cell_size / 2, cell_size, cell_size);
        cr->set_source_rgb(0.85, 0.85, 0.85);
        cr->fill();
      } else if (options.hypotheses && cell.is_hypothesis()) {
        Cairo::SaveGuard saver(cr);

        const auto [x, y] = cell_center(cell.coordinates());
        cr->rectangle(x - cell_size / 2, y - cell_size / 2, cell_size, cell_size);
        cr->set_source_rgb(0.85, 0.85, 1);
        cr->fill();
      }

      Cairo::TextExtents extents;
      cr->get_text_extents(text, extents);
      {
        const auto [x, y] = cell_center(cell.coordinates());
        cr->move_to(x - extents.width / 2 - extents.x_bearing, y - extents.height / 2 - extents.y_bearing);
      }
      cr->show_text(text);
    }
  }

  // Possible values
  if (options.possible) {
    cr->set_font_size(cell_interior_size / 4);
    cr->select_font_face("sans-serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);

    for (const auto& cell : sudoku.cells()) {
      if (!cell.is_set()) {
        assert(!cell.is_propagated());

        for (unsigned value : SudokuConstants<size>::values) {
          Cairo::SaveGuard saver(cr);

          const std::string text(1, SudokuAlphabet<size>::get_symbol(value));
          Cairo::TextExtents extents;
          cr->get_text_extents(text, extents);
          {
            const auto [x, y] = value_center(cell.coordinates(), value);
            cr->move_to(x - extents.width / 2 - extents.x_bearing, y - extents.height / 2 - extents.y_bearing);
          }
          if (cell.is_allowed(value)) {
            cr->set_source_rgb(0.0, 0.0, 0.0);
          } else {
            cr->set_source_rgb(0.8, 0.8, 0.8);
          }
          cr->show_text(text);
        }
      }
    }
  }

  // Grid
  cr->set_source_rgb(0.0, 0.0, 0.0);
  cr->set_line_cap(Cairo::Context::LineCap::SQUARE);
  const double line_widths[] = {thin_line_width, thick_line_width};
  const unsigned strides[] = {1, SudokuConstants<size>::sqrt_size};
  for (unsigned k : {0, 1}) {
    for (unsigned i = 0; i <= size; i += strides[k]) {
      cr->move_to(i * cell_size, 0);
      cr->line_to(i * cell_size, options.grid_size - thick_line_width);
      cr->move_to(0, i * cell_size);
      cr->line_to(options.grid_size - thick_line_width, i * cell_size);
    }

    cr->set_line_width(line_widths[k]);
    cr->stroke();
  }

  // Circled cells
  for (const auto& cell : options.circled_cells) {
    cr->begin_new_sub_path();
    const auto [x, y] = cell_center(cell);
    cr->arc(x, y, 0.8 * cell_size / 2, 0, 2 * M_PI);
  }
  {
    const auto [r, g, b] = options.circled_cells_color;
    cr->set_source_rgb(r, g, b);
  }
  cr->set_line_width(options.circled_cells_line_width);
  cr->stroke();

  // Boxed cells
  for (const auto& cell : options.boxed_cells) {
    const auto [x, y] = cell_center(cell);
    cr->rectangle(x - 0.8 * cell_size / 2, y - 0.8 * cell_size / 2, 0.8 * cell_size, 0.8 * cell_size);
  }
  {
    const auto [r, g, b] = options.boxed_cells_color;
    cr->set_source_rgb(r, g, b);
  }
  cr->set_line_width(options.boxed_cells_line_width);
  cr->stroke();

  // Circled values
  for (const auto& [cell, value] : options.circled_values) {
    cr->begin_new_sub_path();
    const auto [x, y] = value_center(cell, value);
    cr->arc(x, y, 0.8 * 0.5 * cell_size / SudokuConstants<size>::sqrt_size, 0, 2 * M_PI);
  }
  {
    const auto& [r, g, b] = options.circled_values_color;
    cr->set_source_rgb(r, g, b);
  }
  cr->set_line_width(options.circled_values_line_width);
  cr->stroke();

  // Links from cell to value
  {
    // @todo Should we clip the entire thing before drawing all the links?
    // (This changes the image by removing parts of the links that get in front of circles values)
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    {
      const auto [r, g, b] = options.links_from_cell_to_value_color;
      cr->set_source_rgb(r, g, b);
    }
    cr->set_line_width(options.links_from_cell_to_value_line_width);

    for (const auto& [source_cell, target_cell, value] : options.links_from_cell_to_value) {
      Cairo::SaveGuard saver(cr);

      const auto [x1, y1] = cell_center(source_cell);
      const auto [x2, y2] = value_center(target_cell, value);

      cr->rectangle(0, 0, options.grid_size, options.grid_size);
      {
        cr->begin_new_sub_path();
        cr->arc(x1, y1, 0.8 * cell_size / 2, 0, 2 * M_PI);
      }
      {
        cr->begin_new_sub_path();
        cr->arc(x2, y2, 0.8 * 0.5 * cell_size / SudokuConstants<size>::sqrt_size, 0, 2 * M_PI);
      }
      cr->clip();

      cr->move_to(x1, y1);
      cr->line_to(x2, y2);
      cr->stroke();
    }
  }
}

template double round_grid_size<4>(unsigned available_size);
template double round_grid_size<9>(unsigned available_size);
template double round_grid_size<16>(unsigned available_size);
template double round_grid_size<25>(unsigned available_size);

template void draw(Cairo::RefPtr<Cairo::Context> cr, const ExplainableSudoku<4>& sudoku, const DrawOptions& options);
template void draw(Cairo::RefPtr<Cairo::Context> cr, const ExplainableSudoku<9>& sudoku, const DrawOptions& options);
template void draw(Cairo::RefPtr<Cairo::Context> cr, const ExplainableSudoku<16>& sudoku, const DrawOptions& options);
template void draw(Cairo::RefPtr<Cairo::Context> cr, const ExplainableSudoku<25>& sudoku, const DrawOptions& options);


// LCOV_EXCL_START

template<unsigned cols, unsigned rows>
struct TestImage {
  static constexpr unsigned margin = 10;

  explicit TestImage(std::filesystem::path path_, unsigned frame_width_ = 300, unsigned frame_height_ = 300) :
    path(path_),
    frame_width(frame_width_),
    frame_height(frame_height_),
    viewport_width(frame_width - 2 * margin),
    viewport_height(frame_height - 2 * margin),
    surface(Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, cols * frame_width, rows * frame_height)),
    crs()
  {  // NOLINT(whitespace/braces)
    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
    cr->set_source_rgb(1, 1, 1);
    cr->paint();

    for (unsigned col = 0; col != cols; ++col) {
      for (unsigned row = 0; row != rows; ++row) {
        crs[col][row] = Cairo::Context::create(surface);
        crs[col][row]->translate(col * frame_width, row * frame_height);
        crs[col][row]->save();
        crs[col][row]->translate(margin, margin);
      }
    }
  }

  ~TestImage() {
    for (unsigned col = 0; col != cols; ++col) {
      for (unsigned row = 0; row != rows; ++row) {
        crs[col][row]->restore();
        crs[col][row]->rectangle(0, 0, frame_width, frame_height);
        crs[col][row]->rectangle(margin, margin, viewport_width, viewport_height);
        crs[col][row]->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
        crs[col][row]->set_source_rgba(1, 0, 0, 0.5);
        crs[col][row]->fill();
      }
    }

    surface->write_to_png(path.string());
  }

  std::filesystem::path path;
  unsigned frame_width;
  unsigned frame_height;
  unsigned viewport_width;
  unsigned viewport_height;
  Cairo::RefPtr<Cairo::ImageSurface> surface;
  std::array<std::array<Cairo::RefPtr<Cairo::Context>, rows>, cols> crs;
};

// These tests must be validated visually e.g. using 'git diff-image tests/unit' before commit
TEST_CASE("draw - grid") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-grid.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_height);
    image.crs[0][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    draw(image.crs[0][0], ExplainableSudoku<4>(), { .grid_size = grid_size });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_height);
    image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    draw(image.crs[1][0], ExplainableSudoku<9>(), { .grid_size = grid_size });
  }
}

TEST_CASE("draw - grid - multiple sizes") {
  // This test shows a few defects:
  // - for some sizes, the centering of the grid causes a half pixel shift, and the grid lines are not sharp
  // - for small sizes, the fixed line width is too big
  // - for large sizes, the fixed line width is too small
  std::array<std::array<unsigned, 3>, 2> frame_sizes = {{{{100, 140, 200}}, {{280, 400, 560}}}};

  TestImage<3, 2> image(
    "tests/unit/explanation/art/draw-grid-multiple-sizes.png", 580, 580);
  for (unsigned col = 0; col != 3; ++col) {
    for (unsigned row = 0; row != 2; ++row) {
      const unsigned frame_size = frame_sizes[row][col];
      const double grid_size = round_grid_size<9>(frame_size);
      image.crs[col][row]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
      draw(image.crs[col][row], ExplainableSudoku<9>(), { .grid_size = grid_size });
    }
  }
}

TEST_CASE("draw - known-values circled") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-known-values-circled.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_height);
    image.crs[0][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    ExplainableSudoku<4> sudoku;
    for (auto& cell : sudoku.cells()) {
      const auto [row, col] = cell.coordinates();
      cell.set_deduced((row + 2 * col) % 4);
    }
    draw(
      image.crs[0][0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_cells = {SudokuConstants<4>::cells.begin(), SudokuConstants<4>::cells.end()},
      });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_height);
    image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    ExplainableSudoku<9> sudoku;
    for (auto& cell : sudoku.cells()) {
      const auto [row, col] = cell.coordinates();
      cell.set_deduced((row + 2 * col) % 9);
    }
    draw(
      image.crs[1][0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_cells = {SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end()},
      });
  }
}

TEST_CASE("draw - all inputs") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-all-inputs.png");
  const double grid_size = round_grid_size<9>(image.viewport_height);
  image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
  ExplainableSudoku<9> sudoku;
  for (auto& cell : sudoku.cells()) {
    const auto [row, col] = cell.coordinates();
    cell.set_input((row + 2 * col) % 9);
  }
  draw(
    image.crs[1][0],
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
    });
}

TEST_CASE("draw - all todo") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-all-todo.png");
  const double grid_size = round_grid_size<9>(image.viewport_height);
  image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
  ExplainableSudoku<9> sudoku;
  for (auto& cell : sudoku.cells()) {
    const auto [row, col] = cell.coordinates();
    cell.set_deduced((row + 2 * col) % 9);
  }
  draw(
    image.crs[1][0],
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
      .bold_todo = true,
    });
}

TEST_CASE("draw - all processed") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-all-processed.png");
  const double grid_size = round_grid_size<9>(image.viewport_height);
  image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
  ExplainableSudoku<9> sudoku;
  for (auto& cell : sudoku.cells()) {
    const auto [row, col] = cell.coordinates();
    cell.set_deduced((row + 2 * col) % 9);
    cell.set_propagated();
  }
  draw(
    image.crs[1][0],
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
      .bold_todo = true,
    });
}

TEST_CASE("draw - known-values boxed") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-known-values-boxed.png");
  const double grid_size = round_grid_size<9>(image.viewport_height);
  image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
  ExplainableSudoku<9> sudoku;
  for (auto& cell : sudoku.cells()) {
    const auto [row, col] = cell.coordinates();
    cell.set_deduced((row + 2 * col) % 9);
  }
  draw(
    image.crs[1][0],
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
      .boxed_cells = {SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end()},
      .boxed_cells_color = {0, 1, 0},
    });
}

TEST_CASE("draw - all forbidden") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-all-forbidden.png");
  const double grid_size = round_grid_size<9>(image.viewport_height);
  image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
  ExplainableSudoku<9> sudoku;
  for (auto& cell : sudoku.cells()) {
    const auto [row, col] = cell.coordinates();
    for (const unsigned value : SudokuConstants<9>::values) {
      if (value != (row + 2 * col) % 9) {
        cell.forbid(value);
      }
    }
  }
  draw(
    image.crs[1][0],
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
    });
}

TEST_CASE("draw - possible-values circled") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-possible-values-circled.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_height);
    image.crs[0][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    ExplainableSudoku<4> sudoku;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    for (const auto& cell : SudokuConstants<4>::cells) {
      for (const unsigned value : SudokuConstants<4>::values) {
        circled_values.push_back({cell, value});
      }
    }
    draw(
      image.crs[0][0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_values = circled_values,
      });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_height);
    image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    ExplainableSudoku<9> sudoku;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    for (const auto& cell : sudoku.cells()) {
      for (const unsigned value : SudokuConstants<9>::values) {
        circled_values.push_back({cell.coordinates(), value});
      }
    }
    draw(
      image.crs[1][0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_values = circled_values,
      });
  }
}

TEST_CASE("draw - possible-values linked") {
  TestImage<2, 1> image("tests/unit/explanation/art/draw-possible-values-linked.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_height);
    image.crs[0][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    ExplainableSudoku<4> sudoku;
    std::vector<std::tuple<Coordinates, Coordinates, unsigned>>
      links_from_cell_to_value;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    Coordinates source_cell = {2, 3};
    for (const auto& cell : SudokuConstants<4>::cells) {
      if (cell != source_cell) {
        const auto [row, col] = cell;
        for (const unsigned value : SudokuConstants<4>::values) {
          if (value == (row + 2 * col) % 4) {
            links_from_cell_to_value.push_back({source_cell, cell, value});
            circled_values.push_back({cell, value});
          }
        }
      }
    }
    draw(
      image.crs[0][0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_cells = {source_cell},
        .circled_values = circled_values,
        .links_from_cell_to_value = links_from_cell_to_value,
      });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_height);
    image.crs[1][0]->translate((image.viewport_width - grid_size) / 2, (image.viewport_height - grid_size) / 2);
    ExplainableSudoku<9> sudoku;
    std::vector<std::tuple<Coordinates, Coordinates, unsigned>>
      links_from_cell_to_value;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    Coordinates source_cell = {2, 3};
    for (auto& cell : sudoku.cells()) {
      const auto coords = cell.coordinates();
      if (coords != source_cell) {
        const auto [row, col] = coords;
        for (const unsigned value : SudokuConstants<9>::values) {
          if (value == (row + 2 * col) % 9) {
            links_from_cell_to_value.push_back({source_cell, coords, value});
            circled_values.push_back({coords, value});
          }
        }
      }
    }
    draw(
      image.crs[1][0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_cells = {source_cell},
        .circled_values = circled_values,
        .links_from_cell_to_value = links_from_cell_to_value,
      });
  }
}

// LCOV_EXCL_STOP

}  // namespace art
