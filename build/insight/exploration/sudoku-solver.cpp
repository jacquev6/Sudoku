# 1 "src/exploration/sudoku-solver.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/exploration/sudoku-solver.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <functional>
#include <memory>

# 1 "src/puzzle/sudoku.hpp"
// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_SUDOKU_HPP_
#define PUZZLE_SUDOKU_HPP_

#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptor/indexed.hpp>

# 1 "src/puzzle/sudoku-constants.hpp"
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
      auto && __range0 = make_values();
      for(; ; ) {
        unsigned int row;
        {
          auto && __range1 = make_values();
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
      auto && __range0 = make_values();
      for(; ; ) {
        unsigned int row;
        {
          auto && __range1 = make_values();
          for(; ; ) {
            unsigned int col;
            regions[row][col] = {row, col};
          }
          
        }
      }
      
    }
    {
      auto && __range0 = make_values();
      for(; ; ) {
        unsigned int col;
        {
          auto && __range1 = make_values();
          for(; ; ) {
            unsigned int row;
            regions[size + col][row] = {row, col};
          }
          
        }
      }
      
    }
    {
      auto && __range0 = make_values();
      for(; ; ) {
        unsigned int square;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          auto && __range1 = make_values();
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
      auto && __range0 = make_values();
      for(; ; ) {
        unsigned int row;
        {
          auto && __range1 = make_values();
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

/* First instantiated from: sudoku-solver.cpp:309 */
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
      std::array<unsigned int, 4> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 4> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
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
      std::array<unsigned int, 4> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 4> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 4> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int col = *__begin0;
        {
          std::array<unsigned int, 4> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int row = *__begin0;
            regions.operator[](static_cast<unsigned long>(4U + col)).operator[](static_cast<unsigned long>(row)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 4> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int square = *__begin0;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          std::array<unsigned int, 4> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
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
      std::array<unsigned int, 4> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 4> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
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
/* First instantiated from: sudoku-solver.cpp:309 */
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
      std::array<unsigned int, 9> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 9> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
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
      std::array<unsigned int, 9> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 9> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 9> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int col = *__begin0;
        {
          std::array<unsigned int, 9> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int row = *__begin0;
            regions.operator[](static_cast<unsigned long>(9U + col)).operator[](static_cast<unsigned long>(row)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      std::array<unsigned int, 9> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int square = *__begin0;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          std::array<unsigned int, 9> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
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
      std::array<unsigned int, 9> && __range0 = make_values();
      unsigned int * __begin0 = __range0.begin();
      unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          std::array<unsigned int, 9> && __range1 = make_values();
          unsigned int * __begin0 = __range1.begin();
          unsigned int * __end0 = __range1.end();
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
# 19 "src/puzzle/sudoku.hpp"


template<typename CellBase, unsigned int size>
class SudokuBase
{
  
  public: 
  class Cell : public CellBase
  {
    
    public: 
    inline Cell(const SudokuBase<CellBase, size> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_)
    : CellBase{}
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(coords_)}
    {
    }
    
    inline Cell(const SudokuBase<CellBase, size> * sudoku_, const Cell & other)
    : CellBase{other}
    , sudoku{sudoku_}
    , coords{other.coords}
    {
    }
    
    // inline Cell(const Cell &) = delete;
    // inline Cell & operator=(const Cell &) = delete;
    // inline Cell(Cell &&) = delete;
    // inline Cell & operator=(Cell &&) = delete;
    
    public: 
    inline bool operator==(const Cell & other) const
    {
      (static_cast<bool>(this->sudoku == other.sudoku) ? void(0) : __assert_fail("sudoku == other.sudoku", "src/puzzle/sudoku.hpp", 46, __extension____PRETTY_FUNCTION__));
      return this->coords == other.coords;
    }
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<CellBase, size> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
  };
  
  class Region
  {
    
    public: 
    inline Region(const SudokuBase<CellBase, size> * sudoku_, const unsigned int index_)
    : sudoku{sudoku_}
    , _index{index_}
    {
    }
    
    // inline Region(const Region &) = delete;
    // inline Region & operator=(const Region &) = delete;
    // inline Region(Region &&) = delete;
    // inline Region & operator=(Region &&) = delete;
    
    public: 
    inline unsigned int index() const
    {
      return this->_index;
    }
    
    inline auto cells() const
    {
            
      class __lambda_0
      {
        public: 
        template<class type_parameter_1_0>
        inline const SudokuBase::Cell & operator()(const type_parameter_1_0 & coords) const
        {
          const auto __coords0 = coords;
          return __this->sudoku->_cells[row][col];
        }
        private: 
        const SudokuBase::Region * __this;
        
        public:
        __lambda_0(const SudokuBase::Region * _this)
        : __this{_this}
        {}
        
      };
      
      const auto convert = __lambda_0{this};
      return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::regions[this->_index].begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::regions[this->_index].end(), convert));
    }
    
    
    private: 
    const SudokuBase<CellBase, size> * sudoku;
    const unsigned int _index;
  };
  
  
  public: 
  inline SudokuBase()
  : _cells{make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<CellBase, size> & other)
  : _cells{copy_cells(other._cells)}
  {
  }
  
  SudokuBase<CellBase, size> & operator=(const SudokuBase<CellBase, size> &);
  
  // inline SudokuBase(SudokuBase<CellBase, size> &&) = delete;
  // inline SudokuBase<CellBase, size> & operator=(SudokuBase<CellBase, size> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, size>, size>;
  inline CellsArray make_cells()
  {
    return make_cells(std::make_integer_sequence<unsigned int, size>());
  }
  
  template<unsigned int ...row>
  inline CellsArray make_cells(const std::integer_sequence<unsigned int, row...> &)
  {
    return {make_row(row, std::make_integer_sequence<unsigned int, size>())... };
  }
  template<unsigned int ...col>
  inline std::array<Cell, size> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &)
  {
    return {this->make_cell(row, col)... };
  }
  inline Cell make_cell(unsigned int row, unsigned int col) const
  {
    return Cell(this, {row, col});
  }
  
  
  private: 
  inline CellsArray copy_cells(const CellsArray & other_cells)
  {
    return copy_cells(std::make_integer_sequence<unsigned int, size>(), other_cells);
  }
  
  template<unsigned int ...row>
  inline CellsArray copy_cells(const std::integer_sequence<unsigned int, row...> &, const CellsArray & other_cells)
  {
    return {copy_row(row, other_cells, std::make_integer_sequence<unsigned int, size>())... };
  }
  template<unsigned int ...col>
  inline std::array<Cell, size> copy_row(unsigned int row, const CellsArray & other_cells, const std::integer_sequence<unsigned int, col...> &)
  {
    return {this->copy_cell(row, col, other_cells)... };
  }
  inline Cell copy_cell(unsigned int row, unsigned int col, const CellsArray & other_cells) const
  {
    return Cell(this, other_cells[row][col]);
  }
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords)
  {
    const std::pair<unsigned int, unsigned int> __coords1 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "src/puzzle/sudoku.hpp", 149, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "src/puzzle/sudoku.hpp", 150, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const
  {
    const std::pair<unsigned int, unsigned int> __coords2 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords2));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords2));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "src/puzzle/sudoku.hpp", 156, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "src/puzzle/sudoku.hpp", 157, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline auto cells() const
  {
        
    class __lambda_1
    {
      public: 
      template<class type_parameter_1_0>
      inline const Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell0 = cell;
        return __this->_cells[row][col];
      }
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_1(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_1{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto cells()
  {
        
    class __lambda_2
    {
      public: 
      template<class type_parameter_1_0>
      inline Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell1 = cell;
        return __this->_cells[row][col];
      }
      private: 
      SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_2(SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_2{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto regions() const
  {
        
    class __lambda_3
    {
      public: 
      inline const Region operator()(const unsigned int index) const
      {
        return Region(__this, index);
      }
      
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_3(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_3{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::region_indexes.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::region_indexes.end(), convert));
  }
  
  
  protected: 
  CellsArray _cells;
};

/* First instantiated from: sudoku-solver.cpp:365 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<ValueCell, 4>
{
  
  public: 
  class Cell : public ValueCell
  {
    
    public: 
    inline Cell(const SudokuBase<ValueCell, 4> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_);
    
    inline Cell(const SudokuBase<ValueCell, 4> * sudoku_, const Cell & other)
    : ValueCell(static_cast<const ValueCell&>(other))
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(other.coords)}
    {
    }
    
    // inline Cell(const Cell &) = delete;
    // inline Cell & operator=(const Cell &) = delete;
    // inline Cell(Cell &&) = delete;
    // inline Cell & operator=(Cell &&) = delete;
    
    public: 
    inline bool operator==(const Cell & other) const;
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<ValueCell, 4> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
  public: 
  inline SudokuBase();
  
  inline SudokuBase(const SudokuBase<ValueCell, 4> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
  SudokuBase<ValueCell, 4> & operator=(const SudokuBase<ValueCell, 4> &);
  
  // inline SudokuBase(SudokuBase<ValueCell, 4> &&) = delete;
  // inline SudokuBase<ValueCell, 4> & operator=(SudokuBase<ValueCell, 4> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, 4>, 4>;
  inline std::array<std::array<Cell, 4>, 4> make_cells();
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> make_cells(const std::integer_sequence<unsigned int, row...> &);
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  inline Cell make_cell(unsigned int row, unsigned int col) const;
  
  
  private: 
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return this->copy_cells<0, 1, 2, 3>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()), other_cells);
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 4>, 4> & other_cells);
  
  /* First instantiated from: sudoku-solver.cpp:255 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: sudoku-solver.cpp:260 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 4> copy_row<0, 1, 2, 3>(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{static_cast<const SudokuBase<ValueCell, 4> *>(this)->copy_cell(row, 0U, other_cells), static_cast<const SudokuBase<ValueCell, 4> *>(this)->copy_cell(row, 1U, other_cells), static_cast<const SudokuBase<ValueCell, 4> *>(this)->copy_cell(row, 2U, other_cells), static_cast<const SudokuBase<ValueCell, 4> *>(this)->copy_cell(row, 3U, other_cells)}};
  }
  #endif
  
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 4>, 4> & other_cells) const
  {
    return Cell(this, other_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)));
  }
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords)
  {
    const std::pair<unsigned int, unsigned int> __coords1 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    (static_cast<bool>(row < 4U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(149), static_cast<const char *>(__extension__"Cell &SudokuBase<ValueCell, 4>::cell(const Coordinates &) [CellBase = ValueCell, size = 4]")));
    (static_cast<bool>(col < 4U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(150), static_cast<const char *>(__extension__"Cell &SudokuBase<ValueCell, 4>::cell(const Coordinates &) [CellBase = ValueCell, size = 4]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline auto cells() const;
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells()
  {
        
    class __lambda_2
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell1 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell1 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      SudokuBase<ValueCell, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_2 & operator=(const __lambda_2 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_2(const __lambda_2 &) noexcept = default;
      __lambda_2(SudokuBase<ValueCell, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_2 convert = static_cast<const __lambda_2>(__lambda_2{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_2(convert)), boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_2(convert)));
  }
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: sudoku-solver.cpp:365 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<ValueCell, 9>
{
  
  public: 
  class Cell : public ValueCell
  {
    
    public: 
    inline Cell(const SudokuBase<ValueCell, 9> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_);
    
    inline Cell(const SudokuBase<ValueCell, 9> * sudoku_, const Cell & other)
    : ValueCell(static_cast<const ValueCell&>(other))
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(other.coords)}
    {
    }
    
    // inline Cell(const Cell &) = delete;
    // inline Cell & operator=(const Cell &) = delete;
    // inline Cell(Cell &&) = delete;
    // inline Cell & operator=(Cell &&) = delete;
    
    public: 
    inline bool operator==(const Cell & other) const;
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<ValueCell, 9> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
  public: 
  inline SudokuBase();
  
  inline SudokuBase(const SudokuBase<ValueCell, 9> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
  SudokuBase<ValueCell, 9> & operator=(const SudokuBase<ValueCell, 9> &);
  
  // inline SudokuBase(SudokuBase<ValueCell, 9> &&) = delete;
  // inline SudokuBase<ValueCell, 9> & operator=(SudokuBase<ValueCell, 9> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, 9>, 9>;
  inline std::array<std::array<Cell, 9>, 9> make_cells();
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> make_cells(const std::integer_sequence<unsigned int, row...> &);
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  inline Cell make_cell(unsigned int row, unsigned int col) const;
  
  
  private: 
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return this->copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()), other_cells);
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 9>, 9> & other_cells);
  
  /* First instantiated from: sudoku-solver.cpp:255 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &, const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: sudoku-solver.cpp:260 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 9> copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 0U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 1U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 2U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 3U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 4U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 5U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 6U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 7U, other_cells), static_cast<const SudokuBase<ValueCell, 9> *>(this)->copy_cell(row, 8U, other_cells)}};
  }
  #endif
  
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 9>, 9> & other_cells) const
  {
    return Cell(this, other_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)));
  }
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords)
  {
    const std::pair<unsigned int, unsigned int> __coords1 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    (static_cast<bool>(row < 9U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(149), static_cast<const char *>(__extension__"Cell &SudokuBase<ValueCell, 9>::cell(const Coordinates &) [CellBase = ValueCell, size = 9]")));
    (static_cast<bool>(col < 9U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(150), static_cast<const char *>(__extension__"Cell &SudokuBase<ValueCell, 9>::cell(const Coordinates &) [CellBase = ValueCell, size = 9]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline auto cells() const;
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells()
  {
        
    class __lambda_2
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell1 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell1 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      SudokuBase<ValueCell, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_2 & operator=(const __lambda_2 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_2(const __lambda_2 &) noexcept = default;
      __lambda_2(SudokuBase<ValueCell, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_2 convert = static_cast<const __lambda_2>(__lambda_2{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_2(convert)), boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_2(convert)));
  }
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 9>, 9> _cells;
  public: 
};

#endif
/* First instantiated from: sudoku-solver.cpp:528 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<AnnotatedCell<4>, 4>
{
  
  public: 
  class Cell : public AnnotatedCell<4>
  {
    
    public: 
    inline Cell(const SudokuBase<AnnotatedCell<4>, 4> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_)
    : AnnotatedCell<4>()
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(coords_)}
    {
    }
    
    inline Cell(const SudokuBase<AnnotatedCell<4>, 4> * sudoku_, const Cell & other);
    
    // inline Cell(const Cell &) = delete;
    // inline Cell & operator=(const Cell &) = delete;
    // inline Cell(Cell &&) = delete;
    // inline Cell & operator=(Cell &&) = delete;
    
    public: 
    inline bool operator==(const Cell & other) const
    {
      (static_cast<bool>(this->sudoku == other.sudoku) ? void(0) : __assert_fail(static_cast<const char *>("sudoku == other.sudoku"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(46), static_cast<const char *>(__extension__"bool SudokuBase<AnnotatedCell<4>, 4>::Cell::operator==(const Cell &) const [CellBase = AnnotatedCell<4>, size = 4]")));
      return std::operator==(this->coords, other.coords);
    }
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> > regions() const
    {
            
      class __lambda_4
      {
        public: 
        inline const SudokuBase<AnnotatedCell<4>, 4>::Region operator()(const unsigned int region_index) const
        {
          return static_cast<const SudokuBase<AnnotatedCell<4>, 4>::Region>(SudokuBase<AnnotatedCell<4>, 4>::Region(__this->sudoku, region_index));
        }
        
        private: 
        const SudokuBase<AnnotatedCell<4>, 4>::Cell * __this;
        public: 
        // inline /*constexpr */ __lambda_4 & operator=(const __lambda_4 &) /* noexcept */ = delete;
        // inline /*constexpr */ __lambda_4(const __lambda_4 &) noexcept = default;
        __lambda_4(const SudokuBase<AnnotatedCell<4>, 4>::Cell * _this)
        : __this{_this}
        {}
        
      };
      
      const __lambda_4 convert = static_cast<const __lambda_4>(__lambda_4{this});
      return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_4, const unsigned int *>(SudokuConstants<4>::regions_of.operator[](static_cast<unsigned long>(this->coords.first)).operator[](static_cast<unsigned long>(this->coords.second)).begin(), __lambda_4(convert)), boost::iterators::make_transform_iterator<__lambda_4, const unsigned int *>(SudokuConstants<4>::regions_of.operator[](static_cast<unsigned long>(this->coords.first)).operator[](static_cast<unsigned long>(this->coords.second)).end(), __lambda_4(convert)));
    }
    
    
    private: 
    const SudokuBase<AnnotatedCell<4>, 4> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region
  {
    
    public: 
    inline Region(const SudokuBase<AnnotatedCell<4>, 4> * sudoku_, const unsigned int index_)
    : sudoku{sudoku_}
    , _index{index_}
    {
    }
    
    // inline Region(const Region &) = delete;
    // inline Region & operator=(const Region &) = delete;
    // inline Region(Region &&) = delete;
    // inline Region & operator=(Region &&) = delete;
    
    public: 
    inline unsigned int index() const
    {
      return this->_index;
    }
    
    inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
    {
            
      class __lambda_0
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & coords) const
        {
          const auto __coords0 = coords;
          return __this->sudoku->_cells[row][col];
        }
        
        /* First instantiated from: transform_iterator.hpp:126 */
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & coords) const
        {
          const std::pair<unsigned int, unsigned int> __coords0 = std::pair<unsigned int, unsigned int>(coords);
          const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords0));
          const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords0));
          return __this->sudoku->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
        }
        #endif
        
        private: 
        const SudokuBase<AnnotatedCell<4>, 4>::Region * __this;
        public: 
        // inline /*constexpr */ __lambda_0 & operator=(const __lambda_0 &) /* noexcept */ = delete;
        // inline /*constexpr */ __lambda_0(const __lambda_0 &) noexcept = default;
        __lambda_0(const SudokuBase<AnnotatedCell<4>, 4>::Region * _this)
        : __this{_this}
        {}
        
      };
      
      const __lambda_0 convert = static_cast<const __lambda_0>(__lambda_0{this});
      return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::regions.operator[](static_cast<unsigned long>(this->_index)).begin(), __lambda_0(convert)), boost::iterators::make_transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::regions.operator[](static_cast<unsigned long>(this->_index)).end(), __lambda_0(convert)));
    }
    
    
    private: 
    const SudokuBase<AnnotatedCell<4>, 4> * sudoku;
    const unsigned int _index;
    public: 
  };
  
  
  public: 
  inline SudokuBase()
  : _cells{this->make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<AnnotatedCell<4>, 4> & other);
  
  SudokuBase<AnnotatedCell<4>, 4> & operator=(const SudokuBase<AnnotatedCell<4>, 4> &);
  
  // inline SudokuBase(SudokuBase<AnnotatedCell<4>, 4> &&) = delete;
  // inline SudokuBase<AnnotatedCell<4>, 4> & operator=(SudokuBase<AnnotatedCell<4>, 4> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, 4>, 4>;
  inline std::array<std::array<Cell, 4>, 4> make_cells()
  {
    return this->make_cells<0, 1, 2, 3>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()));
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> make_cells(const std::integer_sequence<unsigned int, row...> &);
  
  /* First instantiated from: sudoku-solver.cpp:236 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: sudoku-solver.cpp:241 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 4> make_row<0, 1, 2, 3>(unsigned int row, const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->make_cell(row, 0U), static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->make_cell(row, 1U), static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->make_cell(row, 2U), static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->make_cell(row, 3U)}};
  }
  #endif
  
  inline Cell make_cell(unsigned int row, unsigned int col) const
  {
    return Cell(this, std::pair<unsigned int, unsigned int>{row, col});
  }
  
  
  private: 
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::array<std::array<Cell, 4>, 4> & other_cells);
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 4>, 4> & other_cells);
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 4>, 4> & other_cells) const;
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords);
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const
  {
    const std::pair<unsigned int, unsigned int> __coords2 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords2));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords2));
    (static_cast<bool>(row < 4U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(156), static_cast<const char *>(__extension__"const Cell &SudokuBase<AnnotatedCell<4>, 4>::cell(const Coordinates &) const [CellBase = AnnotatedCell<4>, size = 4]")));
    (static_cast<bool>(col < 4U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(157), static_cast<const char *>(__extension__"const Cell &SudokuBase<AnnotatedCell<4>, 4>::cell(const Coordinates &) const [CellBase = AnnotatedCell<4>, size = 4]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
  {
        
    class __lambda_1
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell0 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell0 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell0));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell0));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      const SudokuBase<AnnotatedCell<4>, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_1 & operator=(const __lambda_1 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_1(const __lambda_1 &) noexcept = default;
      __lambda_1(const SudokuBase<AnnotatedCell<4>, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_1 convert = static_cast<const __lambda_1>(__lambda_1{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_1(convert)), boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_1(convert)));
  }
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells()
  {
        
    class __lambda_2
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell1 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell1 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      SudokuBase<AnnotatedCell<4>, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_2 & operator=(const __lambda_2 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_2(const __lambda_2 &) noexcept = default;
      __lambda_2(SudokuBase<AnnotatedCell<4>, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_2 convert = static_cast<const __lambda_2>(__lambda_2{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_2(convert)), boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_2(convert)));
  }
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: sudoku-solver.cpp:528 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<AnnotatedCell<9>, 9>
{
  
  public: 
  class Cell : public AnnotatedCell<9>
  {
    
    public: 
    inline Cell(const SudokuBase<AnnotatedCell<9>, 9> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_)
    : AnnotatedCell<9>()
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(coords_)}
    {
    }
    
    inline Cell(const SudokuBase<AnnotatedCell<9>, 9> * sudoku_, const Cell & other);
    
    // inline Cell(const Cell &) = delete;
    // inline Cell & operator=(const Cell &) = delete;
    // inline Cell(Cell &&) = delete;
    // inline Cell & operator=(Cell &&) = delete;
    
    public: 
    inline bool operator==(const Cell & other) const
    {
      (static_cast<bool>(this->sudoku == other.sudoku) ? void(0) : __assert_fail(static_cast<const char *>("sudoku == other.sudoku"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(46), static_cast<const char *>(__extension__"bool SudokuBase<AnnotatedCell<9>, 9>::Cell::operator==(const Cell &) const [CellBase = AnnotatedCell<9>, size = 9]")));
      return std::operator==(this->coords, other.coords);
    }
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> > regions() const
    {
            
      class __lambda_4
      {
        public: 
        inline const SudokuBase<AnnotatedCell<9>, 9>::Region operator()(const unsigned int region_index) const
        {
          return static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Region>(SudokuBase<AnnotatedCell<9>, 9>::Region(__this->sudoku, region_index));
        }
        
        private: 
        const SudokuBase<AnnotatedCell<9>, 9>::Cell * __this;
        public: 
        // inline /*constexpr */ __lambda_4 & operator=(const __lambda_4 &) /* noexcept */ = delete;
        // inline /*constexpr */ __lambda_4(const __lambda_4 &) noexcept = default;
        __lambda_4(const SudokuBase<AnnotatedCell<9>, 9>::Cell * _this)
        : __this{_this}
        {}
        
      };
      
      const __lambda_4 convert = static_cast<const __lambda_4>(__lambda_4{this});
      return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_4, const unsigned int *>(SudokuConstants<9>::regions_of.operator[](static_cast<unsigned long>(this->coords.first)).operator[](static_cast<unsigned long>(this->coords.second)).begin(), __lambda_4(convert)), boost::iterators::make_transform_iterator<__lambda_4, const unsigned int *>(SudokuConstants<9>::regions_of.operator[](static_cast<unsigned long>(this->coords.first)).operator[](static_cast<unsigned long>(this->coords.second)).end(), __lambda_4(convert)));
    }
    
    
    private: 
    const SudokuBase<AnnotatedCell<9>, 9> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region
  {
    
    public: 
    inline Region(const SudokuBase<AnnotatedCell<9>, 9> * sudoku_, const unsigned int index_)
    : sudoku{sudoku_}
    , _index{index_}
    {
    }
    
    // inline Region(const Region &) = delete;
    // inline Region & operator=(const Region &) = delete;
    // inline Region(Region &&) = delete;
    // inline Region & operator=(Region &&) = delete;
    
    public: 
    inline unsigned int index() const
    {
      return this->_index;
    }
    
    inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
    {
            
      class __lambda_0
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & coords) const
        {
          const auto __coords0 = coords;
          return __this->sudoku->_cells[row][col];
        }
        
        /* First instantiated from: transform_iterator.hpp:126 */
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & coords) const
        {
          const std::pair<unsigned int, unsigned int> __coords0 = std::pair<unsigned int, unsigned int>(coords);
          const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords0));
          const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords0));
          return __this->sudoku->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
        }
        #endif
        
        private: 
        const SudokuBase<AnnotatedCell<9>, 9>::Region * __this;
        public: 
        // inline /*constexpr */ __lambda_0 & operator=(const __lambda_0 &) /* noexcept */ = delete;
        // inline /*constexpr */ __lambda_0(const __lambda_0 &) noexcept = default;
        __lambda_0(const SudokuBase<AnnotatedCell<9>, 9>::Region * _this)
        : __this{_this}
        {}
        
      };
      
      const __lambda_0 convert = static_cast<const __lambda_0>(__lambda_0{this});
      return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::regions.operator[](static_cast<unsigned long>(this->_index)).begin(), __lambda_0(convert)), boost::iterators::make_transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::regions.operator[](static_cast<unsigned long>(this->_index)).end(), __lambda_0(convert)));
    }
    
    
    private: 
    const SudokuBase<AnnotatedCell<9>, 9> * sudoku;
    const unsigned int _index;
    public: 
  };
  
  
  public: 
  inline SudokuBase()
  : _cells{this->make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<AnnotatedCell<9>, 9> & other);
  
  SudokuBase<AnnotatedCell<9>, 9> & operator=(const SudokuBase<AnnotatedCell<9>, 9> &);
  
  // inline SudokuBase(SudokuBase<AnnotatedCell<9>, 9> &&) = delete;
  // inline SudokuBase<AnnotatedCell<9>, 9> & operator=(SudokuBase<AnnotatedCell<9>, 9> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, 9>, 9>;
  inline std::array<std::array<Cell, 9>, 9> make_cells()
  {
    return this->make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()));
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> make_cells(const std::integer_sequence<unsigned int, row...> &);
  
  /* First instantiated from: sudoku-solver.cpp:236 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: sudoku-solver.cpp:241 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 9> make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(unsigned int row, const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 0U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 1U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 2U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 3U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 4U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 5U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 6U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 7U), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->make_cell(row, 8U)}};
  }
  #endif
  
  inline Cell make_cell(unsigned int row, unsigned int col) const
  {
    return Cell(this, std::pair<unsigned int, unsigned int>{row, col});
  }
  
  
  private: 
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::array<std::array<Cell, 9>, 9> & other_cells);
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 9>, 9> & other_cells);
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 9>, 9> & other_cells) const;
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords);
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const
  {
    const std::pair<unsigned int, unsigned int> __coords2 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords2));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords2));
    (static_cast<bool>(row < 9U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(156), static_cast<const char *>(__extension__"const Cell &SudokuBase<AnnotatedCell<9>, 9>::cell(const Coordinates &) const [CellBase = AnnotatedCell<9>, size = 9]")));
    (static_cast<bool>(col < 9U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(157), static_cast<const char *>(__extension__"const Cell &SudokuBase<AnnotatedCell<9>, 9>::cell(const Coordinates &) const [CellBase = AnnotatedCell<9>, size = 9]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
  {
        
    class __lambda_1
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell0 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell0 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell0));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell0));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      const SudokuBase<AnnotatedCell<9>, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_1 & operator=(const __lambda_1 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_1(const __lambda_1 &) noexcept = default;
      __lambda_1(const SudokuBase<AnnotatedCell<9>, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_1 convert = static_cast<const __lambda_1>(__lambda_1{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_1(convert)), boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_1(convert)));
  }
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells()
  {
        
    class __lambda_2
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell1 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell1 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      SudokuBase<AnnotatedCell<9>, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_2 & operator=(const __lambda_2 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_2(const __lambda_2 &) noexcept = default;
      __lambda_2(SudokuBase<AnnotatedCell<9>, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_2 convert = static_cast<const __lambda_2>(__lambda_2{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_2(convert)), boost::iterators::make_transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_2(convert)));
  }
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 9>, 9> _cells;
  public: 
};

#endif


template<typename CellBase, unsigned size>
auto SudokuBase<CellBase, size>::Cell::regions() const {
  const auto convert = [this](const unsigned region_index) -> const Region {
    return Region(sudoku, region_index);
  };

  return boost::make_iterator_range(
    boost::make_transform_iterator(SudokuConstants<size>::regions_of[coords.first][coords.second].begin(), convert),
    boost::make_transform_iterator(SudokuConstants<size>::regions_of[coords.first][coords.second].end(), convert));
}

template<typename Cell, unsigned int size>
class Sudoku : public SudokuBase<Cell, size>
{
};

/* First instantiated from: sudoku-solver.cpp:994 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<ValueCell, 4> : public SudokuBase<ValueCell, 4>
{
  
  public: 
  static Sudoku<ValueCell, 4> load(std::basic_istream<char> &);
  
  void dump(std::basic_ostream<char> &) const;
  
  static Sudoku<ValueCell, 4> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
  // inline Sudoku(const Sudoku<ValueCell, 4> &) noexcept(false) = default;
  // inline Sudoku(Sudoku<ValueCell, 4> &&) /* noexcept */ = delete;
  // inline Sudoku<ValueCell, 4> & operator=(Sudoku<ValueCell, 4> &&) /* noexcept */ = delete;
};

#endif
/* First instantiated from: sudoku-solver.cpp:994 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<ValueCell, 9> : public SudokuBase<ValueCell, 9>
{
  
  public: 
  static Sudoku<ValueCell, 9> load(std::basic_istream<char> &);
  
  void dump(std::basic_ostream<char> &) const;
  
  static Sudoku<ValueCell, 9> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
  // inline Sudoku(const Sudoku<ValueCell, 9> &) noexcept(false) = default;
  // inline Sudoku(Sudoku<ValueCell, 9> &&) /* noexcept */ = delete;
  // inline Sudoku<ValueCell, 9> & operator=(Sudoku<ValueCell, 9> &&) /* noexcept */ = delete;
};

#endif
/* First instantiated from: alloc_traits.h:850 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<AnnotatedCell<4>, 4> : public SudokuBase<AnnotatedCell<4>, 4>
{
  
  public: 
  inline bool is_solved() const
  {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range0 = /* static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)-> */ cells();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        if(!static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
          return false;
        } 
        
      }
      
    }
    return true;
  }
  
  // inline Sudoku(Sudoku<AnnotatedCell<4>, 4> &&) /* noexcept */ = delete;
  // inline Sudoku<AnnotatedCell<4>, 4> & operator=(Sudoku<AnnotatedCell<4>, 4> &&) /* noexcept */ = delete;
  // inline Sudoku() noexcept(false) = default;
};

#endif
/* First instantiated from: alloc_traits.h:850 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<AnnotatedCell<9>, 9> : public SudokuBase<AnnotatedCell<9>, 9>
{
  
  public: 
  inline bool is_solved() const
  {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range0 = /* static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)-> */ cells();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        if(!static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
          return false;
        } 
        
      }
      
    }
    return true;
  }
  
  // inline Sudoku(Sudoku<AnnotatedCell<9>, 9> &&) /* noexcept */ = delete;
  // inline Sudoku<AnnotatedCell<9>, 9> & operator=(Sudoku<AnnotatedCell<9>, 9> &&) /* noexcept */ = delete;
  // inline Sudoku() noexcept(false) = default;
};

#endif


class ValueCell
{
  
  public: 
  inline constexpr ValueCell() /* noexcept */ = default;
  inline constexpr ValueCell(const ValueCell &) noexcept = default;
  inline constexpr ValueCell & operator=(const ValueCell &) /* noexcept */ = default;
  inline constexpr ValueCell(ValueCell &&) /* noexcept */ = default;
  inline constexpr ValueCell & operator=(ValueCell &&) /* noexcept */ = default;
  
  public: 
  inline void set(unsigned int value_)
  {
    (static_cast<bool>(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(this->value).operator bool()) || (this->value.operator*() == value_)) ? void(0) : __assert_fail(static_cast<const char *>("!value || *value == value_"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(222), static_cast<const char *>(__extension__"void ValueCell::set(unsigned int)")));
    this->value.operator=(std::optional<unsigned int>(value_));
  }
  
  inline std::optional<unsigned int> get() const
  {
    return std::optional<unsigned int>(this->value);
  }
  
  
  private: 
  std::optional<unsigned int> value;
  public: 
};



template<unsigned int size>
class Sudoku<ValueCell, size> : public SudokuBase<ValueCell, size>
{
  
  public: 
  static Sudoku<ValueCell, size> load(std::basic_istream<char> &);
  
  void dump(std::basic_ostream<char> &) const;
  
  static Sudoku<ValueCell, size> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
};



#endif  // PUZZLE_SUDOKU_HPP_
# 10 "src/exploration/sudoku-solver.hpp"
# 1 "src/exploration/events.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <variant>
#include <vector>

# 1 "src/exploration/annotations.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_ANNOTATIONS_HPP_
#define EXPLORATION_ANNOTATIONS_HPP_

#include <array>
#include <bitset>
#include <cassert>
#include <optional>
#include <string>
#include <utility>
#include <vector>

# 15 "src/exploration/annotations.hpp"


template<unsigned int size>
class AnnotatedCell
{
  
  public: 
  inline AnnotatedCell()
  : allowed_values{}
  , set_value{std::optional<unsigned int>()}
  , input{false}
  , propagated{false}
  {
    this->allowed_values.set();
    this->assert_invariants();
  }
  
  
  public: 
  inline bool is_input() const
  {
    this->assert_invariants();
    return this->input;
  }
  
  inline bool is_set() const
  {
    this->assert_invariants();
    return this->set_value.has_value();
  }
  
  inline unsigned int get() const
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "src/exploration/annotations.hpp", 43, __extension____PRETTY_FUNCTION__));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 50, __extension____PRETTY_FUNCTION__));
    return this->allowed_values.test(value);
  }
  
  inline void set_input(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 57, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 58, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "src/exploration/annotations.hpp", 59, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    this->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 71, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 72, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "src/exploration/annotations.hpp", 73, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->assert_invariants();
  }
  
  inline void set_propagated()
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "src/exploration/annotations.hpp", 84, __extension____PRETTY_FUNCTION__));
    this->propagated = true;
    this->assert_invariants();
  }
  
  inline bool is_propagated() const
  {
    this->assert_invariants();
    return this->propagated;
  }
  
  inline void forbid(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 99, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 100, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset(value);
    this->assert_invariants();
  }
  
  inline unsigned int allowed_count() const
  {
    this->assert_invariants();
    return this->allowed_values.count();
  }
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail("allowed_values.any()", "src/exploration/annotations.hpp", 116, __extension____PRETTY_FUNCTION__));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "src/exploration/annotations.hpp", 120, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "src/exploration/annotations.hpp", 125, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == 1) ? void(0) : __assert_fail("allowed_values.count() == 1", "src/exploration/annotations.hpp", 130, __extension____PRETTY_FUNCTION__));
      (static_cast<bool>(this->allowed_values.test(this->set_value.value())) ? void(0) : __assert_fail("allowed_values.test(set_value.value())", "src/exploration/annotations.hpp", 131, __extension____PRETTY_FUNCTION__));
    } 
    
  }
  
  
  private: 
  std::bitset<size> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
};

/* First instantiated from: alloc_traits.h:850 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class AnnotatedCell<4>
{
  
  public: 
  inline AnnotatedCell()
  : allowed_values{std::bitset<4>()}
  , set_value{std::optional<unsigned int>()}
  , input{false}
  , propagated{false}
  {
    this->allowed_values.set();
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  
  public: 
  inline bool is_input() const;
  
  inline bool is_set() const
  {
    this->assert_invariants();
    return this->set_value.has_value();
  }
  
  inline unsigned int get() const
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(43), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<4>::get() const [size = 4]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(50), static_cast<const char *>(__extension__"bool AnnotatedCell<4>::is_allowed(const unsigned int) const [size = 4]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value);
  
  inline void set_deduced(const unsigned int value);
  
  inline void set_propagated();
  
  inline bool is_propagated() const;
  
  inline void forbid(const unsigned int value);
  
  inline unsigned int allowed_count() const
  {
    this->assert_invariants();
    return static_cast<unsigned int>(this->allowed_values.count());
  }
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(116), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(120), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(125), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(130), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(131), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
  }
  
  
  private: 
  std::bitset<4> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
  public: 
};

#endif
/* First instantiated from: alloc_traits.h:850 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class AnnotatedCell<9>
{
  
  public: 
  inline AnnotatedCell()
  : allowed_values{std::bitset<9>()}
  , set_value{std::optional<unsigned int>()}
  , input{false}
  , propagated{false}
  {
    this->allowed_values.set();
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  
  public: 
  inline bool is_input() const;
  
  inline bool is_set() const
  {
    this->assert_invariants();
    return this->set_value.has_value();
  }
  
  inline unsigned int get() const
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(43), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<9>::get() const [size = 9]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(50), static_cast<const char *>(__extension__"bool AnnotatedCell<9>::is_allowed(const unsigned int) const [size = 9]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value);
  
  inline void set_deduced(const unsigned int value);
  
  inline void set_propagated();
  
  inline bool is_propagated() const;
  
  inline void forbid(const unsigned int value);
  
  inline unsigned int allowed_count() const
  {
    this->assert_invariants();
    return static_cast<unsigned int>(this->allowed_values.count());
  }
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(116), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(120), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(125), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(130), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(131), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
  }
  
  
  private: 
  std::bitset<9> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
  public: 
};

#endif


template<unsigned int size>
class Sudoku<AnnotatedCell<size>, size> : public SudokuBase<AnnotatedCell<size>, size>
{
  
  public: 
  inline bool is_solved() const
  {
    {
      auto && __range0 = this->cells();
      for(; ; ) {
        const auto & cell;
        if(!cell.is_set()) {
          return false;
        } 
        
      }
      
    }
    return true;
  }
  
};



template<unsigned size>
using AnnotatedSudoku = Sudoku<AnnotatedCell<size>, size>;


template<unsigned int size>
class Stack
{
  
  public: 
  inline Stack()
  : stack{1}
  {
  }
  
  
  public: 
  inline const AnnotatedSudoku<size> & current() const
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 166, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  inline AnnotatedSudoku<size> & current()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 171, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(current());
  }
  
  inline void pop()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 195, __extension____PRETTY_FUNCTION__));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<AnnotatedSudoku<size> > stack;
};

/* First instantiated from: sudoku-solver.cpp:998 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Stack<4>
{
  
  public: 
  inline Stack()
  : stack{std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > >(static_cast<unsigned long>(1), static_cast<const std::allocator<Sudoku<AnnotatedCell<4>, 4> >>(std::allocator<Sudoku<AnnotatedCell<4>, 4> >()))}
  {
  }
  
  
  public: 
  inline const Sudoku<AnnotatedCell<4>, 4> & current() const
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(166), static_cast<const char *>(__extension__"const AnnotatedSudoku<size> &Stack<4>::current() const [size = 4]")));
    return this->stack.back();
  }
  
  inline Sudoku<AnnotatedCell<4>, 4> & current()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(171), static_cast<const char *>(__extension__"AnnotatedSudoku<size> &Stack<4>::current() [size = 4]")));
    return this->stack.back();
  }
  
  
  public: 
  inline void push();
  
  inline void pop();
  
  
  private: 
  std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > stack;
  public: 
  // inline constexpr ~Stack() noexcept = default;
};

#endif
/* First instantiated from: sudoku-solver.cpp:998 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Stack<9>
{
  
  public: 
  inline Stack()
  : stack{std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > >(static_cast<unsigned long>(1), static_cast<const std::allocator<Sudoku<AnnotatedCell<9>, 9> >>(std::allocator<Sudoku<AnnotatedCell<9>, 9> >()))}
  {
  }
  
  
  public: 
  inline const Sudoku<AnnotatedCell<9>, 9> & current() const
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(166), static_cast<const char *>(__extension__"const AnnotatedSudoku<size> &Stack<9>::current() const [size = 9]")));
    return this->stack.back();
  }
  
  inline Sudoku<AnnotatedCell<9>, 9> & current()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(171), static_cast<const char *>(__extension__"AnnotatedSudoku<size> &Stack<9>::current() [size = 9]")));
    return this->stack.back();
  }
  
  
  public: 
  inline void push();
  
  inline void pop();
  
  
  private: 
  std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > stack;
  public: 
  // inline constexpr ~Stack() noexcept = default;
};

#endif


#endif  // EXPLORATION_ANNOTATIONS_HPP_
# 10 "src/exploration/events.hpp"


namespace exploration
{
  template<unsigned int size>
  struct CellIsSetInInput
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: sudoku-solver.cpp:1005 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsSetInInput(CellIsSetInInput<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: sudoku-solver.cpp:1005 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsSetInInput(CellIsSetInInput<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct InputsAreDone
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr InputsAreDone(InputsAreDone<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr InputsAreDone(InputsAreDone<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr PropagationStartsForSudoku(PropagationStartsForSudoku<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr PropagationStartsForSudoku(PropagationStartsForSudoku<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationStartsForCell(PropagationStartsForCell<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationStartsForCell(PropagationStartsForCell<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct CellPropagates
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellPropagates<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
    // inline constexpr CellPropagates(CellPropagates<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellPropagates<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
    // inline constexpr CellPropagates(CellPropagates<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct CellIsDeducedFromSingleAllowedValue
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsDeducedFromSingleAllowedValue(CellIsDeducedFromSingleAllowedValue<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsDeducedFromSingleAllowedValue(CellIsDeducedFromSingleAllowedValue<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct CellIsDeducedAsSinglePlaceForValueInRegion
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
    // inline constexpr CellIsDeducedAsSinglePlaceForValueInRegion(CellIsDeducedAsSinglePlaceForValueInRegion<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
    // inline constexpr CellIsDeducedAsSinglePlaceForValueInRegion(CellIsDeducedAsSinglePlaceForValueInRegion<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationIsDoneForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationIsDoneForCell(PropagationIsDoneForCell<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationIsDoneForCell(PropagationIsDoneForCell<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationIsDoneForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(PropagationIsDoneForSudoku<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(PropagationIsDoneForSudoku<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct ExplorationStarts
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    // inline constexpr ExplorationStarts(ExplorationStarts<4> &&) noexcept = default;
    // inline constexpr ~ExplorationStarts() noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    // inline constexpr ExplorationStarts(ExplorationStarts<9> &&) noexcept = default;
    // inline constexpr ~ExplorationStarts() noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsMade
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsMade(HypothesisIsMade<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsMade(HypothesisIsMade<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsRejected
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsRejected(HypothesisIsRejected<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsRejected(HypothesisIsRejected<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct SudokuIsSolved
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr SudokuIsSolved(SudokuIsSolved<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr SudokuIsSolved(SudokuIsSolved<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsAccepted
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsAccepted(HypothesisIsAccepted<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsAccepted(HypothesisIsAccepted<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct ExplorationIsDone
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(ExplorationIsDone<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: type_traits:1364 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(ExplorationIsDone<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  using Event = std::variant<CellIsSetInInput<size>, InputsAreDone<size>, PropagationStartsForSudoku<size>, PropagationStartsForCell<size>, CellPropagates<size>, CellIsDeducedFromSingleAllowedValue<size>, CellIsDeducedAsSinglePlaceForValueInRegion<size>, PropagationIsDoneForCell<size>, PropagationIsDoneForSudoku<size>, ExplorationStarts<size>, HypothesisIsMade<size>, HypothesisIsRejected<size>, SudokuIsSolved<size>, HypothesisIsAccepted<size>, ExplorationIsDone<size> >;
  
}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
# 11 "src/exploration/sudoku-solver.hpp"


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_exploration(Sudoku<ValueCell, size>, const std::function<void (exploration::Event<size> &&)> &);
;

#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
# 4 "src/exploration/sudoku-solver.cpp"

#include <cassert>
#include <functional>
#include <list>
#include <set>
#include <utility>
#include <vector>


// FIFO with unique elements
template<typename T>
class UniqueQueue
{
  
  public: 
  inline void add(const T & t)
  {
    if(this->set.insert(t).second) {
      this->list.push_back(t);
    } 
    
  }
  
  inline bool empty() const
  {
    (static_cast<bool>(this->list.empty() == this->set.empty()) ? void(0) : __assert_fail("list.empty() == set.empty()", "src/exploration/sudoku-solver.cpp", 24, __extension____PRETTY_FUNCTION__));
    return this->list.empty();
  }
  
  inline bool has(const T & t) const
  {
    return this->set.count(t);
  }
  
  inline T get()
  {
    (static_cast<bool>(!this->empty()) ? void(0) : __assert_fail("!empty()", "src/exploration/sudoku-solver.cpp", 33, __extension____PRETTY_FUNCTION__));
    const T t = this->list.front() /* NRVO variable */;
    this->list.pop_front();
    this->set.erase(t);
    return t;
  }
  
  
  private: 
  std::list<T> list;
  std::set<T> set;
};

/* First instantiated from: sudoku-solver.cpp:828 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class UniqueQueue<std::pair<unsigned int, unsigned int> >
{
  
  public: 
  inline void add(const std::pair<unsigned int, unsigned int> & t)
  {
    if(this->set.insert(t).second) {
      this->list.push_back(t);
    } 
    
  }
  
  inline bool empty() const
  {
    (static_cast<bool>(static_cast<int>(this->list.empty()) == static_cast<int>(this->set.empty())) ? void(0) : __assert_fail(static_cast<const char *>("list.empty() == set.empty()"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(24), static_cast<const char *>(__extension__"bool UniqueQueue<std::pair<unsigned int, unsigned int>>::empty() const [T = std::pair<unsigned int, unsigned int>]")));
    return this->list.empty();
  }
  
  inline bool has(const std::pair<unsigned int, unsigned int> & t) const;
  
  inline std::pair<unsigned int, unsigned int> get()
  {
    (static_cast<bool>(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> > *>(this)->empty()) ? void(0) : __assert_fail(static_cast<const char *>("!empty()"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(33), static_cast<const char *>(__extension__"T UniqueQueue<std::pair<unsigned int, unsigned int>>::get() [T = std::pair<unsigned int, unsigned int>]")));
    const std::pair<unsigned int, unsigned int> t = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->list.front())) /* NRVO variable */;
    this->list.pop_front();
    this->set.erase(t);
    return std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int> &&>(t));
  }
  
  
  private: 
  std::list<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > list;
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > set;
  public: 
  // inline ~UniqueQueue() noexcept = default;
  // inline UniqueQueue() noexcept = default;
};

#endif



// This is the only way to modify the Stack (everywhere else, it's manipulated through const references).
// This design ensures that the events returned to the client can replicate exactly the evolution of the
// stack that happened during the exploration, because the stack actually evolved only through said events.
// (I think this is brilliant, but I *may* biased as I'm the author of this code).
template<unsigned int size>
struct EventAdder
{
  inline EventAdder(Stack<size> * stack_, const std::function<void (exploration::Event<size> &&)> & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  inline void operator()(exploration::Event<size> && event) const
  {
        
    class __lambda_5
    {
      public: 
      template<class type_parameter_1_0>
      inline auto operator()(const type_parameter_1_0 & e) const
      {
        e.apply(__this->stack);
      }
      private: 
      const EventAdder<size> * __this;
      
      public:
      __lambda_5(const EventAdder<size> * _this)
      : __this{_this}
      {}
      
    };
    
    std::visit(__lambda_5{this}, event);
    this->add_event(std::move(event));
  }
  
  
  private: 
  Stack<size> * stack;
  const std::function<void (exploration::Event<size> &&)> & add_event;
};

/* First instantiated from: sudoku-solver.cpp:999 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<4>
{
  inline EventAdder(Stack<4> * stack_, const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)> & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  inline void operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && event) const
  {
        
    class __lambda_5
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
      {
        e.apply(__this->stack);
      }
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      private: 
      const EventAdder<4> * __this;
      
      public:
      __lambda_5(const EventAdder<4> * _this)
      : __this{_this}
      {}
      
    };
    
    std::visit<__lambda_5, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(__lambda_5{this}, event);
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(event));
  }
  
  
  private: 
  Stack<4> * stack;
  const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)> & add_event;
  public: 
};

#endif
/* First instantiated from: sudoku-solver.cpp:999 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<9>
{
  inline EventAdder(Stack<9> * stack_, const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)> & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  inline void operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && event) const
  {
        
    class __lambda_5
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
      {
        e.apply(__this->stack);
      }
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      private: 
      const EventAdder<9> * __this;
      
      public:
      __lambda_5(const EventAdder<9> * _this)
      : __this{_this}
      {}
      
    };
    
    std::visit<__lambda_5, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(__lambda_5{this}, event);
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(event));
  }
  
  
  private: 
  Stack<9> * stack;
  const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)> & add_event;
  public: 
};

#endif



// Make sure a closing event is added, however the scope is exited
template<unsigned int size>
struct EventsPairGuard
{
  inline EventsPairGuard(const EventAdder<size> & add_event_, exploration::Event<size> && in, exploration::Event<size> && out_)
  : add_event{add_event_}
  , out{std::move(out_)}
  {
    this->add_event(std::move(in));
  }
  
  inline ~EventsPairGuard()
  {
    this->add_event(std::move(this->out));
  }
  
  const EventAdder<size> & add_event;
  exploration::Event<size> out;
};

/* First instantiated from: sudoku-solver.cpp:833 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4>
{
  inline EventsPairGuard(const EventAdder<4> & add_event_, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && in, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && out_)
  : add_event{add_event_}
  , out{std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(out_))}
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(in));
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(this->out));
  }
  
  const EventAdder<4> & add_event;
  std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > out;
  // inline EventsPairGuard<4> & operator=(const EventsPairGuard<4> &) /* noexcept */ = delete;
};

#endif
/* First instantiated from: sudoku-solver.cpp:833 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9>
{
  inline EventsPairGuard(const EventAdder<9> & add_event_, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && in, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && out_)
  : add_event{add_event_}
  , out{std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(out_))}
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(in));
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(this->out));
  }
  
  const EventAdder<9> & add_event;
  std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > out;
  // inline EventsPairGuard<9> & operator=(const EventsPairGuard<9> &) /* noexcept */ = delete;
};

#endif



template<unsigned int size>
bool propagate(const Stack<size> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo_, const EventAdder<size> & add_event)
{
  UniqueQueue<std::pair<unsigned int, unsigned int> > todo = UniqueQueue<std::pair<unsigned int, unsigned int> >();
  {
    const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo_;
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __begin1 = __range2.begin();
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __end1 = __range2.end();
    for(; !operator==(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1), static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__end1)); __begin1.operator++()) {
      const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1).operator*());
      todo.add(cell);
    }
    
  }
  EventsPairGuard<size> guard = add_event, exploration::PropagationStartsForSudoku<size>(), exploration::PropagationIsDoneForSudoku<size>();
  while(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = static_cast<const std::pair<unsigned int, unsigned int>>(todo.get());
    const auto & source_cell = stack.current().cell(source_coords);
    (static_cast<bool>(source_cell.is_set()) ? void(0) : __assert_fail("source_cell.is_set()", "src/exploration/sudoku-solver.cpp", 108, __extension____PRETTY_FUNCTION__));
    const unsigned int value = source_cell.get();
    EventsPairGuard<size> guard = add_event, exploration::PropagationStartsForCell<size>(source_coords, value), exploration::PropagationIsDoneForCell<size>(source_coords, value);
    const std::pair<unsigned int, unsigned int> __source_coords0 = std::pair<unsigned int, unsigned int>(source_coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords0));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords0));
    {
      auto && __range0 = source_cell.regions();
      for(; ; ) {
        const auto & source_region;
        {
          auto && __range1 = source_region.cells();
          for(; ; ) {
            const auto & target_cell;
            const auto target_coords = target_cell.coordinates();
            if(target_cell != source_cell) {
              if(target_cell.is_set()) {
                if(target_cell.get() == value) {
                  return false;
                } 
                
              } else {
                (static_cast<bool>(target_cell.allowed_count() > 1) ? void(0) : __assert_fail("target_cell.allowed_count() > 1", "src/exploration/sudoku-solver.cpp", 126, __extension____PRETTY_FUNCTION__));
                if(target_cell.is_allowed(value)) {
                  add_event(exploration::CellPropagates<size>(source_coords, target_coords, value));
                  if(target_cell.allowed_count() == 1) {
                    {
                      auto && __range3 = SudokuConstants<size>::values;
                      for(; ; ) {
                        unsigned int value;
                        if(target_cell.is_allowed(value)) {
                          add_event(exploration::CellIsDeducedFromSingleAllowedValue<size>(target_coords, value));
                          todo.add(target_coords);
                          break;
                        } 
                        
                      }
                      
                    }
                  } 
                  
                  {
                    auto && __range4 = target_cell.regions();
                    for(; ; ) {
                      const auto & target_region;
                      unsigned int count = static_cast<unsigned int>(0);
                      const typename AnnotatedSudoku<size>::Cell * single_cell;
                      {
                        auto && __range3 = target_region.cells();
                        for(; ; ) {
                          const auto & cell;
                          if(cell.is_allowed(value)) {
                            ++count;
                            single_cell = &cell;
                          } 
                          
                        }
                        
                      }
                      if((count == static_cast<unsigned int>(1)) && !single_cell->is_set()) {
                        const std::pair<unsigned int, unsigned int> single_coords = single_cell->coordinates();
                        add_event(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>(single_coords, value, target_region.index()));
                        todo.add(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event(exploration::SudokuIsSolved<size>());
                  } 
                  
                } else {
                } 
                
              } 
              
            } 
            
          }
          
        }
      }
      
    }
  }
  
  return true;
}


/* First instantiated from: sudoku-solver.cpp:981 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<4>(const Stack<4> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo_, const EventAdder<4> & add_event)
{
  UniqueQueue<std::pair<unsigned int, unsigned int> > todo = UniqueQueue<std::pair<unsigned int, unsigned int> >();
  {
    const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo_;
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __begin1 = __range2.begin();
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __end1 = __range2.end();
    for(; !operator==(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1), static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__end1)); __begin1.operator++()) {
      const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1).operator*());
      todo.add(cell);
    }
    
  }
  EventsPairGuard<4> guard = EventsPairGuard<4>(add_event, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationStartsForSudoku<4>()), std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationIsDoneForSudoku<4>()));
  while(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = static_cast<const std::pair<unsigned int, unsigned int>>(todo.get());
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(108), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 4U]")));
    const unsigned int value = static_cast<const AnnotatedCell<4>&>(source_cell).get();
    EventsPairGuard<4> guard = EventsPairGuard<4>(add_event, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationStartsForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationIsDoneForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
    const std::pair<unsigned int, unsigned int> __source_coords0 = std::pair<unsigned int, unsigned int>(source_coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords0));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords0));
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> > && __range0 = source_cell.regions();
      boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Region & source_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator*();
        {
          boost::iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = source_region.cells();
          boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
          boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
          for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
            const SudokuBase<AnnotatedCell<4>, 4>::Cell & target_cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
            const std::pair<unsigned int, unsigned int> target_coords = static_cast<const std::pair<unsigned int, unsigned int>>(target_cell.coordinates());
            if(!target_cell.operator==(source_cell)) {
              if(static_cast<const AnnotatedCell<4>&>(target_cell).is_set()) {
                if(static_cast<const AnnotatedCell<4>&>(target_cell).get() == value) {
                  return false;
                } 
                
              } else {
                (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 4U]")));
                if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellPropagates<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
                      const unsigned int * __begin0 = __range3.begin();
                      const unsigned int * __end0 = __range3.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellIsDeducedFromSingleAllowedValue<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          todo.add(target_coords);
                          break;
                        } 
                        
                      }
                      
                    }
                  } 
                  
                  {
                    boost::iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> > && __range4 = target_cell.regions();
                    boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range4).begin();
                    boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range4).end();
                    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator++()) {
                      const SudokuBase<AnnotatedCell<4>, 4>::Region & target_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator*();
                      unsigned int count = static_cast<unsigned int>(0);
                      const typename AnnotatedSudoku<4U>::Cell * single_cell;
                      {
                        boost::iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = target_region.cells();
                        boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
                        boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
                        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
                          const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
                          if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(value)) {
                            ++count;
                            single_cell = &cell;
                          } 
                          
                        }
                        
                      }
                      if((count == static_cast<unsigned int>(1)) && !static_cast<const AnnotatedCell<4> *>(single_cell)->is_set()) {
                        const std::pair<unsigned int, unsigned int> single_coords = static_cast<const std::pair<unsigned int, unsigned int>>(single_cell->coordinates());
                        add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        todo.add(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::SudokuIsSolved<4>()));
                  } 
                  
                } else {
                } 
                
              } 
              
            } 
            
          }
          
        }
      }
      
    }
  }
  
  return true;
}
#endif


/* First instantiated from: sudoku-solver.cpp:981 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<9>(const Stack<9> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo_, const EventAdder<9> & add_event)
{
  UniqueQueue<std::pair<unsigned int, unsigned int> > todo = UniqueQueue<std::pair<unsigned int, unsigned int> >();
  {
    const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo_;
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __begin1 = __range2.begin();
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __end1 = __range2.end();
    for(; !operator==(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1), static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__end1)); __begin1.operator++()) {
      const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1).operator*());
      todo.add(cell);
    }
    
  }
  EventsPairGuard<9> guard = EventsPairGuard<9>(add_event, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationStartsForSudoku<9>()), std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationIsDoneForSudoku<9>()));
  while(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = static_cast<const std::pair<unsigned int, unsigned int>>(todo.get());
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(108), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 9U]")));
    const unsigned int value = static_cast<const AnnotatedCell<9>&>(source_cell).get();
    EventsPairGuard<9> guard = EventsPairGuard<9>(add_event, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationStartsForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationIsDoneForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
    const std::pair<unsigned int, unsigned int> __source_coords0 = std::pair<unsigned int, unsigned int>(source_coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords0));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords0));
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> > && __range0 = source_cell.regions();
      boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Region & source_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator*();
        {
          boost::iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = source_region.cells();
          boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
          boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
          for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
            const SudokuBase<AnnotatedCell<9>, 9>::Cell & target_cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
            const std::pair<unsigned int, unsigned int> target_coords = static_cast<const std::pair<unsigned int, unsigned int>>(target_cell.coordinates());
            if(!target_cell.operator==(source_cell)) {
              if(static_cast<const AnnotatedCell<9>&>(target_cell).is_set()) {
                if(static_cast<const AnnotatedCell<9>&>(target_cell).get() == value) {
                  return false;
                } 
                
              } else {
                (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 9U]")));
                if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellPropagates<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
                      const unsigned int * __begin0 = __range3.begin();
                      const unsigned int * __end0 = __range3.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellIsDeducedFromSingleAllowedValue<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          todo.add(target_coords);
                          break;
                        } 
                        
                      }
                      
                    }
                  } 
                  
                  {
                    boost::iterator_range<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> > && __range4 = target_cell.regions();
                    boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range4).begin();
                    boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range4).end();
                    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator++()) {
                      const SudokuBase<AnnotatedCell<9>, 9>::Region & target_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_4, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator*();
                      unsigned int count = static_cast<unsigned int>(0);
                      const typename AnnotatedSudoku<9U>::Cell * single_cell;
                      {
                        boost::iterator_range<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = target_region.cells();
                        boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
                        boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
                        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
                          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_0, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
                          if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(value)) {
                            ++count;
                            single_cell = &cell;
                          } 
                          
                        }
                        
                      }
                      if((count == static_cast<unsigned int>(1)) && !static_cast<const AnnotatedCell<9> *>(single_cell)->is_set()) {
                        const std::pair<unsigned int, unsigned int> single_coords = static_cast<const std::pair<unsigned int, unsigned int>>(single_cell->coordinates());
                        add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        todo.add(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::SudokuIsSolved<9>()));
                  } 
                  
                } else {
                } 
                
              } 
              
            } 
            
          }
          
        }
      }
      
    }
  }
  
  return true;
}
#endif



template<unsigned int size>
std::pair<unsigned int, unsigned int> get_most_constrained_cell(const AnnotatedSudoku<size> & sudoku)
{
  std::pair<unsigned int, unsigned int> best_coords = std::pair<unsigned int, unsigned int>() /* NRVO variable */;
  unsigned int best_count = size + static_cast<unsigned int>(1);
  {
    auto && __range2 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      if(cell.is_set()) {
        continue;
      } 
      
      unsigned int count = cell.allowed_count();
      if(count < best_count) {
        best_coords = cell.coordinates();
        best_count = count;
      } 
      
      if(best_count == static_cast<unsigned int>(2)) {
        break;
      } 
      
    }
    
  }
  return std::pair<unsigned int, unsigned int>(static_cast<std::pair<unsigned int, unsigned int> &&>(best_coords));
}


/* First instantiated from: sudoku-solver.cpp:946 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::pair<unsigned int, unsigned int> get_most_constrained_cell<4>(const Sudoku<AnnotatedCell<4>, 4> & sudoku)
{
  std::pair<unsigned int, unsigned int> best_coords = std::pair<unsigned int, unsigned int>() /* NRVO variable */;
  unsigned int best_count = 4U + static_cast<unsigned int>(1);
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
      if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
        continue;
      } 
      
      unsigned int count = static_cast<const AnnotatedCell<4>&>(cell).allowed_count();
      if(count < best_count) {
        best_coords.operator=(cell.coordinates());
        best_count = count;
      } 
      
      if(best_count == static_cast<unsigned int>(2)) {
        break;
      } 
      
    }
    
  }
  return std::pair<unsigned int, unsigned int>(static_cast<std::pair<unsigned int, unsigned int> &&>(best_coords));
}
#endif


/* First instantiated from: sudoku-solver.cpp:946 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::pair<unsigned int, unsigned int> get_most_constrained_cell<9>(const Sudoku<AnnotatedCell<9>, 9> & sudoku)
{
  std::pair<unsigned int, unsigned int> best_coords = std::pair<unsigned int, unsigned int>() /* NRVO variable */;
  unsigned int best_count = 9U + static_cast<unsigned int>(1);
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
      if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
        continue;
      } 
      
      unsigned int count = static_cast<const AnnotatedCell<9>&>(cell).allowed_count();
      if(count < best_count) {
        best_coords.operator=(cell.coordinates());
        best_count = count;
      } 
      
      if(best_count == static_cast<unsigned int>(2)) {
        break;
      } 
      
    }
    
  }
  return std::pair<unsigned int, unsigned int>(static_cast<std::pair<unsigned int, unsigned int> &&>(best_coords));
}
#endif



template<unsigned int size>
bool propagate_and_explore(const Stack<size> &, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size> &);
;


template<unsigned int size>
bool explore(const Stack<size> & stack, const EventAdder<size> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail("!stack.current().is_solved()", "src/exploration/sudoku-solver.cpp", 211, __extension____PRETTY_FUNCTION__));
  const auto & cell = stack.current().cell(get_most_constrained_cell(stack.current()));
  const std::pair<unsigned int, unsigned int> coords = cell.coordinates();
  std::vector<unsigned int, std::allocator<unsigned int> > allowed_values = std::vector<unsigned int, std::allocator<unsigned int> >();
  {
    auto && __range2 = SudokuConstants<size>::values;
    for(; ; ) {
      unsigned int val;
      if(cell.is_allowed(val)) {
        allowed_values.push_back(static_cast<const unsigned int>(val));
      } 
      
    }
    
  }
  EventsPairGuard<size> guard = add_event, exploration::ExplorationStarts<size>(coords, allowed_values), exploration::ExplorationIsDone<size>(coords);
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin1 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end1 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end1)); __begin1.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1).operator*();
      add_event(exploration::HypothesisIsMade<size>(coords, val));
      if(propagate_and_explore(stack, {coords}, add_event)) {
        add_event(exploration::HypothesisIsAccepted<size>(coords, val));
        return true;
      } else {
        add_event(exploration::HypothesisIsRejected<size>(coords, val));
      } 
      
    }
    
  }
  return false;
}


/* First instantiated from: sudoku-solver.cpp:985 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<4>(const Stack<4> & stack, const EventAdder<4> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(211), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size> &) [size = 4U]")));
  const Cell & cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(static_cast<const std::pair<unsigned int, unsigned int>>(get_most_constrained_cell<4>(stack.current())));
  const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
  std::vector<unsigned int, std::allocator<unsigned int> > allowed_values = std::vector<unsigned int, std::allocator<unsigned int> >();
  {
    const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
    const unsigned int * __begin0 = __range2.begin();
    const unsigned int * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      unsigned int val = *__begin0;
      if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(val)) {
        allowed_values.push_back(static_cast<const unsigned int>(val));
      } 
      
    }
    
  }
  EventsPairGuard<4> guard = EventsPairGuard<4>(add_event, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::ExplorationStarts<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::ExplorationIsDone<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin1 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end1 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end1)); __begin1.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1).operator*();
      add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::HypothesisIsMade<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<4>(stack, std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::less<std::pair<unsigned int, unsigned int> >>(std::less<std::pair<unsigned int, unsigned int> >()), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::HypothesisIsAccepted<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::HypothesisIsRejected<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif


/* First instantiated from: sudoku-solver.cpp:985 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<9>(const Stack<9> & stack, const EventAdder<9> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(211), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size> &) [size = 9U]")));
  const Cell & cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cell(static_cast<const std::pair<unsigned int, unsigned int>>(get_most_constrained_cell<9>(stack.current())));
  const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
  std::vector<unsigned int, std::allocator<unsigned int> > allowed_values = std::vector<unsigned int, std::allocator<unsigned int> >();
  {
    const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
    const unsigned int * __begin0 = __range2.begin();
    const unsigned int * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      unsigned int val = *__begin0;
      if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(val)) {
        allowed_values.push_back(static_cast<const unsigned int>(val));
      } 
      
    }
    
  }
  EventsPairGuard<9> guard = EventsPairGuard<9>(add_event, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::ExplorationStarts<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::ExplorationIsDone<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin1 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end1 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end1)); __begin1.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1).operator*();
      add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::HypothesisIsMade<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<9>(stack, std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::less<std::pair<unsigned int, unsigned int> >>(std::less<std::pair<unsigned int, unsigned int> >()), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::HypothesisIsAccepted<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::HypothesisIsRejected<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif



template<unsigned int size>
bool propagate_and_explore(const Stack<size> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size> & add_event)
{
  if(propagate(stack, todo, add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}


/* First instantiated from: sudoku-solver.cpp:1012 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<4>(const Stack<4> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<4> & add_event)
{
  if(propagate<4>(stack, todo, add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<4>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif


/* First instantiated from: sudoku-solver.cpp:1012 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<9>(const Stack<9> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<9> & add_event)
{
  if(propagate<9>(stack, todo, add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<9>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif



template<unsigned int size>
Sudoku<ValueCell, size> solve_using_exploration(Sudoku<ValueCell, size> sudoku, const std::function<void (exploration::Event<size> &&)> & add_event_)
{
  Stack<size> stack;
  EventAdder<size> add_event = &stack, add_event_;
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    auto && __range2 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      const auto val = cell.get();
      if(val) {
        const std::pair<unsigned int, unsigned int> coords = cell.coordinates();
        add_event(exploration::CellIsSetInInput<size>(coords, *val));
        todo.insert(coords);
      } 
      
    }
    
  }
  add_event(exploration::InputsAreDone<size>());
  propagate_and_explore(stack, std::move<std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo), add_event);
  {
    auto && __range2 = stack.current().cells();
    for(; ; ) {
      const auto & cell;
      if(cell.is_set()) {
        sudoku.cell(cell.coordinates()).set(cell.get());
      } 
      
    }
    
  }
  return sudoku;
}


/* First instantiated from: sudoku-solver.cpp:1022 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_exploration<4>(Sudoku<ValueCell, 4> sudoku, const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)> & add_event_)
{
  Stack<4> stack = Stack<4>();
  EventAdder<4> add_event = EventAdder<4>(&stack, add_event_);
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const SudokuBase<ValueCell, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<4>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellIsSetInInput<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.insert(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<4>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::InputsAreDone<4>()));
  propagate_and_explore<4>(static_cast<const Stack<4>>(stack), static_cast<const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<4>>(add_event));
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
        static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cell(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()))).set(static_cast<const AnnotatedCell<4>&>(cell).get());
      } 
      
    }
    
  }
  return Sudoku<ValueCell, 4>(static_cast<const Sudoku<ValueCell, 4> &&>(sudoku));
}
#endif


/* First instantiated from: sudoku-solver.cpp:1027 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_exploration<9>(Sudoku<ValueCell, 9> sudoku, const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)> & add_event_)
{
  Stack<9> stack = Stack<9>();
  EventAdder<9> add_event = EventAdder<9>(&stack, add_event_);
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const SudokuBase<ValueCell, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<9>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellIsSetInInput<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.insert(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<9>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::InputsAreDone<9>()));
  propagate_and_explore<9>(static_cast<const Stack<9>>(stack), static_cast<const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<9>>(add_event));
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
        static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cell(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()))).set(static_cast<const AnnotatedCell<9>&>(cell).get());
      } 
      
    }
    
  }
  return Sudoku<ValueCell, 9>(static_cast<const Sudoku<ValueCell, 9> &&>(sudoku));
}
#endif


template Sudoku<ValueCell, 4> solve_using_exploration(
  Sudoku<ValueCell, 4>,
  const std::function<void(exploration::Event<4>&&)>&
);

template Sudoku<ValueCell, 9> solve_using_exploration(
  Sudoku<ValueCell, 9>,
  const std::function<void(exploration::Event<9>&&)>&
);
