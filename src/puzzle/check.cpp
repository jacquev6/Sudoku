// Copyright 2023 Vincent Jacques

#include "check.hpp"

#include <bitset>
#include <cassert>


template<unsigned size>
bool is_solved(const Sudoku<ValueCell, size>& sudoku) {
  for (const auto& cell : sudoku.cells()) {
    if (!cell.get()) {
      return false;
    }
  }

  for (const auto& region : sudoku.regions()) {
    std::bitset<size> seen;
    for (const auto& cell : region.cells()) {
      const unsigned val = *cell.get();
      assert(val < size);
      if (seen[val]) {
        return false;
      }
      seen[val] = true;
    }
  }

  return true;
}

template bool is_solved(const Sudoku<ValueCell, 4>&);
template bool is_solved(const Sudoku<ValueCell, 9>&);
