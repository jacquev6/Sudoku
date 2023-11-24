// Copyright 2023 Vincent Jacques

// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_SUDOKU_CONSTANTS_HPP_
#define PUZZLE_SUDOKU_CONSTANTS_HPP_

#include <array>
#include <utility>


// @todo Put this typedef in a template<unsigned size> (probably SudokuConstants),
// to let the type system detect if we try to mix coordinates for different size puzzles
typedef std::pair<unsigned, unsigned> Coordinates;


template<unsigned int size>
class SudokuConstants
{
  
  private: 
  static inline constexpr unsigned int sqrt(unsigned int res, unsigned int l, unsigned int r)
  {
    if(l == r) {
      return r;
    } else {
      const unsigned int mid = (r + l) / static_cast<unsigned int>(2);
      if((mid * mid) >= res) {
        return sqrt(res, l, mid);
      } else {
        return sqrt(res, mid + static_cast<unsigned int>(1), r);
      } 
      
    } 
    
  }
  
  static inline constexpr unsigned int sqrt(unsigned int res)
  {
    return sqrt(res, 1, res);
  }
  
  
  private: 
  static inline constexpr auto make_values()
  {
    std::array<unsigned int, size> values;
    for(unsigned int i = static_cast<unsigned int>(0); i != size; ++i) {
      values[i] = i;
    }
    
    return values;
  }
  
  static inline constexpr auto make_cells()
  {
    std::array<std::pair<unsigned int, unsigned int>, size * size> cells;
    {
      auto && __range2 = make_values();
      for(; ; ) {
        unsigned int row;
        {
          auto && __range3 = make_values();
          for(; ; ) {
            unsigned int col;
            cells[(row * size) + col] = {row, col};
          }
          
        }
      }
      
    }
    return cells;
  }
  
  static inline constexpr auto make_region_indexes()
  {
    std::array<unsigned int, 3 * size> region_indexes;
    for(unsigned int i = static_cast<unsigned int>(0); i != (static_cast<unsigned int>(3) * size); ++i) {
      region_indexes[i] = i;
    }
    
    return region_indexes;
  }
  
  static inline constexpr auto make_regions()
  {
    std::array<std::array<std::pair<unsigned int, unsigned int>, size>, 3 * size> regions;
    {
      auto && __range2 = make_values();
      for(; ; ) {
        unsigned int row;
        {
          auto && __range3 = make_values();
          for(; ; ) {
            unsigned int col;
            regions[row][col] = {row, col};
          }
          
        }
      }
      
    }
    {
      auto && __range2 = make_values();
      for(; ; ) {
        unsigned int col;
        {
          auto && __range3 = make_values();
          for(; ; ) {
            unsigned int row;
            regions[size + col][row] = {row, col};
          }
          
        }
      }
      
    }
    {
      auto && __range2 = make_values();
      for(; ; ) {
        unsigned int square;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          auto && __range3 = make_values();
          for(; ; ) {
            unsigned int cell;
            const unsigned int delta_row = cell / sqrt_size;
            const unsigned int delta_col = cell % sqrt_size;
            const unsigned int row = top_row + delta_row;
            const unsigned int col = left_col + delta_col;
            regions[(static_cast<unsigned int>(2) * size) + square][cell] = {row, col};
          }
          
        }
      }
      
    }
    return regions;
  }
  
  static inline constexpr auto make_regions_of()
  {
    std::array<std::array<std::array<unsigned int, 3>, size>, size> regions_of;
    {
      auto && __range2 = make_values();
      for(; ; ) {
        unsigned int row;
        {
          auto && __range3 = make_values();
          for(; ; ) {
            unsigned int col;
            regions_of[row][col] = {row, size + col, ((static_cast<unsigned int>(2) * size) + ((row / sqrt_size) * sqrt_size)) + (col / sqrt_size)};
          }
          
        }
      }
      
    }
    return regions_of;
  }
  
  
  public: 
  inline static constexpr const unsigned int sqrt_size = sqrt(size);
  inline static constexpr const auto values = make_values();
  inline static constexpr const auto cells = make_cells();
  inline static constexpr const auto region_indexes = make_region_indexes();
  inline static constexpr const auto regions = make_regions();
  inline static constexpr const auto regions_of = make_regions_of();
  
  private: 
  
  /* PASSED: static_assert((sqrt_size * sqrt_size) == size, "'size' must be a perfect square"); */
};

/* First instantiated from: sudoku-constants.cpp:121 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuConstants<4>
{
  
  private: 
  static inline constexpr unsigned int sqrt(unsigned int res, unsigned int l, unsigned int r)
  {
    if(l == r) {
      return r;
    } else {
      const unsigned int mid = (r + l) / static_cast<unsigned int>(2);
      if((mid * mid) >= res) {
        return sqrt(res, l, mid);
      } else {
        return sqrt(res, mid + static_cast<unsigned int>(1), r);
      } 
      
    } 
    
  }
  
  static inline constexpr unsigned int sqrt(unsigned int res)
  {
    return sqrt(res, static_cast<unsigned int>(1), res);
  }
  
  
  private: 
  static inline constexpr std::array<unsigned int, 4> make_values()
  {
    std::array<unsigned int, 4> values;
    for(unsigned int i = static_cast<unsigned int>(0); i != 4U; ++i) {
      values.operator[](static_cast<unsigned long>(i)) = i;
    }
    
    return std::array<unsigned int, 4>(static_cast<std::array<unsigned int, 4> &&>(values));
  }
  
  static inline constexpr std::array<std::pair<unsigned int, unsigned int>, 16> make_cells()
  {
    std::array<std::pair<unsigned int, unsigned int>, 16> cells = std::array<std::pair<unsigned int, unsigned int>, 16>();
    {
      std::array<unsigned int, 4> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 4> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            cells.operator[](static_cast<unsigned long>((row * 4U) + col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    return std::array<std::pair<unsigned int, unsigned int>, 16>(static_cast<std::array<std::pair<unsigned int, unsigned int>, 16> &&>(cells));
  }
  
  static inline constexpr std::array<unsigned int, 12> make_region_indexes()
  {
    std::array<unsigned int, 12> region_indexes;
    for(unsigned int i = static_cast<unsigned int>(0); i != (static_cast<unsigned int>(3) * 4U); ++i) {
      region_indexes.operator[](static_cast<unsigned long>(i)) = i;
    }
    
    return std::array<unsigned int, 12>(static_cast<std::array<unsigned int, 12> &&>(region_indexes));
  }
  
  static inline constexpr std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12> make_regions()
  {
    std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12> regions = std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12>();
    {
      std::array<unsigned int, 4> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 4> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 4> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int col = *__begin0;
        {
          std::array<unsigned int, 4> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int row = *__begin0;
            regions.operator[](static_cast<unsigned long>(4U + col)).operator[](static_cast<unsigned long>(row)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 4> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int square = *__begin0;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          std::array<unsigned int, 4> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int cell = *__begin0;
            const unsigned int delta_row = cell / sqrt_size;
            const unsigned int delta_col = cell % sqrt_size;
            const unsigned int row = top_row + delta_row;
            const unsigned int col = left_col + delta_col;
            regions.operator[](static_cast<unsigned long>((static_cast<unsigned int>(2) * 4U) + square)).operator[](static_cast<unsigned long>(cell)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    return std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12>(static_cast<std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12> &&>(regions));
  }
  
  static inline constexpr std::array<std::array<std::array<unsigned int, 3>, 4>, 4> make_regions_of()
  {
    std::array<std::array<std::array<unsigned int, 3>, 4>, 4> regions_of;
    {
      std::array<unsigned int, 4> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 4> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions_of.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=({{row, 4U + col, ((static_cast<unsigned int>(2) * 4U) + ((row / sqrt_size) * sqrt_size)) + (col / sqrt_size)}});
          }
          
        }
      }
      
    }
    return std::array<std::array<std::array<unsigned int, 3>, 4>, 4>(static_cast<std::array<std::array<std::array<unsigned int, 3>, 4>, 4> &&>(regions_of));
  }
  
  
  public: 
  inline static constexpr const unsigned int sqrt_size = sqrt(4U);
  inline static constexpr const std::array<unsigned int, 4> values = static_cast<const std::array<unsigned int, 4>>(make_values());
  inline static constexpr const std::array<std::pair<unsigned int, unsigned int>, 16> cells = static_cast<const std::array<std::pair<unsigned int, unsigned int>, 16>>(make_cells());
  inline static constexpr const std::array<unsigned int, 12> region_indexes = static_cast<const std::array<unsigned int, 12>>(make_region_indexes());
  inline static constexpr const std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12> regions = static_cast<const std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12>>(make_regions());
  inline static constexpr const std::array<std::array<std::array<unsigned int, 3>, 4>, 4> regions_of = static_cast<const std::array<std::array<std::array<unsigned int, 3>, 4>, 4>>(make_regions_of());
  
  private: 
  
  /* PASSED: static_assert((sqrt_size * sqrt_size) == 4U, "'size' must be a perfect square"); */
};

#endif
/* First instantiated from: sudoku-constants.cpp:154 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuConstants<9>
{
  
  private: 
  static inline constexpr unsigned int sqrt(unsigned int res, unsigned int l, unsigned int r)
  {
    if(l == r) {
      return r;
    } else {
      const unsigned int mid = (r + l) / static_cast<unsigned int>(2);
      if((mid * mid) >= res) {
        return sqrt(res, l, mid);
      } else {
        return sqrt(res, mid + static_cast<unsigned int>(1), r);
      } 
      
    } 
    
  }
  
  static inline constexpr unsigned int sqrt(unsigned int res)
  {
    return sqrt(res, static_cast<unsigned int>(1), res);
  }
  
  
  private: 
  static inline constexpr std::array<unsigned int, 9> make_values()
  {
    std::array<unsigned int, 9> values;
    for(unsigned int i = static_cast<unsigned int>(0); i != 9U; ++i) {
      values.operator[](static_cast<unsigned long>(i)) = i;
    }
    
    return std::array<unsigned int, 9>(static_cast<std::array<unsigned int, 9> &&>(values));
  }
  
  static inline constexpr std::array<std::pair<unsigned int, unsigned int>, 81> make_cells()
  {
    std::array<std::pair<unsigned int, unsigned int>, 81> cells = std::array<std::pair<unsigned int, unsigned int>, 81>();
    {
      std::array<unsigned int, 9> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 9> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            cells.operator[](static_cast<unsigned long>((row * 9U) + col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    return std::array<std::pair<unsigned int, unsigned int>, 81>(static_cast<std::array<std::pair<unsigned int, unsigned int>, 81> &&>(cells));
  }
  
  static inline constexpr std::array<unsigned int, 27> make_region_indexes()
  {
    std::array<unsigned int, 27> region_indexes;
    for(unsigned int i = static_cast<unsigned int>(0); i != (static_cast<unsigned int>(3) * 9U); ++i) {
      region_indexes.operator[](static_cast<unsigned long>(i)) = i;
    }
    
    return std::array<unsigned int, 27>(static_cast<std::array<unsigned int, 27> &&>(region_indexes));
  }
  
  static inline constexpr std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27> make_regions()
  {
    std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27> regions = std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27>();
    {
      std::array<unsigned int, 9> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 9> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 9> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int col = *__begin0;
        {
          std::array<unsigned int, 9> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int row = *__begin0;
            regions.operator[](static_cast<unsigned long>(9U + col)).operator[](static_cast<unsigned long>(row)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 9> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int square = *__begin0;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          std::array<unsigned int, 9> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int cell = *__begin0;
            const unsigned int delta_row = cell / sqrt_size;
            const unsigned int delta_col = cell % sqrt_size;
            const unsigned int row = top_row + delta_row;
            const unsigned int col = left_col + delta_col;
            regions.operator[](static_cast<unsigned long>((static_cast<unsigned int>(2) * 9U) + square)).operator[](static_cast<unsigned long>(cell)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    return std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27>(static_cast<std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27> &&>(regions));
  }
  
  static inline constexpr std::array<std::array<std::array<unsigned int, 3>, 9>, 9> make_regions_of()
  {
    std::array<std::array<std::array<unsigned int, 3>, 9>, 9> regions_of;
    {
      std::array<unsigned int, 9> && __range2 = make_values();
      unsigned int * __begin0 = __range2.begin();
      unsigned int * __end0 = __range2.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 9> && __range3 = make_values();
          unsigned int * __begin0 = __range3.begin();
          unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions_of.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=({{row, 9U + col, ((static_cast<unsigned int>(2) * 9U) + ((row / sqrt_size) * sqrt_size)) + (col / sqrt_size)}});
          }
          
        }
      }
      
    }
    return std::array<std::array<std::array<unsigned int, 3>, 9>, 9>(static_cast<std::array<std::array<std::array<unsigned int, 3>, 9>, 9> &&>(regions_of));
  }
  
  
  public: 
  inline static constexpr const unsigned int sqrt_size = sqrt(9U);
  inline static constexpr const std::array<unsigned int, 9> values = static_cast<const std::array<unsigned int, 9>>(make_values());
  inline static constexpr const std::array<std::pair<unsigned int, unsigned int>, 81> cells = static_cast<const std::array<std::pair<unsigned int, unsigned int>, 81>>(make_cells());
  inline static constexpr const std::array<unsigned int, 27> region_indexes = static_cast<const std::array<unsigned int, 27>>(make_region_indexes());
  inline static constexpr const std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27> regions = static_cast<const std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27>>(make_regions());
  inline static constexpr const std::array<std::array<std::array<unsigned int, 3>, 9>, 9> regions_of = static_cast<const std::array<std::array<std::array<unsigned int, 3>, 9>, 9>>(make_regions_of());
  
  private: 
  
  /* PASSED: static_assert((sqrt_size * sqrt_size) == 9U, "'size' must be a perfect square"); */
};

#endif


#endif  // PUZZLE_SUDOKU_CONSTANTS_HPP_


/* PASSED: static_assert(std::operator==(SudokuConstants<4>::values, const std::array<unsigned int, 4>{{static_cast<unsigned int>(0), static_cast<unsigned int>(1), static_cast<unsigned int>(2), static_cast<unsigned int>(3)}})); */


/* PASSED: static_assert(std::operator==(SudokuConstants<4>::cells, const std::array<std::pair<unsigned int, unsigned int>, 16>{{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{0, 3}, std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{1, 1}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{1, 3}, std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{2, 2}, std::pair<unsigned int, unsigned int>{2, 3}, std::pair<unsigned int, unsigned int>{3, 0}, std::pair<unsigned int, unsigned int>{3, 1}, std::pair<unsigned int, unsigned int>{3, 2}, std::pair<unsigned int, unsigned int>{3, 3}}})); */


/* PASSED: static_assert(std::operator==(SudokuConstants<4>::region_indexes, const std::array<unsigned int, 12>{{static_cast<unsigned int>(0), static_cast<unsigned int>(1), static_cast<unsigned int>(2), static_cast<unsigned int>(3), static_cast<unsigned int>(4), static_cast<unsigned int>(5), static_cast<unsigned int>(6), static_cast<unsigned int>(7), static_cast<unsigned int>(8), static_cast<unsigned int>(9), static_cast<unsigned int>(10), static_cast<unsigned int>(11)}})); */


/* PASSED: static_assert(std::operator==(SudokuConstants<4>::regions, const std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12>{{{{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{0, 3}}}, {{std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{1, 1}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{1, 3}}}, {{std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{2, 2}, std::pair<unsigned int, unsigned int>{2, 3}}}, {{std::pair<unsigned int, unsigned int>{3, 0}, std::pair<unsigned int, unsigned int>{3, 1}, std::pair<unsigned int, unsigned int>{3, 2}, std::pair<unsigned int, unsigned int>{3, 3}}}, {{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{3, 0}}}, {{std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{1, 1}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{3, 1}}}, {{std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{2, 2}, std::pair<unsigned int, unsigned int>{3, 2}}}, {{std::pair<unsigned int, unsigned int>{0, 3}, std::pair<unsigned int, unsigned int>{1, 3}, std::pair<unsigned int, unsigned int>{2, 3}, std::pair<unsigned int, unsigned int>{3, 3}}}, {{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{1, 1}}}, {{std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{0, 3}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{1, 3}}}, {{std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{3, 0}, std::pair<unsigned int, unsigned int>{3, 1}}}, {{std::pair<unsigned int, unsigned int>{2, 2}, std::pair<unsigned int, unsigned int>{2, 3}, std::pair<unsigned int, unsigned int>{3, 2}, std::pair<unsigned int, unsigned int>{3, 3}}}}})); */


/* PASSED: static_assert(std::operator==(SudokuConstants<9>::regions, const std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27>{{{{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{0, 3}, std::pair<unsigned int, unsigned int>{0, 4}, std::pair<unsigned int, unsigned int>{0, 5}, std::pair<unsigned int, unsigned int>{0, 6}, std::pair<unsigned int, unsigned int>{0, 7}, std::pair<unsigned int, unsigned int>{0, 8}}}, {{std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{1, 1}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{1, 3}, std::pair<unsigned int, unsigned int>{1, 4}, std::pair<unsigned int, unsigned int>{1, 5}, std::pair<unsigned int, unsigned int>{1, 6}, std::pair<unsigned int, unsigned int>{1, 7}, std::pair<unsigned int, unsigned int>{1, 8}}}, {{std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{2, 2}, std::pair<unsigned int, unsigned int>{2, 3}, std::pair<unsigned int, unsigned int>{2, 4}, std::pair<unsigned int, unsigned int>{2, 5}, std::pair<unsigned int, unsigned int>{2, 6}, std::pair<unsigned int, unsigned int>{2, 7}, std::pair<unsigned int, unsigned int>{2, 8}}}, {{std::pair<unsigned int, unsigned int>{3, 0}, std::pair<unsigned int, unsigned int>{3, 1}, std::pair<unsigned int, unsigned int>{3, 2}, std::pair<unsigned int, unsigned int>{3, 3}, std::pair<unsigned int, unsigned int>{3, 4}, std::pair<unsigned int, unsigned int>{3, 5}, std::pair<unsigned int, unsigned int>{3, 6}, std::pair<unsigned int, unsigned int>{3, 7}, std::pair<unsigned int, unsigned int>{3, 8}}}, {{std::pair<unsigned int, unsigned int>{4, 0}, std::pair<unsigned int, unsigned int>{4, 1}, std::pair<unsigned int, unsigned int>{4, 2}, std::pair<unsigned int, unsigned int>{4, 3}, std::pair<unsigned int, unsigned int>{4, 4}, std::pair<unsigned int, unsigned int>{4, 5}, std::pair<unsigned int, unsigned int>{4, 6}, std::pair<unsigned int, unsigned int>{4, 7}, std::pair<unsigned int, unsigned int>{4, 8}}}, {{std::pair<unsigned int, unsigned int>{5, 0}, std::pair<unsigned int, unsigned int>{5, 1}, std::pair<unsigned int, unsigned int>{5, 2}, std::pair<unsigned int, unsigned int>{5, 3}, std::pair<unsigned int, unsigned int>{5, 4}, std::pair<unsigned int, unsigned int>{5, 5}, std::pair<unsigned int, unsigned int>{5, 6}, std::pair<unsigned int, unsigned int>{5, 7}, std::pair<unsigned int, unsigned int>{5, 8}}}, {{std::pair<unsigned int, unsigned int>{6, 0}, std::pair<unsigned int, unsigned int>{6, 1}, std::pair<unsigned int, unsigned int>{6, 2}, std::pair<unsigned int, unsigned int>{6, 3}, std::pair<unsigned int, unsigned int>{6, 4}, std::pair<unsigned int, unsigned int>{6, 5}, std::pair<unsigned int, unsigned int>{6, 6}, std::pair<unsigned int, unsigned int>{6, 7}, std::pair<unsigned int, unsigned int>{6, 8}}}, {{std::pair<unsigned int, unsigned int>{7, 0}, std::pair<unsigned int, unsigned int>{7, 1}, std::pair<unsigned int, unsigned int>{7, 2}, std::pair<unsigned int, unsigned int>{7, 3}, std::pair<unsigned int, unsigned int>{7, 4}, std::pair<unsigned int, unsigned int>{7, 5}, std::pair<unsigned int, unsigned int>{7, 6}, std::pair<unsigned int, unsigned int>{7, 7}, std::pair<unsigned int, unsigned int>{7, 8}}}, {{std::pair<unsigned int, unsigned int>{8, 0}, std::pair<unsigned int, unsigned int>{8, 1}, std::pair<unsigned int, unsigned int>{8, 2}, std::pair<unsigned int, unsigned int>{8, 3}, std::pair<unsigned int, unsigned int>{8, 4}, std::pair<unsigned int, unsigned int>{8, 5}, std::pair<unsigned int, unsigned int>{8, 6}, std::pair<unsigned int, unsigned int>{8, 7}, std::pair<unsigned int, unsigned int>{8, 8}}}, {{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{3, 0}, std::pair<unsigned int, unsigned int>{4, 0}, std::pair<unsigned int, unsigned int>{5, 0}, std::pair<unsigned int, unsigned int>{6, 0}, std::pair<unsigned int, unsigned int>{7, 0}, std::pair<unsigned int, unsigned int>{8, 0}}}, {{std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{1, 1}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{3, 1}, std::pair<unsigned int, unsigned int>{4, 1}, std::pair<unsigned int, unsigned int>{5, 1}, std::pair<unsigned int, unsigned int>{6, 1}, std::pair<unsigned int, unsigned int>{7, 1}, std::pair<unsigned int, unsigned int>{8, 1}}}, {{std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{2, 2}, std::pair<unsigned int, unsigned int>{3, 2}, std::pair<unsigned int, unsigned int>{4, 2}, std::pair<unsigned int, unsigned int>{5, 2}, std::pair<unsigned int, unsigned int>{6, 2}, std::pair<unsigned int, unsigned int>{7, 2}, std::pair<unsigned int, unsigned int>{8, 2}}}, {{std::pair<unsigned int, unsigned int>{0, 3}, std::pair<unsigned int, unsigned int>{1, 3}, std::pair<unsigned int, unsigned int>{2, 3}, std::pair<unsigned int, unsigned int>{3, 3}, std::pair<unsigned int, unsigned int>{4, 3}, std::pair<unsigned int, unsigned int>{5, 3}, std::pair<unsigned int, unsigned int>{6, 3}, std::pair<unsigned int, unsigned int>{7, 3}, std::pair<unsigned int, unsigned int>{8, 3}}}, {{std::pair<unsigned int, unsigned int>{0, 4}, std::pair<unsigned int, unsigned int>{1, 4}, std::pair<unsigned int, unsigned int>{2, 4}, std::pair<unsigned int, unsigned int>{3, 4}, std::pair<unsigned int, unsigned int>{4, 4}, std::pair<unsigned int, unsigned int>{5, 4}, std::pair<unsigned int, unsigned int>{6, 4}, std::pair<unsigned int, unsigned int>{7, 4}, std::pair<unsigned int, unsigned int>{8, 4}}}, {{std::pair<unsigned int, unsigned int>{0, 5}, std::pair<unsigned int, unsigned int>{1, 5}, std::pair<unsigned int, unsigned int>{2, 5}, std::pair<unsigned int, unsigned int>{3, 5}, std::pair<unsigned int, unsigned int>{4, 5}, std::pair<unsigned int, unsigned int>{5, 5}, std::pair<unsigned int, unsigned int>{6, 5}, std::pair<unsigned int, unsigned int>{7, 5}, std::pair<unsigned int, unsigned int>{8, 5}}}, {{std::pair<unsigned int, unsigned int>{0, 6}, std::pair<unsigned int, unsigned int>{1, 6}, std::pair<unsigned int, unsigned int>{2, 6}, std::pair<unsigned int, unsigned int>{3, 6}, std::pair<unsigned int, unsigned int>{4, 6}, std::pair<unsigned int, unsigned int>{5, 6}, std::pair<unsigned int, unsigned int>{6, 6}, std::pair<unsigned int, unsigned int>{7, 6}, std::pair<unsigned int, unsigned int>{8, 6}}}, {{std::pair<unsigned int, unsigned int>{0, 7}, std::pair<unsigned int, unsigned int>{1, 7}, std::pair<unsigned int, unsigned int>{2, 7}, std::pair<unsigned int, unsigned int>{3, 7}, std::pair<unsigned int, unsigned int>{4, 7}, std::pair<unsigned int, unsigned int>{5, 7}, std::pair<unsigned int, unsigned int>{6, 7}, std::pair<unsigned int, unsigned int>{7, 7}, std::pair<unsigned int, unsigned int>{8, 7}}}, {{std::pair<unsigned int, unsigned int>{0, 8}, std::pair<unsigned int, unsigned int>{1, 8}, std::pair<unsigned int, unsigned int>{2, 8}, std::pair<unsigned int, unsigned int>{3, 8}, std::pair<unsigned int, unsigned int>{4, 8}, std::pair<unsigned int, unsigned int>{5, 8}, std::pair<unsigned int, unsigned int>{6, 8}, std::pair<unsigned int, unsigned int>{7, 8}, std::pair<unsigned int, unsigned int>{8, 8}}}, {{std::pair<unsigned int, unsigned int>{0, 0}, std::pair<unsigned int, unsigned int>{0, 1}, std::pair<unsigned int, unsigned int>{0, 2}, std::pair<unsigned int, unsigned int>{1, 0}, std::pair<unsigned int, unsigned int>{1, 1}, std::pair<unsigned int, unsigned int>{1, 2}, std::pair<unsigned int, unsigned int>{2, 0}, std::pair<unsigned int, unsigned int>{2, 1}, std::pair<unsigned int, unsigned int>{2, 2}}}, {{std::pair<unsigned int, unsigned int>{0, 3}, std::pair<unsigned int, unsigned int>{0, 4}, std::pair<unsigned int, unsigned int>{0, 5}, std::pair<unsigned int, unsigned int>{1, 3}, std::pair<unsigned int, unsigned int>{1, 4}, std::pair<unsigned int, unsigned int>{1, 5}, std::pair<unsigned int, unsigned int>{2, 3}, std::pair<unsigned int, unsigned int>{2, 4}, std::pair<unsigned int, unsigned int>{2, 5}}}, {{std::pair<unsigned int, unsigned int>{0, 6}, std::pair<unsigned int, unsigned int>{0, 7}, std::pair<unsigned int, unsigned int>{0, 8}, std::pair<unsigned int, unsigned int>{1, 6}, std::pair<unsigned int, unsigned int>{1, 7}, std::pair<unsigned int, unsigned int>{1, 8}, std::pair<unsigned int, unsigned int>{2, 6}, std::pair<unsigned int, unsigned int>{2, 7}, std::pair<unsigned int, unsigned int>{2, 8}}}, {{std::pair<unsigned int, unsigned int>{3, 0}, std::pair<unsigned int, unsigned int>{3, 1}, std::pair<unsigned int, unsigned int>{3, 2}, std::pair<unsigned int, unsigned int>{4, 0}, std::pair<unsigned int, unsigned int>{4, 1}, std::pair<unsigned int, unsigned int>{4, 2}, std::pair<unsigned int, unsigned int>{5, 0}, std::pair<unsigned int, unsigned int>{5, 1}, std::pair<unsigned int, unsigned int>{5, 2}}}, {{std::pair<unsigned int, unsigned int>{3, 3}, std::pair<unsigned int, unsigned int>{3, 4}, std::pair<unsigned int, unsigned int>{3, 5}, std::pair<unsigned int, unsigned int>{4, 3}, std::pair<unsigned int, unsigned int>{4, 4}, std::pair<unsigned int, unsigned int>{4, 5}, std::pair<unsigned int, unsigned int>{5, 3}, std::pair<unsigned int, unsigned int>{5, 4}, std::pair<unsigned int, unsigned int>{5, 5}}}, {{std::pair<unsigned int, unsigned int>{3, 6}, std::pair<unsigned int, unsigned int>{3, 7}, std::pair<unsigned int, unsigned int>{3, 8}, std::pair<unsigned int, unsigned int>{4, 6}, std::pair<unsigned int, unsigned int>{4, 7}, std::pair<unsigned int, unsigned int>{4, 8}, std::pair<unsigned int, unsigned int>{5, 6}, std::pair<unsigned int, unsigned int>{5, 7}, std::pair<unsigned int, unsigned int>{5, 8}}}, {{std::pair<unsigned int, unsigned int>{6, 0}, std::pair<unsigned int, unsigned int>{6, 1}, std::pair<unsigned int, unsigned int>{6, 2}, std::pair<unsigned int, unsigned int>{7, 0}, std::pair<unsigned int, unsigned int>{7, 1}, std::pair<unsigned int, unsigned int>{7, 2}, std::pair<unsigned int, unsigned int>{8, 0}, std::pair<unsigned int, unsigned int>{8, 1}, std::pair<unsigned int, unsigned int>{8, 2}}}, {{std::pair<unsigned int, unsigned int>{6, 3}, std::pair<unsigned int, unsigned int>{6, 4}, std::pair<unsigned int, unsigned int>{6, 5}, std::pair<unsigned int, unsigned int>{7, 3}, std::pair<unsigned int, unsigned int>{7, 4}, std::pair<unsigned int, unsigned int>{7, 5}, std::pair<unsigned int, unsigned int>{8, 3}, std::pair<unsigned int, unsigned int>{8, 4}, std::pair<unsigned int, unsigned int>{8, 5}}}, {{std::pair<unsigned int, unsigned int>{6, 6}, std::pair<unsigned int, unsigned int>{6, 7}, std::pair<unsigned int, unsigned int>{6, 8}, std::pair<unsigned int, unsigned int>{7, 6}, std::pair<unsigned int, unsigned int>{7, 7}, std::pair<unsigned int, unsigned int>{7, 8}, std::pair<unsigned int, unsigned int>{8, 6}, std::pair<unsigned int, unsigned int>{8, 7}, std::pair<unsigned int, unsigned int>{8, 8}}}}})); */


/* PASSED: static_assert(std::operator==(SudokuConstants<4>::regions_of, const std::array<std::array<std::array<unsigned int, 3>, 4>, 4>{{{{{{static_cast<unsigned int>(0), static_cast<unsigned int>(4), static_cast<unsigned int>(8)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(5), static_cast<unsigned int>(8)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(6), static_cast<unsigned int>(9)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(7), static_cast<unsigned int>(9)}}}}, {{{{static_cast<unsigned int>(1), static_cast<unsigned int>(4), static_cast<unsigned int>(8)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(5), static_cast<unsigned int>(8)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(6), static_cast<unsigned int>(9)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(7), static_cast<unsigned int>(9)}}}}, {{{{static_cast<unsigned int>(2), static_cast<unsigned int>(4), static_cast<unsigned int>(10)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(5), static_cast<unsigned int>(10)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(6), static_cast<unsigned int>(11)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(7), static_cast<unsigned int>(11)}}}}, {{{{static_cast<unsigned int>(3), static_cast<unsigned int>(4), static_cast<unsigned int>(10)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(5), static_cast<unsigned int>(10)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(6), static_cast<unsigned int>(11)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(7), static_cast<unsigned int>(11)}}}}}})); */


/* PASSED: static_assert(std::operator==(SudokuConstants<9>::regions_of, const std::array<std::array<std::array<unsigned int, 3>, 9>, 9>{{{{{{static_cast<unsigned int>(0), static_cast<unsigned int>(9), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(10), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(11), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(12), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(13), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(14), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(15), static_cast<unsigned int>(20)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(16), static_cast<unsigned int>(20)}}, {{static_cast<unsigned int>(0), static_cast<unsigned int>(17), static_cast<unsigned int>(20)}}}}, {{{{static_cast<unsigned int>(1), static_cast<unsigned int>(9), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(10), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(11), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(12), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(13), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(14), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(15), static_cast<unsigned int>(20)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(16), static_cast<unsigned int>(20)}}, {{static_cast<unsigned int>(1), static_cast<unsigned int>(17), static_cast<unsigned int>(20)}}}}, {{{{static_cast<unsigned int>(2), static_cast<unsigned int>(9), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(10), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(11), static_cast<unsigned int>(18)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(12), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(13), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(14), static_cast<unsigned int>(19)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(15), static_cast<unsigned int>(20)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(16), static_cast<unsigned int>(20)}}, {{static_cast<unsigned int>(2), static_cast<unsigned int>(17), static_cast<unsigned int>(20)}}}}, {{{{static_cast<unsigned int>(3), static_cast<unsigned int>(9), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(10), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(11), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(12), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(13), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(14), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(15), static_cast<unsigned int>(23)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(16), static_cast<unsigned int>(23)}}, {{static_cast<unsigned int>(3), static_cast<unsigned int>(17), static_cast<unsigned int>(23)}}}}, {{{{static_cast<unsigned int>(4), static_cast<unsigned int>(9), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(10), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(11), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(12), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(13), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(14), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(15), static_cast<unsigned int>(23)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(16), static_cast<unsigned int>(23)}}, {{static_cast<unsigned int>(4), static_cast<unsigned int>(17), static_cast<unsigned int>(23)}}}}, {{{{static_cast<unsigned int>(5), static_cast<unsigned int>(9), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(10), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(11), static_cast<unsigned int>(21)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(12), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(13), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(14), static_cast<unsigned int>(22)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(15), static_cast<unsigned int>(23)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(16), static_cast<unsigned int>(23)}}, {{static_cast<unsigned int>(5), static_cast<unsigned int>(17), static_cast<unsigned int>(23)}}}}, {{{{static_cast<unsigned int>(6), static_cast<unsigned int>(9), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(10), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(11), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(12), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(13), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(14), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(15), static_cast<unsigned int>(26)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(16), static_cast<unsigned int>(26)}}, {{static_cast<unsigned int>(6), static_cast<unsigned int>(17), static_cast<unsigned int>(26)}}}}, {{{{static_cast<unsigned int>(7), static_cast<unsigned int>(9), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(10), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(11), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(12), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(13), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(14), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(15), static_cast<unsigned int>(26)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(16), static_cast<unsigned int>(26)}}, {{static_cast<unsigned int>(7), static_cast<unsigned int>(17), static_cast<unsigned int>(26)}}}}, {{{{static_cast<unsigned int>(8), static_cast<unsigned int>(9), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(10), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(11), static_cast<unsigned int>(24)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(12), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(13), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(14), static_cast<unsigned int>(25)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(15), static_cast<unsigned int>(26)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(16), static_cast<unsigned int>(26)}}, {{static_cast<unsigned int>(8), static_cast<unsigned int>(17), static_cast<unsigned int>(26)}}}}}})); */

