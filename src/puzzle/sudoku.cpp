// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>


namespace experimental {

template<unsigned size>
void Sudoku<ValueCell, size>::set(const Coordinates& cell, unsigned val) {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  assert(val < size);
  this->cells[row][col].set(val);
}

template<unsigned size>
std::optional<unsigned> Sudoku<ValueCell, size>::get(const Coordinates& cell) const {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  return this->cells[row][col].get();
}

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
        sudoku.set({row, col}, c - '1');
      }
    }
  }

  return sudoku;
}

template<unsigned size>
void Sudoku<ValueCell, size>::dump(std::ostream& os) const {
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

template class Sudoku<ValueCell, 4>;
template class Sudoku<ValueCell, 9>;

}  // namespace experimental
