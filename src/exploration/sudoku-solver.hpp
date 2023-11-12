// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <functional>
#include <memory>

#include "../puzzle/sudoku.hpp"
#include "events.hpp"


template<unsigned size>
Sudoku<ValueCell, size> solve_using_exploration(
  Sudoku<ValueCell, size>,
  const std::function<void(std::unique_ptr<exploration::Event<size>>)>& =
    [](std::unique_ptr<exploration::Event<size>>) {});

#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
