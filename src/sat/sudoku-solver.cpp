// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <minisat/simp/SimpSolver.h>

#include <chrones.hpp>

#include "../puzzle/sudoku-constants.hpp"


template<unsigned size>
std::optional<Sudoku<ValueCell, size>> solve_using_sat(Sudoku<ValueCell, size> sudoku) {
  CHRONE();

  Minisat::SimpSolver solver;

  std::array<std::array<std::array<Minisat::Var, size>, size>, size> has_value;
  {
    CHRONE("variables");
    for (const unsigned row : SudokuConstants<size>::values) {
      for (const unsigned col : SudokuConstants<size>::values) {
        for (const unsigned val : SudokuConstants<size>::values) {
          has_value[row][col][val] = solver.newVar();
        }
      }
    }
  }

  {
    CHRONE("structural constraints");
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
    for (const auto& region : SudokuConstants<size>::regions) {
      // ... each value...
      for (const unsigned val : SudokuConstants<size>::values) {
        // ... appears at most once
        for (const auto& cell1 : region) {
          for (const auto& cell2 : region) {
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
  }

  {
    CHRONE("circumstantial constraints");
    // Circumstantial constraints: inputs are honored
    for (const auto& cell : sudoku.cells()) {
      const auto [row, col] = cell.coordinates();
      const auto value = cell.get();
      if (value) {
        solver.addClause(Minisat::mkLit(has_value[row][col][*value]));
      }
    }
  }

  Minisat::lbool solved = Minisat::l_False;
  {
    CHRONE("solve");
    Minisat::vec<Minisat::Lit> dummy;
    solved = solver.solveLimited(dummy);
  }

  {
    CHRONE("decode");
    if (solved == Minisat::l_True) {
      for (auto& cell : sudoku.cells()) {
        const auto [row, col] = cell.coordinates();
        for (const unsigned val : SudokuConstants<size>::values) {
          if (solver.model[has_value[row][col][val]] == Minisat::l_True) {
            cell.set(val);
          }
        }
      }
      return sudoku;
    } else {
      return std::nullopt;
    }
  }
}

template std::optional<Sudoku<ValueCell, 4>> solve_using_sat(Sudoku<ValueCell, 4>);
template std::optional<Sudoku<ValueCell, 9>> solve_using_sat(Sudoku<ValueCell, 9>);
