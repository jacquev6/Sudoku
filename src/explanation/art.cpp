// Copyright 2023 Vincent Jacques

#include "art.hpp"

#include <filesystem>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


namespace art {

constexpr unsigned thick_line_width = 4;
constexpr unsigned thin_line_width = 2;

template<unsigned size>
double round_grid_size(unsigned available_size) {
  return (available_size - thick_line_width) / size * size + thick_line_width;
}

template<unsigned size>
void draw(Cairo::RefPtr<Cairo::Context> cr, const AnnotatedSudoku<size>& sudoku, const DrawOptions& options) {
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
  for (const auto cell : SudokuConstants<size>::cells) {
    if (sudoku.is_set(cell)) {
      assert(sudoku.is_set(cell));
      const std::string text = std::to_string(sudoku.get(cell) + 1);

      if (options.bold_todo && !sudoku.is_propagated(cell)) {
        cr->select_font_face("sans-serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
      } else {
        cr->select_font_face("sans-serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      }

      if (sudoku.is_input(cell)) {
        Cairo::SaveGuard saver(cr);

        const auto [x, y] = cell_center(cell);
        cr->rectangle(x - cell_size / 2, y - cell_size / 2, cell_size, cell_size);
        cr->set_source_rgb(0.85, 0.85, 0.85);
        cr->fill();
      }

      Cairo::TextExtents extents;
      cr->get_text_extents(text, extents);
      {
        const auto [x, y] = cell_center(cell);
        cr->move_to(x - extents.width / 2 - extents.x_bearing, y - extents.height / 2 - extents.y_bearing);
      }
      cr->show_text(text);
    }
  }

  // Possible values
  if (options.possible) {
    cr->set_font_size(cell_interior_size / 4);
    cr->select_font_face("sans-serif", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);

    for (const auto cell : SudokuConstants<size>::cells) {
      if (!sudoku.is_set(cell)) {
        assert(!sudoku.is_propagated(cell));

        for (unsigned value : SudokuConstants<size>::values) {
          Cairo::SaveGuard saver(cr);

          const std::string text = std::to_string(value + 1);
          Cairo::TextExtents extents;
          cr->get_text_extents(text, extents);
          {
            const auto [x, y] = value_center(cell, value);
            cr->move_to(x - extents.width / 2 - extents.x_bearing, y - extents.height / 2 - extents.y_bearing);
          }
          if (sudoku.is_allowed(cell, value)) {
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
  for (const auto cell : options.circled_cells) {
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
  for (const auto cell : options.boxed_cells) {
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
  for (const auto [cell, value] : options.circled_values) {
    cr->begin_new_sub_path();
    const auto [x, y] = value_center(cell, value);
    cr->arc(x, y, 0.8 * 0.5 * cell_size / SudokuConstants<size>::sqrt_size, 0, 2 * M_PI);
  }
  {
    const auto [r, g, b] = options.circled_values_color;
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

    for (const auto [source_cell, target_cell, value] : options.links_from_cell_to_value) {
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

template void draw(Cairo::RefPtr<Cairo::Context> cr, const AnnotatedSudoku<4>& sudoku, const DrawOptions& options);
template void draw(Cairo::RefPtr<Cairo::Context> cr, const AnnotatedSudoku<9>& sudoku, const DrawOptions& options);


// LCOV_EXCL_START

template<unsigned cols = 2>
struct TestImage {
  static constexpr unsigned frame_size = 300;
  static constexpr unsigned margin = 10;
  static constexpr unsigned viewport_size = frame_size - 2 * margin;

  explicit TestImage(std::filesystem::path path_) :
    path(path_),
    surface(Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, cols * frame_size, frame_size)),
    cr(Cairo::Context::create(surface)),
    crs()
  {  // NOLINT(whitespace/braces)
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr->save();
    cr->translate(frame_size + margin, margin);

    for (unsigned col = 0; col != cols; ++col) {
      crs[col] = Cairo::Context::create(surface);
      crs[col]->save();
      crs[col]->translate(col * frame_size + margin, margin);
    }
  }

  ~TestImage() {
    cr->restore();
    cr->rectangle(0, 0, cols * frame_size, frame_size);
    for (unsigned col = 0; col != cols; ++col) {
      cr->rectangle(col * frame_size + margin, margin, viewport_size, viewport_size);
    }
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(1, 0, 0, 0.5);
    cr->fill();

    surface->write_to_png(path.string());
  }

  std::filesystem::path path;
  Cairo::RefPtr<Cairo::ImageSurface> surface;
  Cairo::RefPtr<Cairo::Context> cr;
  std::array<Cairo::RefPtr<Cairo::Context>, cols> crs;
};

// These tests must be validated visually e.g. using 'git diff-image tests/unit' before commit
TEST_CASE("draw - grid") {
  TestImage image("tests/unit/explanation/art/draw-grid.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_size);
    image.crs[0]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    draw(image.crs[0], AnnotatedSudoku<4>(), { .grid_size = grid_size });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_size);
    image.crs[1]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    draw(image.crs[1], AnnotatedSudoku<9>(), { .grid_size = grid_size });
  }
}

TEST_CASE("draw - known-values circled") {
  TestImage image("tests/unit/explanation/art/draw-known-values-circled.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_size);
    image.crs[0]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    AnnotatedSudoku<4> sudoku;
    for (const auto cell : SudokuConstants<4>::cells) {
      const auto [row, col] = cell;
      sudoku.set_deduced(cell, (row + 2 * col) % 4);
    }
    draw(
      image.crs[0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_cells = {SudokuConstants<4>::cells.begin(), SudokuConstants<4>::cells.end()},
      });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_size);
    image.crs[1]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    AnnotatedSudoku<9> sudoku;
    for (const auto cell : SudokuConstants<9>::cells) {
      const auto [row, col] = cell;
      sudoku.set_deduced(cell, (row + 2 * col) % 9);
    }
    draw(
      image.crs[1],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_cells = {SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end()},
      });
  }
}

TEST_CASE("draw - all inputs") {
  TestImage image("tests/unit/explanation/art/draw-all-inputs.png");
  const double grid_size = round_grid_size<9>(image.viewport_size);
  image.cr->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
  AnnotatedSudoku<9> sudoku;
  for (const auto cell : SudokuConstants<9>::cells) {
    const auto [row, col] = cell;
    sudoku.set_input(cell, (row + 2 * col) % 9);
  }
  draw(
    image.cr,
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
    });
}

TEST_CASE("draw - all todo") {
  TestImage image("tests/unit/explanation/art/draw-all-todo.png");
  const double grid_size = round_grid_size<9>(image.viewport_size);
  image.cr->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
  AnnotatedSudoku<9> sudoku;
  for (const auto cell : SudokuConstants<9>::cells) {
    const auto [row, col] = cell;
    sudoku.set_deduced(cell, (row + 2 * col) % 9);
  }
  draw(
    image.cr,
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
      .bold_todo = true,
    });
}

TEST_CASE("draw - all processed") {
  TestImage image("tests/unit/explanation/art/draw-all-processed.png");
  const double grid_size = round_grid_size<9>(image.viewport_size);
  image.cr->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
  AnnotatedSudoku<9> sudoku;
  for (const auto cell : SudokuConstants<9>::cells) {
    const auto [row, col] = cell;
    sudoku.set_deduced(cell, (row + 2 * col) % 9);
    sudoku.set_propagated(cell);
  }
  draw(
    image.cr,
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
      .bold_todo = true,
    });
}

TEST_CASE("draw - known-values boxed") {
  TestImage image("tests/unit/explanation/art/draw-known-values-boxed.png");
  const double grid_size = round_grid_size<9>(image.viewport_size);
  image.cr->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
  AnnotatedSudoku<9> sudoku;
  for (const auto cell : SudokuConstants<9>::cells) {
    const auto [row, col] = cell;
    sudoku.set_deduced(cell, (row + 2 * col) % 9);
  }
  draw(
    image.cr,
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
      .boxed_cells = {SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end()},
      .boxed_cells_color = {0, 1, 0},
    });
}

TEST_CASE("draw - all forbidden") {
  TestImage image("tests/unit/explanation/art/draw-all-forbidden.png");
  const double grid_size = round_grid_size<9>(image.viewport_size);
  image.cr->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
  AnnotatedSudoku<9> sudoku;
  for (const auto cell : SudokuConstants<9>::cells) {
    const auto [row, col] = cell;
    for (const unsigned value : SudokuConstants<9>::values) {
      if (value != (row + 2 * col) % 9) {
        sudoku.forbid(cell, value);
      }
    }
  }
  draw(
    image.cr,
    sudoku,
    {
      .grid_size = grid_size,
      .possible = true,
    });
}

TEST_CASE("draw - possible-values circled") {
  TestImage image("tests/unit/explanation/art/draw-possible-values-circled.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_size);
    image.crs[0]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    AnnotatedSudoku<4> sudoku;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    for (const auto cell : SudokuConstants<4>::cells) {
      for (const unsigned value : SudokuConstants<4>::values) {
        circled_values.push_back({cell, value});
      }
    }
    draw(
      image.crs[0],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_values = circled_values,
      });
  }
  {
    const double grid_size = round_grid_size<9>(image.viewport_size);
    image.crs[1]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    AnnotatedSudoku<9> sudoku;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    for (const auto cell : SudokuConstants<9>::cells) {
      for (const unsigned value : SudokuConstants<9>::values) {
        circled_values.push_back({cell, value});
      }
    }
    draw(
      image.crs[1],
      sudoku,
      {
        .grid_size = grid_size,
        .possible = true,
        .circled_values = circled_values,
      });
  }
}

TEST_CASE("draw - possible-values linked") {
  TestImage image("tests/unit/explanation/art/draw-possible-values-linked.png");
  {
    const double grid_size = round_grid_size<4>(image.viewport_size);
    image.crs[0]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    AnnotatedSudoku<4> sudoku;
    std::vector<std::tuple<Coordinates, Coordinates, unsigned>>
      links_from_cell_to_value;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    Coordinates source_cell = {2, 3};
    for (const auto cell : SudokuConstants<4>::cells) {
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
      image.crs[0],
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
    const double grid_size = round_grid_size<9>(image.viewport_size);
    image.crs[1]->translate((image.viewport_size - grid_size) / 2, (image.viewport_size - grid_size) / 2);
    AnnotatedSudoku<9> sudoku;
    std::vector<std::tuple<Coordinates, Coordinates, unsigned>>
      links_from_cell_to_value;
    std::vector<std::tuple<Coordinates, unsigned>> circled_values;
    Coordinates source_cell = {2, 3};
    for (const auto cell : SudokuConstants<9>::cells) {
      if (cell != source_cell) {
        const auto [row, col] = cell;
        for (const unsigned value : SudokuConstants<9>::values) {
          if (value == (row + 2 * col) % 9) {
            links_from_cell_to_value.push_back({source_cell, cell, value});
            circled_values.push_back({cell, value});
          }
        }
      }
    }
    draw(
      image.crs[1],
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
