// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>


namespace io {

template<unsigned size>
void Sudoku<size>::set(const Coordinates& cell, unsigned val) {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  assert(val < size);
  assert(!cells[row][col] || *cells[row][col] == val);
  cells[row][col] = val;
}

template<unsigned size>
std::optional<unsigned> Sudoku<size>::get(const Coordinates& cell) const {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  return cells[row][col];
}

template<unsigned size>
Sudoku<size> Sudoku<size>::load(std::istream& is) {
  Sudoku<size> sudoku;

  std::string line;
  // @todo Improve robustness to malformed inputs
  for (const unsigned row : SudokuConstants<size>::values) {
    std::getline(is, line);

    for (const unsigned col : SudokuConstants<size>::values) {
      const char c = line[col];
      if (c >= '1' && c <= '9') {
        sudoku.set({row, col}, c - '1');
      }
    }
  }

  return sudoku;
}

template<unsigned size>
void Sudoku<size>::dump(std::ostream& os) const {
  for (const unsigned row : SudokuConstants<size>::values) {
    for (const unsigned col : SudokuConstants<size>::values) {
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

template class Sudoku<4>;
template class Sudoku<9>;

}  // namespace io
