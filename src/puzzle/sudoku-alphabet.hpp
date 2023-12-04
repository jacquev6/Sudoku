// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_SUDOKU_ALPHABET_HPP_
#define PUZZLE_SUDOKU_ALPHABET_HPP_

#include <cassert>
#include <map>
#include <optional>


template<unsigned size> struct Symbols {};

template<> struct Symbols<4> {
  static constexpr char symbols[] = "1234";
};

template<> struct Symbols<9> {
  static constexpr char symbols[] = "123456789";
};

template<> struct Symbols<16> {
  static constexpr char symbols[] = "123456789ABCDEFG";
};

template<> struct Symbols<25> {
  static constexpr char symbols[] = "123456789ABCDEFGHIJKLMNOP";
};

template<unsigned size>
class SudokuAlphabet {
  static_assert(sizeof(Symbols<size>::symbols) == size + 1);

 public:
  static constexpr std::optional<unsigned> get_value(char c) {
    for (unsigned i = 0; i != size; ++i) {
      if (Symbols<size>::symbols[i] == c) {
        return i;
      }
    }
    return {};
  }

  static constexpr char get_symbol(std::optional<unsigned> value) {
    if (value) {
      assert(*value < size);
      return Symbols<size>::symbols[*value];
    } else {
      return '.';
    }
  }
};

#endif  // PUZZLE_SUDOKU_ALPHABET_HPP_
