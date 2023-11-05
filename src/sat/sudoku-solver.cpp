// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <minisat/simp/SimpSolver.h>

#include "../puzzle/sudoku-constants.hpp"


template<unsigned size>
io::Sudoku<size> solve_using_sat(io::Sudoku<size> sudoku) {
  Minisat::SimpSolver solver;

  std::array<std::array<std::array<Minisat::Var, size>, size>, size> has_value;
  for (const unsigned row : SudokuConstants<size>::values) {
    for (const unsigned col : SudokuConstants<size>::values) {
      for (const unsigned val : SudokuConstants<size>::values) {
        has_value[row][col][val] = solver.newVar();
      }
    }
  }

  // Structural constraints: each cell...
  for (const auto& cell : SudokuConstants<size>::cells) {
    const auto [row, col] = cell;

    {
      // ... has at least one value
      Minisat::vec<Minisat::Lit> clause;
      for (const unsigned val : SudokuConstants<size>::values) {
        clause.push(Minisat::mkLit(has_value[row][col][val]));
      }
      solver.addClause(clause);
    }

    // ... has at most one value
    for (const unsigned val1 : SudokuConstants<size>::values) {
      for (const unsigned val2 : SudokuConstants<size>::values) {
        if (val1 < val2) {
          solver.addClause(~Minisat::mkLit(has_value[row][col][val1]), ~Minisat::mkLit(has_value[row][col][val2]));
        }
      }
    }
  }

  // Structural constraints: in each region...
  for (const auto region : SudokuConstants<size>::regions) {
    // ... each value...
    for (const unsigned val : SudokuConstants<size>::values) {
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
  for (const auto& cell : SudokuConstants<size>::cells) {
    const auto [row, col] = cell;
    const auto value = sudoku.get(cell);
    if (value) {
      solver.addClause(Minisat::mkLit(has_value[row][col][*value]));
    }
  }

  Minisat::vec<Minisat::Lit> dummy;
  if (solver.solveLimited(dummy) == Minisat::l_True) {
    for (const auto& cell : SudokuConstants<size>::cells) {
      const auto [row, col] = cell;
      for (const unsigned val : SudokuConstants<size>::values) {
        if (solver.model[has_value[row][col][val]] == Minisat::l_True) {
          sudoku.set({row, col}, val);
        }
      }
    }
  }

  return sudoku;
}

template io::Sudoku<4> solve_using_sat(io::Sudoku<4>);
template io::Sudoku<9> solve_using_sat(io::Sudoku<9>);
template io::Sudoku<16> solve_using_sat(io::Sudoku<16>);
template io::Sudoku<25> solve_using_sat(io::Sudoku<25>);
template io::Sudoku<36> solve_using_sat(io::Sudoku<36>);
