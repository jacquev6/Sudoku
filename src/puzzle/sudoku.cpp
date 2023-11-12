// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>


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
        sudoku.cell_at({row, col}).set(c - '1');
      }
    }
  }

  return sudoku;
}

template<unsigned size>
void Sudoku<ValueCell, size>::dump(std::ostream& os) const {
  for (const unsigned row : SudokuConstants<size>::values) {
    for (const unsigned col : SudokuConstants<size>::values) {
      const auto value = this->cell_at({row, col}).get();
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
