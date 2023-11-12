// Copyright 2023 Vincent Jacques

#ifndef SAT_SUDOKU_SOLVER_HPP_
#define SAT_SUDOKU_SOLVER_HPP_

#include "../puzzle/sudoku.hpp"


template<unsigned size>
Sudoku<ValueCell, size> solve_using_sat(Sudoku<ValueCell, size>);

#endif  // SAT_SUDOKU_SOLVER_HPP_
