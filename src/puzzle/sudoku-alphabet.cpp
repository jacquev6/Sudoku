// Copyright 2023 Vincent Jacques

#include "sudoku-alphabet.hpp"

static_assert(SudokuAlphabet<4>::get_symbol(std::nullopt) == '.');
static_assert(SudokuAlphabet<4>::get_symbol(0) == '1');
static_assert(SudokuAlphabet<4>::get_symbol(1) == '2');
static_assert(SudokuAlphabet<4>::get_symbol(2) == '3');
static_assert(SudokuAlphabet<4>::get_symbol(3) == '4');
static_assert(SudokuAlphabet<4>::get_value('.') == std::nullopt);
static_assert(SudokuAlphabet<4>::get_value('1') == 0);
static_assert(SudokuAlphabet<4>::get_value('2') == 1);
static_assert(SudokuAlphabet<4>::get_value('3') == 2);
static_assert(SudokuAlphabet<4>::get_value('4') == 3);
