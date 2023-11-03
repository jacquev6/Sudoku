// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <minisat/simp/SimpSolver.h>


Sudoku solve_using_sat(Sudoku sudoku) {
  Minisat::SimpSolver solver;

  std::array<std::array<std::array<Minisat::Var, Sudoku::size>, Sudoku::size>, Sudoku::size> has_value;
  for (const unsigned row : Sudoku::values) {
    for (const unsigned col : Sudoku::values) {
      for (const unsigned val : Sudoku::values) {
        has_value[row][col][val] = solver.newVar();
      }
    }
  }

  // Structural constraints: each cell...
  for (const auto& cell : Sudoku::cells) {
    const auto [row, col] = cell;

    {
      // ... has at least one value
      Minisat::vec<Minisat::Lit> clause;
      for (const unsigned val : Sudoku::values) {
        clause.push(Minisat::mkLit(has_value[row][col][val]));
      }
      solver.addClause(clause);
    }

    // ... has at most one value
    for (const unsigned val1 : Sudoku::values) {
      for (const unsigned val2 : Sudoku::values) {
        if (val1 < val2) {
          solver.addClause(~Minisat::mkLit(has_value[row][col][val1]), ~Minisat::mkLit(has_value[row][col][val2]));
        }
      }
    }
  }

  // Structural constraints: in each region...
  for (const auto region : Sudoku::regions) {
    // ... each value...
    for (const unsigned val : Sudoku::values) {
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
  for (const auto& cell : Sudoku::cells) {
    const auto [row, col] = cell;
    if (sudoku.is_set(cell)) {
      const unsigned val = sudoku.get(cell);
      solver.addClause(Minisat::mkLit(has_value[row][col][val]));
    }
  }

  Minisat::vec<Minisat::Lit> dummy;
  const auto ret = solver.solveLimited(dummy);
  if (ret == Minisat::l_True) {
    for (const unsigned row : Sudoku::values) {
      for (const unsigned col : Sudoku::values) {
        for (const unsigned val : Sudoku::values) {
          if (solver.model[has_value[row][col][val]] == Minisat::l_True) {
            sudoku.set({row, col}, val);
          }
        }
      }
    }
  }

  return sudoku;
}
