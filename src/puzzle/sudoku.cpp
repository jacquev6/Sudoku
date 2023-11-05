// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>
#include <map>


namespace io {

template<unsigned size>
constexpr std::map<char, unsigned> invert_symbols(const char symbols[size]) {
  std::map<char, unsigned> result;
  for (unsigned i = 0; i < size; ++i) {
    result[symbols[i]] = i;
  }
  return result;
}

template<unsigned size>
struct Alphabet {};

template<> struct Alphabet<4> {
  static constexpr char value_to_symbol[] = {'1', '2', '3', '4'};
  static const std::map<char, unsigned> symbol_to_value;
};
const std::map<char, unsigned> Alphabet<4>::symbol_to_value = invert_symbols<4>(value_to_symbol);

template<> struct Alphabet<9> {
  static constexpr char value_to_symbol[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  static const std::map<char, unsigned> symbol_to_value;
};
const std::map<char, unsigned> Alphabet<9>::symbol_to_value = invert_symbols<9>(value_to_symbol);

template<> struct Alphabet<16> {
  static constexpr char value_to_symbol[] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  static const std::map<char, unsigned> symbol_to_value;
};
const std::map<char, unsigned> Alphabet<16>::symbol_to_value = invert_symbols<16>(value_to_symbol);

template<> struct Alphabet<25> {
  static const std::map<char, unsigned> symbol_to_value;
  static constexpr char value_to_symbol[] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
};
const std::map<char, unsigned> Alphabet<25>::symbol_to_value = invert_symbols<25>(value_to_symbol);

template<> struct Alphabet<36> {
  static constexpr char value_to_symbol[] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0'};
  static const std::map<char, unsigned> symbol_to_value;
};
const std::map<char, unsigned> Alphabet<36>::symbol_to_value = invert_symbols<36>(value_to_symbol);

template<unsigned size>
void Sudoku<size>::set(const Coordinates& cell, unsigned val) {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  assert(val < size);
  assert(!cells[row][col] || *cells[row][col] == val);
  cells[row][col] = val;
}

template<unsigned size>
std::optional<unsigned> Sudoku<size>::get(const Coordinates& cell) const {
  const auto [row, col] = cell;
  assert(row < size);
  assert(col < size);
  return cells[row][col];
}

template<unsigned size>
Sudoku<size> Sudoku<size>::load(std::istream& is) {
  Sudoku<size> sudoku;

  std::string line;
  // @todo Improve robustness to malformed inputs
  for (const unsigned row : SudokuConstants<size>::values) {
    std::getline(is, line);

    for (const unsigned col : SudokuConstants<size>::values) {
      const char c = line[col];
      const auto it = Alphabet<size>::symbol_to_value.find(c);
      if (it != Alphabet<size>::symbol_to_value.end()) {
        sudoku.set({row, col}, it->second);
      }
    }
  }

  return sudoku;
}

template<unsigned size>
void Sudoku<size>::dump(std::ostream& os) const {
  for (const unsigned row : SudokuConstants<size>::values) {
    for (const unsigned col : SudokuConstants<size>::values) {
      const auto value = get({row, col});
      if (value) {
        assert(value < size);
        static_assert(sizeof(Alphabet<size>::value_to_symbol) == size * sizeof(char));
        os << Alphabet<size>::value_to_symbol[*value];
      } else {
        os << '.';
      }
    }
    os << '\n';
  }
}

template class Sudoku<4>;
template class Sudoku<9>;
template class Sudoku<16>;
template class Sudoku<25>;
template class Sudoku<36>;

}  // namespace io
