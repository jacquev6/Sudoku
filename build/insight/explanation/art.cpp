// Copyright 2023 Vincent Jacques

// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_ART_HPP_
#define EXPLANATION_ART_HPP_

#include <cairomm/cairomm.h>

#include <tuple>
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

/* First instantiated from: art.cpp:660 */
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
/* First instantiated from: art.cpp:660 */
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
      (static_cast<bool>(this->sudoku == other.sudoku) ? void(0) : __assert_fail("sudoku == other.sudoku", "/wd/src/explanation/art.cpp", 186, __extension____PRETTY_FUNCTION__));
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
            
      class __lambda_214_28
      {
        public: 
        template<class type_parameter_1_0>
        inline const SudokuBase::Cell & operator()(const type_parameter_1_0 & coords) const
        {
          const auto __coords215 = coords;
          return __this->sudoku->_cells[row][col];
        }
        private: 
        const SudokuBase::Region * __this;
        
        public:
        __lambda_214_28(const SudokuBase::Region * _this)
        : __this{_this}
        {}
        
      };
      
      const auto convert = __lambda_214_28{this};
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
    const std::pair<unsigned int, unsigned int> __coords288 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords288));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords288));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "/wd/src/explanation/art.cpp", 289, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "/wd/src/explanation/art.cpp", 290, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const
  {
    const std::pair<unsigned int, unsigned int> __coords295 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords295));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords295));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "/wd/src/explanation/art.cpp", 296, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "/wd/src/explanation/art.cpp", 297, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline auto cells() const
  {
        
    class __lambda_302_26
    {
      public: 
      template<class type_parameter_1_0>
      inline const Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell303 = cell;
        return __this->_cells[row][col];
      }
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_302_26(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_302_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto cells()
  {
        
    class __lambda_313_26
    {
      public: 
      template<class type_parameter_1_0>
      inline Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell314 = cell;
        return __this->_cells[row][col];
      }
      private: 
      SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_313_26(SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_313_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto regions() const
  {
        
    class __lambda_324_26
    {
      public: 
      inline const Region operator()(const unsigned int index) const
      {
        return Region(__this, index);
      }
      
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_324_26(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_324_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::region_indexes.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::region_indexes.end(), convert));
  }
  
  
  protected: 
  CellsArray _cells;
};

/* First instantiated from: art.cpp:513 */
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
    inline bool operator==(const Cell & other) const;
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<AnnotatedCell<4>, 4> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
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
  
  /* First instantiated from: art.cpp:246 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: art.cpp:251 */
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
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
  {
        
    class __lambda_302_26
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell303 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell303 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell303));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell303));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      const SudokuBase<AnnotatedCell<4>, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_302_26 & operator=(const __lambda_302_26 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_302_26(const __lambda_302_26 &) noexcept = default;
      __lambda_302_26(const SudokuBase<AnnotatedCell<4>, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_302_26 convert = static_cast<const __lambda_302_26>(__lambda_302_26{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_302_26(convert)), boost::iterators::make_transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_302_26(convert)));
  }
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells()
  {
        
    class __lambda_313_26
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell314 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell314 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell314));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell314));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      SudokuBase<AnnotatedCell<4>, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_313_26 & operator=(const __lambda_313_26 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_313_26(const __lambda_313_26 &) noexcept = default;
      __lambda_313_26(SudokuBase<AnnotatedCell<4>, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_313_26 convert = static_cast<const __lambda_313_26>(__lambda_313_26{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_313_26(convert)), boost::iterators::make_transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_313_26(convert)));
  }
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: art.cpp:513 */
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
    inline bool operator==(const Cell & other) const;
    
    inline std::pair<unsigned int, unsigned int> coordinates() const
    {
      return std::pair<unsigned int, unsigned int>(this->coords);
    }
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<AnnotatedCell<9>, 9> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
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
  
  /* First instantiated from: art.cpp:246 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: art.cpp:251 */
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
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells() const
  {
        
    class __lambda_302_26
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ const Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell303 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ const Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell303 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell303));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell303));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      const SudokuBase<AnnotatedCell<9>, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_302_26 & operator=(const __lambda_302_26 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_302_26(const __lambda_302_26 &) noexcept = default;
      __lambda_302_26(const SudokuBase<AnnotatedCell<9>, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_302_26 convert = static_cast<const __lambda_302_26>(__lambda_302_26{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_302_26(convert)), boost::iterators::make_transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_302_26(convert)));
  }
  
  inline boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > cells()
  {
        
    class __lambda_313_26
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ Cell & operator()(const type_parameter_0_0 & cell) const
      {
        const auto __cell314 = cell;
        return __this->_cells[row][col];
      }
      
      /* First instantiated from: transform_iterator.hpp:126 */
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ Cell & operator()<std::pair<unsigned int, unsigned int> >(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell314 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell314));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell314));
        return __this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
      }
      #endif
      
      private: 
      SudokuBase<AnnotatedCell<9>, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_313_26 & operator=(const __lambda_313_26 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_313_26(const __lambda_313_26 &) noexcept = default;
      __lambda_313_26(SudokuBase<AnnotatedCell<9>, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_313_26 convert = static_cast<const __lambda_313_26>(__lambda_313_26{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_313_26(convert)), boost::iterators::make_transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_313_26(convert)));
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

/* First instantiated from: art.cpp:670 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<AnnotatedCell<4>, 4> : public SudokuBase<AnnotatedCell<4>, 4>
{
  
  public: 
  inline bool is_solved() const;
  
  // inline Sudoku(Sudoku<AnnotatedCell<4>, 4> &&) /* noexcept */ = delete;
  // inline Sudoku<AnnotatedCell<4>, 4> & operator=(Sudoku<AnnotatedCell<4>, 4> &&) /* noexcept */ = delete;
  // inline Sudoku() noexcept(false) = default;
};

#endif
/* First instantiated from: art.cpp:670 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<AnnotatedCell<9>, 9> : public SudokuBase<AnnotatedCell<9>, 9>
{
  
  public: 
  inline bool is_solved() const;
  
  // inline Sudoku(Sudoku<AnnotatedCell<9>, 9> &&) /* noexcept */ = delete;
  // inline Sudoku<AnnotatedCell<9>, 9> & operator=(Sudoku<AnnotatedCell<9>, 9> &&) /* noexcept */ = delete;
  // inline Sudoku() noexcept(false) = default;
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
    (static_cast<bool>(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(this->value).operator bool()) || (this->value.operator*() == value_)) ? void(0) : __assert_fail(static_cast<const char *>("!value || *value == value_"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(362), static_cast<const char *>(__extension__"void ValueCell::set(unsigned int)")));
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "/wd/src/explanation/art.cpp", 413, __extension____PRETTY_FUNCTION__));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/art.cpp", 420, __extension____PRETTY_FUNCTION__));
    return this->allowed_values.test(value);
  }
  
  inline void set_input(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/art.cpp", 427, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/explanation/art.cpp", 428, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "/wd/src/explanation/art.cpp", 429, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    this->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/art.cpp", 441, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/explanation/art.cpp", 442, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "/wd/src/explanation/art.cpp", 443, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->assert_invariants();
  }
  
  inline void set_propagated()
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "/wd/src/explanation/art.cpp", 454, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/art.cpp", 469, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/explanation/art.cpp", 470, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail("allowed_values.any()", "/wd/src/explanation/art.cpp", 486, __extension____PRETTY_FUNCTION__));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "/wd/src/explanation/art.cpp", 490, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "/wd/src/explanation/art.cpp", 495, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == 1) ? void(0) : __assert_fail("allowed_values.count() == 1", "/wd/src/explanation/art.cpp", 500, __extension____PRETTY_FUNCTION__));
      (static_cast<bool>(this->allowed_values.test(this->set_value.value())) ? void(0) : __assert_fail("allowed_values.test(set_value.value())", "/wd/src/explanation/art.cpp", 501, __extension____PRETTY_FUNCTION__));
    } 
    
  }
  
  
  private: 
  std::bitset<size> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
};

/* First instantiated from: art.cpp:165 */
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(413), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<4>::get() const [size = 4]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(420), static_cast<const char *>(__extension__"bool AnnotatedCell<4>::is_allowed(const unsigned int) const [size = 4]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value);
  
  inline void set_deduced(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(441), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(442), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(443), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline void set_propagated();
  
  inline bool is_propagated() const
  {
    this->assert_invariants();
    return this->propagated;
  }
  
  inline void forbid(const unsigned int value);
  
  inline unsigned int allowed_count() const;
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(486), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(490), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(495), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(500), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(501), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
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
/* First instantiated from: art.cpp:165 */
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(413), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<9>::get() const [size = 9]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(420), static_cast<const char *>(__extension__"bool AnnotatedCell<9>::is_allowed(const unsigned int) const [size = 9]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(427), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(428), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(429), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(441), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(442), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(443), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_propagated()
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(454), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_propagated() [size = 9]")));
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
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(469), static_cast<const char *>(__extension__"void AnnotatedCell<9>::forbid(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(470), static_cast<const char *>(__extension__"void AnnotatedCell<9>::forbid(const unsigned int) [size = 9]")));
    this->allowed_values.reset(static_cast<unsigned long>(value));
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline unsigned int allowed_count() const;
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(486), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(490), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(495), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(500), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(501), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/explanation/art.cpp", 536, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  inline AnnotatedSudoku<size> & current()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/explanation/art.cpp", 541, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(current());
  }
  
  inline void pop()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/explanation/art.cpp", 565, __extension____PRETTY_FUNCTION__));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<AnnotatedSudoku<size> > stack;
};



#endif  // EXPLORATION_ANNOTATIONS_HPP_


namespace Cairo
{
  class SaveGuard
  {
    
    public: 
    inline explicit SaveGuard(const std::shared_ptr<Context> & cr_)
    : cr{std::shared_ptr<Context>(cr_)}
    {
      static_cast<const std::__shared_ptr_access<Context, 2, false, false>&>(this->cr).operator->()->save();
    }
    
    inline ~SaveGuard() noexcept
    {
      static_cast<const std::__shared_ptr_access<Context, 2, false, false>&>(this->cr).operator->()->restore();
    }
    
    
    private: 
    std::shared_ptr<Context> cr;
    public: 
  };
  
  
}  // namespace Cairo


namespace art
{
  template<unsigned int size>
  double round_grid_size(unsigned int);
  
  /* First instantiated from: art.cpp:819 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<4>(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / 4U) * 4U) + thick_line_width);
  }
  #endif
  
  
  /* First instantiated from: art.cpp:820 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<9>(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / 9U) * 9U) + thick_line_width);
  }
  #endif
  
  struct DrawOptions
  {
    double grid_size;
    bool possible = false;
    bool bold_todo = false;
    std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells;
    double circled_cells_line_width = static_cast<double>(2);
    std::tuple<double, double, double> circled_cells_color = std::tuple<double, double, double>{1, 0, 0};
    std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells;
    double boxed_cells_line_width = static_cast<double>(2);
    std::tuple<double, double, double> boxed_cells_color = std::tuple<double, double, double>{1, 0, 0};
    std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values;
    double circled_values_line_width = static_cast<double>(2);
    std::tuple<double, double, double> circled_values_color = std::tuple<double, double, double>{1, 0, 0};
    std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value;
    double links_from_cell_to_value_line_width = static_cast<double>(2);
    std::tuple<double, double, double> links_from_cell_to_value_color = std::tuple<double, double, double>{1, 0, 0};
    // inline constexpr ~DrawOptions() noexcept = default;
  };
  
  template<unsigned int size>
  void draw(std::shared_ptr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &);
  
  /* First instantiated from: art.cpp:822 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<4>(std::shared_ptr<Cairo::Context> cr, const Sudoku<AnnotatedCell<4>, 4> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(4U);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_653_28
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell654 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_653_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_653_28 cell_center = static_cast<const __lambda_653_28>(__lambda_653_28{cell_size});
        
    class __lambda_658_29
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell659 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int value_x = value % SudokuConstants<4>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<4>::sqrt_size;
        return std::make_pair<double, double>((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size)), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size)));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_658_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_658_29 value_center = static_cast<const __lambda_658_29>(__lambda_658_29{cell_size});
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(static_cast<const AnnotatedCell<4>&>(cell).get() + static_cast<unsigned int>(1)));
          if(options.bold_todo && !static_cast<const AnnotatedCell<4>&>(cell).is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(static_cast<const AnnotatedCell<4>&>(cell).is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const std::pair<double, double> __operator683 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const std::pair<double, double> __operator692 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
          if(!static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
            (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(cell).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!cell.is_propagated()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(706), static_cast<const char *>(__extension__"void art::draw(Cairo::RefPtr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &) [size = 4U]")));
            {
              const std::array<unsigned int, 4> & __range5 = SudokuConstants<4>::values;
              const unsigned int * __begin0 = __range5.begin();
              const unsigned int * __end0 = __range5.end();
              for(; __begin0 != __end0; ++__begin0) {
                unsigned int value = *__begin0;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const std::pair<double, double> __operator715 = static_cast<const std::pair<double, double>>(value_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()), value));
                  const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[2] = {static_cast<const unsigned int>(1), SudokuConstants<4>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= 4U; i = i + static_cast<const unsigned int *>(strides)[k]) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator749 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options753 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const std::pair<double, double> __operator761 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options765 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator772 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator774 = static_cast<const std::pair<double, double>>(value_center.operator()(cell, value));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options778 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options790 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator795 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const std::pair<double, double> __operator798 = static_cast<const std::pair<double, double>>(cell_center.operator()(source_cell));
          const double && x1 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const double && y1 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const std::pair<double, double> __operator799 = static_cast<const std::pair<double, double>>(value_center.operator()(target_cell, value));
          const double && x2 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          const double && y2 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  #endif
  
  
  /* First instantiated from: art.cpp:823 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<9>(std::shared_ptr<Cairo::Context> cr, const Sudoku<AnnotatedCell<9>, 9> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(9U);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_653_28
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell654 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_653_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_653_28 cell_center = static_cast<const __lambda_653_28>(__lambda_653_28{cell_size});
        
    class __lambda_658_29
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell659 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int value_x = value % SudokuConstants<9>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<9>::sqrt_size;
        return std::make_pair<double, double>((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size)), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size)));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_658_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_658_29 value_center = static_cast<const __lambda_658_29>(__lambda_658_29{cell_size});
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(static_cast<const AnnotatedCell<9>&>(cell).get() + static_cast<unsigned int>(1)));
          if(options.bold_todo && !static_cast<const AnnotatedCell<9>&>(cell).is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(static_cast<const AnnotatedCell<9>&>(cell).is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const std::pair<double, double> __operator683 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const std::pair<double, double> __operator692 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
          if(!static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
            (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(cell).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!cell.is_propagated()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(706), static_cast<const char *>(__extension__"void art::draw(Cairo::RefPtr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &) [size = 9U]")));
            {
              const std::array<unsigned int, 9> & __range5 = SudokuConstants<9>::values;
              const unsigned int * __begin0 = __range5.begin();
              const unsigned int * __end0 = __range5.end();
              for(; __begin0 != __end0; ++__begin0) {
                unsigned int value = *__begin0;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const std::pair<double, double> __operator715 = static_cast<const std::pair<double, double>>(value_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()), value));
                  const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[2] = {static_cast<const unsigned int>(1), SudokuConstants<9>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= 9U; i = i + static_cast<const unsigned int *>(strides)[k]) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator749 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options753 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const std::pair<double, double> __operator761 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options765 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator772 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator774 = static_cast<const std::pair<double, double>>(value_center.operator()(cell, value));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options778 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options790 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator795 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const std::pair<double, double> __operator798 = static_cast<const std::pair<double, double>>(cell_center.operator()(source_cell));
          const double && x1 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const double && y1 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const std::pair<double, double> __operator799 = static_cast<const std::pair<double, double>>(value_center.operator()(target_cell, value));
          const double && x2 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          const double && y2 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  #endif
  
  
}  // namespace art

#endif  // EXPLANATION_ART_HPP_

#include <filesystem>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


namespace art
{
  constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  template<unsigned int size>
  double round_grid_size(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / size) * size) + thick_line_width);
  }
  
  /* First instantiated from: art.cpp:819 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<4>(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / 4U) * 4U) + thick_line_width);
  }
  #endif
  
  
  /* First instantiated from: art.cpp:820 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<9>(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / 9U) * 9U) + thick_line_width);
  }
  #endif
  
  template<unsigned int size>
  void draw(std::shared_ptr<Cairo::Context> cr, const AnnotatedSudoku<size> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(size);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_653_28
    {
      public: 
      inline auto operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell654 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_653_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const auto cell_center = __lambda_653_28{cell_size};
        
    class __lambda_658_29
    {
      public: 
      inline auto operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell659 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int value_x = value % SudokuConstants<size>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<size>::sqrt_size;
        return std::make_pair((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / SudokuConstants<size>::sqrt_size), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / SudokuConstants<size>::sqrt_size));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_658_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const auto value_center = __lambda_658_29{cell_size};
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      auto && __range2 = sudoku.cells();
      for(; ; ) {
        const auto & cell;
        if(cell.is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = std::to_string(cell.get() + 1);
          if(options.bold_todo && !cell.is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(cell.is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const auto __cell_center683 = cell_center(cell.coordinates());
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const auto __cell_center692 = cell_center(cell.coordinates());
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        auto && __range3 = sudoku.cells();
        for(; ; ) {
          const auto & cell;
          if(!cell.is_set()) {
            (static_cast<bool>(!cell.is_propagated()) ? void(0) : __assert_fail("!cell.is_propagated()", "/wd/src/explanation/art.cpp", 706, __extension____PRETTY_FUNCTION__));
            {
              auto && __range5 = SudokuConstants<size>::values;
              for(; ; ) {
                unsigned int value;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const auto __value_center715 = value_center(cell.coordinates(), value);
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(cell.is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[] = {1, SudokuConstants<size>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= size; i = static_cast<unsigned int>(static_cast<<dependent type>>(i) + strides[k])) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const auto __cell_center749 = cell_center(cell);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), 0, static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options753 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const auto __cell_center761 = cell_center(cell);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options765 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator772 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const auto __value_center774 = value_center(cell, value);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / SudokuConstants<size>::sqrt_size, 0, static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options778 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options790 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator795 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const auto __cell_center798 = cell_center(source_cell);
          const auto __value_center799 = value_center(target_cell, value);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), 0, static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / SudokuConstants<size>::sqrt_size, 0, static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  
  /* First instantiated from: art.cpp:822 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<4>(std::shared_ptr<Cairo::Context> cr, const Sudoku<AnnotatedCell<4>, 4> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(4U);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_653_28
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell654 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_653_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_653_28 cell_center = static_cast<const __lambda_653_28>(__lambda_653_28{cell_size});
        
    class __lambda_658_29
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell659 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int value_x = value % SudokuConstants<4>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<4>::sqrt_size;
        return std::make_pair<double, double>((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size)), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size)));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_658_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_658_29 value_center = static_cast<const __lambda_658_29>(__lambda_658_29{cell_size});
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(static_cast<const AnnotatedCell<4>&>(cell).get() + static_cast<unsigned int>(1)));
          if(options.bold_todo && !static_cast<const AnnotatedCell<4>&>(cell).is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(static_cast<const AnnotatedCell<4>&>(cell).is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const std::pair<double, double> __operator683 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const std::pair<double, double> __operator692 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
          if(!static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
            (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(cell).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!cell.is_propagated()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(706), static_cast<const char *>(__extension__"void art::draw(Cairo::RefPtr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &) [size = 4U]")));
            {
              const std::array<unsigned int, 4> & __range5 = SudokuConstants<4>::values;
              const unsigned int * __begin0 = __range5.begin();
              const unsigned int * __end0 = __range5.end();
              for(; __begin0 != __end0; ++__begin0) {
                unsigned int value = *__begin0;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const std::pair<double, double> __operator715 = static_cast<const std::pair<double, double>>(value_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()), value));
                  const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[2] = {static_cast<const unsigned int>(1), SudokuConstants<4>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= 4U; i = i + static_cast<const unsigned int *>(strides)[k]) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator749 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options753 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const std::pair<double, double> __operator761 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options765 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator772 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator774 = static_cast<const std::pair<double, double>>(value_center.operator()(cell, value));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options778 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options790 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator795 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const std::pair<double, double> __operator798 = static_cast<const std::pair<double, double>>(cell_center.operator()(source_cell));
          const double && x1 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const double && y1 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const std::pair<double, double> __operator799 = static_cast<const std::pair<double, double>>(value_center.operator()(target_cell, value));
          const double && x2 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          const double && y2 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  #endif
  
  
  /* First instantiated from: art.cpp:823 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<9>(std::shared_ptr<Cairo::Context> cr, const Sudoku<AnnotatedCell<9>, 9> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(9U);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_653_28
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell654 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell654));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_653_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_653_28 cell_center = static_cast<const __lambda_653_28>(__lambda_653_28{cell_size});
        
    class __lambda_658_29
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell659 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell659));
        const unsigned int value_x = value % SudokuConstants<9>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<9>::sqrt_size;
        return std::make_pair<double, double>((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size)), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size)));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_658_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_658_29 value_center = static_cast<const __lambda_658_29>(__lambda_658_29{cell_size});
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(static_cast<const AnnotatedCell<9>&>(cell).get() + static_cast<unsigned int>(1)));
          if(options.bold_todo && !static_cast<const AnnotatedCell<9>&>(cell).is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(static_cast<const AnnotatedCell<9>&>(cell).is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const std::pair<double, double> __operator683 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator683));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const std::pair<double, double> __operator692 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator692));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
        boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_302_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
          if(!static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
            (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(cell).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!cell.is_propagated()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(706), static_cast<const char *>(__extension__"void art::draw(Cairo::RefPtr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &) [size = 9U]")));
            {
              const std::array<unsigned int, 9> & __range5 = SudokuConstants<9>::values;
              const unsigned int * __begin0 = __range5.begin();
              const unsigned int * __end0 = __range5.end();
              for(; __begin0 != __end0; ++__begin0) {
                unsigned int value = *__begin0;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const std::pair<double, double> __operator715 = static_cast<const std::pair<double, double>>(value_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()), value));
                  const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator715));
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[2] = {static_cast<const unsigned int>(1), SudokuConstants<9>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= 9U; i = i + static_cast<const unsigned int *>(strides)[k]) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator749 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator749));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options753 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options753));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const std::pair<double, double> __operator761 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator761));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options765 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options765));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator772 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator772));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator774 = static_cast<const std::pair<double, double>>(value_center.operator()(cell, value));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator774));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options778 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options778));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options790 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options790));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator795 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator795));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const std::pair<double, double> __operator798 = static_cast<const std::pair<double, double>>(cell_center.operator()(source_cell));
          const double && x1 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const double && y1 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator798));
          const std::pair<double, double> __operator799 = static_cast<const std::pair<double, double>>(value_center.operator()(target_cell, value));
          const double && x2 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          const double && y2 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator799));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  #endif
  
  template<unsigned int cols, unsigned int rows>
  struct TestImage
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit TestImage(std::filesystem::path path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(static_cast<const std::filesystem::path>(path_))}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(cols * this->frame_width), static_cast<int>(rows * this->frame_height))}
    , crs{}
    {
      std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
      for(unsigned int col = static_cast<unsigned int>(0); col != cols; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != rows; ++row) {
          this->crs[col][row] = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
          this->crs[col][row]->translate(col * this->frame_width, row * this->frame_height);
          this->crs[col][row]->save();
          this->crs[col][row]->translate(margin, margin);
        }
        
      }
      
    }
    
    inline ~TestImage()
    {
      for(unsigned int col = static_cast<unsigned int>(0); col != cols; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != rows; ++row) {
          this->crs[col][row]->restore();
          this->crs[col][row]->rectangle(0, 0, this->frame_width, this->frame_height);
          this->crs[col][row]->rectangle(margin, margin, this->viewport_width, this->viewport_height);
          this->crs[col][row]->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
          this->crs[col][row]->set_source_rgba(1, 0, 0, 0.5);
          this->crs[col][row]->fill();
        }
        
      }
      
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::array<std::array<Cairo::RefPtr<Cairo::Context>, rows>, cols> crs;
  };
  
  /* First instantiated from: art.cpp:881 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct TestImage<2, 1>
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit TestImage(std::filesystem::path path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(static_cast<const std::filesystem::path>(path_))}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(2U * this->frame_width), static_cast<int>(1U * this->frame_height))}
    , crs{std::array<std::array<std::shared_ptr<Cairo::Context>, 1>, 2>()}
    {
      std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
      for(unsigned int col = static_cast<unsigned int>(0); col != 2U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 1U; ++row) {
          this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row)).operator=(Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface)))));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(col * this->frame_width), static_cast<double>(row * this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->save();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
        }
        
      }
      
    }
    
    inline ~TestImage() noexcept
    {
      for(unsigned int col = static_cast<unsigned int>(0); col != 2U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 1U; ++row) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->restore();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_source_rgba(static_cast<double>(1), static_cast<double>(0), static_cast<double>(0), 0.5);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->fill();
        }
        
      }
      
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::array<std::array<std::shared_ptr<Cairo::Context>, 1>, 2> crs;
  };
  
  #endif
  /* First instantiated from: art.cpp:901 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct TestImage<3, 2>
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit TestImage(std::filesystem::path path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(static_cast<const std::filesystem::path>(path_))}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(3U * this->frame_width), static_cast<int>(2U * this->frame_height))}
    , crs{std::array<std::array<std::shared_ptr<Cairo::Context>, 2>, 3>()}
    {
      std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
      for(unsigned int col = static_cast<unsigned int>(0); col != 3U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 2U; ++row) {
          this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row)).operator=(Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface)))));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(col * this->frame_width), static_cast<double>(row * this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->save();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
        }
        
      }
      
    }
    
    inline ~TestImage() noexcept
    {
      for(unsigned int col = static_cast<unsigned int>(0); col != 3U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 2U; ++row) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->restore();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_source_rgba(static_cast<double>(1), static_cast<double>(0), static_cast<double>(0), 0.5);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->fill();
        }
        
      }
      
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::array<std::array<std::shared_ptr<Cairo::Context>, 2>, 3> crs;
  };
  
  #endif
  static void DOCTEST_ANON_FUNC_2();
  static const int DOCTEST_ANON_VAR_3 = doctest::detail::consume(&DOCTEST_ANON_VAR_3, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_2, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(880), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - grid")))));
  static void DOCTEST_ANON_FUNC_2()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-grid.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(Sudoku<AnnotatedCell<4>, 4>()), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(Sudoku<AnnotatedCell<9>, 9>()), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  static void DOCTEST_ANON_FUNC_4();
  static const int DOCTEST_ANON_VAR_5 = doctest::detail::consume(&DOCTEST_ANON_VAR_5, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_4, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(894), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - grid - multiple sizes")))));
  static void DOCTEST_ANON_FUNC_4()
  {
    std::array<std::array<unsigned int, 3>, 2> frame_sizes = {{{{static_cast<unsigned int>(100), static_cast<unsigned int>(140), static_cast<unsigned int>(200)}}, {{static_cast<unsigned int>(280), static_cast<unsigned int>(400), static_cast<unsigned int>(560)}}}};
    TestImage<3, 2> image = TestImage<3, 2>(std::filesystem::path("tests/unit/explanation/art/draw-grid-multiple-sizes.png", std::filesystem::path::auto_format), static_cast<unsigned int>(580), static_cast<unsigned int>(580));
    for(unsigned int col = static_cast<unsigned int>(0); col != static_cast<unsigned int>(3); ++col) {
      for(unsigned int row = static_cast<unsigned int>(0); row != static_cast<unsigned int>(2); ++row) {
        const unsigned int frame_size = frame_sizes.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
        const double grid_size = round_grid_size<9>(frame_size);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
        draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(Sudoku<AnnotatedCell<9>, 9>()), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    }
    
  }
  static void DOCTEST_ANON_FUNC_6();
  static const int DOCTEST_ANON_VAR_7 = doctest::detail::consume(&DOCTEST_ANON_VAR_7, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_6, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(913), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - known-values circled")))));
  static void DOCTEST_ANON_FUNC_6()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-known-values-circled.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<4>, 4> sudoku = Sudoku<AnnotatedCell<4>, 4>();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin2).operator++()) {
          SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin2).operator*();
          const std::pair<unsigned int, unsigned int> __cell920 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<4>, 4>::Cell>(cell).coordinates());
          const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell920));
          const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell920));
          static_cast<AnnotatedCell<4>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(4));
        }
        
      }
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{SudokuConstants<4>::cells.begin(), SudokuConstants<4>::cells.end(), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator++()) {
          SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator*();
          const std::pair<unsigned int, unsigned int> __cell937 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
          const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell937));
          const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell937));
          static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
        }
        
      }
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end(), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  static void DOCTEST_ANON_FUNC_8();
  static const int DOCTEST_ANON_VAR_9 = doctest::detail::consume(&DOCTEST_ANON_VAR_9, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_8, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(951), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all inputs")))));
  static void DOCTEST_ANON_FUNC_8()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-inputs.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell957 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell957));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell957));
        static_cast<AnnotatedCell<9>&>(cell).set_input((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_10();
  static const int DOCTEST_ANON_VAR_11 = doctest::detail::consume(&DOCTEST_ANON_VAR_11, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_10, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(969), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all todo")))));
  static void DOCTEST_ANON_FUNC_10()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-todo.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell975 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell975));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell975));
        static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_12();
  static const int DOCTEST_ANON_VAR_13 = doctest::detail::consume(&DOCTEST_ANON_VAR_13, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_12, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(988), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all processed")))));
  static void DOCTEST_ANON_FUNC_12()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-processed.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell994 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell994));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell994));
        static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
        static_cast<AnnotatedCell<9>&>(cell).set_propagated();
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_14();
  static const int DOCTEST_ANON_VAR_15 = doctest::detail::consume(&DOCTEST_ANON_VAR_15, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_14, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(1008), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - known-values boxed")))));
  static void DOCTEST_ANON_FUNC_14()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-known-values-boxed.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell1014 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1014));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1014));
        static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end(), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_16();
  static const int DOCTEST_ANON_VAR_17 = doctest::detail::consume(&DOCTEST_ANON_VAR_17, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_16, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(1028), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all forbidden")))));
  static void DOCTEST_ANON_FUNC_16()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-forbidden.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell1034 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1034));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1034));
        {
          const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
          const unsigned int * __begin2 = __range2.begin();
          const unsigned int * __end2 = __range2.end();
          for(; __begin2 != __end2; ++__begin2) {
            const unsigned int value = *__begin2;
            if(value != ((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9))) {
              static_cast<AnnotatedCell<9>&>(cell).forbid(value);
            } 
            
          }
          
        }
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_18();
  static const int DOCTEST_ANON_VAR_19 = doctest::detail::consume(&DOCTEST_ANON_VAR_19, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_18, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(1050), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - possible-values circled")))));
  static void DOCTEST_ANON_FUNC_18()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-possible-values-circled.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<4>, 4> sudoku = Sudoku<AnnotatedCell<4>, 4>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      {
        const std::array<std::pair<unsigned int, unsigned int>, 16> & __range2 = SudokuConstants<4>::cells;
        const std::pair<unsigned int, unsigned int> * __begin2 = __range2.begin();
        const std::pair<unsigned int, unsigned int> * __end2 = __range2.end();
        for(; __begin2 != __end2; ++__begin2) {
          const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(*__begin2);
          {
            const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
            const unsigned int * __begin3 = __range3.begin();
            const unsigned int * __end3 = __range3.end();
            for(; __begin3 != __end3; ++__begin3) {
              const unsigned int value = *__begin3;
              circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{cell, value});
            }
            
          }
        }
        
      }
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator++()) {
          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator*());
          {
            const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
            const unsigned int * __begin3 = __range3.begin();
            const unsigned int * __end3 = __range3.end();
            for(; __begin3 != __end3; ++__begin3) {
              const unsigned int value = *__begin3;
              circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{cell.coordinates(), value});
            }
            
          }
        }
        
      }
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  static void DOCTEST_ANON_FUNC_20();
  static const int DOCTEST_ANON_VAR_21 = doctest::detail::consume(&DOCTEST_ANON_VAR_21, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_20, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(1092), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - possible-values linked")))));
  static void DOCTEST_ANON_FUNC_20()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-possible-values-linked.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<4>, 4> sudoku = Sudoku<AnnotatedCell<4>, 4>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>{2, 3};
      {
        const std::array<std::pair<unsigned int, unsigned int>, 16> & __range2 = SudokuConstants<4>::cells;
        const std::pair<unsigned int, unsigned int> * __begin2 = __range2.begin();
        const std::pair<unsigned int, unsigned int> * __end2 = __range2.end();
        for(; __begin2 != __end2; ++__begin2) {
          const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(*__begin2);
          if(!std::operator==(cell, static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))) {
            const std::pair<unsigned int, unsigned int> __cell1104 = std::pair<unsigned int, unsigned int>(cell);
            const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1104));
            const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell1104));
            {
              const std::array<unsigned int, 4> & __range4 = SudokuConstants<4>::values;
              const unsigned int * __begin4 = __range4.begin();
              const unsigned int * __end4 = __range4.end();
              for(; __begin4 != __end4; ++__begin4) {
                const unsigned int value = *__begin4;
                if(value == ((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(4))) {
                  links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{source_cell, cell, value});
                  circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{cell, value});
                } 
                
              }
              
            }
          } 
          
        }
        
      }
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>{2, 3};
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator++()) {
          SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_313_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator*();
          const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
          if(!std::operator==(coords, static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))) {
            const std::pair<unsigned int, unsigned int> __coords1135 = std::pair<unsigned int, unsigned int>(coords);
            const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1135));
            const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1135));
            {
              const std::array<unsigned int, 9> & __range4 = SudokuConstants<9>::values;
              const unsigned int * __begin4 = __range4.begin();
              const unsigned int * __end4 = __range4.end();
              for(; __begin4 != __end4; ++__begin4) {
                const unsigned int value = *__begin4;
                if(value == ((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9))) {
                  links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{source_cell, coords, value});
                  circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{coords, value});
                } 
                
              }
              
            }
          } 
          
        }
        
      }
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  
}  // namespace art
