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


template<unsigned size>
class AnnotatedSudoku {
 public:
  AnnotatedSudoku() : allowed_values(), set_values() {
    for (unsigned row : SudokuConstants<size>::values) {
      for (unsigned col : SudokuConstants<size>::values) {
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
    for (const auto& cell : SudokuConstants<size>::cells) {
      if (!is_set(cell)) {
        return false;
      }
    }
    return true;
  }

 public:
  void set_input(const Coordinates& cell, unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(cell, value));
    assert(!is_set(cell));

    at(allowed_values, cell).reset();
    at(allowed_values, cell).set(value);
    at(set_values, cell) = value;
    at(inputs, cell) = true;

    assert_invariants();
  }

  void set_deduced(const Coordinates& cell, unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(cell, value));
    assert(!is_set(cell));

    at(allowed_values, cell).reset();
    at(allowed_values, cell).set(value);
    at(set_values, cell) = value;

    assert_invariants();
  }

  bool is_input(const Coordinates& cell) const {
    assert_invariants();

    return at(inputs, cell);
  }

  bool is_set(const Coordinates& cell) const {
    assert_invariants();

    return at(set_values, cell).has_value();
  }

  unsigned get(const Coordinates& cell) const {
    assert_invariants();

    return at(set_values, cell).value();
  }

  void set_propagated(const Coordinates& cell) {
    assert_invariants();
    assert(is_set(cell));

    at(propagated, cell) = true;

    assert_invariants();
  }

  bool is_propagated(const Coordinates& cell) const {
    assert_invariants();

    return at(propagated, cell);
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

  bool at(const std::array<std::bitset<size>, size>& arr, const Coordinates& cell) const {
    const auto [row, col] = cell;
    assert(row < size);
    assert(col < size);
    return arr[row][col];
  }

  std::bitset<size>::reference at(
    std::array<std::bitset<size>, size>& arr,  // NOLINT(runtime/references)
    const Coordinates& cell
  ) {
    const auto [row, col] = cell;
    assert(row < size);
    assert(col < size);
    return arr[row][col];
  }

  void assert_invariants() const {
    // At least one value is always allowed
    for (unsigned row : SudokuConstants<size>::values) {
      for (unsigned col : SudokuConstants<size>::values) {
        assert(allowed_values[row][col].any());
      }
    }

    // 'inputs' forces 'set_values'
    for (unsigned row : SudokuConstants<size>::values) {
      for (unsigned col : SudokuConstants<size>::values) {
        if (inputs[row][col]) {
          assert(set_values[row][col].has_value());
        }
      }
    }

    // 'propagated' forces 'set_values'
    for (unsigned row : SudokuConstants<size>::values) {
      for (unsigned col : SudokuConstants<size>::values) {
        if (propagated[row][col]) {
          assert(set_values[row][col].has_value());
        }
      }
    }

    // 'set_values' forces 'allowed_values'
    for (unsigned row : SudokuConstants<size>::values) {
      for (unsigned col : SudokuConstants<size>::values) {
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
  std::array<std::bitset<size>, size> inputs;
  std::array<std::bitset<size>, size> propagated;
};

#endif  // EXPLORATION_SUDOKU_HPP_
