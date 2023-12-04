// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"
#include "sudoku-alphabet.hpp"

#include <cassert>
#include <map>

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
      const std::optional<unsigned> value = SudokuAlphabet<size>::get_value(c);
      if (value) {
        sudoku.cell({row, col}).set(*value);
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
      os << SudokuAlphabet<size>::get_symbol(*value);
    }
    os << '\n';
  }
}

template class Sudoku<ValueCell, 4>;
template class Sudoku<ValueCell, 9>;
template class Sudoku<ValueCell, 16>;
template class Sudoku<ValueCell, 25>;


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

TEST_CASE("sudoku - modify through .cells") {
  Sudoku<TestCell, 4> sudoku;
  for (auto& cell : sudoku.cells()) {
    cell.val = 1;
  }
  for (const auto& cell : sudoku.cells()) {
    CHECK(cell.val == 1);
  }
}

TEST_CASE("sudoku - modify through .regions then .cells") {
  Sudoku<TestCell, 4> sudoku;
  for (auto& region : sudoku.regions()) {
    for (auto& cell : region.cells()) {
      cell.val = 1;
    }
  }
  for (const auto& cell : sudoku.cells()) {
    CHECK(cell.val == 1);
  }
}

TEST_CASE("sudoku - modify through .cells then .regions then .cells") {
  Sudoku<TestCell, 4> sudoku;
  for (auto& cell : sudoku.cells()) {
    for (auto& region : cell.regions()) {
      for (auto& cell : region.cells()) {
        cell.val = 1;
      }
    }
  }
  for (const auto& cell : sudoku.cells()) {
    CHECK(cell.val == 1);
  }
}

// LCOV_EXCL_STOP
