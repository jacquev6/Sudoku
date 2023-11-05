// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_SUDOKU_HPP_
#define PUZZLE_SUDOKU_HPP_

#include <array>
#include <iostream>
#include <optional>
#include <string>

#include "sudoku-constants.hpp"


namespace io {

template<unsigned size>
class Sudoku {
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

#endif  // PUZZLE_SUDOKU_HPP_
