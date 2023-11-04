// Copyright 2023 Vincent Jacques

#ifndef IO_SUDOKU_HPP_
#define IO_SUDOKU_HPP_

#include <array>
#include <iostream>
#include <optional>
#include <string>

#include "../sudoku-constants.hpp"


namespace io {

class Sudoku {
 public:
  static constexpr unsigned size = SudokuConstants::size;
  using Coordinates = SudokuConstants::Coordinates;

 public:
  Sudoku() = default;

  Sudoku(const Sudoku&) = default;
  Sudoku& operator=(const Sudoku&) = default;
  Sudoku(Sudoku&&) = default;
  Sudoku& operator=(Sudoku&&) = default;

 public:
  static Sudoku load(std::istream&);
  void dump(std::ostream&) const;

  static Sudoku from_string(const std::string&);
  std::string to_string() const;

 public:
  void set(const Coordinates& cell, unsigned value);
  std::optional<unsigned> get(const Coordinates& cell) const;

 private:
  std::array<std::array<std::optional<unsigned>, size>, size> cells;
};

}  // namespace io

#endif  // IO_SUDOKU_HPP_
