// Copyright 2023 Vincent Jacques

#include "check.hpp"

#include <bitset>
#include <cassert>


bool is_solved(const io::Sudoku& sudoku) {
  for (const auto cell : SudokuConstants::cells) {
    if (!sudoku.get(cell)) {
      return false;
    }
  }

  for (const auto region : SudokuConstants::regions) {
    std::bitset<SudokuConstants::size> seen;
    for (const auto cell : region) {
      const unsigned val = *sudoku.get(cell);
      assert(val < SudokuConstants::size);
      if (seen[val]) {
        return false;
      }
      seen[val] = true;
    }
  }

  return true;
}
