// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_SUDOKU_CONSTANTS_HPP_
#define PUZZLE_SUDOKU_CONSTANTS_HPP_

#include <array>
#include <utility>


template<unsigned size_>
class SudokuConstantsT {
 private:
  // Square root heavily inspired by
  // https://baptiste-wicht.com/posts/2014/07/compile-integer-square-roots-at-compile-time-in-cpp.html
  static constexpr unsigned sqrt(unsigned res, unsigned l, unsigned r) {
    if (l == r) {
      return r;
    } else {
      const auto mid = (r + l) / 2;
      if (mid * mid >= res) {
        return sqrt(res, l, mid);
      } else {
        return sqrt(res, mid + 1, r);
      }
    }
  }

  static constexpr unsigned sqrt(unsigned res) {
    return sqrt(res, 1, res);
  }

  static constexpr unsigned sqrt_size = sqrt(size_);

  static_assert(sqrt_size * sqrt_size == size_, "'size' must be a perfect square");

 private:
  static constexpr auto make_values() {
    std::array<unsigned, size> values;
    for (unsigned i = 0; i != size; ++i) {
      values[i] = i;
    }
    return values;
  }

  static constexpr auto make_cells() {
    std::array<std::pair<unsigned, unsigned>, size * size> cells;
    for (unsigned row : make_values()) {
      for (unsigned col : make_values()) {
        cells[row * size + col] = {row, col};
      }
    }
    return cells;
  }

  static constexpr auto make_regions() {
    std::array<std::array<std::pair<unsigned, unsigned>, size>, 3 * size> regions;
    for (unsigned row : make_values()) {
      for (unsigned col : make_values()) {
        regions[row][col] = {row, col};
      }
    }
    for (unsigned col : make_values()) {
      for (unsigned row : make_values()) {
        regions[size + col][row] = {row, col};
      }
    }
    for (unsigned square : make_values()) {
      const unsigned top_row = square / sqrt_size * sqrt_size;
      const unsigned left_col = square % sqrt_size * sqrt_size;
      for (unsigned cell : make_values()) {
        const unsigned delta_row = cell / sqrt_size;
        const unsigned delta_col = cell % sqrt_size;
        const unsigned row = top_row + delta_row;
        const unsigned col = left_col + delta_col;
        regions[2 * size + square][cell] = {row, col};
      }
    }
    return regions;
  }

  static constexpr auto make_regions_of() {
    std::array<std::array<std::array<unsigned, 3>, size>, size> regions_of;
    for (unsigned row : make_values()) {
      for (unsigned col : make_values()) {
        regions_of[row][col] = {
          row,
          size + col,
          2 * size + row / sqrt_size * sqrt_size + col / sqrt_size
        };
      }
    }
    return regions_of;
  }

 public:
  typedef std::pair<unsigned, unsigned> Coordinates;

  static constexpr unsigned size = size_;
  static constexpr auto values = make_values();
  static constexpr auto cells = make_cells();
  static constexpr auto regions = make_regions();
  static constexpr auto regions_of = make_regions_of();
};

typedef SudokuConstantsT<9> SudokuConstants;

#endif  // PUZZLE_SUDOKU_CONSTANTS_HPP_