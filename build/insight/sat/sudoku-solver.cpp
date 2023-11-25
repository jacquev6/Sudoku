# 1 "src/sat/sudoku-solver.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/sat/sudoku-solver.hpp"
// Copyright 2023 Vincent Jacques

#ifndef SAT_SUDOKU_SOLVER_HPP_
#define SAT_SUDOKU_SOLVER_HPP_

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

/* First instantiated from: sudoku-solver.cpp:391 */
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
/* First instantiated from: sudoku-solver.cpp:391 */
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

/* First instantiated from: sudoku-solver.cpp:362 */
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
  
  /* First instantiated from: sudoku-solver.cpp:252 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: sudoku-solver.cpp:257 */
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
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords);
  
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
/* First instantiated from: sudoku-solver.cpp:362 */
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
  
  /* First instantiated from: sudoku-solver.cpp:252 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &, const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: sudoku-solver.cpp:257 */
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
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords);
  
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

/* First instantiated from: sudoku-solver.cpp:387 */
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
/* First instantiated from: sudoku-solver.cpp:387 */
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
# 7 "src/sat/sudoku-solver.hpp"


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_sat(Sudoku<ValueCell, size>);
;

#endif  // SAT_SUDOKU_SOLVER_HPP_
# 4 "src/sat/sudoku-solver.cpp"

#include <minisat/simp/SimpSolver.h>

# 8 "src/sat/sudoku-solver.cpp"


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_sat(Sudoku<ValueCell, size> sudoku)
{
  Minisat::SimpSolver solver = Minisat::SimpSolver();
  std::array<std::array<std::array<Minisat::Var, size>, size>, size> has_value;
  {
    auto && __range2 = SudokuConstants<size>::values;
    for(; ; ) {
      const unsigned int row;
      {
        auto && __range0 = SudokuConstants<size>::values;
        for(; ; ) {
          const unsigned int col;
          {
            auto && __range1 = SudokuConstants<size>::values;
            for(; ; ) {
              const unsigned int val;
              has_value[row][col][val] = solver.newVar(Minisat::lbool(Minisat::l_Undef), true);
            }
            
          }
        }
        
      }
    }
    
  }
  {
    auto && __range2 = SudokuConstants<size>::cells;
    for(; ; ) {
      const auto & cell;
      const auto __cell2 = cell;
      {
        Minisat::vec<Minisat::Lit, int> clause = Minisat::vec<Minisat::Lit, int>();
        {
          auto && __range1 = SudokuConstants<size>::values;
          for(; ; ) {
            const unsigned int val;
            push(Minisat::mkLit(has_value[row][col][val]));
          }
          
        }
        solver.addClause(static_cast<const Minisat::vec<Minisat::Lit, int>>(clause));
      };
      {
        auto && __range0 = SudokuConstants<size>::values;
        for(; ; ) {
          const unsigned int val1;
          {
            auto && __range1 = SudokuConstants<size>::values;
            for(; ; ) {
              const unsigned int val2;
              if(val1 < val2) {
                addClause(~Minisat::mkLit(has_value[row][col][val1]), ~Minisat::mkLit(has_value[row][col][val2]));
              } 
              
            }
            
          }
        }
        
      }
    }
    
  }
  {
    auto && __range2 = SudokuConstants<size>::regions;
    for(; ; ) {
      const auto & region;
      {
        auto && __range0 = SudokuConstants<size>::values;
        for(; ; ) {
          const unsigned int val;
          {
            auto && __range1 = region;
            for(; ; ) {
              const auto cell1;
              {
                auto && __range3 = region;
                for(; ; ) {
                  const auto cell2;
                  if(cell1 < cell2) {
                    addClause(~Minisat::mkLit(has_value[cell1.first][cell1.second][val]), ~Minisat::mkLit(has_value[cell2.first][cell2.second][val]));
                  } 
                  
                }
                
              }
            }
            
          }
        }
        
      }
    }
    
  }
  {
    auto && __range2 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      const auto __cell3 = cell.coordinates();
      const auto value = cell.get();
      if(value) {
        addClause(Minisat::mkLit(has_value[row][col][*value]));
      } 
      
    }
    
  }
  Minisat::vec<Minisat::Lit, int> dummy = Minisat::vec<Minisat::Lit, int>();
  if(static_cast<const Minisat::lbool>(solver.solveLimited(static_cast<const Minisat::vec<Minisat::Lit, int>>(dummy), true, false)).operator==(Minisat::lbool(Minisat::l_True))) {
    {
      auto && __range0 = sudoku.cells();
      for(; ; ) {
        auto & cell;
        const auto __cell4 = cell.coordinates();
        {
          auto && __range1 = SudokuConstants<size>::values;
          for(; ; ) {
            const unsigned int val;
            if(static_cast<Minisat::Solver&>(solver).model[has_value[row][col][val]] == Minisat::l_True) {
              cell.set(val);
            } 
            
          }
          
        }
      }
      
    }
  } 
  
  return sudoku;
}


/* First instantiated from: sudoku-solver.cpp:465 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_sat<4>(Sudoku<ValueCell, 4> sudoku)
{
  Minisat::SimpSolver solver = Minisat::SimpSolver();
  std::array<std::array<std::array<int, 4>, 4>, 4> has_value;
  {
    const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
    const unsigned int * __begin0 = __range2.begin();
    const unsigned int * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      const unsigned int row = *__begin0;
      {
        const std::array<unsigned int, 4> & __range0 = SudokuConstants<4>::values;
        const unsigned int * __begin0 = __range0.begin();
        const unsigned int * __end0 = __range0.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int col = *__begin0;
          {
            const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
            const unsigned int * __begin0 = __range1.begin();
            const unsigned int * __end0 = __range1.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val = *__begin0;
              has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)) = solver.newVar(Minisat::lbool(Minisat::l_Undef), true);
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::pair<unsigned int, unsigned int>, 16> & __range2 = SudokuConstants<4>::cells;
    const std::pair<unsigned int, unsigned int> * __begin0 = __range2.begin();
    const std::pair<unsigned int, unsigned int> * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::pair<unsigned int, unsigned int> & cell = *__begin0;
      const std::pair<unsigned int, unsigned int> __cell2 = std::pair<unsigned int, unsigned int>(cell);
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell2));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell2));
      {
        Minisat::vec<Minisat::Lit, int> clause = Minisat::vec<Minisat::Lit, int>();
        {
          const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            clause.push(static_cast<const Minisat::Lit>(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)), false)));
          }
          
        }
        solver.addClause(static_cast<const Minisat::vec<Minisat::Lit, int>>(clause));
      };
      {
        const std::array<unsigned int, 4> & __range0 = SudokuConstants<4>::values;
        const unsigned int * __begin0 = __range0.begin();
        const unsigned int * __end0 = __range0.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val1 = *__begin0;
          {
            const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
            const unsigned int * __begin0 = __range1.begin();
            const unsigned int * __end0 = __range1.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val2 = *__begin0;
              if(val1 < val2) {
                solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val1)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val2)), false)));
              } 
              
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12> & __range2 = SudokuConstants<4>::regions;
    const std::array<std::pair<unsigned int, unsigned int>, 4> * __begin0 = __range2.begin();
    const std::array<std::pair<unsigned int, unsigned int>, 4> * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::array<std::pair<unsigned int, unsigned int>, 4> & region = *__begin0;
      {
        const std::array<unsigned int, 4> & __range0 = SudokuConstants<4>::values;
        const unsigned int * __begin0 = __range0.begin();
        const unsigned int * __end0 = __range0.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val = *__begin0;
          {
            const std::array<std::pair<unsigned int, unsigned int>, 4> & __range1 = region;
            const std::pair<unsigned int, unsigned int> * __begin0 = __range1.begin();
            const std::pair<unsigned int, unsigned int> * __end0 = __range1.end();
            for(; __begin0 != __end0; ++__begin0) {
              const std::pair<unsigned int, unsigned int> cell1 = std::pair<unsigned int, unsigned int>(*__begin0);
              {
                const std::array<std::pair<unsigned int, unsigned int>, 4> & __range3 = region;
                const std::pair<unsigned int, unsigned int> * __begin0 = __range3.begin();
                const std::pair<unsigned int, unsigned int> * __end0 = __range3.end();
                for(; __begin0 != __end0; ++__begin0) {
                  const std::pair<unsigned int, unsigned int> cell2 = std::pair<unsigned int, unsigned int>(*__begin0);
                  if(operator<(std::operator<=>(cell1, cell2), __cmp_cat::__unspec(static_cast<std::__cmp_cat::__unspec *>(0)))) {
                    solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell1.first)).operator[](static_cast<unsigned long>(cell1.second)).operator[](static_cast<unsigned long>(val)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell2.first)).operator[](static_cast<unsigned long>(cell2.second)).operator[](static_cast<unsigned long>(val)), false)));
                  } 
                  
                }
                
              }
            }
            
          }
        }
        
      }
    }
    
  }
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const SudokuBase<ValueCell, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::pair<unsigned int, unsigned int> __cell3 = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell3));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell3));
      const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(value.operator bool())) {
        solver.addClause(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(value.operator*())), false));
      } 
      
    }
    
  }
  Minisat::vec<Minisat::Lit, int> dummy = Minisat::vec<Minisat::Lit, int>();
  if(static_cast<const Minisat::lbool>(solver.solveLimited(static_cast<const Minisat::vec<Minisat::Lit, int>>(dummy), true, false)).operator==(Minisat::lbool(Minisat::l_True))) {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range0 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        const std::pair<unsigned int, unsigned int> __cell4 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<ValueCell, 4>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell4));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell4));
        {
          const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            if(static_cast<const Minisat::lbool>(static_cast<Minisat::Solver&>(solver).model.operator[](has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)))).operator==(Minisat::lbool(Minisat::l_True))) {
              static_cast<ValueCell&>(cell).set(val);
            } 
            
          }
          
        }
      }
      
    }
  } 
  
  return Sudoku<ValueCell, 4>(static_cast<const Sudoku<ValueCell, 4> &&>(sudoku));
}
#endif


/* First instantiated from: sudoku-solver.cpp:466 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_sat<9>(Sudoku<ValueCell, 9> sudoku)
{
  Minisat::SimpSolver solver = Minisat::SimpSolver();
  std::array<std::array<std::array<int, 9>, 9>, 9> has_value;
  {
    const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
    const unsigned int * __begin0 = __range2.begin();
    const unsigned int * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      const unsigned int row = *__begin0;
      {
        const std::array<unsigned int, 9> & __range0 = SudokuConstants<9>::values;
        const unsigned int * __begin0 = __range0.begin();
        const unsigned int * __end0 = __range0.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int col = *__begin0;
          {
            const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
            const unsigned int * __begin0 = __range1.begin();
            const unsigned int * __end0 = __range1.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val = *__begin0;
              has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)) = solver.newVar(Minisat::lbool(Minisat::l_Undef), true);
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::pair<unsigned int, unsigned int>, 81> & __range2 = SudokuConstants<9>::cells;
    const std::pair<unsigned int, unsigned int> * __begin0 = __range2.begin();
    const std::pair<unsigned int, unsigned int> * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::pair<unsigned int, unsigned int> & cell = *__begin0;
      const std::pair<unsigned int, unsigned int> __cell2 = std::pair<unsigned int, unsigned int>(cell);
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell2));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell2));
      {
        Minisat::vec<Minisat::Lit, int> clause = Minisat::vec<Minisat::Lit, int>();
        {
          const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            clause.push(static_cast<const Minisat::Lit>(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)), false)));
          }
          
        }
        solver.addClause(static_cast<const Minisat::vec<Minisat::Lit, int>>(clause));
      };
      {
        const std::array<unsigned int, 9> & __range0 = SudokuConstants<9>::values;
        const unsigned int * __begin0 = __range0.begin();
        const unsigned int * __end0 = __range0.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val1 = *__begin0;
          {
            const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
            const unsigned int * __begin0 = __range1.begin();
            const unsigned int * __end0 = __range1.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val2 = *__begin0;
              if(val1 < val2) {
                solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val1)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val2)), false)));
              } 
              
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27> & __range2 = SudokuConstants<9>::regions;
    const std::array<std::pair<unsigned int, unsigned int>, 9> * __begin0 = __range2.begin();
    const std::array<std::pair<unsigned int, unsigned int>, 9> * __end0 = __range2.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::array<std::pair<unsigned int, unsigned int>, 9> & region = *__begin0;
      {
        const std::array<unsigned int, 9> & __range0 = SudokuConstants<9>::values;
        const unsigned int * __begin0 = __range0.begin();
        const unsigned int * __end0 = __range0.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val = *__begin0;
          {
            const std::array<std::pair<unsigned int, unsigned int>, 9> & __range1 = region;
            const std::pair<unsigned int, unsigned int> * __begin0 = __range1.begin();
            const std::pair<unsigned int, unsigned int> * __end0 = __range1.end();
            for(; __begin0 != __end0; ++__begin0) {
              const std::pair<unsigned int, unsigned int> cell1 = std::pair<unsigned int, unsigned int>(*__begin0);
              {
                const std::array<std::pair<unsigned int, unsigned int>, 9> & __range3 = region;
                const std::pair<unsigned int, unsigned int> * __begin0 = __range3.begin();
                const std::pair<unsigned int, unsigned int> * __end0 = __range3.end();
                for(; __begin0 != __end0; ++__begin0) {
                  const std::pair<unsigned int, unsigned int> cell2 = std::pair<unsigned int, unsigned int>(*__begin0);
                  if(operator<(std::operator<=>(cell1, cell2), __cmp_cat::__unspec(static_cast<std::__cmp_cat::__unspec *>(0)))) {
                    solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell1.first)).operator[](static_cast<unsigned long>(cell1.second)).operator[](static_cast<unsigned long>(val)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell2.first)).operator[](static_cast<unsigned long>(cell2.second)).operator[](static_cast<unsigned long>(val)), false)));
                  } 
                  
                }
                
              }
            }
            
          }
        }
        
      }
    }
    
  }
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const SudokuBase<ValueCell, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::pair<unsigned int, unsigned int> __cell3 = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell3));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell3));
      const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(value.operator bool())) {
        solver.addClause(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(value.operator*())), false));
      } 
      
    }
    
  }
  Minisat::vec<Minisat::Lit, int> dummy = Minisat::vec<Minisat::Lit, int>();
  if(static_cast<const Minisat::lbool>(solver.solveLimited(static_cast<const Minisat::vec<Minisat::Lit, int>>(dummy), true, false)).operator==(Minisat::lbool(Minisat::l_True))) {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range0 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        const std::pair<unsigned int, unsigned int> __cell4 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<ValueCell, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell4));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell4));
        {
          const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            if(static_cast<const Minisat::lbool>(static_cast<Minisat::Solver&>(solver).model.operator[](has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)))).operator==(Minisat::lbool(Minisat::l_True))) {
              static_cast<ValueCell&>(cell).set(val);
            } 
            
          }
          
        }
      }
      
    }
  } 
  
  return Sudoku<ValueCell, 9>(static_cast<const Sudoku<ValueCell, 9> &&>(sudoku));
}
#endif


template Sudoku<ValueCell, 4> solve_using_sat(Sudoku<ValueCell, 4>);
template Sudoku<ValueCell, 9> solve_using_sat(Sudoku<ValueCell, 9>);
