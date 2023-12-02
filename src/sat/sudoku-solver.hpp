// Copyright 2023 Vincent Jacques

#ifndef SAT_SUDOKU_SOLVER_HPP_
#define SAT_SUDOKU_SOLVER_HPP_

#include <optional>

#include "../puzzle/sudoku.hpp"


template<unsigned size>
std::optional<Sudoku<ValueCell, size>> solve_using_sat(Sudoku<ValueCell, size>);

#endif  // SAT_SUDOKU_SOLVER_HPP_
