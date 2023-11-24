// Copyright 2023 Vincent Jacques

#include "sudoku.hpp"

#include <cassert>

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


template<unsigned size>
Sudoku<ValueCell, size> Sudoku<ValueCell, size>::load(std::istream& is) {
  Sudoku<ValueCell, size> sudoku;

  std::string line;
  // @todo Improve robustness to malformed inputs
  for (const unsigned row : SudokuConstants<size>::values) {
    std::getline(is, line);

    for (const unsigned col : SudokuConstants<size>::values) {
      const char c = line[col];
      if (c >= '1' && c <= '9') {
        sudoku.cell({row, col}).set(c - '1');
      }
    }
  }

  return sudoku;
}

template<unsigned size>
void Sudoku<ValueCell, size>::dump(std::ostream& os) const {
  for (const unsigned row : SudokuConstants<size>::values) {
    for (const unsigned col : SudokuConstants<size>::values) {
      const auto value = this->cell({row, col}).get();
      if (value) {
        os << *value + 1;
      } else {
        os << '.';
      }
    }
    os << '\n';
  }
}



template<>
class Sudoku<ValueCell, static_cast<unsigned int>(4)> : public SudokuBase<ValueCell, 4>
{
  
  public: 
  static Sudoku<ValueCell, static_cast<unsigned int>(4)> load(std::basic_istream<char> & is)
  {
    Sudoku<ValueCell, static_cast<unsigned int>(4)> sudoku = Sudoku<ValueCell, static_cast<unsigned int>(4)>() /* NRVO variable */;
    std::basic_string<char, std::char_traits<char>, std::allocator<char> > line = std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
    {
      const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
      const unsigned int * __begin0 = __range1.begin();
      const unsigned int * __end0 = __range1.end();
      for(; __begin0 != __end0; ++__begin0) {
        const unsigned int row = *__begin0;
        std::getline<char, std::char_traits<char>, std::allocator<char> >(is, line);
        {
          const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
          const unsigned int * __begin0 = __range2.begin();
          const unsigned int * __end0 = __range2.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int col = *__begin0;
            const char c = line.operator[](static_cast<unsigned long>(col));
            if((static_cast<int>(c) >= static_cast<int>('1')) && (static_cast<int>(c) <= static_cast<int>('9'))) {
              static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cell(std::pair<unsigned int, unsigned int>{row, col})).set(static_cast<unsigned int>(static_cast<int>(c) - static_cast<int>('1')));
            } 
            
          }
          
        }
      }
      
    }
    return Sudoku<ValueCell, static_cast<unsigned int>(4)>(static_cast<const Sudoku<ValueCell, static_cast<unsigned int>(4)> &&>(sudoku));
  }
  
  void dump(std::basic_ostream<char> & os) const
  {
    {
      const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
      const unsigned int * __begin0 = __range1.begin();
      const unsigned int * __end0 = __range1.end();
      for(; __begin0 != __end0; ++__begin0) {
        const unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
          const unsigned int * __begin0 = __range2.begin();
          const unsigned int * __end0 = __range2.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int col = *__begin0;
            const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(/* static_cast<const SudokuBase<ValueCell, 4> *>(this)-> */ cell(std::pair<unsigned int, unsigned int>{row, col})).get());
            if(static_cast<bool>(value.operator bool())) {
              os.operator<<(value.operator*() + static_cast<unsigned int>(1));
            } else {
              std::operator<<(os, '.');
            } 
            
          }
          
        }
        std::operator<<(os, '\n');
      }
      
    }
  }
  
  static Sudoku<ValueCell, static_cast<unsigned int>(4)> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
  // inline Sudoku(const Sudoku<ValueCell, static_cast<unsigned int>(4)> &) noexcept(false) = default;
  // inline Sudoku(Sudoku<ValueCell, static_cast<unsigned int>(4)> &&) /* noexcept */ = delete;
  // inline Sudoku<ValueCell, static_cast<unsigned int>(4)> & operator=(Sudoku<ValueCell, static_cast<unsigned int>(4)> &&) /* noexcept */ = delete;
  // inline Sudoku() noexcept(false) = default;
};





template<>
class Sudoku<ValueCell, static_cast<unsigned int>(9)> : public SudokuBase<ValueCell, 9>
{
  
  public: 
  static Sudoku<ValueCell, static_cast<unsigned int>(9)> load(std::basic_istream<char> & is)
  {
    Sudoku<ValueCell, static_cast<unsigned int>(9)> sudoku = Sudoku<ValueCell, static_cast<unsigned int>(9)>() /* NRVO variable */;
    std::basic_string<char, std::char_traits<char>, std::allocator<char> > line = std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
    {
      const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
      const unsigned int * __begin0 = __range1.begin();
      const unsigned int * __end0 = __range1.end();
      for(; __begin0 != __end0; ++__begin0) {
        const unsigned int row = *__begin0;
        std::getline<char, std::char_traits<char>, std::allocator<char> >(is, line);
        {
          const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
          const unsigned int * __begin0 = __range2.begin();
          const unsigned int * __end0 = __range2.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int col = *__begin0;
            const char c = line.operator[](static_cast<unsigned long>(col));
            if((static_cast<int>(c) >= static_cast<int>('1')) && (static_cast<int>(c) <= static_cast<int>('9'))) {
              static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cell(std::pair<unsigned int, unsigned int>{row, col})).set(static_cast<unsigned int>(static_cast<int>(c) - static_cast<int>('1')));
            } 
            
          }
          
        }
      }
      
    }
    return Sudoku<ValueCell, static_cast<unsigned int>(9)>(static_cast<const Sudoku<ValueCell, static_cast<unsigned int>(9)> &&>(sudoku));
  }
  
  void dump(std::basic_ostream<char> & os) const
  {
    {
      const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
      const unsigned int * __begin0 = __range1.begin();
      const unsigned int * __end0 = __range1.end();
      for(; __begin0 != __end0; ++__begin0) {
        const unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
          const unsigned int * __begin0 = __range2.begin();
          const unsigned int * __end0 = __range2.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int col = *__begin0;
            const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(/* static_cast<const SudokuBase<ValueCell, 9> *>(this)-> */ cell(std::pair<unsigned int, unsigned int>{row, col})).get());
            if(static_cast<bool>(value.operator bool())) {
              os.operator<<(value.operator*() + static_cast<unsigned int>(1));
            } else {
              std::operator<<(os, '.');
            } 
            
          }
          
        }
        std::operator<<(os, '\n');
      }
      
    }
  }
  
  static Sudoku<ValueCell, static_cast<unsigned int>(9)> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
  // inline Sudoku(const Sudoku<ValueCell, static_cast<unsigned int>(9)> &) noexcept(false) = default;
  // inline Sudoku(Sudoku<ValueCell, static_cast<unsigned int>(9)> &&) /* noexcept */ = delete;
  // inline Sudoku<ValueCell, static_cast<unsigned int>(9)> & operator=(Sudoku<ValueCell, static_cast<unsigned int>(9)> &&) /* noexcept */ = delete;
  // inline Sudoku() noexcept(false) = default;
};





// LCOV_EXCL_START

struct TestCell
{
  unsigned int val = static_cast<unsigned int>(0);
  // inline constexpr TestCell(const TestCell &) noexcept = default;
  // inline constexpr TestCell() noexcept = default;
};



TEST_CASE("sudoku - cells") {
  Sudoku<TestCell, 4> sudoku;
  std::vector<Coordinates> cells;
  for (const auto& cell : sudoku.cells()) {
    CHECK(!cell.val);
    cells.push_back(cell.coordinates());
  }
  CHECK(cells == std::vector(SudokuConstants<4>::cells.begin(), SudokuConstants<4>::cells.end()));
}

TEST_CASE("sudoku - copy - ephemeral cells") {
  Sudoku<TestCell, 4> sudoku1;
  CHECK(sudoku1.cell({0, 0}).val == 0);
  sudoku1.cell({0, 0}).val = 1;
  CHECK(sudoku1.cell({0, 0}).val == 1);

  Sudoku<TestCell, 4> sudoku2 = sudoku1;
  CHECK(sudoku2.cell({0, 0}).val == 1);
  sudoku1.cell({0, 0}).val = 2;
  sudoku2.cell({0, 0}).val = 3;
  CHECK(sudoku1.cell({0, 0}).val == 2);
  CHECK(sudoku2.cell({0, 0}).val == 3);
}

TEST_CASE("sudoku - copy - long-lived cells") {
  Sudoku<TestCell, 4> sudoku1;
  auto& cell1 = sudoku1.cell({0, 0});
  CHECK(cell1.val == 0);
  cell1.val = 1;
  CHECK(cell1.val == 1);

  Sudoku<TestCell, 4> sudoku2 = sudoku1;
  auto& cell2 = sudoku2.cell({0, 0});

  CHECK(cell2.val == 1);
  cell1.val = 2;
  cell2.val = 3;
  CHECK(cell1.val == 2);
  CHECK(cell2.val == 3);
}

TEST_CASE("sudoku - cell equality") {
  Sudoku<TestCell, 4> sudoku;
  CHECK(sudoku.cell({0, 0}) == sudoku.cell({0, 0}));
  CHECK(sudoku.cell({0, 0}) != sudoku.cell({0, 1}));
  CHECK(sudoku.cell({0, 0}) != sudoku.cell({1, 0}));
  CHECK(sudoku.cell({0, 0}) != sudoku.cell({1, 1}));
}

// LCOV_EXCL_STOP
