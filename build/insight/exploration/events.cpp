// Copyright 2023 Vincent Jacques

// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <variant>
#include <vector>

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

/* First instantiated from: events.cpp:306 */
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
/* First instantiated from: events.cpp:306 */
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
      (static_cast<bool>(this->sudoku == other.sudoku) ? void(0) : __assert_fail("sudoku == other.sudoku", "/wd/src/exploration/events.cpp", 184, __extension____PRETTY_FUNCTION__));
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
            
      class __lambda_212_28
      {
        public: 
        template<class type_parameter_1_0>
        inline const SudokuBase::Cell & operator()(const type_parameter_1_0 & coords) const
        {
          const auto __coords213 = coords;
          return __this->sudoku->_cells[row][col];
        }
        private: 
        const SudokuBase::Region * __this;
        
        public:
        __lambda_212_28(const SudokuBase::Region * _this)
        : __this{_this}
        {}
        
      };
      
      const auto convert = __lambda_212_28{this};
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
    const std::pair<unsigned int, unsigned int> __coords286 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords286));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords286));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "/wd/src/exploration/events.cpp", 287, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "/wd/src/exploration/events.cpp", 288, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const
  {
    const std::pair<unsigned int, unsigned int> __coords293 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords293));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords293));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "/wd/src/exploration/events.cpp", 294, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "/wd/src/exploration/events.cpp", 295, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline auto cells() const
  {
        
    class __lambda_300_26
    {
      public: 
      template<class type_parameter_1_0>
      inline const Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell301 = cell;
        return __this->_cells[row][col];
      }
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_300_26(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_300_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto cells()
  {
        
    class __lambda_311_26
    {
      public: 
      template<class type_parameter_1_0>
      inline Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell312 = cell;
        return __this->_cells[row][col];
      }
      private: 
      SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_311_26(SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_311_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto regions() const
  {
        
    class __lambda_322_26
    {
      public: 
      inline const Region operator()(const unsigned int index) const
      {
        return Region(__this, index);
      }
      
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_322_26(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_322_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::region_indexes.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::region_indexes.end(), convert));
  }
  
  
  protected: 
  CellsArray _cells;
};

/* First instantiated from: events.cpp:511 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<AnnotatedCell<4>, 4>
{
  
  public: 
  class Cell : public AnnotatedCell<4>
  {
    
    public: 
    inline Cell(const SudokuBase<AnnotatedCell<4>, 4> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_);
    
    inline Cell(const SudokuBase<AnnotatedCell<4>, 4> * sudoku_, const Cell & other)
    : AnnotatedCell<4>(static_cast<const AnnotatedCell<4>&>(other))
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
    
    inline std::pair<unsigned int, unsigned int> coordinates() const;
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<AnnotatedCell<4>, 4> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
  public: 
  inline SudokuBase();
  
  inline SudokuBase(const SudokuBase<AnnotatedCell<4>, 4> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
  SudokuBase<AnnotatedCell<4>, 4> & operator=(const SudokuBase<AnnotatedCell<4>, 4> &);
  
  // inline SudokuBase(SudokuBase<AnnotatedCell<4>, 4> &&) = delete;
  // inline SudokuBase<AnnotatedCell<4>, 4> & operator=(SudokuBase<AnnotatedCell<4>, 4> &&) = delete;
  
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
  
  /* First instantiated from: events.cpp:263 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: events.cpp:268 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 4> copy_row<0, 1, 2, 3>(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->copy_cell(row, 0U, other_cells), static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->copy_cell(row, 1U, other_cells), static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->copy_cell(row, 2U, other_cells), static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)->copy_cell(row, 3U, other_cells)}};
  }
  #endif
  
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 4>, 4> & other_cells) const
  {
    return Cell(this, other_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)));
  }
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords)
  {
    const std::pair<unsigned int, unsigned int> __coords286 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords286));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords286));
    (static_cast<bool>(row < 4U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(287), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<4>, 4>::cell(const Coordinates &) [CellBase = AnnotatedCell<4>, size = 4]")));
    (static_cast<bool>(col < 4U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(288), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<4>, 4>::cell(const Coordinates &) [CellBase = AnnotatedCell<4>, size = 4]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
  {
        
    class __lambda_300_26
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell301 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell301 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell301));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell301));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      const SudokuBase<AnnotatedCell<4>, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_300_26 & operator=(const __lambda_300_26 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_300_26(const __lambda_300_26 &) noexcept = default;
      __lambda_300_26(const SudokuBase<AnnotatedCell<4>, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_300_26 convert = static_cast<const __lambda_300_26>(__lambda_300_26{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_300_26(convert)), boost::iterators::make_transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_300_26(convert)));
  }
  
  inline auto cells();
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: events.cpp:511 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<AnnotatedCell<9>, 9>
{
  
  public: 
  class Cell : public AnnotatedCell<9>
  {
    
    public: 
    inline Cell(const SudokuBase<AnnotatedCell<9>, 9> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_);
    
    inline Cell(const SudokuBase<AnnotatedCell<9>, 9> * sudoku_, const Cell & other)
    : AnnotatedCell<9>(static_cast<const AnnotatedCell<9>&>(other))
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
    
    inline std::pair<unsigned int, unsigned int> coordinates() const;
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<AnnotatedCell<9>, 9> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
  public: 
  inline SudokuBase();
  
  inline SudokuBase(const SudokuBase<AnnotatedCell<9>, 9> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
  SudokuBase<AnnotatedCell<9>, 9> & operator=(const SudokuBase<AnnotatedCell<9>, 9> &);
  
  // inline SudokuBase(SudokuBase<AnnotatedCell<9>, 9> &&) = delete;
  // inline SudokuBase<AnnotatedCell<9>, 9> & operator=(SudokuBase<AnnotatedCell<9>, 9> &&) = delete;
  
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
  
  /* First instantiated from: events.cpp:263 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &, const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: events.cpp:268 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 9> copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 0U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 1U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 2U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 3U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 4U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 5U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 6U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 7U, other_cells), static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)->copy_cell(row, 8U, other_cells)}};
  }
  #endif
  
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 9>, 9> & other_cells) const
  {
    return Cell(this, other_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)));
  }
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords)
  {
    const std::pair<unsigned int, unsigned int> __coords286 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords286));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords286));
    (static_cast<bool>(row < 9U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(287), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<9>, 9>::cell(const Coordinates &) [CellBase = AnnotatedCell<9>, size = 9]")));
    (static_cast<bool>(col < 9U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(288), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<9>, 9>::cell(const Coordinates &) [CellBase = AnnotatedCell<9>, size = 9]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
  {
        
    class __lambda_300_26
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell301 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell301 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell301));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell301));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      const SudokuBase<AnnotatedCell<9>, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_300_26 & operator=(const __lambda_300_26 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_300_26(const __lambda_300_26 &) noexcept = default;
      __lambda_300_26(const SudokuBase<AnnotatedCell<9>, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_300_26 convert = static_cast<const __lambda_300_26>(__lambda_300_26{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_300_26(convert)), boost::iterators::make_transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_300_26(convert)));
  }
  
  inline auto cells();
  
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

/* First instantiated from: events.cpp:713 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<AnnotatedCell<4>, 4> : public SudokuBase<AnnotatedCell<4>, 4>
{
  
  public: 
  inline bool is_solved() const
  {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = /* static_cast<const SudokuBase<AnnotatedCell<4>, 4> *>(this)-> */ cells();
      boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        if(!static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
          return false;
        } 
        
      }
      
    }
    return true;
  }
  
  // inline Sudoku(const Sudoku<AnnotatedCell<4>, 4> &) noexcept(false) = default;
  // inline Sudoku(Sudoku<AnnotatedCell<4>, 4> &&) /* noexcept */ = delete;
  // inline Sudoku<AnnotatedCell<4>, 4> & operator=(Sudoku<AnnotatedCell<4>, 4> &&) /* noexcept */ = delete;
};

#endif
/* First instantiated from: events.cpp:713 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<AnnotatedCell<9>, 9> : public SudokuBase<AnnotatedCell<9>, 9>
{
  
  public: 
  inline bool is_solved() const
  {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = /* static_cast<const SudokuBase<AnnotatedCell<9>, 9> *>(this)-> */ cells();
      boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_300_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        if(!static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
          return false;
        } 
        
      }
      
    }
    return true;
  }
  
  // inline Sudoku(const Sudoku<AnnotatedCell<9>, 9> &) noexcept(false) = default;
  // inline Sudoku(Sudoku<AnnotatedCell<9>, 9> &&) /* noexcept */ = delete;
  // inline Sudoku<AnnotatedCell<9>, 9> & operator=(Sudoku<AnnotatedCell<9>, 9> &&) /* noexcept */ = delete;
};

#endif


class ValueCell
{
  
  public: 
  inline constexpr ValueCell() /* noexcept */ = default;
  inline constexpr ValueCell(const ValueCell &) /* noexcept */ = default;
  inline constexpr ValueCell & operator=(const ValueCell &) /* noexcept */ = default;
  inline constexpr ValueCell(ValueCell &&) /* noexcept */ = default;
  inline constexpr ValueCell & operator=(ValueCell &&) /* noexcept */ = default;
  
  public: 
  inline void set(unsigned int value_)
  {
    (static_cast<bool>(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(this->value).operator bool()) || (this->value.operator*() == value_)) ? void(0) : __assert_fail(static_cast<const char *>("!value || *value == value_"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(360), static_cast<const char *>(__extension__"void ValueCell::set(unsigned int)")));
    this->value.operator=(std::optional<unsigned int>(value_));
  }
  
  inline std::optional<unsigned int> get() const
  {
    return std::optional<unsigned int>(this->value);
  }
  
  
  private: 
  std::optional<unsigned int> value;
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "/wd/src/exploration/events.cpp", 411, __extension____PRETTY_FUNCTION__));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/exploration/events.cpp", 418, __extension____PRETTY_FUNCTION__));
    return this->allowed_values.test(value);
  }
  
  inline void set_input(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/exploration/events.cpp", 425, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/exploration/events.cpp", 426, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "/wd/src/exploration/events.cpp", 427, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    this->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/exploration/events.cpp", 439, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/exploration/events.cpp", 440, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "/wd/src/exploration/events.cpp", 441, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->assert_invariants();
  }
  
  inline void set_propagated()
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "/wd/src/exploration/events.cpp", 452, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/exploration/events.cpp", 467, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/exploration/events.cpp", 468, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail("allowed_values.any()", "/wd/src/exploration/events.cpp", 484, __extension____PRETTY_FUNCTION__));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "/wd/src/exploration/events.cpp", 488, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "/wd/src/exploration/events.cpp", 493, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == 1) ? void(0) : __assert_fail("allowed_values.count() == 1", "/wd/src/exploration/events.cpp", 498, __extension____PRETTY_FUNCTION__));
      (static_cast<bool>(this->allowed_values.test(this->set_value.value())) ? void(0) : __assert_fail("allowed_values.test(set_value.value())", "/wd/src/exploration/events.cpp", 499, __extension____PRETTY_FUNCTION__));
    } 
    
  }
  
  
  private: 
  std::bitset<size> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
};

/* First instantiated from: events.cpp:163 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class AnnotatedCell<4>
{
  
  public: 
  inline AnnotatedCell();
  
  
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(411), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<4>::get() const [size = 4]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(418), static_cast<const char *>(__extension__"bool AnnotatedCell<4>::is_allowed(const unsigned int) const [size = 4]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(425), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_input(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(426), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_input(const unsigned int) [size = 4]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(427), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_input(const unsigned int) [size = 4]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(439), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(440), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(441), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline void set_propagated()
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(452), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_propagated() [size = 4]")));
    this->propagated = true;
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline bool is_propagated() const
  {
    this->assert_invariants();
    return this->propagated;
  }
  
  inline void forbid(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(467), static_cast<const char *>(__extension__"void AnnotatedCell<4>::forbid(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(468), static_cast<const char *>(__extension__"void AnnotatedCell<4>::forbid(const unsigned int) [size = 4]")));
    this->allowed_values.reset(static_cast<unsigned long>(value));
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline unsigned int allowed_count() const;
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(484), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(488), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(493), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(498), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(499), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
  }
  
  
  private: 
  std::bitset<4> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
  public: 
  // inline constexpr AnnotatedCell(const AnnotatedCell<4> &) noexcept = default;
};

#endif
/* First instantiated from: events.cpp:163 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class AnnotatedCell<9>
{
  
  public: 
  inline AnnotatedCell();
  
  
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(411), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<9>::get() const [size = 9]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(418), static_cast<const char *>(__extension__"bool AnnotatedCell<9>::is_allowed(const unsigned int) const [size = 9]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(425), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(426), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(427), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(439), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(440), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(441), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_propagated()
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(452), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_propagated() [size = 9]")));
    this->propagated = true;
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline bool is_propagated() const
  {
    this->assert_invariants();
    return this->propagated;
  }
  
  inline void forbid(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(467), static_cast<const char *>(__extension__"void AnnotatedCell<9>::forbid(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(468), static_cast<const char *>(__extension__"void AnnotatedCell<9>::forbid(const unsigned int) [size = 9]")));
    this->allowed_values.reset(static_cast<unsigned long>(value));
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline unsigned int allowed_count() const;
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(484), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(488), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(493), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(498), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(499), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
  }
  
  
  private: 
  std::bitset<9> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
  public: 
  // inline constexpr AnnotatedCell(const AnnotatedCell<9> &) noexcept = default;
};

#endif


template<unsigned int size>
class Sudoku<AnnotatedCell<size>, size> : public SudokuBase<AnnotatedCell<size>, size>
{
  
  public: 
  inline bool is_solved() const
  {
    {
      auto && __range2 = this->cells();
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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/exploration/events.cpp", 534, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  inline AnnotatedSudoku<size> & current()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/exploration/events.cpp", 539, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(current());
  }
  
  inline void pop()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/exploration/events.cpp", 563, __extension____PRETTY_FUNCTION__));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<AnnotatedSudoku<size> > stack;
};

/* First instantiated from: events.cpp:713 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Stack<4>
{
  
  public: 
  inline Stack();
  
  
  public: 
  inline const Sudoku<AnnotatedCell<4>, 4> & current() const;
  
  inline Sudoku<AnnotatedCell<4>, 4> & current()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(539), static_cast<const char *>(__extension__"AnnotatedSudoku<size> &Stack<4>::current() [size = 4]")));
    return this->stack.back();
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(static_cast<const Sudoku<AnnotatedCell<4>, 4>>(this->current()));
  }
  
  inline void pop()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(563), static_cast<const char *>(__extension__"void Stack<4>::pop() [size = 4]")));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > stack;
  public: 
};

#endif
/* First instantiated from: events.cpp:713 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Stack<9>
{
  
  public: 
  inline Stack();
  
  
  public: 
  inline const Sudoku<AnnotatedCell<9>, 9> & current() const;
  
  inline Sudoku<AnnotatedCell<9>, 9> & current()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(539), static_cast<const char *>(__extension__"AnnotatedSudoku<size> &Stack<9>::current() [size = 9]")));
    return this->stack.back();
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(static_cast<const Sudoku<AnnotatedCell<9>, 9>>(this->current()));
  }
  
  inline void pop()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(563), static_cast<const char *>(__extension__"void Stack<9>::pop() [size = 9]")));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > stack;
  public: 
};

#endif


#endif  // EXPLORATION_ANNOTATIONS_HPP_


namespace exploration
{
  template<unsigned int size>
  struct CellIsSetInInput
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct InputsAreDone
  {
    void apply(Stack<size> *) const;
    
  };
  
  template<unsigned int size>
  struct PropagationStartsForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  template<unsigned int size>
  struct PropagationStartsForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct CellPropagates
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct CellIsDeducedFromSingleAllowedValue
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct CellIsDeducedAsSinglePlaceForValueInRegion
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  template<unsigned int size>
  struct PropagationIsDoneForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct PropagationIsDoneForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  template<unsigned int size>
  struct ExplorationStarts
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  template<unsigned int size>
  struct HypothesisIsMade
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct HypothesisIsRejected
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct SudokuIsSolved
  {
    void apply(Stack<size> *) const;
    
  };
  
  template<unsigned int size>
  struct HypothesisIsAccepted
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<unsigned int size>
  struct ExplorationIsDone
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  template<unsigned int size>
  using Event = std::variant<CellIsSetInInput<size>, InputsAreDone<size>, PropagationStartsForSudoku<size>, PropagationStartsForCell<size>, CellPropagates<size>, CellIsDeducedFromSingleAllowedValue<size>, CellIsDeducedAsSinglePlaceForValueInRegion<size>, PropagationIsDoneForCell<size>, PropagationIsDoneForSudoku<size>, ExplorationStarts<size>, HypothesisIsMade<size>, HypothesisIsRejected<size>, SudokuIsSolved<size>, HypothesisIsAccepted<size>, ExplorationIsDone<size> >;
  
}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_

namespace exploration
{
  void CellIsSetInInput::apply(Stack<size> * stack) const
  {
    stack->current().cell(this->cell).set_input(this->value);
  }
  
  void InputsAreDone::apply(Stack<size> * stack) const
  {
  }
  
  void PropagationStartsForSudoku::apply(Stack<size> * stack) const
  {
  }
  
  void PropagationStartsForCell::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 726, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->cell).get() == this->value) ? void(0) : __assert_fail("stack->current().cell(cell).get() == value", "/wd/src/exploration/events.cpp", 727, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 728, __extension____PRETTY_FUNCTION__));
  }
  
  void CellPropagates::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().cell(this->source_cell).is_set()) ? void(0) : __assert_fail("stack->current().cell(source_cell).is_set()", "/wd/src/exploration/events.cpp", 733, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->source_cell).get() == this->value) ? void(0) : __assert_fail("stack->current().cell(source_cell).get() == value", "/wd/src/exploration/events.cpp", 734, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->target_cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(target_cell).is_set()", "/wd/src/exploration/events.cpp", 735, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->target_cell).is_allowed(this->value)) ? void(0) : __assert_fail("stack->current().cell(target_cell).is_allowed(value)", "/wd/src/exploration/events.cpp", 736, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->source_cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(source_cell).is_propagated()", "/wd/src/exploration/events.cpp", 737, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->target_cell).forbid(this->value);
  }
  
  void CellIsDeducedFromSingleAllowedValue::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(!stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 744, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 745, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->cell).set_deduced(this->value);
  }
  
  void CellIsDeducedAsSinglePlaceForValueInRegion::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(!stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 752, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 753, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->cell).set_deduced(this->value);
  }
  
  void PropagationIsDoneForCell::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 760, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->cell).get() == this->value) ? void(0) : __assert_fail("stack->current().cell(cell).get() == value", "/wd/src/exploration/events.cpp", 761, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 762, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->cell).set_propagated();
  }
  
  void PropagationIsDoneForSudoku::apply(Stack<size> * stack) const
  {
  }
  
  void ExplorationStarts::apply(Stack<size> * stack) const
  {
  }
  
  void HypothesisIsMade::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(!stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 777, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->cell).is_allowed(this->value)) ? void(0) : __assert_fail("stack->current().cell(cell).is_allowed(value)", "/wd/src/exploration/events.cpp", 778, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 779, __extension____PRETTY_FUNCTION__));
    stack->push();
    stack->current().cell(this->cell).set_deduced(this->value);
  }
  
  void HypothesisIsRejected::apply(Stack<size> * stack) const
  {
    stack->pop();
  }
  
  void SudokuIsSolved::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().is_solved()) ? void(0) : __assert_fail("stack->current().is_solved()", "/wd/src/exploration/events.cpp", 792, __extension____PRETTY_FUNCTION__));
  }
  
  void HypothesisIsAccepted::apply(Stack<size> * stack) const
  {
  }
  
  void ExplorationIsDone::apply(Stack<size> * stack) const
  {
  }
  
  template<>
  struct CellIsSetInInput<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_input(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsSetInInput<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_input(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct InputsAreDone<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
  };
  
  template<>
  struct InputsAreDone<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationStartsForSudoku<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationStartsForSudoku<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationStartsForCell<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(726), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(727), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(728), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<4>::apply(Stack<size> *) const [size = 4]")));
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct PropagationStartsForCell<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(726), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(727), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(728), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<9>::apply(Stack<size> *) const [size = 9]")));
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellPropagates<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->source_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(733), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->source_cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(734), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->target_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(target_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(735), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->target_cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(target_cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(736), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->source_cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(source_cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(737), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->target_cell)).forbid(this->value);
    }
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  template<>
  struct CellPropagates<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->source_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(733), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->source_cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(734), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->target_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(target_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(735), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->target_cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(target_cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(736), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->source_cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(source_cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(737), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->target_cell)).forbid(this->value);
    }
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsDeducedFromSingleAllowedValue<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(744), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(745), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsDeducedFromSingleAllowedValue<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(744), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(745), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(752), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(753), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(752), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(753), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  template<>
  struct PropagationIsDoneForCell<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(760), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(761), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(762), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_propagated();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct PropagationIsDoneForCell<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(760), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(761), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(762), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_propagated();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct PropagationIsDoneForSudoku<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationIsDoneForSudoku<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
  };
  
  template<>
  struct ExplorationStarts<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  template<>
  struct ExplorationStarts<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  template<>
  struct HypothesisIsMade<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(777), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(778), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(779), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<4>::apply(Stack<size> *) const [size = 4]")));
      stack->push();
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsMade<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(777), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(778), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(779), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<9>::apply(Stack<size> *) const [size = 9]")));
      stack->push();
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsRejected<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      stack->pop();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsRejected<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      stack->pop();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct SudokuIsSolved<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const Sudoku<AnnotatedCell<4>, 4>>(stack->current()).is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().is_solved()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(792), static_cast<const char *>(__extension__"void exploration::SudokuIsSolved<4>::apply(Stack<size> *) const [size = 4]")));
    }
    
  };
  
  template<>
  struct SudokuIsSolved<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const Sudoku<AnnotatedCell<9>, 9>>(stack->current()).is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().is_solved()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(792), static_cast<const char *>(__extension__"void exploration::SudokuIsSolved<9>::apply(Stack<size> *) const [size = 9]")));
    }
    
  };
  
  template<>
  struct HypothesisIsAccepted<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsAccepted<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct ExplorationIsDone<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  template<>
  struct ExplorationIsDone<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  
}  // namespace exploration
