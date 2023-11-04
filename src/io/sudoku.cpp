// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>

#include "../sudoku-constants.hpp"


namespace io {

void Sudoku::set(const Coordinates& cell, unsigned val) {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  assert(val < size);
  assert(!cells[row][col] || *cells[row][col] == val);
  cells[row][col] = val;
}

std::optional<unsigned> Sudoku::get(const Coordinates& cell) const {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  return cells[row][col];
}

Sudoku Sudoku::load(std::istream& is) {
  Sudoku sudoku;

  std::string line;
  // @todo Improve robustness to malformed inputs
  for (const unsigned row : SudokuConstants::values) {
    std::getline(is, line);

    for (const unsigned col : SudokuConstants::values) {
      const char c = line[col];
      if (c >= '1' && c <= '9') {
        sudoku.set({row, col}, c - '1');
      }
    }
  }

  return sudoku;
}

void Sudoku::dump(std::ostream& os) const {
  for (const unsigned row : SudokuConstants::values) {
    for (const unsigned col : SudokuConstants::values) {
      const auto value = get({row, col});
      if (value) {
        os << *value + 1;
      } else {
        os << '.';
      }
    }
    os << '\n';
  }
}

}  // namespace io
