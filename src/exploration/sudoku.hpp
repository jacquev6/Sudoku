// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_HPP_
#define EXPLORATION_SUDOKU_HPP_

#include <array>
#include <bitset>
#include <cassert>
#include <optional>
#include <string>
#include <utility>

#include "../puzzle/sudoku-constants.hpp"


class AnnotatedSudoku : public SudokuConstants {
 public:
  AnnotatedSudoku() : allowed_values(), set_values() {
    for (unsigned row : values) {
      for (unsigned col : values) {
        allowed_values[row][col].set();
      }
    }

    assert_invariants();
  }

  AnnotatedSudoku(const AnnotatedSudoku&) = default;
  AnnotatedSudoku& operator=(const AnnotatedSudoku&) = default;
  AnnotatedSudoku(AnnotatedSudoku&&) = default;
  AnnotatedSudoku& operator=(AnnotatedSudoku&&) = default;

  ~AnnotatedSudoku() = default;

 public:
  bool is_solved() const {
    for (const auto& cell : cells) {
      if (!is_set(cell)) {
        return false;
      }
    }
    return true;
  }

 public:
  void set(const Coordinates& cell, unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(cell, value));

    at(allowed_values, cell).reset();
    at(allowed_values, cell).set(value);
    at(set_values, cell) = value;

    assert_invariants();
  }

  bool is_set(const Coordinates& cell) const {
    assert_invariants();

    return at(set_values, cell).has_value();
  }

  unsigned get(const Coordinates& cell) const {
    assert_invariants();

    return at(set_values, cell).value();
  }

 public:
  void forbid(const Coordinates& cell, unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(cell, value));

    at(allowed_values, cell).reset(value);

    assert_invariants();
  }

  unsigned allowed_count(const Coordinates& cell) const {
    assert_invariants();

    return at(allowed_values, cell).count();
  }

  bool is_allowed(const Coordinates& cell, unsigned value) const {
    assert_invariants();
    assert(value < size);

    return at(allowed_values, cell).test(value);
  }

 private:
  template<typename T>
  const T& at(const std::array<std::array<T, size>, size>& arr, const Coordinates& cell) const {
    const auto [row, col] = cell;
    assert(row < size);
    assert(col < size);
    return arr[row][col];
  }

  template<typename T>
  T& at(
    std::array<std::array<T, size>, size>& arr,  // NOLINT(runtime/references)  This is private, and convenient
    const Coordinates& cell
  ) {
    const auto [row, col] = cell;
    assert(row < size);
    assert(col < size);
    return arr[row][col];
  }

  void assert_invariants() const {
    // At least one value is always allowed
    for (unsigned row : values) {
      for (unsigned col : values) {
        assert(allowed_values[row][col].any());
      }
    }

    // 'allowed_values' is consistent with 'set_values'
    for (unsigned row : values) {
      for (unsigned col : values) {
        if (set_values[row][col].has_value()) {
          assert(allowed_values[row][col].count() == 1);
          assert(allowed_values[row][col].test(set_values[row][col].value()));
        }
      }
    }
  }

 private:
  std::array<std::array<std::bitset<size>, size>, size> allowed_values;
  std::array<std::array<std::optional<unsigned>, size>, size> set_values;
};

#endif  // EXPLORATION_SUDOKU_HPP_
