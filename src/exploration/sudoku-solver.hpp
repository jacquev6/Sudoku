// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <functional>
#include <memory>

#include "../sudoku.hpp"
#include "events.hpp"


Sudoku solve_using_exploration(
  Sudoku,
  const std::function<void(std::unique_ptr<exploration::Event>)>& = [](std::unique_ptr<exploration::Event>) {});

#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
