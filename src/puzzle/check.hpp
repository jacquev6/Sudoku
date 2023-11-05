// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_CHECK_HPP_
#define PUZZLE_CHECK_HPP_

#include "sudoku.hpp"

template<unsigned size>
bool is_solved(const io::Sudoku<size>&);

#endif  // PUZZLE_CHECK_HPP_
