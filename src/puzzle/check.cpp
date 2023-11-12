// Copyright 2023 Vincent Jacques

#include "check.hpp"

#include <bitset>
#include <cassert>

template<unsigned size>
bool is_solved(const io::Sudoku<size>& sudoku) {
  for (const auto cell : SudokuConstants<size>::cells) {
    if (!sudoku.cell_at(cell).get()) {
      return false;
    }
  }

  for (const auto region : SudokuConstants<size>::regions) {
    std::bitset<size> seen;
    for (const auto cell : region) {
      const unsigned val = *sudoku.cell_at(cell).get();
      assert(val < size);
      if (seen[val]) {
        return false;
      }
      seen[val] = true;
    }
  }

  return true;
}

template bool is_solved(const io::Sudoku<4>&);
template bool is_solved(const io::Sudoku<9>&);
