// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <functional>
#include <memory>

#include "../io/sudoku.hpp"
#include "events.hpp"


io::Sudoku solve_using_exploration(
  const io::Sudoku&,
  const std::function<void(std::unique_ptr<exploration::Event>)>& = [](std::unique_ptr<exploration::Event>) {});

#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
