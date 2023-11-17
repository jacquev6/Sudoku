// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


template<unsigned size>
Sudoku<ValueCell, size> Sudoku<ValueCell, size>::load(std::istream& is) {
  Sudoku<ValueCell, size> sudoku;

  std::string line;
  // @todo Improve robustness to malformed inputs
  for (const unsigned row : SudokuConstants<size>::values) {
    std::getline(is, line);

    for (const unsigned col : SudokuConstants<size>::values) {
      const char c = line[col];
      if (c >= '1' && c <= '9') {
        sudoku.cell({row, col}).set(c - '1');
      }
    }
  }

  return sudoku;
}

template<unsigned size>
void Sudoku<ValueCell, size>::dump(std::ostream& os) const {
  for (const unsigned row : SudokuConstants<size>::values) {
    for (const unsigned col : SudokuConstants<size>::values) {
      const auto value = this->cell({row, col}).get();
      if (value) {
        os << *value + 1;
      } else {
        os << '.';
      }
    }
    os << '\n';
  }
}

template class Sudoku<ValueCell, 4>;
template class Sudoku<ValueCell, 9>;


// LCOV_EXCL_START

struct TestCell { unsigned val = 0; };

TEST_CASE("sudoku - cells") {
  Sudoku<TestCell, 4> sudoku;
  std::vector<Coordinates> cells;
  for (const auto& cell : sudoku.cells()) {
    CHECK(!cell.val);
    cells.push_back(cell.coordinates());
  }
  CHECK(cells == std::vector(SudokuConstants<4>::cells.begin(), SudokuConstants<4>::cells.end()));
}

TEST_CASE("sudoku - copy - ephemeral cells") {
  Sudoku<TestCell, 4> sudoku1;
  CHECK(sudoku1.cell({0, 0}).val == 0);
  sudoku1.cell({0, 0}).val = 1;
  CHECK(sudoku1.cell({0, 0}).val == 1);

  Sudoku<TestCell, 4> sudoku2 = sudoku1;
  CHECK(sudoku2.cell({0, 0}).val == 1);
  sudoku1.cell({0, 0}).val = 2;
  sudoku2.cell({0, 0}).val = 3;
  CHECK(sudoku1.cell({0, 0}).val == 2);
  CHECK(sudoku2.cell({0, 0}).val == 3);
}

TEST_CASE("sudoku - copy - long-lived cells") {
  Sudoku<TestCell, 4> sudoku1;
  auto& cell1 = sudoku1.cell({0, 0});
  CHECK(cell1.val == 0);
  cell1.val = 1;
  CHECK(cell1.val == 1);

  Sudoku<TestCell, 4> sudoku2 = sudoku1;
  auto& cell2 = sudoku2.cell({0, 0});

  CHECK(cell2.val == 1);
  cell1.val = 2;
  cell2.val = 3;
  CHECK(cell1.val == 2);
  CHECK(cell2.val == 3);
}

TEST_CASE("sudoku - cell equality") {
  Sudoku<TestCell, 4> sudoku;
  CHECK(sudoku.cell({0, 0}) == sudoku.cell({0, 0}));
  CHECK(sudoku.cell({0, 0}) != sudoku.cell({0, 1}));
  CHECK(sudoku.cell({0, 0}) != sudoku.cell({1, 0}));
  CHECK(sudoku.cell({0, 0}) != sudoku.cell({1, 1}));
}

// LCOV_EXCL_STOP
