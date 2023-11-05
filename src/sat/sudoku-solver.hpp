// Copyright 2023 Vincent Jacques

#ifndef SAT_SUDOKU_SOLVER_HPP_
#define SAT_SUDOKU_SOLVER_HPP_

#include "../puzzle/sudoku.hpp"


template<unsigned size>
io::Sudoku<size> solve_using_sat(io::Sudoku<size>);

#endif  // SAT_SUDOKU_SOLVER_HPP_
