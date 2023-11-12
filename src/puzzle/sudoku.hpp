// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_SUDOKU_HPP_
#define PUZZLE_SUDOKU_HPP_

#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range.hpp>

#include "sudoku-constants.hpp"


template<typename Cell, unsigned size>
class SudokuBase {
 public:
  SudokuBase() : cells(make_cells(std::make_integer_sequence<unsigned, size>())) {}

  SudokuBase(const SudokuBase&) = default;
  SudokuBase& operator=(const SudokuBase&) = default;
  SudokuBase(SudokuBase&&) = default;
  SudokuBase& operator=(SudokuBase&&) = default;

 private:
  template<unsigned... row>
  std::array<std::array<Cell, size>, size> make_cells(const std::integer_sequence<unsigned, row...>&) {
    return {make_row(row, std::make_integer_sequence<unsigned, size>())...};
  }

  template<unsigned... col>
  std::array<Cell, size> make_row(unsigned row, const std::integer_sequence<unsigned, col...>&) {
    return {make_cell(row, col)...};
  }

  Cell make_cell(unsigned, unsigned) {
    return Cell();
  }

 public:
  Cell& cell_at(const Coordinates& coords) {
    const auto [row, col] = coords;
    assert(row < size);
    assert(col < size);
    return cells[row][col];
  }

  const Cell& cell_at(const Coordinates& coords) const {
    const auto [row, col] = coords;
    assert(row < size);
    assert(col < size);
    return cells[row][col];
  }

  auto all_cells() const {
    const auto convert = [this](const auto& cell) -> const Cell& {
      const auto [row, col] = cell;
      return this->cells[row][col];
    };

    return boost::make_iterator_range(
      boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert),
      boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }

 protected:
  std::array<std::array<Cell, size>, size> cells;
};

template<typename Cell, unsigned size>
class Sudoku : public SudokuBase<Cell, size> {};

class ValueCell {
 public:
  ValueCell() = default;

  ValueCell(const ValueCell&) = default;
  ValueCell& operator=(const ValueCell&) = default;
  ValueCell(ValueCell&&) = default;
  ValueCell& operator=(ValueCell&&) = default;

 public:
  void set(unsigned value_) {
    assert(!value || *value == value_);
    value = value_;
  }

  std::optional<unsigned> get() const {
    return value;
  }

 private:
  std::optional<unsigned> value;
};

template<unsigned size>
class Sudoku<ValueCell, size> : public SudokuBase<ValueCell, size> {
 public:
  static Sudoku<ValueCell, size> load(std::istream&);
  void dump(std::ostream&) const;

  static Sudoku<ValueCell, size> from_string(const std::string&);
  std::string to_string() const;
};

#endif  // PUZZLE_SUDOKU_HPP_
