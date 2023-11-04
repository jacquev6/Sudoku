// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <minisat/simp/SimpSolver.h>

#include "../sudoku-constants.hpp"


io::Sudoku solve_using_sat(io::Sudoku sudoku) {
  Minisat::SimpSolver solver;

  std::array<std::array<std::array<Minisat::Var, SudokuConstants::size>, SudokuConstants::size>, SudokuConstants::size> has_value;
  for (const unsigned row : SudokuConstants::values) {
    for (const unsigned col : SudokuConstants::values) {
      for (const unsigned val : SudokuConstants::values) {
        has_value[row][col][val] = solver.newVar();
      }
    }
  }

  // Structural constraints: each cell...
  for (const auto& cell : SudokuConstants::cells) {
    const auto [row, col] = cell;

    {
      // ... has at least one value
      Minisat::vec<Minisat::Lit> clause;
      for (const unsigned val : SudokuConstants::values) {
        clause.push(Minisat::mkLit(has_value[row][col][val]));
      }
      solver.addClause(clause);
    }

    // ... has at most one value
    for (const unsigned val1 : SudokuConstants::values) {
      for (const unsigned val2 : SudokuConstants::values) {
        if (val1 < val2) {
          solver.addClause(~Minisat::mkLit(has_value[row][col][val1]), ~Minisat::mkLit(has_value[row][col][val2]));
        }
      }
    }
  }

  // Structural constraints: in each region...
  for (const auto region : SudokuConstants::regions) {
    // ... each value...
    for (const unsigned val : SudokuConstants::values) {
      // ... appears at most once
      for (const auto cell1 : region) {
        for (const auto cell2 : region) {
          if (cell1 < cell2) {
            solver.addClause(
              ~Minisat::mkLit(has_value[cell1.first][cell1.second][val]),
              ~Minisat::mkLit(has_value[cell2.first][cell2.second][val]));
          }
        }
      }
      // ... appears at least once
      // Not needed because these clauses are implied by the cell constraints
    }
  }

  // Circumstantial constraints: inputs are honored
  for (const auto& cell : SudokuConstants::cells) {
    const auto [row, col] = cell;
    const auto value = sudoku.get(cell);
    if (value) {
      solver.addClause(Minisat::mkLit(has_value[row][col][*value]));
    }
  }

  Minisat::vec<Minisat::Lit> dummy;
  if (solver.solveLimited(dummy) == Minisat::l_True) {
    for (const auto& cell : SudokuConstants::cells) {
      const auto [row, col] = cell;
      for (const unsigned val : SudokuConstants::values) {
        if (solver.model[has_value[row][col][val]] == Minisat::l_True) {
          sudoku.set({row, col}, val);
        }
      }
    }
  }

  return sudoku;
}
