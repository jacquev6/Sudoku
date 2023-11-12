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

#include "sudoku-constants.hpp"


namespace experimental {

namespace details {

template<typename CellBase, unsigned size>
class SudokuBase {
 public:
  class Cell : public CellBase {
   public:
    Cell(SudokuBase* sudoku_, const Coordinates& coordinates_) :
      CellBase(),
      sudoku(sudoku_),
      coordinates(coordinates_)
    {}

   private:
    SudokuBase* sudoku;
    Coordinates coordinates;
  };

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
    return {Cell(this, {row, col})...};
  }

 public:
  std::vector<Cell*> all_cells() const;

 protected:
  std::array<std::array<Cell, size>, size> cells;
};

}  // namespace details

template<typename Cell, unsigned size>
class Sudoku : public details::SudokuBase<Cell, size> {};

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
class Sudoku<ValueCell, size> : public details::SudokuBase<ValueCell, size> {
 public:
  static Sudoku<ValueCell, size> load(std::istream&);
  void dump(std::ostream&) const;

  static Sudoku<ValueCell, size> from_string(const std::string&);
  std::string to_string() const;

 public:
  void set(const Coordinates&, unsigned);
  std::optional<unsigned> get(const Coordinates&) const;
};

}  // namespace experimental


namespace io {

template<unsigned size>
using Sudoku = experimental::Sudoku<experimental::ValueCell, size>;

}  // namespace io

#endif  // PUZZLE_SUDOKU_HPP_
