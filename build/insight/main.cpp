# 1 "src/main.cpp"
// Copyright 2023 Vincent Jacques

#include <CLI11.hpp>

# 1 "src/explanation/html-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>
#include <fstream>
#include <string>

# 1 "src/exploration/events.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

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


typedef std::pair<unsigned, unsigned> Coordinates;


template<unsigned int size>
class SudokuConstants
{
  
  private: 
  static inline constexpr auto sqrt(unsigned int res, unsigned int l, unsigned int r)
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
  
  static inline constexpr auto sqrt(unsigned int res)
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
      auto && __range0 = values;
      for(; ; ) {
        unsigned int row;
        {
          auto && __range1 = values;
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
      auto && __range0 = values;
      for(; ; ) {
        unsigned int row;
        {
          auto && __range1 = values;
          for(; ; ) {
            unsigned int col;
            regions[row][col] = {row, col};
          }
          
        }
      }
      
    }
    {
      auto && __range0 = values;
      for(; ; ) {
        unsigned int col;
        {
          auto && __range1 = values;
          for(; ; ) {
            unsigned int row;
            regions[size + col][row] = {row, col};
          }
          
        }
      }
      
    }
    {
      auto && __range0 = values;
      for(; ; ) {
        unsigned int square;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          auto && __range1 = values;
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
      auto && __range0 = values;
      for(; ; ) {
        unsigned int row;
        {
          auto && __range1 = values;
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
  inline static constexpr const auto sqrt_size = sqrt(size);
  inline static constexpr const auto values = make_values();
  inline static constexpr const auto cells = make_cells();
  inline static constexpr const auto region_indexes = make_region_indexes();
  inline static constexpr const auto regions = make_regions();
  inline static constexpr const auto regions_of = make_regions_of();
  
  private: 
  
  /* PASSED: static_assert((sqrt_size * sqrt_size) == size, "'size' must be a perfect square"); */
};

/* First instantiated from: main.cpp:332 */
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
      const std::array<unsigned int, 4> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 4> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
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
      const std::array<unsigned int, 4> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 4> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      const std::array<unsigned int, 4> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int col = *__begin0;
        {
          const std::array<unsigned int, 4> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int row = *__begin0;
            regions.operator[](static_cast<unsigned long>(4U + col)).operator[](static_cast<unsigned long>(row)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      const std::array<unsigned int, 4> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int square = *__begin0;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          const std::array<unsigned int, 4> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
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
      const std::array<unsigned int, 4> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 4> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
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
/* First instantiated from: main.cpp:332 */
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
      const std::array<unsigned int, 9> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 9> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
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
      const std::array<unsigned int, 9> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 9> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int col = *__begin0;
            regions.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      const std::array<unsigned int, 9> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int col = *__begin0;
        {
          const std::array<unsigned int, 9> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
          for(; __begin0 != __end0; ++__begin0) {
            unsigned int row = *__begin0;
            regions.operator[](static_cast<unsigned long>(9U + col)).operator[](static_cast<unsigned long>(row)).operator=(std::pair<unsigned int, unsigned int>{row, col});
          }
          
        }
      }
      
    }
    {
      const std::array<unsigned int, 9> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int square = *__begin0;
        const unsigned int top_row = (square / sqrt_size) * sqrt_size;
        const unsigned int left_col = (square % sqrt_size) * sqrt_size;
        {
          const std::array<unsigned int, 9> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
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
      const std::array<unsigned int, 9> & __range0 = values;
      const unsigned int * __begin0 = __range0.begin();
      const unsigned int * __end0 = __range0.end();
      for(; __begin0 != __end0; ++__begin0) {
        unsigned int row = *__begin0;
        {
          const std::array<unsigned int, 9> & __range1 = values;
          const unsigned int * __begin0 = __range1.begin();
          const unsigned int * __end0 = __range1.end();
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

/* First instantiated from: main.cpp:388 */
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
  
  /* First instantiated from: main.cpp:278 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main.cpp:283 */
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
/* First instantiated from: main.cpp:388 */
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
  
  /* First instantiated from: main.cpp:278 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &, const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main.cpp:283 */
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
/* First instantiated from: main.cpp:527 */
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
  
  /* First instantiated from: main.cpp:259 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main.cpp:264 */
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
/* First instantiated from: main.cpp:527 */
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
  
  /* First instantiated from: main.cpp:259 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main.cpp:264 */
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

/* First instantiated from: main.cpp:1881 */
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
/* First instantiated from: main.cpp:1881 */
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

/* First instantiated from: main.cpp:751 */
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
/* First instantiated from: main.cpp:751 */
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
# 9 "src/exploration/events.hpp"


namespace exploration
{
  template<unsigned int size>
  struct CellIsSetInInput
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main.cpp:1804 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: main.cpp:1804 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct InputsAreDone
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main.cpp:1809 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<4>
  {
    void apply(Stack<4> *) const;
    
  };
  
  #endif
  /* First instantiated from: main.cpp:1809 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<9>
  {
    void apply(Stack<9> *) const;
    
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main.cpp:1631 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
  };
  
  #endif
  /* First instantiated from: main.cpp:1631 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<9>
  {
    void apply(Stack<9> *) const;
    
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main.cpp:1643 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: main.cpp:1643 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
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
  
  /* First instantiated from: alloc_traits.h:850 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellPropagates<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: alloc_traits.h:850 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellPropagates<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct CellIsDeducedFromSingleAllowedValue
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: alloc_traits.h:850 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsDeducedFromSingleAllowedValue(const CellIsDeducedFromSingleAllowedValue<4> &) noexcept = default;
    // inline constexpr CellIsDeducedFromSingleAllowedValue(CellIsDeducedFromSingleAllowedValue<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: alloc_traits.h:850 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsDeducedFromSingleAllowedValue(const CellIsDeducedFromSingleAllowedValue<9> &) noexcept = default;
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
  
  /* First instantiated from: alloc_traits.h:850 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
    // inline constexpr CellIsDeducedAsSinglePlaceForValueInRegion(const CellIsDeducedAsSinglePlaceForValueInRegion<4> &) noexcept = default;
    // inline constexpr CellIsDeducedAsSinglePlaceForValueInRegion(CellIsDeducedAsSinglePlaceForValueInRegion<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: alloc_traits.h:850 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
    // inline constexpr CellIsDeducedAsSinglePlaceForValueInRegion(const CellIsDeducedAsSinglePlaceForValueInRegion<9> &) noexcept = default;
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
  
  /* First instantiated from: main.cpp:1644 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationIsDoneForCell(const PropagationIsDoneForCell<4> &) noexcept = default;
  };
  
  #endif
  /* First instantiated from: main.cpp:1644 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationIsDoneForCell(const PropagationIsDoneForCell<9> &) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationIsDoneForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main.cpp:1632 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(const PropagationIsDoneForSudoku<4> &) noexcept = default;
  };
  
  #endif
  /* First instantiated from: main.cpp:1632 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(const PropagationIsDoneForSudoku<9> &) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct ExplorationStarts
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  /* First instantiated from: main.cpp:1756 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  #endif
  /* First instantiated from: main.cpp:1756 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsMade
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main.cpp:1761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: main.cpp:1761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsRejected
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main.cpp:1766 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: main.cpp:1766 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct SudokuIsSolved
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main.cpp:1695 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<4>
  {
    void apply(Stack<4> *) const;
    
  };
  
  #endif
  /* First instantiated from: main.cpp:1695 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<9>
  {
    void apply(Stack<9> *) const;
    
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsAccepted
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main.cpp:1763 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: main.cpp:1763 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct ExplorationIsDone
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  /* First instantiated from: main.cpp:1757 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(const ExplorationIsDone<4> &) noexcept = default;
  };
  
  #endif
  /* First instantiated from: main.cpp:1757 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(const ExplorationIsDone<9> &) noexcept = default;
  };
  
  #endif
  
}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
# 11 "src/explanation/html-explainer.hpp"


template<unsigned int size>
class HtmlExplainer
{
  
  public: 
  inline explicit HtmlExplainer(const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<size> &);
  
  void operator()(const exploration::InputsAreDone<size> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<size> &);
  
  void operator()(const exploration::PropagationStartsForCell<size> &);
  
  void operator()(const exploration::CellPropagates<size> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<size> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<size> &);
  
  void operator()(const exploration::ExplorationStarts<size> &);
  
  void operator()(const exploration::HypothesisIsMade<size> &);
  
  void operator()(const exploration::HypothesisIsRejected<size> &);
  
  void operator()(const exploration::SudokuIsSolved<size> &);
  
  void operator()(const exploration::HypothesisIsAccepted<size> &);
  
  void operator()(const exploration::ExplorationIsDone<size> &);
  
  
  private: 
  inline const AnnotatedSudoku<size> & current() const
  {
    return this->stack.current();
  }
  
  struct Image;
  Image image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &) const;
  
  
  private: 
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<size> stack;
};

/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class HtmlExplainer<4>
{
  
  public: 
  inline explicit HtmlExplainer(const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{Stack<4>()}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<4> &);
  
  void operator()(const exploration::InputsAreDone<4> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<4> &);
  
  void operator()(const exploration::PropagationStartsForCell<4> &);
  
  void operator()(const exploration::CellPropagates<4> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<4> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<4> &);
  
  void operator()(const exploration::ExplorationStarts<4> &);
  
  void operator()(const exploration::HypothesisIsMade<4> &);
  
  void operator()(const exploration::HypothesisIsRejected<4> &);
  
  void operator()(const exploration::SudokuIsSolved<4> &);
  
  void operator()(const exploration::HypothesisIsAccepted<4> &);
  
  void operator()(const exploration::ExplorationIsDone<4> &);
  
  
  private: 
  inline const Sudoku<AnnotatedCell<4>, 4> & current() const;
  
  struct Image;
  Image image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &) const;
  
  
  private: 
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<4> stack;
  public: 
  // inline HtmlExplainer(const HtmlExplainer<4> &) /* noexcept */ = delete;
  // inline HtmlExplainer<4> & operator=(const HtmlExplainer<4> &) /* noexcept */ = delete;
  // inline ~HtmlExplainer() = default;
};

#endif
/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class HtmlExplainer<9>
{
  
  public: 
  inline explicit HtmlExplainer(const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{Stack<9>()}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<9> &);
  
  void operator()(const exploration::InputsAreDone<9> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<9> &);
  
  void operator()(const exploration::PropagationStartsForCell<9> &);
  
  void operator()(const exploration::CellPropagates<9> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<9> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<9> &);
  
  void operator()(const exploration::ExplorationStarts<9> &);
  
  void operator()(const exploration::HypothesisIsMade<9> &);
  
  void operator()(const exploration::HypothesisIsRejected<9> &);
  
  void operator()(const exploration::SudokuIsSolved<9> &);
  
  void operator()(const exploration::HypothesisIsAccepted<9> &);
  
  void operator()(const exploration::ExplorationIsDone<9> &);
  
  
  private: 
  inline const Sudoku<AnnotatedCell<9>, 9> & current() const;
  
  struct Image;
  Image image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &) const;
  
  
  private: 
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<9> stack;
  public: 
  // inline HtmlExplainer(const HtmlExplainer<9> &) /* noexcept */ = delete;
  // inline HtmlExplainer<9> & operator=(const HtmlExplainer<9> &) /* noexcept */ = delete;
  // inline ~HtmlExplainer() = default;
};

#endif


#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
# 6 "src/main.cpp"
# 1 "src/explanation/reorder.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_REORDER_HPP_
#define EXPLANATION_REORDER_HPP_

#include <functional>
#include <vector>

# 10 "src/explanation/reorder.hpp"


template<unsigned int size, typename ProcessEvent>
class Reorder
{
  
  public: 
  inline explicit Reorder(ProcessEvent * process_event_)
  : process_event{*process_event_}
  {
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::InputsAreDone<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::CellPropagates<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<size> & event)
  {
    this->process_event(event);
    this->flush_pending_events();
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::ExplorationStarts<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::HypothesisIsMade<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::SudokuIsSolved<size> & event)
  {
    this->flush_pending_events();
    this->process_event(event);
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<size> & event)
  {
    this->process_event(event);
  }
  
  inline void operator()(const exploration::ExplorationIsDone<size> & event)
  {
    this->process_event(event);
  }
  
  
  private: 
  inline void flush_pending_events()
  {
    {
      auto && __range0 = this->pending_cell_is_deduced_from_single_allowed_value_events;
      for(; ; ) {
        const auto & event;
        this->process_event(event);
      }
      
    }
    {
      auto && __range0 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
      for(; ; ) {
        const auto & event;
        this->process_event(event);
      }
      
    }
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  
  private: 
  ProcessEvent & process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size> > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};

/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Reorder<4, TextExplainer<4> >
{
  
  public: 
  inline explicit Reorder(TextExplainer<4> * process_event_)
  : process_event{*process_event_}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >()}
  {
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::InputsAreDone<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellPropagates<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<4> & event)
  {
    this->process_event.operator()(event);
    this->flush_pending_events();
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationStarts<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsMade<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::SudokuIsSolved<4> & event)
  {
    this->flush_pending_events();
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationIsDone<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  
  private: 
  inline void flush_pending_events()
  {
    {
      std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range0 = this->pending_cell_is_deduced_from_single_allowed_value_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    {
      std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range0 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  
  private: 
  TextExplainer<4> & process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline Reorder<4, TextExplainer<4> > & operator=(const Reorder<4, TextExplainer<4> > &) /* noexcept */ = delete;
  // inline Reorder<4, TextExplainer<4> > & operator=(Reorder<4, TextExplainer<4> > &&) /* noexcept */ = delete;
  // inline constexpr ~Reorder() noexcept = default;
};

#endif
/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Reorder<4, VideoExplainer<4> >
{
  
  public: 
  inline explicit Reorder(VideoExplainer<4> * process_event_)
  : process_event{*process_event_}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >()}
  {
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::InputsAreDone<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellPropagates<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<4> & event)
  {
    this->process_event.operator()(event);
    this->flush_pending_events();
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationStarts<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsMade<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::SudokuIsSolved<4> & event)
  {
    this->flush_pending_events();
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationIsDone<4> & event)
  {
    this->process_event.operator()(event);
  }
  
  
  private: 
  inline void flush_pending_events()
  {
    {
      std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range0 = this->pending_cell_is_deduced_from_single_allowed_value_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    {
      std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range0 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  
  private: 
  VideoExplainer<4> & process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline Reorder<4, VideoExplainer<4> > & operator=(const Reorder<4, VideoExplainer<4> > &) /* noexcept */ = delete;
  // inline Reorder<4, VideoExplainer<4> > & operator=(Reorder<4, VideoExplainer<4> > &&) /* noexcept */ = delete;
  // inline constexpr ~Reorder() noexcept = default;
};

#endif
/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Reorder<9, TextExplainer<9> >
{
  
  public: 
  inline explicit Reorder(TextExplainer<9> * process_event_)
  : process_event{*process_event_}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >()}
  {
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::InputsAreDone<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellPropagates<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<9> & event)
  {
    this->process_event.operator()(event);
    this->flush_pending_events();
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationStarts<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsMade<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::SudokuIsSolved<9> & event)
  {
    this->flush_pending_events();
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationIsDone<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  
  private: 
  inline void flush_pending_events()
  {
    {
      std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range0 = this->pending_cell_is_deduced_from_single_allowed_value_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    {
      std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range0 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  
  private: 
  TextExplainer<9> & process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline Reorder<9, TextExplainer<9> > & operator=(const Reorder<9, TextExplainer<9> > &) /* noexcept */ = delete;
  // inline Reorder<9, TextExplainer<9> > & operator=(Reorder<9, TextExplainer<9> > &&) /* noexcept */ = delete;
  // inline constexpr ~Reorder() noexcept = default;
};

#endif
/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Reorder<9, VideoExplainer<9> >
{
  
  public: 
  inline explicit Reorder(VideoExplainer<9> * process_event_)
  : process_event{*process_event_}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >()}
  {
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::InputsAreDone<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellPropagates<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<9> & event)
  {
    this->process_event.operator()(event);
    this->flush_pending_events();
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationStarts<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsMade<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::SudokuIsSolved<9> & event)
  {
    this->flush_pending_events();
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  inline void operator()(const exploration::ExplorationIsDone<9> & event)
  {
    this->process_event.operator()(event);
  }
  
  
  private: 
  inline void flush_pending_events()
  {
    {
      std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range0 = this->pending_cell_is_deduced_from_single_allowed_value_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    {
      std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range0 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end0)); __begin0.operator++()) {
        const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin0).operator*());
        this->process_event.operator()(event);
      }
      
    }
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  
  private: 
  VideoExplainer<9> & process_event;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline Reorder<9, VideoExplainer<9> > & operator=(const Reorder<9, VideoExplainer<9> > &) /* noexcept */ = delete;
  // inline Reorder<9, VideoExplainer<9> > & operator=(Reorder<9, VideoExplainer<9> > &&) /* noexcept */ = delete;
  // inline constexpr ~Reorder() noexcept = default;
};

#endif


#endif  // EXPLANATION_REORDER_HPP_
# 7 "src/main.cpp"
# 1 "src/explanation/text-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <string>

#include <boost/format.hpp>

# 11 "src/explanation/text-explainer.hpp"


template<unsigned int size>
class TextExplainer
{
  
  public: 
  inline explicit TextExplainer(std::basic_ostream<char> & os_)
  : os{os_}
  , hypotheses_count{static_cast<unsigned int>(0)}
  {
  }
  
  inline ~TextExplainer()
  {
    (static_cast<bool>(this->hypotheses_count == static_cast<unsigned int>(0)) ? void(0) : __assert_fail("hypotheses_count == 0", "src/explanation/text-explainer.hpp", 19, __extension____PRETTY_FUNCTION__));
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<size> & event)
  {
    this->print_prefix();
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%2%, %3%) is set to %1% in the input\n"))) % (event.value + 1)) % (event.cell.first + 1)) % (event.cell.second + 1));
  }
  
  inline void operator()(const exploration::InputsAreDone<size> &)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("All inputs have been set\n"));
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<size> &)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("Propagation starts\n"));
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<size> & event)
  {
    this->print_prefix();
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagation starts for %1% in (%2%, %3%)\n"))) % (event.value + 1)) % (event.cell.first + 1)) % (event.cell.second + 1));
  }
  
  inline void operator()(const exploration::CellPropagates<size> & event)
  {
    this->print_prefix();
    this->os << (((((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n"))) % (event.value + 1)) % (event.source_cell.first + 1)) % (event.source_cell.second + 1)) % (event.target_cell.first + 1)) % (event.target_cell.second + 1));
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size> & event)
  {
    this->print_prefix();
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) can only be %3%\n"))) % (event.cell.first + 1)) % (event.cell.second + 1)) % (event.value + 1));
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> & event)
  {
    this->print_prefix();
    this->os << ((((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("In region %4%, only (%1%, %2%) can be %3%\n"))) % (event.cell.first + 1)) % (event.cell.second + 1)) % (event.value + 1)) % (event.region + 1));
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<size> & event)
  {
    this->print_prefix();
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("%1% in (%2%, %3%) has been fully propagated\n"))) % (event.value + 1)) % (event.cell.first + 1)) % (event.cell.second + 1));
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<size> & event)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("All cells have been fully propagated\n"));
  }
  
  inline void operator()(const exploration::ExplorationStarts<size> & event)
  {
    this->print_prefix();
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Exploration starts for (%1%, %2%) with %3% possible values\n"))) % (event.cell.first + 1)) % (event.cell.second + 1)) % event.allowed_values.size());
  }
  
  inline void operator()(const exploration::HypothesisIsMade<size> & event)
  {
    this->print_prefix();
    ++this->hypotheses_count;
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) may be %3%\n"))) % (event.cell.first + 1)) % (event.cell.second + 1)) % (event.value + 1));
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<size> & event)
  {
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail("hypotheses_count > 0", "src/explanation/text-explainer.hpp", 89, __extension____PRETTY_FUNCTION__));
    this->print_prefix();
    --this->hypotheses_count;
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n"))) % (event.cell.first + 1)) % (event.cell.second + 1)) % (event.value + 1));
  }
  
  inline void operator()(const exploration::SudokuIsSolved<size> & event)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("Sudoku is solved\n"));
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<size> & event)
  {
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail("hypotheses_count > 0", "src/explanation/text-explainer.hpp", 102, __extension____PRETTY_FUNCTION__));
    this->print_prefix();
    --this->hypotheses_count;
    this->os << (((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) can indeed be %3%\n"))) % (event.cell.first + 1)) % (event.cell.second + 1)) % (event.value + 1));
  }
  
  inline void operator()(const exploration::ExplorationIsDone<size> & event)
  {
    this->print_prefix();
    this->os << ((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Exploration is done for (%1%, %2%)\n"))) % (event.cell.first + 1)) % (event.cell.second + 1));
  }
  
  
  private: 
  inline void print_prefix()
  {
    for(unsigned int i = static_cast<unsigned int>(0); i < this->hypotheses_count; ++i) {
      std::operator<<(this->os, static_cast<const char *>("  "));
    }
    
  }
  
  
  private: 
  std::basic_ostream<char> & os;
  unsigned int hypotheses_count;
};

/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class TextExplainer<4>
{
  
  public: 
  inline explicit TextExplainer(std::basic_ostream<char> & os_)
  : os{os_}
  , hypotheses_count{static_cast<unsigned int>(0)}
  {
  }
  
  inline ~TextExplainer() noexcept
  {
    (static_cast<bool>(this->hypotheses_count == static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count == 0"), static_cast<const char *>("src/explanation/text-explainer.hpp"), static_cast<unsigned int>(19), static_cast<const char *>(__extension__"TextExplainer<4>::~TextExplainer() [size = 4]")));
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%2%, %3%) is set to %1% in the input\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::InputsAreDone<4> &)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("All inputs have been set\n"));
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<4> &)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("Propagation starts\n"));
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagation starts for %1% in (%2%, %3%)\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::CellPropagates<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.source_cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.source_cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.target_cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.target_cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) can only be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("In region %4%, only (%1%, %2%) can be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.region + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("%1% in (%2%, %3%) has been fully propagated\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<4> & event)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("All cells have been fully propagated\n"));
  }
  
  inline void operator()(const exploration::ExplorationStarts<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Exploration starts for (%1%, %2%) with %3% possible values\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned long>(event.allowed_values.size()))));
  }
  
  inline void operator()(const exploration::HypothesisIsMade<4> & event)
  {
    this->print_prefix();
    ++this->hypotheses_count;
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) may be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<4> & event)
  {
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("src/explanation/text-explainer.hpp"), static_cast<unsigned int>(89), static_cast<const char *>(__extension__"void TextExplainer<4>::operator()(const exploration::HypothesisIsRejected<size> &) [size = 4]")));
    this->print_prefix();
    --this->hypotheses_count;
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::SudokuIsSolved<4> & event)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("Sudoku is solved\n"));
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<4> & event)
  {
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("src/explanation/text-explainer.hpp"), static_cast<unsigned int>(102), static_cast<const char *>(__extension__"void TextExplainer<4>::operator()(const exploration::HypothesisIsAccepted<size> &) [size = 4]")));
    this->print_prefix();
    --this->hypotheses_count;
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) can indeed be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::ExplorationIsDone<4> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Exploration is done for (%1%, %2%)\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  
  private: 
  inline void print_prefix()
  {
    for(unsigned int i = static_cast<unsigned int>(0); i < this->hypotheses_count; ++i) {
      std::operator<<(this->os, static_cast<const char *>("  "));
    }
    
  }
  
  
  private: 
  std::basic_ostream<char> & os;
  unsigned int hypotheses_count;
  public: 
  // inline TextExplainer<4> & operator=(const TextExplainer<4> &) /* noexcept */ = delete;
};

#endif
/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class TextExplainer<9>
{
  
  public: 
  inline explicit TextExplainer(std::basic_ostream<char> & os_)
  : os{os_}
  , hypotheses_count{static_cast<unsigned int>(0)}
  {
  }
  
  inline ~TextExplainer() noexcept
  {
    (static_cast<bool>(this->hypotheses_count == static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count == 0"), static_cast<const char *>("src/explanation/text-explainer.hpp"), static_cast<unsigned int>(19), static_cast<const char *>(__extension__"TextExplainer<9>::~TextExplainer() [size = 9]")));
  }
  
  
  public: 
  inline void operator()(const exploration::CellIsSetInInput<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%2%, %3%) is set to %1% in the input\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::InputsAreDone<9> &)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("All inputs have been set\n"));
  }
  
  inline void operator()(const exploration::PropagationStartsForSudoku<9> &)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("Propagation starts\n"));
  }
  
  inline void operator()(const exploration::PropagationStartsForCell<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagation starts for %1% in (%2%, %3%)\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::CellPropagates<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.source_cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.source_cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.target_cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.target_cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) can only be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("In region %4%, only (%1%, %2%) can be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.region + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::PropagationIsDoneForCell<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("%1% in (%2%, %3%) has been fully propagated\n"))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::PropagationIsDoneForSudoku<9> & event)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("All cells have been fully propagated\n"));
  }
  
  inline void operator()(const exploration::ExplorationStarts<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Exploration starts for (%1%, %2%) with %3% possible values\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned long>(event.allowed_values.size()))));
  }
  
  inline void operator()(const exploration::HypothesisIsMade<9> & event)
  {
    this->print_prefix();
    ++this->hypotheses_count;
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) may be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::HypothesisIsRejected<9> & event)
  {
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("src/explanation/text-explainer.hpp"), static_cast<unsigned int>(89), static_cast<const char *>(__extension__"void TextExplainer<9>::operator()(const exploration::HypothesisIsRejected<size> &) [size = 9]")));
    this->print_prefix();
    --this->hypotheses_count;
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::SudokuIsSolved<9> & event)
  {
    this->print_prefix();
    std::operator<<(this->os, static_cast<const char *>("Sudoku is solved\n"));
  }
  
  inline void operator()(const exploration::HypothesisIsAccepted<9> & event)
  {
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("src/explanation/text-explainer.hpp"), static_cast<unsigned int>(102), static_cast<const char *>(__extension__"void TextExplainer<9>::operator()(const exploration::HypothesisIsAccepted<size> &) [size = 9]")));
    this->print_prefix();
    --this->hypotheses_count;
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("(%1%, %2%) can indeed be %3%\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.value + static_cast<unsigned int>(1))))));
  }
  
  inline void operator()(const exploration::ExplorationIsDone<9> & event)
  {
    this->print_prefix();
    boost::operator<<(this->os, static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Exploration is done for (%1%, %2%)\n"))).operator%(static_cast<const unsigned int>((event.cell.first + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((event.cell.second + static_cast<unsigned int>(1))))));
  }
  
  
  private: 
  inline void print_prefix()
  {
    for(unsigned int i = static_cast<unsigned int>(0); i < this->hypotheses_count; ++i) {
      std::operator<<(this->os, static_cast<const char *>("  "));
    }
    
  }
  
  
  private: 
  std::basic_ostream<char> & os;
  unsigned int hypotheses_count;
  public: 
  // inline TextExplainer<9> & operator=(const TextExplainer<9> &) /* noexcept */ = delete;
};

#endif


#endif  // EXPLANATION_TEXT_EXPLAINER_HPP_
# 8 "src/main.cpp"
# 1 "src/explanation/video/frames-serializer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_

#include <filesystem>
#include <iomanip>
#include <string>

# 1 "src/explanation/video/serializer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_SERIALIZER_HPP_

#include <cairomm/surface.h>

#include <utility>
#include <vector>


namespace video
{
  struct Serializer
  {
    inline virtual constexpr ~Serializer() noexcept = default;
    virtual void serialize(std::shared_ptr<Cairo::ImageSurface>) = 0;
    
    // inline constexpr Serializer() noexcept = default;
  };
  
  struct MultipleSerializer : public Serializer
  {
    inline explicit MultipleSerializer(std::vector<Serializer *, std::allocator<Serializer *> > serializers_)
    : Serializer()
    , serializers{std::vector<Serializer *, std::allocator<Serializer *> >(std::move<std::vector<Serializer *, std::allocator<Serializer *> > &>(serializers_))}
    {
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      {
        std::vector<Serializer *, std::allocator<Serializer *> > & __range0 = this->serializers;
        __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > > __begin1 = __range0.begin();
        __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > > __end1 = __range0.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__end1)); __begin1.operator++()) {
          Serializer *& serializer = static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__begin1).operator*();
          serializer->serialize(std::shared_ptr<Cairo::ImageSurface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(surface)));
        }
        
      }
    }
    
    
    private: 
    std::vector<Serializer *, std::allocator<Serializer *> > serializers;
    public: 
    // inline virtual constexpr ~MultipleSerializer() noexcept = default;
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_SERIALIZER_HPP_
# 11 "src/explanation/video/frames-serializer.hpp"


namespace video
{
  struct FramesSerializer : public Serializer
  {
    inline explicit FramesSerializer(const std::filesystem::path & directory_path_)
    : Serializer()
    , frame_index{static_cast<unsigned int>(0)}
    , directory_path{std::filesystem::path(directory_path_)}
    {
      std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path &&>((operator/(static_cast<const std::filesystem::path>(this->directory_path), static_cast<const std::filesystem::path>(std::filesystem::path(this->next_frame_name(), std::filesystem::path::auto_format))))).string()));
    }
    
    inline std::basic_string<char, std::char_traits<char>, std::allocator<char> > next_frame_name()
    {
      std::basic_ostringstream<char> oss = std::basic_ostringstream<char>();
      std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(oss), std::setfill<char>('0')), std::setw(6)).operator<<(this->frame_index), static_cast<const char *>(".png"));
      ++this->frame_index;
      return static_cast<const std::basic_ostringstream<char>>(oss).str();
    }
    
    
    private: 
    unsigned int frame_index;
    std::filesystem::path directory_path;
    public: 
    // inline virtual ~FramesSerializer() noexcept = default;
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
# 9 "src/main.cpp"
# 1 "src/explanation/video-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_EXPLAINER_HPP_
#define EXPLANATION_VIDEO_EXPLAINER_HPP_

#include <cairomm/cairomm.h>

#include <filesystem>
#include <iomanip>
#include <ranges>  // NOLINT(build/include_order)
#include <string>
#include <tuple>
#include <vector>

# 16 "src/explanation/video-explainer.hpp"
# 17 "src/explanation/video-explainer.hpp"


// Like Cairo::SaveGuard
class CairoSaveGuard
{
  
  public: 
  inline explicit CairoSaveGuard(Cairo::Context & cr_)
  : cr{cr_}
  {
    this->cr.save();
  }
  
  inline ~CairoSaveGuard() noexcept
  {
    this->cr.restore();
  }
  
  
  private: 
  Cairo::Context & cr;
  public: 
};



template<unsigned int size>
class VideoExplainer
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  inline static constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  inline static constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  
  public: 
  inline VideoExplainer(video::Serializer * video_serializer_, const bool quick_, unsigned int frame_width_, unsigned int frame_height_)
  : before{}
  , after{}
  , frame_width_pixels{frame_width_}
  , frame_height_pixels{frame_height_}
  , viewport_height_pixels{this->frame_height_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , viewport_width_pixels{this->frame_width_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width_pixels), static_cast<int>(this->frame_height_pixels))}
  , context{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  , cr{static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->context).operator*()}
  , video_serializer{video_serializer_}
  , quick{quick_}
  {
  }
  
  
  private: 
  template<typename Event>
  class VisitEventsGuard
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<size> * explainer_, const Event & event)
    : explainer{*explainer_}
    , events{}
    , before{this->explainer.before}
    , after{this->explainer.after}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<size> * explainer_, const std::vector<Event> & events_)
    : explainer{*explainer_}
    , events{}
    , before{this->explainer.before}
    , after{this->explainer.after}
    {
      {
        auto && __range1 = events_;
        for(; ; ) {
          const auto & event;
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VisitEventsGuard<Event> &) = delete;
    // inline VisitEventsGuard<Event> & operator=(const VisitEventsGuard<Event> &) = delete;
    // inline VisitEventsGuard(VisitEventsGuard<Event> &&) = delete;
    // inline VisitEventsGuard<Event> & operator=(VisitEventsGuard<Event> &&) = delete;
    inline ~VisitEventsGuard()
    {
      {
        auto && __range1 = this->events;
        for(; ; ) {
          const auto & event;
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<size> & explainer;
    std::vector<Event> events;
    
    public: 
    const Stack<size> & before;
    const Stack<size> & after;
  };
  
  template<typename Event>
  VisitEventsGuard(VideoExplainer<size> *, const Event &) -> VisitEventsGuard<Event>;
  template<typename Event>
  VisitEventsGuard(VideoExplainer<size> *, const std::vector<Event> &) -> VisitEventsGuard<Event>;
  class FrameGuard
  {
    
    public: 
    inline explicit FrameGuard(VideoExplainer<size> * explainer_)
    : explainer{*explainer_}
    , cr{this->explainer.cr}
    {
      {
        CairoSaveGuard saver = CairoSaveGuard(this->cr);
        this->cr.set_source_rgb(1.0, 0.80000000000000004, 0.80000000000000004);
        this->cr.paint();
        this->cr.set_source_rgb(1.0, 1.0, 1.0);
        this->cr.rectangle(this->explainer.margin_pixels, this->explainer.margin_pixels, this->explainer.viewport_width_pixels, this->explainer.viewport_height_pixels);
        this->cr.fill();
      };
      this->cr.save();
      this->cr.translate(this->explainer.margin_pixels, this->explainer.margin_pixels);
    }
    
    // inline FrameGuard(const FrameGuard &) = delete;
    // inline FrameGuard & operator=(const FrameGuard &) = delete;
    // inline FrameGuard(FrameGuard &&) = delete;
    // inline FrameGuard & operator=(FrameGuard &&) = delete;
    inline ~FrameGuard()
    {
      this->cr.restore();
      CairoSaveGuard saver = CairoSaveGuard(this->cr);
      this->cr.rectangle(0, 0, this->explainer.frame_width_pixels, this->explainer.frame_height_pixels);
      this->cr.rectangle(this->explainer.margin_pixels, this->explainer.margin_pixels, this->explainer.viewport_width_pixels, this->explainer.viewport_height_pixels);
      this->cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      this->cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      this->cr.fill();
      this->explainer.video_serializer->serialize(this->explainer.surface);
    }
    
    
    private: 
    VideoExplainer<size> & explainer;
    Cairo::Context & cr;
  };
  
  struct Text
  {
    std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
    double font_size;
    enum 
    {
      Normal, 
      Bold
    };
    
    enum (unnamed) weight;
  };
  
  struct Layout
  {
    std::vector<Text> above = {};
    std::vector<Text> below = {};
  };
  
  
  private: 
  inline unsigned int quicken(unsigned int n)
  {
    if(this->quick) {
      return static_cast<unsigned int>(1);
    } else {
      return n;
    } 
    
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<size> &);
  
  void operator()(const exploration::InputsAreDone<size> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<size> &);
  
  void operator()(const exploration::PropagationStartsForCell<size> &);
  
  void operator()(const exploration::CellPropagates<size> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<size> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<size> &);
  
  void operator()(const exploration::ExplorationStarts<size> &);
  
  void operator()(const exploration::HypothesisIsMade<size> &);
  
  void operator()(const exploration::HypothesisIsRejected<size> &);
  
  void operator()(const exploration::SudokuIsSolved<size> &);
  
  void operator()(const exploration::HypothesisIsAccepted<size> &);
  
  void operator()(const exploration::ExplorationIsDone<size> &);
  
  void flush_pending_cell_propagates_events();
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events();
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  
  void flush_pending_events();
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double above_height = static_cast<double>(0);
    {
      auto && __range0 = layout.above;
      for(; ; ) {
        const auto & text;
        this->cr.set_font_size(text.font_size);
        switch(text.weight) {
          case Text::Normal: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case Text::Bold: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        this->cr.get_text_extents(text.text, extents);
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, above_height - extents.y_bearing);
        this->cr.show_text(text.text);
        above_height = above_height + extents.height;
      }
      
    }
    double below_height = static_cast<double>(0);
    {
      auto && __range0 = layout.below | std::ranges::views::reverse;
      for(; ; ) {
        const auto & text;
        this->cr.set_font_size(text.font_size);
        switch(text.weight) {
          case Text::Normal: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case Text::Bold: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        this->cr.get_text_extents(text.text, extents);
        below_height = below_height + extents.height;
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, (static_cast<double>(this->viewport_height_pixels) - below_height) - extents.y_bearing);
        this->cr.show_text(text.text);
      }
      
    }
    const unsigned int available_height = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height) - below_height);
    const unsigned int grid_size = (((available_height - thick_line_width) / size) * size) + thick_line_width;
    const unsigned int grid_x = (this->viewport_width_pixels - grid_size) / static_cast<unsigned int>(2);
    const unsigned int grid_y = static_cast<const unsigned int>(above_height + (static_cast<double>((available_height - grid_size) / static_cast<unsigned int>(2))));
    return std::tuple<double, double, double>(std::make_tuple<const unsigned int &, const unsigned int &, const unsigned int &>(grid_x, grid_y, grid_size));
  }
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    const double above_height_before = this->compute_text_height(before.above);
    const double below_height_before = this->compute_text_height(before.below);
    const unsigned int available_height_before = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_before) - below_height_before);
    const unsigned int grid_size_before = (((available_height_before - thick_line_width) / size) * size) + thick_line_width;
    const double grid_x_before = static_cast<const double>((this->viewport_width_pixels - grid_size_before) / static_cast<unsigned int>(2));
    const double grid_y_before = above_height_before + (static_cast<double>((available_height_before - grid_size_before) / static_cast<unsigned int>(2)));
    const double above_height_after = this->compute_text_height(after.above);
    const double below_height_after = this->compute_text_height(after.below);
    const unsigned int available_height_after = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_after) - below_height_after);
    const unsigned int grid_size_after = (((available_height_after - thick_line_width) / size) * size) + thick_line_width;
    const double grid_x_after = static_cast<const double>((this->viewport_width_pixels - grid_size_after) / static_cast<unsigned int>(2));
    const double grid_y_after = above_height_after + (static_cast<double>((available_height_after - grid_size_after) / static_cast<unsigned int>(2)));
    const double grid_size = static_cast<double>(grid_size_before) + (ratio * static_cast<double>((grid_size_after - grid_size_before)));
    const double grid_x = grid_x_before + (ratio * (grid_x_after - grid_x_before));
    const double grid_y = grid_y_before + (ratio * (grid_y_after - grid_y_before));
    return std::make_tuple<const double &, const double &, const double &>(grid_x, grid_y, grid_size);
  }
  
  inline double compute_text_height(const std::vector<Text> & texts) const
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double height = static_cast<double>(0);
    {
      auto && __range0 = texts;
      for(; ; ) {
        const auto & text;
        this->cr.set_font_size(text.font_size);
        switch(text.weight) {
          case Text::Normal: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case Text::Bold: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        this->cr.get_text_extents(text.text, extents);
        height = height + extents.height;
      }
      
    }
    return height;
  }
  
  
  private: 
  Stack<size> before;
  Stack<size> after;
  unsigned int frame_width_pixels;
  unsigned int frame_height_pixels;
  unsigned int viewport_height_pixels;
  unsigned int viewport_width_pixels;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> context;
  Cairo::Context & cr;
  video::Serializer * video_serializer;
  const bool quick;
  
  private: 
  unsigned int single_propagations_handled;
  unsigned int cell_propagations_handled;
  unsigned int deductions_handled;
  std::vector<exploration::CellPropagates<size> > pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size> > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};

/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class VideoExplainer<4>
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  static constexpr const unsigned int thick_line_width;
  static constexpr const unsigned int thin_line_width;
  
  public: 
  inline VideoExplainer(video::Serializer * video_serializer_, const bool quick_, unsigned int frame_width_, unsigned int frame_height_)
  : before{Stack<4>()}
  , after{Stack<4>()}
  , frame_width_pixels{frame_width_}
  , frame_height_pixels{frame_height_}
  , viewport_height_pixels{this->frame_height_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , viewport_width_pixels{this->frame_width_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width_pixels), static_cast<int>(this->frame_height_pixels))}
  , context{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  , cr{static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->context).operator*()}
  , video_serializer{video_serializer_}
  , quick{quick_}
  , single_propagations_handled{static_cast<unsigned int>(0)}
  , cell_propagations_handled{static_cast<unsigned int>(0)}
  , deductions_handled{static_cast<unsigned int>(0)}
  , pending_cell_propagates_events{std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >()}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >()}
  {
  }
  
  
  private: 
  template<typename Event>
  class VisitEventsGuard;
  public: 
  private: 
  template<typename Event>
  VisitEventsGuard(VideoExplainer<4> *, const Event &) -> VisitEventsGuard<Event>;
  template<typename Event>
  VisitEventsGuard(VideoExplainer<4> *, const std::vector<Event> &) -> VisitEventsGuard<Event>;
  class FrameGuard;
  struct Text;
  struct Layout;
  
  private: 
  inline unsigned int quicken(unsigned int n);
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<4> &);
  
  void operator()(const exploration::InputsAreDone<4> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<4> &);
  
  void operator()(const exploration::PropagationStartsForCell<4> &);
  
  void operator()(const exploration::CellPropagates<4> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<4> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<4> &);
  
  void operator()(const exploration::ExplorationStarts<4> &);
  
  void operator()(const exploration::HypothesisIsMade<4> &);
  
  void operator()(const exploration::HypothesisIsRejected<4> &);
  
  void operator()(const exploration::SudokuIsSolved<4> &);
  
  void operator()(const exploration::HypothesisIsAccepted<4> &);
  
  void operator()(const exploration::ExplorationIsDone<4> &);
  
  void flush_pending_cell_propagates_events();
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events();
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  
  void flush_pending_events();
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout);
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio);
  
  inline double compute_text_height(const std::vector<Text, std::allocator<Text> > & texts) const;
  
  
  private: 
  Stack<4> before;
  Stack<4> after;
  unsigned int frame_width_pixels;
  unsigned int frame_height_pixels;
  unsigned int viewport_height_pixels;
  unsigned int viewport_width_pixels;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> context;
  Cairo::Context & cr;
  video::Serializer * video_serializer;
  const bool quick;
  
  private: 
  unsigned int single_propagations_handled;
  unsigned int cell_propagations_handled;
  unsigned int deductions_handled;
  std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline VideoExplainer<4> & operator=(const VideoExplainer<4> &) /* noexcept */ = delete;
  // inline VideoExplainer<4> & operator=(VideoExplainer<4> &&) /* noexcept */ = delete;
  // inline ~VideoExplainer() noexcept = default;
};

#endif
/* First instantiated from: type_traits:1274 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class VideoExplainer<9>
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  static constexpr const unsigned int thick_line_width;
  static constexpr const unsigned int thin_line_width;
  
  public: 
  inline VideoExplainer(video::Serializer * video_serializer_, const bool quick_, unsigned int frame_width_, unsigned int frame_height_)
  : before{Stack<9>()}
  , after{Stack<9>()}
  , frame_width_pixels{frame_width_}
  , frame_height_pixels{frame_height_}
  , viewport_height_pixels{this->frame_height_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , viewport_width_pixels{this->frame_width_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width_pixels), static_cast<int>(this->frame_height_pixels))}
  , context{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  , cr{static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->context).operator*()}
  , video_serializer{video_serializer_}
  , quick{quick_}
  , single_propagations_handled{static_cast<unsigned int>(0)}
  , cell_propagations_handled{static_cast<unsigned int>(0)}
  , deductions_handled{static_cast<unsigned int>(0)}
  , pending_cell_propagates_events{std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >()}
  , pending_cell_is_deduced_from_single_allowed_value_events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >()}
  , pending_cell_is_deduced_as_single_place_for_value_in_region_events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >()}
  {
  }
  
  
  private: 
  template<typename Event>
  class VisitEventsGuard;
  public: 
  private: 
  template<typename Event>
  VisitEventsGuard(VideoExplainer<9> *, const Event &) -> VisitEventsGuard<Event>;
  template<typename Event>
  VisitEventsGuard(VideoExplainer<9> *, const std::vector<Event> &) -> VisitEventsGuard<Event>;
  class FrameGuard;
  struct Text;
  struct Layout;
  
  private: 
  inline unsigned int quicken(unsigned int n);
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<9> &);
  
  void operator()(const exploration::InputsAreDone<9> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<9> &);
  
  void operator()(const exploration::PropagationStartsForCell<9> &);
  
  void operator()(const exploration::CellPropagates<9> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<9> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<9> &);
  
  void operator()(const exploration::ExplorationStarts<9> &);
  
  void operator()(const exploration::HypothesisIsMade<9> &);
  
  void operator()(const exploration::HypothesisIsRejected<9> &);
  
  void operator()(const exploration::SudokuIsSolved<9> &);
  
  void operator()(const exploration::HypothesisIsAccepted<9> &);
  
  void operator()(const exploration::ExplorationIsDone<9> &);
  
  void flush_pending_cell_propagates_events();
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events();
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  
  void flush_pending_events();
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout);
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio);
  
  inline double compute_text_height(const std::vector<Text, std::allocator<Text> > & texts) const;
  
  
  private: 
  Stack<9> before;
  Stack<9> after;
  unsigned int frame_width_pixels;
  unsigned int frame_height_pixels;
  unsigned int viewport_height_pixels;
  unsigned int viewport_width_pixels;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> context;
  Cairo::Context & cr;
  video::Serializer * video_serializer;
  const bool quick;
  
  private: 
  unsigned int single_propagations_handled;
  unsigned int cell_propagations_handled;
  unsigned int deductions_handled;
  std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
  public: 
  // inline VideoExplainer<9> & operator=(const VideoExplainer<9> &) /* noexcept */ = delete;
  // inline VideoExplainer<9> & operator=(VideoExplainer<9> &&) /* noexcept */ = delete;
  // inline ~VideoExplainer() noexcept = default;
};

#endif


#endif  // EXPLANATION_VIDEO_EXPLAINER_HPP_
# 10 "src/main.cpp"
# 1 "src/explanation/video/video-serializer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_

extern "C" {

#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>

}  // extern "C"

#include <cassert>
#include <filesystem>
#include <memory>

# 19 "src/explanation/video/video-serializer.hpp"


namespace video
{
  struct VideoSerializer : public Serializer
  {
    inline explicit VideoSerializer(const std::filesystem::path & video_path_, unsigned int frame_width_, unsigned int frame_height_)
    : Serializer()
    , frame_index{static_cast<unsigned int>(0)}
    , video_path{std::filesystem::path(video_path_)}
    , frame_width_pixels{frame_width_}
    , frame_height_pixels{frame_height_}
    , codec{avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO)}
    , context{avcodec_alloc_context3(this->codec)}
    , picture{av_frame_alloc()}
    , pkt{av_packet_alloc()}
    , outfile{fopen(static_cast<const std::filesystem::path>(this->video_path).c_str(), static_cast<const char *>("wb"))}
    {
      (static_cast<bool>(this->codec) ? void(0) : __assert_fail(static_cast<const char *>("codec"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(39), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, unsigned int, unsigned int)")));
      (static_cast<bool>(this->pkt) ? void(0) : __assert_fail(static_cast<const char *>("pkt"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(40), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, unsigned int, unsigned int)")));
      (static_cast<bool>(this->outfile) ? void(0) : __assert_fail(static_cast<const char *>("outfile"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(41), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, unsigned int, unsigned int)")));
      this->context->bit_rate = static_cast<long>(400000);
      this->context->width = static_cast<int>(this->frame_width_pixels);
      this->context->height = static_cast<int>(this->frame_height_pixels);
      this->context->time_base.operator=(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CompoundLiteralExpr */);
      this->context->framerate.operator=(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CompoundLiteralExpr */);
      this->context->gop_size = 10;
      this->context->max_b_frames = 1;
      this->context->pix_fmt = AV_PIX_FMT_YUV420P;
      int ret = avcodec_open2(this->context, this->codec, static_cast<AVDictionary **>(NULL));
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(53), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, unsigned int, unsigned int)")));
      this->picture->format = static_cast<int>(this->context->pix_fmt);
      this->picture->width = static_cast<int>(this->frame_width_pixels);
      this->picture->height = static_cast<int>(this->frame_height_pixels);
      ret = av_frame_get_buffer(this->picture, 32);
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(60), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, unsigned int, unsigned int)")));
    }
    
    inline virtual ~VideoSerializer() noexcept
    {
      this->encode(static_cast<AVFrame *>(nullptr));
      uint8_t endcode[4] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(1), static_cast<unsigned char>(183)};
      fwrite(reinterpret_cast<const void *>(static_cast<unsigned char *>(endcode)), static_cast<unsigned long>(1), sizeof(endcode), this->outfile);
      fclose(this->outfile);
      avcodec_free_context(&this->context);
      av_frame_free(&this->picture);
      av_packet_free(&this->pkt);
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      int ret = av_frame_make_writable(this->picture);
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(77), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<unsigned int>(static_cast<const Cairo::ImageSurface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->get_width()) == this->frame_width_pixels) ? void(0) : __assert_fail(static_cast<const char *>("surface->get_width() == frame_width_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<unsigned int>(static_cast<const Cairo::ImageSurface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->get_height()) == this->frame_height_pixels) ? void(0) : __assert_fail(static_cast<const char *>("surface->get_height() == frame_height_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(80), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      unsigned char * data = static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->()->get_data();
      (static_cast<bool>(data) ? void(0) : __assert_fail(static_cast<const char *>("data"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(82), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<unsigned int>(static_cast<int *>(this->picture->linesize)[0]) == this->frame_width_pixels) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[0] == frame_width_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(84), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<unsigned int>(static_cast<int *>(this->picture->linesize)[1]) == (this->frame_width_pixels / static_cast<unsigned int>(2))) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[1] == frame_width_pixels / 2"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(85), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<unsigned int>(static_cast<int *>(this->picture->linesize)[2]) == (this->frame_width_pixels / static_cast<unsigned int>(2))) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[2] == frame_width_pixels / 2"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(86), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      for(int y = 0; static_cast<unsigned int>(y) < this->frame_height_pixels; ++y) {
        for(int x = 0; static_cast<unsigned int>(x) < this->frame_width_pixels; ++x) {
          static_cast<unsigned char **>(this->picture->data)[0][(y * static_cast<int *>(this->picture->linesize)[0]) + x] = (static_cast<unsigned char>(((static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>(y) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>(x * 4))) + static_cast<unsigned int>(0)])) * 0.29899999999999999) + (static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>(y) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>(x * 4))) + static_cast<unsigned int>(1)])) * 0.58699999999999997)) + (static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>(y) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>(x * 4))) + static_cast<unsigned int>(2)])) * 0.114)));
        }
        
      }
      
      for(int y = 0; static_cast<unsigned int>(y) < (this->frame_height_pixels / static_cast<unsigned int>(2)); ++y) {
        for(int x = 0; static_cast<unsigned int>(x) < (this->frame_width_pixels / static_cast<unsigned int>(2)); ++x) {
          static_cast<unsigned char **>(this->picture->data)[1][(y * static_cast<int *>(this->picture->linesize)[1]) + x] = (static_cast<unsigned char>((((static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>((y * 2)) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>((x * 2) * 4))) + static_cast<unsigned int>(0)])) * -0.16900000000000001) + (static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>((y * 2)) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>((x * 2) * 4))) + static_cast<unsigned int>(1)])) * -0.33100000000000002)) + (static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>((y * 2)) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>((x * 2) * 4))) + static_cast<unsigned int>(2)])) * 0.5)) + static_cast<double>(128)));
          static_cast<unsigned char **>(this->picture->data)[2][(y * static_cast<int *>(this->picture->linesize)[2]) + x] = (static_cast<unsigned char>((((static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>((y * 2)) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>((x * 2) * 4))) + static_cast<unsigned int>(0)])) * 0.5) + (static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>((y * 2)) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>((x * 2) * 4))) + static_cast<unsigned int>(1)])) * -0.41899999999999998)) + (static_cast<double>(static_cast<int>(data[(((static_cast<unsigned int>((y * 2)) * this->frame_width_pixels) * static_cast<unsigned int>(4)) + (static_cast<unsigned int>((x * 2) * 4))) + static_cast<unsigned int>(2)])) * -0.081000000000000003)) + static_cast<double>(128)));
        }
        
      }
      
      this->picture->pts = static_cast<long>(this->frame_index);
      this->encode(this->picture);
      ++this->frame_index;
    }
    
    
    private: 
    inline void encode(AVFrame * picture)
    {
      int ret = avcodec_send_frame(this->context, static_cast<const AVFrame *>(picture));
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(131), static_cast<const char *>(__extension__"void video::VideoSerializer::encode(AVFrame *)")));
      while(ret >= 0) {
        ret = avcodec_receive_packet(this->context, this->pkt);
        if((ret == (-(11))) || (ret == (-static_cast<int>(((static_cast<unsigned int>((static_cast<int>(('E')) | (static_cast<int>(('O')) << 8)) | (static_cast<int>(('F')) << 16))) | (static_cast<unsigned int>((' ')) << 24)))))) {
          return;
        } 
        
        (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(138), static_cast<const char *>(__extension__"void video::VideoSerializer::encode(AVFrame *)")));
        fwrite(reinterpret_cast<const void *>(this->pkt->data), static_cast<unsigned long>(1), static_cast<unsigned long>(this->pkt->size), this->outfile);
        av_packet_unref(this->pkt);
      }
      
    }
    
    
    private: 
    unsigned int frame_index;
    std::filesystem::path video_path;
    unsigned int frame_width_pixels;
    unsigned int frame_height_pixels;
    const AVCodec * codec;
    AVCodecContext * context;
    AVFrame * picture;
    AVPacket * pkt;
    FILE * outfile;
    public: 
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
# 11 "src/main.cpp"
# 1 "src/exploration/sudoku-solver.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_SUDOKU_SOLVER_HPP_
#define EXPLORATION_SUDOKU_SOLVER_HPP_

#include <deque>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

# 13 "src/exploration/sudoku-solver.hpp"
# 14 "src/exploration/sudoku-solver.hpp"


// This is the only way to modify the Stack (everywhere else, it's manipulated through const references).
// This design ensures that the events returned to the client can replicate exactly the evolution of the
// stack that happened during the exploration, because the stack actually evolved only through said events.
// (I think this is brilliant, but I *may* biased as I'm the author of this code).
template<unsigned int size, typename AddEvent>
struct EventAdder
{
  inline EventAdder(Stack<size> * stack_, const AddEvent & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  template<typename Event>
  inline void operator()(const Event & event) const
  {
    event.apply(this->stack);
    this->add_event(event);
  }
  
  private: 
  Stack<size> * stack;
  const AddEvent & add_event;
};

/* First instantiated from: main.cpp:1798 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<4, __lambda_5>
{
  inline EventAdder(Stack<4> * stack_, const __lambda_5 & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  template<typename Event>
  inline void operator()(const Event & event) const;
  
  /* First instantiated from: main.cpp:1804 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1809 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1658 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1663 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1683 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1695 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1763 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1766 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  private: 
  Stack<4> * stack;
  const __lambda_5 & add_event;
  public: 
};

#endif
/* First instantiated from: main.cpp:1798 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<4, __lambda_6>
{
  inline EventAdder(Stack<4> * stack_, const __lambda_6 & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  template<typename Event>
  inline void operator()(const Event & event) const;
  
  /* First instantiated from: main.cpp:1804 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1809 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1658 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1663 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1683 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1695 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1763 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1766 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  private: 
  Stack<4> * stack;
  const __lambda_6 & add_event;
  public: 
};

#endif
/* First instantiated from: main.cpp:1798 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<9, __lambda_5>
{
  inline EventAdder(Stack<9> * stack_, const __lambda_5 & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  template<typename Event>
  inline void operator()(const Event & event) const;
  
  /* First instantiated from: main.cpp:1804 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1809 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1658 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1663 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1683 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1695 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1763 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1766 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  private: 
  Stack<9> * stack;
  const __lambda_5 & add_event;
  public: 
};

#endif
/* First instantiated from: main.cpp:1798 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<9, __lambda_6>
{
  inline EventAdder(Stack<9> * stack_, const __lambda_6 & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  template<typename Event>
  inline void operator()(const Event & event) const;
  
  /* First instantiated from: main.cpp:1804 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1809 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1658 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1663 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1683 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1695 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1763 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1766 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main.cpp:1611 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  private: 
  Stack<9> * stack;
  const __lambda_6 & add_event;
  public: 
};

#endif



// Make sure a closing event is added, however the scope is exited
template<unsigned int size, typename AddEvent, typename EventIn, typename EventOut>
struct EventsPairGuard
{
  inline EventsPairGuard(const EventAdder<size, AddEvent> & add_event_, const EventIn & in, const EventOut & out_)
  : add_event{add_event_}
  , out{out_}
  {
    this->add_event(in);
  }
  
  inline ~EventsPairGuard()
  {
    this->add_event(this->out);
  }
  
  const EventAdder<size, AddEvent> & add_event;
  EventOut out;
};

/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >
{
  inline EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::PropagationStartsForSudoku<4> & in, const exploration::PropagationIsDoneForSudoku<4> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForSudoku<4>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForSudoku<4>>(this->out));
  }
  
  const EventAdder<4, __lambda_5> & add_event;
  exploration::PropagationIsDoneForSudoku<4> out;
};

#endif
/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >
{
  inline EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::PropagationStartsForSudoku<4> & in, const exploration::PropagationIsDoneForSudoku<4> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForSudoku<4>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForSudoku<4>>(this->out));
  }
  
  const EventAdder<4, __lambda_6> & add_event;
  exploration::PropagationIsDoneForSudoku<4> out;
};

#endif
/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> >
{
  inline EventsPairGuard(const EventAdder<9, __lambda_5> & add_event_, const exploration::PropagationStartsForSudoku<9> & in, const exploration::PropagationIsDoneForSudoku<9> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForSudoku<9>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForSudoku<9>>(this->out));
  }
  
  const EventAdder<9, __lambda_5> & add_event;
  exploration::PropagationIsDoneForSudoku<9> out;
};

#endif
/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> >
{
  inline EventsPairGuard(const EventAdder<9, __lambda_6> & add_event_, const exploration::PropagationStartsForSudoku<9> & in, const exploration::PropagationIsDoneForSudoku<9> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForSudoku<9>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForSudoku<9>>(this->out));
  }
  
  const EventAdder<9, __lambda_6> & add_event;
  exploration::PropagationIsDoneForSudoku<9> out;
};

#endif
/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >
{
  inline EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::PropagationStartsForCell<4> & in, const exploration::PropagationIsDoneForCell<4> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForCell<4>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForCell<4>>(this->out));
  }
  
  const EventAdder<4, __lambda_5> & add_event;
  exploration::PropagationIsDoneForCell<4> out;
};

#endif
/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >
{
  inline EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::PropagationStartsForCell<4> & in, const exploration::PropagationIsDoneForCell<4> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForCell<4>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForCell<4>>(this->out));
  }
  
  const EventAdder<4, __lambda_6> & add_event;
  exploration::PropagationIsDoneForCell<4> out;
};

#endif
/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> >
{
  inline EventsPairGuard(const EventAdder<9, __lambda_5> & add_event_, const exploration::PropagationStartsForCell<9> & in, const exploration::PropagationIsDoneForCell<9> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForCell<9>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForCell<9>>(this->out));
  }
  
  const EventAdder<9, __lambda_5> & add_event;
  exploration::PropagationIsDoneForCell<9> out;
};

#endif
/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> >
{
  inline EventsPairGuard(const EventAdder<9, __lambda_6> & add_event_, const exploration::PropagationStartsForCell<9> & in, const exploration::PropagationIsDoneForCell<9> & out_)
  : add_event{add_event_}
  , out{exploration::PropagationIsDoneForCell<9>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::PropagationIsDoneForCell<9>>(this->out));
  }
  
  const EventAdder<9, __lambda_6> & add_event;
  exploration::PropagationIsDoneForCell<9> out;
};

#endif
/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4, __lambda_5, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >
{
  inline EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::ExplorationStarts<4> & in, const exploration::ExplorationIsDone<4> & out_)
  : add_event{add_event_}
  , out{exploration::ExplorationIsDone<4>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::ExplorationIsDone<4>>(this->out));
  }
  
  const EventAdder<4, __lambda_5> & add_event;
  exploration::ExplorationIsDone<4> out;
};

#endif
/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4, __lambda_6, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >
{
  inline EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::ExplorationStarts<4> & in, const exploration::ExplorationIsDone<4> & out_)
  : add_event{add_event_}
  , out{exploration::ExplorationIsDone<4>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::ExplorationIsDone<4>>(this->out));
  }
  
  const EventAdder<4, __lambda_6> & add_event;
  exploration::ExplorationIsDone<4> out;
};

#endif
/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9, __lambda_5, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> >
{
  inline EventsPairGuard(const EventAdder<9, __lambda_5> & add_event_, const exploration::ExplorationStarts<9> & in, const exploration::ExplorationIsDone<9> & out_)
  : add_event{add_event_}
  , out{exploration::ExplorationIsDone<9>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::ExplorationIsDone<9>>(this->out));
  }
  
  const EventAdder<9, __lambda_5> & add_event;
  exploration::ExplorationIsDone<9> out;
};

#endif
/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9, __lambda_6, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> >
{
  inline EventsPairGuard(const EventAdder<9, __lambda_6> & add_event_, const exploration::ExplorationStarts<9> & in, const exploration::ExplorationIsDone<9> & out_)
  : add_event{add_event_}
  , out{exploration::ExplorationIsDone<9>(out_)}
  {
    this->add_event.operator()(in);
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(static_cast<const exploration::ExplorationIsDone<9>>(this->out));
  }
  
  const EventAdder<9, __lambda_6> & add_event;
  exploration::ExplorationIsDone<9> out;
};

#endif



/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::PropagationStartsForSudoku<4> & in, const exploration::PropagationIsDoneForSudoku<4> & out_) -> EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >;
#endif


/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::PropagationStartsForCell<4> & in, const exploration::PropagationIsDoneForCell<4> & out_) -> EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >;
#endif


/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::ExplorationStarts<4> & in, const exploration::ExplorationIsDone<4> & out_) -> EventsPairGuard<4, __lambda_5, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >;
#endif


/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::PropagationStartsForSudoku<4> & in, const exploration::PropagationIsDoneForSudoku<4> & out_) -> EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >;
#endif


/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::PropagationStartsForCell<4> & in, const exploration::PropagationIsDoneForCell<4> & out_) -> EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >;
#endif


/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::ExplorationStarts<4> & in, const exploration::ExplorationIsDone<4> & out_) -> EventsPairGuard<4, __lambda_6, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >;
#endif


/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<9, __lambda_5> & add_event_, const exploration::PropagationStartsForSudoku<9> & in, const exploration::PropagationIsDoneForSudoku<9> & out_) -> EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> >;
#endif


/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<9, __lambda_5> & add_event_, const exploration::PropagationStartsForCell<9> & in, const exploration::PropagationIsDoneForCell<9> & out_) -> EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> >;
#endif


/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<9, __lambda_5> & add_event_, const exploration::ExplorationStarts<9> & in, const exploration::ExplorationIsDone<9> & out_) -> EventsPairGuard<9, __lambda_5, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> >;
#endif


/* First instantiated from: main.cpp:1629 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<9, __lambda_6> & add_event_, const exploration::PropagationStartsForSudoku<9> & in, const exploration::PropagationIsDoneForSudoku<9> & out_) -> EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> >;
#endif


/* First instantiated from: main.cpp:1641 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<9, __lambda_6> & add_event_, const exploration::PropagationStartsForCell<9> & in, const exploration::PropagationIsDoneForCell<9> & out_) -> EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> >;
#endif


/* First instantiated from: main.cpp:1754 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<9, __lambda_6> & add_event_, const exploration::ExplorationStarts<9> & in, const exploration::ExplorationIsDone<9> & out_) -> EventsPairGuard<9, __lambda_6, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> >;
#endif


template<unsigned int size, typename AddEvent>
bool propagate(const Stack<size> & stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo, const EventAdder<size, AddEvent> & add_event)
{
  {
    std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo;
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __begin2 = __range2.begin();
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __end2 = __range2.end();
    for(; !operator==(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2), static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__end2)); __begin2.operator++()) {
      const std::pair<unsigned int, unsigned int> & coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2).operator*());
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail("std::count(todo.begin(), todo.end(), coords) == 1", "src/exploration/sudoku-solver.hpp", 67, __extension____PRETTY_FUNCTION__));
    }
    
  }
  EventsPairGuard guard = add_event, exploration::PropagationStartsForSudoku<size>(), exploration::PropagationIsDoneForSudoku<size>();
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const auto & source_cell = stack.current().cell(source_coords);
    (static_cast<bool>(source_cell.is_set()) ? void(0) : __assert_fail("source_cell.is_set()", "src/exploration/sudoku-solver.hpp", 79, __extension____PRETTY_FUNCTION__));
    const unsigned int value = source_cell.get();
    EventsPairGuard guard = add_event, exploration::PropagationStartsForCell<size>(source_coords, value), exploration::PropagationIsDoneForCell<size>(source_coords, value);
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
                (static_cast<bool>(target_cell.allowed_count() > 1) ? void(0) : __assert_fail("target_cell.allowed_count() > 1", "src/exploration/sudoku-solver.hpp", 97, __extension____PRETTY_FUNCTION__));
                if(target_cell.is_allowed(value)) {
                  add_event(exploration::CellPropagates<size>(source_coords, target_coords, value));
                  if(target_cell.allowed_count() == 1) {
                    {
                      auto && __range3 = SudokuConstants<size>::values;
                      for(; ; ) {
                        unsigned int value;
                        if(target_cell.is_allowed(value)) {
                          add_event(exploration::CellIsDeducedFromSingleAllowedValue<size>(target_coords, value));
                          (static_cast<bool>(std::count(todo.begin(), todo.end(), target_coords) == 0) ? void(0) : __assert_fail("std::count(todo.begin(), todo.end(), target_coords) == 0", "src/exploration/sudoku-solver.hpp", 106, __extension____PRETTY_FUNCTION__));
                          push_back(target_coords);
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
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail("std::count(todo.begin(), todo.end(), single_coords) == 0", "src/exploration/sudoku-solver.hpp", 126, __extension____PRETTY_FUNCTION__));
                        todo.push_back(single_coords);
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


/* First instantiated from: main.cpp:1780 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<4, __lambda_5>(const Stack<4> & stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo, const EventAdder<4, __lambda_5> & add_event)
{
  {
    std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo;
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __begin2 = __range2.begin();
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __end2 = __range2.end();
    for(; !operator==(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2), static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__end2)); __begin2.operator++()) {
      const std::pair<unsigned int, unsigned int> & coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2).operator*());
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), coords) == 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(67), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
    }
    
  }
  EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> > guard = EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >(add_event, static_cast<const exploration::PropagationStartsForSudoku<4>>(exploration::PropagationStartsForSudoku<4>()), static_cast<const exploration::PropagationIsDoneForSudoku<4>>(exploration::PropagationIsDoneForSudoku<4>()));
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
    const unsigned int value = static_cast<const AnnotatedCell<4>&>(source_cell).get();
    EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> > guard = EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >(add_event, static_cast<const exploration::PropagationStartsForCell<4>>(exploration::PropagationStartsForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::PropagationIsDoneForCell<4>>(exploration::PropagationIsDoneForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
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
                (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(97), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
                if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(static_cast<const exploration::CellPropagates<4>>(exploration::CellPropagates<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
                      const unsigned int * __begin0 = __range3.begin();
                      const unsigned int * __end0 = __range3.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(exploration::CellIsDeducedFromSingleAllowedValue<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), target_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), target_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(106), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
                          todo.push_back(target_coords);
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
                        add_event.operator()(static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), single_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(static_cast<const exploration::SudokuIsSolved<4>>(exploration::SudokuIsSolved<4>()));
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


/* First instantiated from: main.cpp:1780 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<4, __lambda_6>(const Stack<4> & stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo, const EventAdder<4, __lambda_6> & add_event)
{
  {
    std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo;
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __begin2 = __range2.begin();
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __end2 = __range2.end();
    for(; !operator==(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2), static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__end2)); __begin2.operator++()) {
      const std::pair<unsigned int, unsigned int> & coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2).operator*());
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), coords) == 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(67), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.cpp:135:7)]")));
    }
    
  }
  EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> > guard = EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >(add_event, static_cast<const exploration::PropagationStartsForSudoku<4>>(exploration::PropagationStartsForSudoku<4>()), static_cast<const exploration::PropagationIsDoneForSudoku<4>>(exploration::PropagationIsDoneForSudoku<4>()));
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.cpp:135:7)]")));
    const unsigned int value = static_cast<const AnnotatedCell<4>&>(source_cell).get();
    EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> > guard = EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >(add_event, static_cast<const exploration::PropagationStartsForCell<4>>(exploration::PropagationStartsForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::PropagationIsDoneForCell<4>>(exploration::PropagationIsDoneForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
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
                (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(97), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.cpp:135:7)]")));
                if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(static_cast<const exploration::CellPropagates<4>>(exploration::CellPropagates<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
                      const unsigned int * __begin0 = __range3.begin();
                      const unsigned int * __end0 = __range3.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(exploration::CellIsDeducedFromSingleAllowedValue<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), target_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), target_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(106), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.cpp:135:7)]")));
                          todo.push_back(target_coords);
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
                        add_event.operator()(static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), single_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.cpp:135:7)]")));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(static_cast<const exploration::SudokuIsSolved<4>>(exploration::SudokuIsSolved<4>()));
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


/* First instantiated from: main.cpp:1780 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<9, __lambda_5>(const Stack<9> & stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo, const EventAdder<9, __lambda_5> & add_event)
{
  {
    std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo;
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __begin2 = __range2.begin();
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __end2 = __range2.end();
    for(; !operator==(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2), static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__end2)); __begin2.operator++()) {
      const std::pair<unsigned int, unsigned int> & coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2).operator*());
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), coords) == 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(67), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
    }
    
  }
  EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> > guard = EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> >(add_event, static_cast<const exploration::PropagationStartsForSudoku<9>>(exploration::PropagationStartsForSudoku<9>()), static_cast<const exploration::PropagationIsDoneForSudoku<9>>(exploration::PropagationIsDoneForSudoku<9>()));
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
    const unsigned int value = static_cast<const AnnotatedCell<9>&>(source_cell).get();
    EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> > guard = EventsPairGuard<9, __lambda_5, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> >(add_event, static_cast<const exploration::PropagationStartsForCell<9>>(exploration::PropagationStartsForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::PropagationIsDoneForCell<9>>(exploration::PropagationIsDoneForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
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
                (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(97), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
                if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(static_cast<const exploration::CellPropagates<9>>(exploration::CellPropagates<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
                      const unsigned int * __begin0 = __range3.begin();
                      const unsigned int * __end0 = __range3.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(exploration::CellIsDeducedFromSingleAllowedValue<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), target_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), target_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(106), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
                          todo.push_back(target_coords);
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
                        add_event.operator()(static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), single_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(static_cast<const exploration::SudokuIsSolved<9>>(exploration::SudokuIsSolved<9>()));
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


/* First instantiated from: main.cpp:1780 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<9, __lambda_6>(const Stack<9> & stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo, const EventAdder<9, __lambda_6> & add_event)
{
  {
    std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = todo;
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __begin2 = __range2.begin();
    std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *> __end2 = __range2.end();
    for(; !operator==(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2), static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__end2)); __begin2.operator++()) {
      const std::pair<unsigned int, unsigned int> & coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>>(__begin2).operator*());
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), coords) == 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(67), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/main.cpp:135:7)]")));
    }
    
  }
  EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> > guard = EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForSudoku<9>, exploration::PropagationIsDoneForSudoku<9> >(add_event, static_cast<const exploration::PropagationStartsForSudoku<9>>(exploration::PropagationStartsForSudoku<9>()), static_cast<const exploration::PropagationIsDoneForSudoku<9>>(exploration::PropagationIsDoneForSudoku<9>()));
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/main.cpp:135:7)]")));
    const unsigned int value = static_cast<const AnnotatedCell<9>&>(source_cell).get();
    EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> > guard = EventsPairGuard<9, __lambda_6, exploration::PropagationStartsForCell<9>, exploration::PropagationIsDoneForCell<9> >(add_event, static_cast<const exploration::PropagationStartsForCell<9>>(exploration::PropagationStartsForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::PropagationIsDoneForCell<9>>(exploration::PropagationIsDoneForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
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
                (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(97), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/main.cpp:135:7)]")));
                if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(static_cast<const exploration::CellPropagates<9>>(exploration::CellPropagates<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
                      const unsigned int * __begin0 = __range3.begin();
                      const unsigned int * __end0 = __range3.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(exploration::CellIsDeducedFromSingleAllowedValue<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), target_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), target_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(106), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/main.cpp:135:7)]")));
                          todo.push_back(target_coords);
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
                        add_event.operator()(static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), single_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/main.cpp:135:7)]")));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(static_cast<const exploration::SudokuIsSolved<9>>(exploration::SudokuIsSolved<9>()));
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


/* First instantiated from: main.cpp:1745 */
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


/* First instantiated from: main.cpp:1745 */
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



template<unsigned int size, typename AddEvent>
bool propagate_and_explore(const Stack<size> &, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size, AddEvent> &);
;


template<unsigned int size, typename AddEvent>
bool explore(const Stack<size> & stack, const EventAdder<size, AddEvent> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail("!stack.current().is_solved()", "src/exploration/sudoku-solver.hpp", 184, __extension____PRETTY_FUNCTION__));
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
  EventsPairGuard guard = add_event, exploration::ExplorationStarts<size>(coords, allowed_values), exploration::ExplorationIsDone<size>(coords);
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin2 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end2 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end2)); __begin2.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2).operator*();
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


/* First instantiated from: main.cpp:1784 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<4, __lambda_5>(const Stack<4> & stack, const EventAdder<4, __lambda_5> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(184), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
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
  EventsPairGuard<4, __lambda_5, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> > guard = EventsPairGuard<4, __lambda_5, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >(add_event, static_cast<const exploration::ExplorationStarts<4>>(exploration::ExplorationStarts<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::ExplorationIsDone<4>>(exploration::ExplorationIsDone<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin2 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end2 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end2)); __begin2.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2).operator*();
      add_event.operator()(static_cast<const exploration::HypothesisIsMade<4>>(exploration::HypothesisIsMade<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<4, __lambda_5>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(static_cast<const exploration::HypothesisIsAccepted<4>>(exploration::HypothesisIsAccepted<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(static_cast<const exploration::HypothesisIsRejected<4>>(exploration::HypothesisIsRejected<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif


/* First instantiated from: main.cpp:1784 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<4, __lambda_6>(const Stack<4> & stack, const EventAdder<4, __lambda_6> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(184), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.cpp:135:7)]")));
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
  EventsPairGuard<4, __lambda_6, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> > guard = EventsPairGuard<4, __lambda_6, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >(add_event, static_cast<const exploration::ExplorationStarts<4>>(exploration::ExplorationStarts<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::ExplorationIsDone<4>>(exploration::ExplorationIsDone<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin2 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end2 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end2)); __begin2.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2).operator*();
      add_event.operator()(static_cast<const exploration::HypothesisIsMade<4>>(exploration::HypothesisIsMade<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<4, __lambda_6>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(static_cast<const exploration::HypothesisIsAccepted<4>>(exploration::HypothesisIsAccepted<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(static_cast<const exploration::HypothesisIsRejected<4>>(exploration::HypothesisIsRejected<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif


/* First instantiated from: main.cpp:1784 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<9, __lambda_5>(const Stack<9> & stack, const EventAdder<9, __lambda_5> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(184), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:264:42)]")));
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
  EventsPairGuard<9, __lambda_5, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> > guard = EventsPairGuard<9, __lambda_5, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> >(add_event, static_cast<const exploration::ExplorationStarts<9>>(exploration::ExplorationStarts<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::ExplorationIsDone<9>>(exploration::ExplorationIsDone<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin2 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end2 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end2)); __begin2.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2).operator*();
      add_event.operator()(static_cast<const exploration::HypothesisIsMade<9>>(exploration::HypothesisIsMade<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<9, __lambda_5>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(static_cast<const exploration::HypothesisIsAccepted<9>>(exploration::HypothesisIsAccepted<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(static_cast<const exploration::HypothesisIsRejected<9>>(exploration::HypothesisIsRejected<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif


/* First instantiated from: main.cpp:1784 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<9, __lambda_6>(const Stack<9> & stack, const EventAdder<9, __lambda_6> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(184), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size, AddEvent> &) [size = 9U, AddEvent = (lambda at src/main.cpp:135:7)]")));
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
  EventsPairGuard<9, __lambda_6, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> > guard = EventsPairGuard<9, __lambda_6, exploration::ExplorationStarts<9>, exploration::ExplorationIsDone<9> >(add_event, static_cast<const exploration::ExplorationStarts<9>>(exploration::ExplorationStarts<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::ExplorationIsDone<9>>(exploration::ExplorationIsDone<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range2 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin2 = __range2.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end2 = __range2.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end2)); __begin2.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin2).operator*();
      add_event.operator()(static_cast<const exploration::HypothesisIsMade<9>>(exploration::HypothesisIsMade<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<9, __lambda_6>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(static_cast<const exploration::HypothesisIsAccepted<9>>(exploration::HypothesisIsAccepted<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(static_cast<const exploration::HypothesisIsRejected<9>>(exploration::HypothesisIsRejected<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif



template<unsigned int size, typename AddEvent>
bool propagate_and_explore(const Stack<size> & stack, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size, AddEvent> & add_event)
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


/* First instantiated from: main.cpp:1811 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<4, __lambda_5>(const Stack<4> & stack, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<4, __lambda_5> & add_event)
{
  if(propagate<4, __lambda_5>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(todo), add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<4, __lambda_5>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif


/* First instantiated from: main.cpp:1811 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<4, __lambda_6>(const Stack<4> & stack, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<4, __lambda_6> & add_event)
{
  if(propagate<4, __lambda_6>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(todo), add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<4, __lambda_6>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif


/* First instantiated from: main.cpp:1811 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<9, __lambda_5>(const Stack<9> & stack, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<9, __lambda_5> & add_event)
{
  if(propagate<9, __lambda_5>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(todo), add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<9, __lambda_5>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif


/* First instantiated from: main.cpp:1811 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<9, __lambda_6>(const Stack<9> & stack, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<9, __lambda_6> & add_event)
{
  if(propagate<9, __lambda_6>(stack, std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(todo), add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<9, __lambda_6>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif



template<unsigned int size, typename AddEvent>
Sudoku<ValueCell, size> solve_using_exploration(Sudoku<ValueCell, size> sudoku, const AddEvent & add_event_)
{
  Stack<size> stack;
  EventAdder<size, AddEvent> add_event = &stack, add_event_;
  std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    auto && __range2 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      const auto val = cell.get();
      if(val) {
        const std::pair<unsigned int, unsigned int> coords = cell.coordinates();
        add_event(exploration::CellIsSetInInput<size>(coords, *val));
        todo.push_back(coords);
      } 
      
    }
    
  }
  add_event(exploration::InputsAreDone<size>());
  propagate_and_explore(stack, std::move<std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo), add_event);
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


/* First instantiated from: main.cpp:1974 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_exploration<4, __lambda_6>(Sudoku<ValueCell, 4> sudoku, const __lambda_6 & add_event_)
{
  Stack<4> stack = Stack<4>();
  EventAdder<4, __lambda_6> add_event = EventAdder<4, __lambda_6>(&stack, add_event_);
  std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const SudokuBase<ValueCell, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<4, __lambda_6>>(add_event).operator()(static_cast<const exploration::CellIsSetInInput<4>>(exploration::CellIsSetInInput<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.push_back(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<4, __lambda_6>>(add_event).operator()(static_cast<const exploration::InputsAreDone<4>>(exploration::InputsAreDone<4>()));
  propagate_and_explore<4, __lambda_6>(static_cast<const Stack<4>>(stack), static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<4, __lambda_6>>(add_event));
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


/* First instantiated from: main.cpp:1823 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_exploration<4, __lambda_5>(Sudoku<ValueCell, 4> sudoku, const __lambda_5 & add_event_)
{
  Stack<4> stack = Stack<4>();
  EventAdder<4, __lambda_5> add_event = EventAdder<4, __lambda_5>(&stack, add_event_);
  std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const SudokuBase<ValueCell, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<4, __lambda_5>>(add_event).operator()(static_cast<const exploration::CellIsSetInInput<4>>(exploration::CellIsSetInInput<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.push_back(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<4, __lambda_5>>(add_event).operator()(static_cast<const exploration::InputsAreDone<4>>(exploration::InputsAreDone<4>()));
  propagate_and_explore<4, __lambda_5>(static_cast<const Stack<4>>(stack), static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<4, __lambda_5>>(add_event));
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


/* First instantiated from: main.cpp:1974 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_exploration<9, __lambda_6>(Sudoku<ValueCell, 9> sudoku, const __lambda_6 & add_event_)
{
  Stack<9> stack = Stack<9>();
  EventAdder<9, __lambda_6> add_event = EventAdder<9, __lambda_6>(&stack, add_event_);
  std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const SudokuBase<ValueCell, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<9, __lambda_6>>(add_event).operator()(static_cast<const exploration::CellIsSetInInput<9>>(exploration::CellIsSetInInput<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.push_back(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<9, __lambda_6>>(add_event).operator()(static_cast<const exploration::InputsAreDone<9>>(exploration::InputsAreDone<9>()));
  propagate_and_explore<9, __lambda_6>(static_cast<const Stack<9>>(stack), static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<9, __lambda_6>>(add_event));
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


/* First instantiated from: main.cpp:1823 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_exploration<9, __lambda_5>(Sudoku<ValueCell, 9> sudoku, const __lambda_5 & add_event_)
{
  Stack<9> stack = Stack<9>();
  EventAdder<9, __lambda_5> add_event = EventAdder<9, __lambda_5>(&stack, add_event_);
  std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
    boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const SudokuBase<ValueCell, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_2, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<9, __lambda_5>>(add_event).operator()(static_cast<const exploration::CellIsSetInInput<9>>(exploration::CellIsSetInInput<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.push_back(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<9, __lambda_5>>(add_event).operator()(static_cast<const exploration::InputsAreDone<9>>(exploration::InputsAreDone<9>()));
  propagate_and_explore<9, __lambda_5>(static_cast<const Stack<9>>(stack), static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<9, __lambda_5>>(add_event));
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


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_exploration(Sudoku<ValueCell, size> sudoku)
{
      
  class __lambda_5
  {
    public: 
    template<class type_parameter_1_0>
    inline auto operator()(const type_parameter_1_0 &) const
    {
    }
    private: 
    template<class type_parameter_1_0>
    static inline auto __invoke(const type_parameter_1_0 & __param0)
    {
      return __lambda_5{}.operator()<type_parameter_1_0>(__param0);
    }
    
    public:
    // /*constexpr */ __lambda_5() = default;
    
  };
  
  return solve_using_exploration(sudoku, __lambda_5{});
}


/* First instantiated from: main.cpp:1902 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_exploration<4>(Sudoku<ValueCell, 4> sudoku)
{
      
  class __lambda_5
  {
    public: 
    template<class type_parameter_0_0>
    inline /*constexpr */ auto operator()(const type_parameter_0_0 &) const
    {
    }
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> &) const
    {
    }
    #endif
    
    private: 
    template<class type_parameter_0_0>
    static inline /*constexpr */ auto __invoke(const type_parameter_0_0 & __param0)
    {
      return __lambda_5{}.operator()<type_parameter_0_0>(__param0);
    }
    
    public:
    // /*constexpr */ __lambda_5() = default;
    
  };
  
  return solve_using_exploration<4, __lambda_5>(Sudoku<ValueCell, 4>(static_cast<const Sudoku<ValueCell, 4>>(sudoku)), static_cast<const __lambda_5>(__lambda_5{}));
}
#endif


/* First instantiated from: main.cpp:1902 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_exploration<9>(Sudoku<ValueCell, 9> sudoku)
{
      
  class __lambda_5
  {
    public: 
    template<class type_parameter_0_0>
    inline /*constexpr */ auto operator()(const type_parameter_0_0 &) const
    {
    }
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> &) const
    {
    }
    #endif
    
    
    #ifdef INSIGHTS_USE_TEMPLATE
    template<>
    inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> &) const
    {
    }
    #endif
    
    private: 
    template<class type_parameter_0_0>
    static inline /*constexpr */ auto __invoke(const type_parameter_0_0 & __param0)
    {
      return __lambda_5{}.operator()<type_parameter_0_0>(__param0);
    }
    
    public:
    // /*constexpr */ __lambda_5() = default;
    
  };
  
  return solve_using_exploration<9, __lambda_5>(Sudoku<ValueCell, 9>(static_cast<const Sudoku<ValueCell, 9>>(sudoku)), static_cast<const __lambda_5>(__lambda_5{}));
}
#endif


#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
# 12 "src/main.cpp"
# 1 "src/puzzle/check.hpp"
// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_CHECK_HPP_
#define PUZZLE_CHECK_HPP_

# 7 "src/puzzle/check.hpp"

template<unsigned int size>
bool is_solved(const Sudoku<ValueCell, size> &);
;

#endif  // PUZZLE_CHECK_HPP_
# 13 "src/main.cpp"
# 1 "src/sat/sudoku-solver.hpp"
// Copyright 2023 Vincent Jacques

#ifndef SAT_SUDOKU_SOLVER_HPP_
#define SAT_SUDOKU_SOLVER_HPP_

# 7 "src/sat/sudoku-solver.hpp"


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_sat(Sudoku<ValueCell, size>);
;

#endif  // SAT_SUDOKU_SOLVER_HPP_
# 14 "src/main.cpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


struct Options
{
  bool solve;
  bool use_sat;
  bool explain;
  std::filesystem::path input_path;
  std::optional<std::filesystem::path> text_path;
  std::optional<std::filesystem::path> html_path;
  std::optional<std::filesystem::path> html_text_path;
  std::optional<std::filesystem::path> video_path;
  bool quick_video;
  std::optional<std::filesystem::path> video_frames_path;
  std::optional<std::filesystem::path> video_text_path;
  unsigned int width;
  unsigned int height;
  // inline ~Options() noexcept = default;
};



template<unsigned int size>
int main_(const Options & options)
{
      
  class __lambda_7
  {
    public: 
    inline auto operator()() const
    {
      if(operator==(options.input_path, std::filesystem::path("-", std::filesystem::path::auto_format))) {
        return Sudoku<ValueCell, size>::load(std::cin);
      } else {
        std::basic_ifstream<char> input = std::basic_ifstream<char>(options.input_path, std::ios_base::in);
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail("input.is_open()", "src/main.cpp", 44, __extension____PRETTY_FUNCTION__));
        return Sudoku<ValueCell, size>::load(input);
      } 
      
    }
    
    private: 
    const Options & options;
    
    public:
    __lambda_7(const Options & _options)
    : options{_options}
    {}
    
  };
  
  const auto sudoku = (__lambda_7{options})();
  if(options.solve) {
    if(options.use_sat) {
      const auto solved = solve_using_sat(sudoku);
      if(is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using SAT")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      const auto solved = solve_using_exploration(sudoku);
      if(is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } 
    
  } else {
    if(options.explain) {
      unsigned int stdout_users = static_cast<unsigned int>(0);
      std::optional<std::basic_ofstream<char> > text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<size> > text_explainer;
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        text_explainer.emplace(std::cout);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          text_output.emplace<const std::filesystem::path &>(options.text_path.operator*());
          (static_cast<bool>(text_output.operator->()->is_open()) ? void(0) : __assert_fail("text_output->is_open()", "src/main.cpp", 81, __extension____PRETTY_FUNCTION__));
          text_explainer.emplace(text_output.operator*());
        } 
        
      } 
      
      std::optional<HtmlExplainer<size> > html_explainer;
      if(static_cast<bool>(options.html_path.operator bool())) {
        html_explainer.emplace(options.html_path.operator*(), options.width, options.height);
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      std::optional<std::basic_ofstream<char> > video_text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<size> > video_text_explainer_;
      std::optional<Reorder<size, TextExplainer<size> > > video_text_explainer;
      if(static_cast<bool>(options.video_text_path.operator bool())) {
        if(std::operator==(options.video_text_path, "-")) {
          ++stdout_users;
          video_text_explainer_.emplace(std::cout);
        } else {
          video_text_output.emplace<const std::filesystem::path &>(options.video_text_path.operator*());
          (static_cast<bool>(video_text_output.operator->()->is_open()) ? void(0) : __assert_fail("video_text_output->is_open()", "src/main.cpp", 103, __extension____PRETTY_FUNCTION__));
          video_text_explainer_.emplace(video_text_output.operator*());
        } 
        
        video_text_explainer.emplace(&*video_text_explainer_);
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      std::optional<VideoExplainer<size> > video_explainer_;
      std::optional<Reorder<size, VideoExplainer<size> > > video_explainer;
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail("video_serializers.size() == 2", "src/main.cpp", 120, __extension____PRETTY_FUNCTION__));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >{std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>())})));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        video_explainer_.emplace(static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
        video_explainer.emplace(&*video_explainer_);
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
                  
      class __lambda_6
      {
        public: 
        template<class type_parameter_1_0>
        inline auto operator()(const type_parameter_1_0 & event) const
        {
          if(text_explainer) {
            (*text_explainer)(event);
          } 
          
          if(html_explainer) {
            (*html_explainer)(event);
          } 
          
          if(video_text_explainer) {
            (*video_text_explainer)(event);
          } 
          
          if(video_explainer) {
            (*video_explainer)(event);
          } 
          
        }
        
      };
      
      const auto solved = solve_using_exploration<size>(sudoku, __lambda_6{});
      if(is_solved(solved)) {
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      __builtin_unreachable();
    } 
    
  } 
  
}


/* First instantiated from: main.cpp:2115 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int main_<4>(const Options & options)
{
      
  class __lambda_7
  {
    public: 
    inline Sudoku<ValueCell, 4> operator()() const
    {
      if(operator==(options.input_path, std::filesystem::path("-", std::filesystem::path::auto_format))) {
        return Sudoku<ValueCell, 4>::load(std::cin);
      } else {
        std::basic_ifstream<char> input = std::basic_ifstream<char>(options.input_path, std::ios_base::in);
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("input.is_open()"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(44), static_cast<const char *>(__extension__"auto main_(const Options &)::(anonymous class)::operator()() const")));
        return Sudoku<ValueCell, 4>::load(static_cast<std::basic_istream<char>&>(input));
      } 
      
    }
    
    private: 
    const Options & options;
    
    public:
    __lambda_7(const Options & _options)
    : options{_options}
    {}
    
  } __lambda_7{options};
  
  const Sudoku<ValueCell, 4> sudoku = static_cast<const Sudoku<ValueCell, 4>>(static_cast<const __lambda_7>((__lambda_7)).operator()());
  if(options.solve) {
    if(options.use_sat) {
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_sat<4>(Sudoku<ValueCell, 4>(sudoku)));
      if(is_solved<4>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using SAT")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_exploration<4>(Sudoku<ValueCell, 4>(sudoku)));
      if(is_solved<4>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } 
    
  } else {
    if(options.explain) {
      unsigned int stdout_users = static_cast<unsigned int>(0);
      std::optional<std::basic_ofstream<char> > text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<4> > text_explainer = std::optional<TextExplainer<4> >();
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        text_explainer.emplace<std::basic_ostream<char> &>(std::cout);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          text_output.emplace<const std::filesystem::path &>(options.text_path.operator*());
          (static_cast<bool>(text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("text_output->is_open()"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(81), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
          text_explainer.emplace<std::basic_ofstream<char> &>(text_output.operator*());
        } 
        
      } 
      
      std::optional<HtmlExplainer<4> > html_explainer = std::optional<HtmlExplainer<4> >();
      if(static_cast<bool>(options.html_path.operator bool())) {
        html_explainer.emplace<const std::filesystem::path &, const unsigned int &, const unsigned int &>(options.html_path.operator*(), options.width, options.height);
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      std::optional<std::basic_ofstream<char> > video_text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<4> > video_text_explainer_ = std::optional<TextExplainer<4> >();
      std::optional<Reorder<4, TextExplainer<4> > > video_text_explainer = std::optional<Reorder<4, TextExplainer<4> > >();
      if(static_cast<bool>(options.video_text_path.operator bool())) {
        if(std::operator==(options.video_text_path, "-")) {
          ++stdout_users;
          video_text_explainer_.emplace<std::basic_ostream<char> &>(std::cout);
        } else {
          video_text_output.emplace<const std::filesystem::path &>(options.video_text_path.operator*());
          (static_cast<bool>(video_text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("video_text_output->is_open()"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(103), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
          video_text_explainer_.emplace<std::basic_ofstream<char> &>(video_text_output.operator*());
        } 
        
        video_text_explainer.emplace<TextExplainer<4> *>(&video_text_explainer_.operator*());
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      std::optional<VideoExplainer<4> > video_explainer_ = std::optional<VideoExplainer<4> >();
      std::optional<Reorder<4, VideoExplainer<4> > > video_explainer = std::optional<Reorder<4, VideoExplainer<4> > >();
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail(static_cast<const char *>("video_serializers.size() == 2"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(120), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>()))))));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        video_explainer_.emplace<video::Serializer *, const bool &, const unsigned int &, const unsigned int &>(static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
        video_explainer.emplace<VideoExplainer<4> *>(&video_explainer_.operator*());
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
                  
      class __lambda_6
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ auto operator()(const type_parameter_0_0 & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*())(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*())(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*())(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*())(event);
          } 
          
        }
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, TextExplainer<4> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4, VideoExplainer<4> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        private: 
        std::optional<TextExplainer<4> > & text_explainer;
        std::optional<HtmlExplainer<4> > & html_explainer;
        std::optional<Reorder<4, TextExplainer<4> > > & video_text_explainer;
        std::optional<Reorder<4, VideoExplainer<4> > > & video_explainer;
        
        public:
        __lambda_6(std::optional<TextExplainer<4> > & _text_explainer, std::optional<HtmlExplainer<4> > & _html_explainer, std::optional<Reorder<4, TextExplainer<4> > > & _video_text_explainer, std::optional<Reorder<4, VideoExplainer<4> > > & _video_explainer)
        : text_explainer{_text_explainer}
        , html_explainer{_html_explainer}
        , video_text_explainer{_video_text_explainer}
        , video_explainer{_video_explainer}
        {}
        
      };
      
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_exploration<4U>(Sudoku<ValueCell, 4>(sudoku), static_cast<const __lambda_6>(__lambda_6{text_explainer, html_explainer, video_text_explainer, video_explainer})));
      if(is_solved<4>(solved)) {
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      __builtin_unreachable();
    } 
    
  } 
  
}
#endif


/* First instantiated from: main.cpp:2117 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int main_<9>(const Options & options)
{
      
  class __lambda_7
  {
    public: 
    inline Sudoku<ValueCell, 9> operator()() const
    {
      if(operator==(options.input_path, std::filesystem::path("-", std::filesystem::path::auto_format))) {
        return Sudoku<ValueCell, 9>::load(std::cin);
      } else {
        std::basic_ifstream<char> input = std::basic_ifstream<char>(options.input_path, std::ios_base::in);
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("input.is_open()"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(44), static_cast<const char *>(__extension__"auto main_(const Options &)::(anonymous class)::operator()() const")));
        return Sudoku<ValueCell, 9>::load(static_cast<std::basic_istream<char>&>(input));
      } 
      
    }
    
    private: 
    const Options & options;
    
    public:
    __lambda_7(const Options & _options)
    : options{_options}
    {}
    
  } __lambda_7{options};
  
  const Sudoku<ValueCell, 9> sudoku = static_cast<const Sudoku<ValueCell, 9>>(static_cast<const __lambda_7>((__lambda_7)).operator()());
  if(options.solve) {
    if(options.use_sat) {
      const Sudoku<ValueCell, 9> solved = static_cast<const Sudoku<ValueCell, 9>>(solve_using_sat<9>(Sudoku<ValueCell, 9>(sudoku)));
      if(is_solved<9>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using SAT")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      const Sudoku<ValueCell, 9> solved = static_cast<const Sudoku<ValueCell, 9>>(solve_using_exploration<9>(Sudoku<ValueCell, 9>(sudoku)));
      if(is_solved<9>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } 
    
  } else {
    if(options.explain) {
      unsigned int stdout_users = static_cast<unsigned int>(0);
      std::optional<std::basic_ofstream<char> > text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<9> > text_explainer = std::optional<TextExplainer<9> >();
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        text_explainer.emplace<std::basic_ostream<char> &>(std::cout);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          text_output.emplace<const std::filesystem::path &>(options.text_path.operator*());
          (static_cast<bool>(text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("text_output->is_open()"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(81), static_cast<const char *>(__extension__"int main_(const Options &) [size = 9U]")));
          text_explainer.emplace<std::basic_ofstream<char> &>(text_output.operator*());
        } 
        
      } 
      
      std::optional<HtmlExplainer<9> > html_explainer = std::optional<HtmlExplainer<9> >();
      if(static_cast<bool>(options.html_path.operator bool())) {
        html_explainer.emplace<const std::filesystem::path &, const unsigned int &, const unsigned int &>(options.html_path.operator*(), options.width, options.height);
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      std::optional<std::basic_ofstream<char> > video_text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<9> > video_text_explainer_ = std::optional<TextExplainer<9> >();
      std::optional<Reorder<9, TextExplainer<9> > > video_text_explainer = std::optional<Reorder<9, TextExplainer<9> > >();
      if(static_cast<bool>(options.video_text_path.operator bool())) {
        if(std::operator==(options.video_text_path, "-")) {
          ++stdout_users;
          video_text_explainer_.emplace<std::basic_ostream<char> &>(std::cout);
        } else {
          video_text_output.emplace<const std::filesystem::path &>(options.video_text_path.operator*());
          (static_cast<bool>(video_text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("video_text_output->is_open()"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(103), static_cast<const char *>(__extension__"int main_(const Options &) [size = 9U]")));
          video_text_explainer_.emplace<std::basic_ofstream<char> &>(video_text_output.operator*());
        } 
        
        video_text_explainer.emplace<TextExplainer<9> *>(&video_text_explainer_.operator*());
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      std::optional<VideoExplainer<9> > video_explainer_ = std::optional<VideoExplainer<9> >();
      std::optional<Reorder<9, VideoExplainer<9> > > video_explainer = std::optional<Reorder<9, VideoExplainer<9> > >();
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail(static_cast<const char *>("video_serializers.size() == 2"), static_cast<const char *>("src/main.cpp"), static_cast<unsigned int>(120), static_cast<const char *>(__extension__"int main_(const Options &) [size = 9U]")));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>()))))));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        video_explainer_.emplace<video::Serializer *, const bool &, const unsigned int &, const unsigned int &>(static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
        video_explainer.emplace<VideoExplainer<9> *>(&video_explainer_.operator*());
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
                  
      class __lambda_6
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ auto operator()(const type_parameter_0_0 & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*())(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*())(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*())(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*())(event);
          } 
          
        }
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            (text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            (html_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, TextExplainer<9> > >>(video_text_explainer).operator bool())) {
            (video_text_explainer.operator*()).operator()(event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9, VideoExplainer<9> > >>(video_explainer).operator bool())) {
            (video_explainer.operator*()).operator()(event);
          } 
          
        }
        #endif
        
        private: 
        std::optional<TextExplainer<9> > & text_explainer;
        std::optional<HtmlExplainer<9> > & html_explainer;
        std::optional<Reorder<9, TextExplainer<9> > > & video_text_explainer;
        std::optional<Reorder<9, VideoExplainer<9> > > & video_explainer;
        
        public:
        __lambda_6(std::optional<TextExplainer<9> > & _text_explainer, std::optional<HtmlExplainer<9> > & _html_explainer, std::optional<Reorder<9, TextExplainer<9> > > & _video_text_explainer, std::optional<Reorder<9, VideoExplainer<9> > > & _video_explainer)
        : text_explainer{_text_explainer}
        , html_explainer{_html_explainer}
        , video_text_explainer{_video_text_explainer}
        , video_explainer{_video_explainer}
        {}
        
      };
      
      const Sudoku<ValueCell, 9> solved = static_cast<const Sudoku<ValueCell, 9>>(solve_using_exploration<9U>(Sudoku<ValueCell, 9>(sudoku), static_cast<const __lambda_6>(__lambda_6{text_explainer, html_explainer, video_text_explainer, video_explainer})));
      if(is_solved<9>(solved)) {
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      __builtin_unreachable();
    } 
    
  } 
  
}
#endif


struct ExistingFileOrStdinValidator : public CLI::Validator
{
  inline ExistingFileOrStdinValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE(or - for stdin)"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_8
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str) const
      {
        if(std::operator==(str, static_cast<const char *>("-"))) {
          return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
        } else {
          return static_cast<const CLI::Validator&>(CLI::ExistingFile).operator()(str);
        } 
        
      }
      
      using retType_1996_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_1996_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_8{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_8(const __lambda_8 &) noexcept = default;
      // inline /*constexpr */ __lambda_8(__lambda_8 &&) noexcept = default;
      // /*constexpr */ __lambda_8() = default;
      
    } __lambda_8{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_8);
  }
  
  // inline ~ExistingFileOrStdinValidator() noexcept = default;
};



const ExistingFileOrStdinValidator ExistingFileOrStdin = ExistingFileOrStdinValidator();


struct FileOrStdoutValidator : public CLI::Validator
{
  inline FileOrStdoutValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE(or - for stdout)"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_9
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str) const
      {
        return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
      }
      
      using retType_2010_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_2010_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_9{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_9(const __lambda_9 &) noexcept = default;
      // inline /*constexpr */ __lambda_9(__lambda_9 &&) noexcept = default;
      // /*constexpr */ __lambda_9() = default;
      
    } __lambda_9{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_9);
  }
  
  // inline ~FileOrStdoutValidator() noexcept = default;
};



const FileOrStdoutValidator FileOrStdout = FileOrStdoutValidator();


struct FileValidator : public CLI::Validator
{
  inline FileValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_10
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str) const
      {
        return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
      }
      
      using retType_2018_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_2018_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_10{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_10(const __lambda_10 &) noexcept = default;
      // inline /*constexpr */ __lambda_10(__lambda_10 &&) noexcept = default;
      // /*constexpr */ __lambda_10() = default;
      
    } __lambda_10{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_10);
  }
  
  // inline ~FileValidator() noexcept = default;
};



const FileValidator File = FileValidator();



int main(int argc, char ** argv)
{
  CLI::App app = CLI::App{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Solve a Sudoku, and explain how!"), static_cast<const std::allocator<char>>(std::allocator<char>())), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>()))};
  unsigned int size = static_cast<unsigned int>(9);
  app.add_option<unsigned int, unsigned int, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--size"), static_cast<const std::allocator<char>>(std::allocator<char>())), size, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Size of the Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())))->option_text(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("4, 9 (default), 16..."), static_cast<const std::allocator<char>>(std::allocator<char>())));
  app.require_subcommand(1);
  CLI::App * solve = app.add_subcommand(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solve"), static_cast<const std::allocator<char>>(std::allocator<char>())), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Just solve a Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())));
  CLI::App * explain = app.add_subcommand(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("explain"), static_cast<const std::allocator<char>>(std::allocator<char>())), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Explain how to solve a Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())));
  bool use_sat = false;
  solve->add_flag<bool, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--sat"), static_cast<const std::allocator<char>>(std::allocator<char>())), use_sat, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Use the 'Minisat' SAT solver instead of the default exploration algorithm"), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> text_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--text"), static_cast<const std::allocator<char>>(std::allocator<char>())), text_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate detailed textual explanation in the given file"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(FileOrStdout)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> html_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--html"), static_cast<const std::allocator<char>>(std::allocator<char>())), html_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate HTML explanation in the given directory"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(CLI::NonexistentPath)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> html_text_path = std::optional<std::filesystem::path>();
  std::optional<std::filesystem::path> video_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--video"), static_cast<const std::allocator<char>>(std::allocator<char>())), video_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate video explanation in the given '.mpg' file"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(File)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  bool quick_video = false;
  static_cast<CLI::OptionBase<CLI::Option> *>(explain->add_flag<bool, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--quick-video"), static_cast<const std::allocator<char>>(std::allocator<char>())), quick_video, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Make the video explanation quick (for testing)"), static_cast<const std::allocator<char>>(std::allocator<char>()))))->group(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> video_frames_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--video-frames"), static_cast<const std::allocator<char>>(std::allocator<char>())), video_frames_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate PNG frames from the video explanation in the given directory"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(CLI::NonexistentPath)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> video_text_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--video-text"), static_cast<const std::allocator<char>>(std::allocator<char>())), video_text_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate textual explanation in the given file, reordered to match the video explanation"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(FileOrStdout)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  unsigned int width = static_cast<unsigned int>(640);
  explain->add_option<unsigned int, unsigned int, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--width"), static_cast<const std::allocator<char>>(std::allocator<char>())), width, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Width of the images in the HTML and video explanations"), static_cast<const std::allocator<char>>(std::allocator<char>())))->default_val<char[4]>("640");
  unsigned int height = static_cast<unsigned int>(480);
  explain->add_option<unsigned int, unsigned int, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--height"), static_cast<const std::allocator<char>>(std::allocator<char>())), height, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Height of the images in the HTML and video explanations"), static_cast<const std::allocator<char>>(std::allocator<char>())))->default_val<char[4]>("480");
  std::filesystem::path input_path = std::filesystem::path();
  {
    std::initializer_list<CLI::App *> && __range2 = std::initializer_list<CLI::App *>{solve, explain};
    CLI::App *const * __begin2 = static_cast<const std::initializer_list<CLI::App *>>(__range2).begin();
    CLI::App *const * __end2 = static_cast<const std::initializer_list<CLI::App *>>(__range2).end();
    for(; __begin2 != __end2; ++__begin2) {
      CLI::App * subcommand = *__begin2;
      static_cast<CLI::OptionBase<CLI::Option> *>(subcommand->add_option<std::filesystem::path, std::filesystem::path, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("INPUT"), static_cast<const std::allocator<char>>(std::allocator<char>())), input_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Input file"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(ExistingFileOrStdin)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>()))))->required(true);
    }
    
  }
  try 
  {
    (app).parse((argc), static_cast<const char *const *>((argv)));
  } catch(const CLI::ParseError & e) {
    return static_cast<const CLI::App>((app)).exit(static_cast<const CLI::Error&>(e), std::cout, std::cerr);
  }
  ;
  ;
  if(((((!static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(text_path).operator bool()) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(html_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(html_text_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(video_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(video_frames_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(video_text_path).operator bool())) {
    text_path.operator=("-");
  } 
  
  Options options = {static_cast<const CLI::App *>(solve)->parsed(), use_sat, static_cast<const CLI::App *>(explain)->parsed(), std::filesystem::path(static_cast<const std::filesystem::path>(input_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(text_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(html_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(html_text_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(video_path)), quick_video, std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(video_frames_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(video_text_path)), width, height};
  switch(size) {
    case static_cast<unsigned int>(4): return main_<4>(static_cast<const Options>(options));
    case static_cast<unsigned int>(9): return main_<9>(static_cast<const Options>(options));
    default: std::operator<<(std::cerr, static_cast<const char *>("ERROR: unsupported size: ")).operator<<(size).operator<<(std::endl);
    return 1;
  }
  return 0;
}

