# 1 "src/explanation/html-explainer.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/explanation/html-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>

# 1 "src/explanation/explanation.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_EXPLANATION_HPP_
#define EXPLANATION_EXPLANATION_HPP_

#include <optional>
#include <tuple>
#include <utility>
#include <vector>

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

/* First instantiated from: html-explainer.cpp:328 */
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
/* First instantiated from: html-explainer.cpp:328 */
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

/* First instantiated from: html-explainer.cpp:395 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<ValueCell, 4>
{
  
  public: 
  class Cell : public ValueCell
  {
    
    public: 
    inline Cell(const SudokuBase<ValueCell, 4> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_);
    
    inline Cell(const SudokuBase<ValueCell, 4> * sudoku_, const Cell & other);
    
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
  
  inline SudokuBase(const SudokuBase<ValueCell, 4> & other);
  
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
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::array<std::array<Cell, 4>, 4> & other_cells);
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 4>, 4> & other_cells);
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 4>, 4> & other_cells) const;
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords);
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
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
      const SudokuBase<ValueCell, 4> * __this;
      public: 
      // inline /*constexpr */ __lambda_1 & operator=(const __lambda_1 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_1(const __lambda_1 &) noexcept = default;
      __lambda_1(const SudokuBase<ValueCell, 4> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_1 convert = static_cast<const __lambda_1>(__lambda_1{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.begin(), __lambda_1(convert)), boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<4>::cells.end(), __lambda_1(convert)));
  }
  
  inline auto cells();
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: html-explainer.cpp:395 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<ValueCell, 9>
{
  
  public: 
  class Cell : public ValueCell
  {
    
    public: 
    inline Cell(const SudokuBase<ValueCell, 9> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_);
    
    inline Cell(const SudokuBase<ValueCell, 9> * sudoku_, const Cell & other);
    
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
  
  inline SudokuBase(const SudokuBase<ValueCell, 9> & other);
  
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
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::array<std::array<Cell, 9>, 9> & other_cells);
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 9>, 9> & other_cells);
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  inline Cell copy_cell(unsigned int row, unsigned int col, const std::array<std::array<Cell, 9>, 9> & other_cells) const;
  
  
  public: 
  inline Cell & cell(const std::pair<unsigned int, unsigned int> & coords);
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
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
      const SudokuBase<ValueCell, 9> * __this;
      public: 
      // inline /*constexpr */ __lambda_1 & operator=(const __lambda_1 &) /* noexcept */ = delete;
      // inline /*constexpr */ __lambda_1(const __lambda_1 &) noexcept = default;
      __lambda_1(const SudokuBase<ValueCell, 9> * _this)
      : __this{_this}
      {}
      
    };
    
    const __lambda_1 convert = static_cast<const __lambda_1>(__lambda_1{this});
    return boost::make_iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> >(boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.begin(), __lambda_1(convert)), boost::iterators::make_transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *>(SudokuConstants<9>::cells.end(), __lambda_1(convert)));
  }
  
  inline auto cells();
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 9>, 9> _cells;
  public: 
};

#endif
/* First instantiated from: html-explainer.cpp:555 */
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
  inline SudokuBase()
  : _cells{this->make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<AnnotatedCell<4>, 4> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
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
  
  /* First instantiated from: html-explainer.cpp:266 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: html-explainer.cpp:271 */
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
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return this->copy_cells<0, 1, 2, 3>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()), other_cells);
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 4>, 4> & other_cells);
  
  /* First instantiated from: html-explainer.cpp:285 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: html-explainer.cpp:290 */
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
    const std::pair<unsigned int, unsigned int> __coords1 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    (static_cast<bool>(row < 4U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(149), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<4>, 4>::cell(const Coordinates &) [CellBase = AnnotatedCell<4>, size = 4]")));
    (static_cast<bool>(col < 4U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(150), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<4>, 4>::cell(const Coordinates &) [CellBase = AnnotatedCell<4>, size = 4]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline auto cells() const;
  
  inline auto cells();
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: html-explainer.cpp:555 */
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
  inline SudokuBase()
  : _cells{this->make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<AnnotatedCell<9>, 9> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
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
  
  /* First instantiated from: html-explainer.cpp:266 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: html-explainer.cpp:271 */
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
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return this->copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()), other_cells);
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> copy_cells(const std::integer_sequence<unsigned int, row...> &, const std::array<std::array<Cell, 9>, 9> & other_cells);
  
  /* First instantiated from: html-explainer.cpp:285 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &, const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: html-explainer.cpp:290 */
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
    const std::pair<unsigned int, unsigned int> __coords1 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords1));
    (static_cast<bool>(row < 9U) ? void(0) : __assert_fail(static_cast<const char *>("row < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(149), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<9>, 9>::cell(const Coordinates &) [CellBase = AnnotatedCell<9>, size = 9]")));
    (static_cast<bool>(col < 9U) ? void(0) : __assert_fail(static_cast<const char *>("col < size"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(150), static_cast<const char *>(__extension__"Cell &SudokuBase<AnnotatedCell<9>, 9>::cell(const Coordinates &) [CellBase = AnnotatedCell<9>, size = 9]")));
    return this->_cells.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const;
  
  inline auto cells() const;
  
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

/* First instantiated from: html-explainer.cpp:785 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<ValueCell, 4> : public SudokuBase<ValueCell, 4>
{
  
  public: 
  static Sudoku<ValueCell, 4> load(std::basic_istream<char> &);
  
  void dump(std::basic_ostream<char> &) const;
  
  static Sudoku<ValueCell, 4> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
  // inline Sudoku(Sudoku<ValueCell, 4> &&) /* noexcept */ = delete;
  // inline Sudoku<ValueCell, 4> & operator=(Sudoku<ValueCell, 4> &&) /* noexcept */ = delete;
};

#endif
/* First instantiated from: html-explainer.cpp:785 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class Sudoku<ValueCell, 9> : public SudokuBase<ValueCell, 9>
{
  
  public: 
  static Sudoku<ValueCell, 9> load(std::basic_istream<char> &);
  
  void dump(std::basic_ostream<char> &) const;
  
  static Sudoku<ValueCell, 9> from_string(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &);
  
  std::basic_string<char, std::char_traits<char>, std::allocator<char> > to_string() const;
  
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
  inline bool is_solved() const;
  
  // inline Sudoku(const Sudoku<AnnotatedCell<4>, 4> &) noexcept(false) = default;
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
  inline bool is_solved() const;
  
  // inline Sudoku(const Sudoku<AnnotatedCell<9>, 9> &) noexcept(false) = default;
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
  , hypothesis{false}
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
  
  inline bool is_hypothesis() const
  {
    this->assert_invariants();
    return this->hypothesis;
  }
  
  inline bool is_set() const
  {
    this->assert_invariants();
    return this->set_value.has_value();
  }
  
  inline unsigned int get() const
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "src/exploration/annotations.hpp", 49, __extension____PRETTY_FUNCTION__));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 56, __extension____PRETTY_FUNCTION__));
    return this->allowed_values.test(value);
  }
  
  inline void set_input(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 63, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 64, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "src/exploration/annotations.hpp", 65, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    this->assert_invariants();
  }
  
  inline void set_hypothesis(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 77, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 78, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "src/exploration/annotations.hpp", 79, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->hypothesis = true;
    this->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 91, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 92, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "src/exploration/annotations.hpp", 93, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->assert_invariants();
  }
  
  inline void set_propagated()
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "src/exploration/annotations.hpp", 104, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "src/exploration/annotations.hpp", 119, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "src/exploration/annotations.hpp", 120, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail("allowed_values.any()", "src/exploration/annotations.hpp", 136, __extension____PRETTY_FUNCTION__));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "src/exploration/annotations.hpp", 140, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "src/exploration/annotations.hpp", 145, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == 1) ? void(0) : __assert_fail("allowed_values.count() == 1", "src/exploration/annotations.hpp", 150, __extension____PRETTY_FUNCTION__));
      (static_cast<bool>(this->allowed_values.test(this->set_value.value())) ? void(0) : __assert_fail("allowed_values.test(set_value.value())", "src/exploration/annotations.hpp", 151, __extension____PRETTY_FUNCTION__));
    } 
    
  }
  
  
  private: 
  std::bitset<size> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool hypothesis;
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
  , hypothesis{false}
  , propagated{false}
  {
    this->allowed_values.set();
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  
  public: 
  inline bool is_input() const;
  
  inline bool is_hypothesis() const;
  
  inline bool is_set() const
  {
    this->assert_invariants();
    return this->set_value.has_value();
  }
  
  inline unsigned int get() const;
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(56), static_cast<const char *>(__extension__"bool AnnotatedCell<4>::is_allowed(const unsigned int) const [size = 4]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(63), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_input(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(64), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_input(const unsigned int) [size = 4]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(65), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_input(const unsigned int) [size = 4]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline void set_hypothesis(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(77), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_hypothesis(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(78), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_hypothesis(const unsigned int) [size = 4]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_hypothesis(const unsigned int) [size = 4]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->hypothesis = true;
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(91), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(92), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(93), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_deduced(const unsigned int) [size = 4]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline void set_propagated()
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(104), static_cast<const char *>(__extension__"void AnnotatedCell<4>::set_propagated() [size = 4]")));
    this->propagated = true;
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline bool is_propagated() const;
  
  inline void forbid(const unsigned int value)
  {
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(119), static_cast<const char *>(__extension__"void AnnotatedCell<4>::forbid(const unsigned int) [size = 4]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<4> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(120), static_cast<const char *>(__extension__"void AnnotatedCell<4>::forbid(const unsigned int) [size = 4]")));
    this->allowed_values.reset(static_cast<unsigned long>(value));
    static_cast<const AnnotatedCell<4> *>(this)->assert_invariants();
  }
  
  inline unsigned int allowed_count() const;
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(136), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(140), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(145), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(150), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(151), static_cast<const char *>(__extension__"void AnnotatedCell<4>::assert_invariants() const [size = 4]")));
    } 
    
  }
  
  
  private: 
  std::bitset<4> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool hypothesis;
  bool propagated;
  public: 
  // inline constexpr AnnotatedCell(const AnnotatedCell<4> &) noexcept = default;
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
  , hypothesis{false}
  , propagated{false}
  {
    this->allowed_values.set();
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  
  public: 
  inline bool is_input() const;
  
  inline bool is_hypothesis() const;
  
  inline bool is_set() const
  {
    this->assert_invariants();
    return this->set_value.has_value();
  }
  
  inline unsigned int get() const;
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(56), static_cast<const char *>(__extension__"bool AnnotatedCell<9>::is_allowed(const unsigned int) const [size = 9]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(63), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(64), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(65), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_input(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_hypothesis(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(77), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_hypothesis(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(78), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_hypothesis(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_hypothesis(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->hypothesis = true;
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(91), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(92), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    (static_cast<bool>(!static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(93), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_deduced(const unsigned int) [size = 9]")));
    this->allowed_values.reset();
    this->allowed_values.set(static_cast<unsigned long>(value), true);
    this->set_value.operator=(std::optional<unsigned int>(value));
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline void set_propagated()
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(104), static_cast<const char *>(__extension__"void AnnotatedCell<9>::set_propagated() [size = 9]")));
    this->propagated = true;
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline bool is_propagated() const;
  
  inline void forbid(const unsigned int value)
  {
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
    (static_cast<bool>(value < 9U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(119), static_cast<const char *>(__extension__"void AnnotatedCell<9>::forbid(const unsigned int) [size = 9]")));
    (static_cast<bool>(static_cast<const AnnotatedCell<9> *>(this)->is_allowed(value)) ? void(0) : __assert_fail(static_cast<const char *>("is_allowed(value)"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(120), static_cast<const char *>(__extension__"void AnnotatedCell<9>::forbid(const unsigned int) [size = 9]")));
    this->allowed_values.reset(static_cast<unsigned long>(value));
    static_cast<const AnnotatedCell<9> *>(this)->assert_invariants();
  }
  
  inline unsigned int allowed_count() const;
  
  
  private: 
  inline void assert_invariants() const
  {
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.any()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(136), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(140), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail(static_cast<const char *>("set_value.has_value()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(145), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.count() == 1"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(150), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
      (static_cast<bool>(this->allowed_values.test(static_cast<unsigned long>(this->set_value.value()))) ? void(0) : __assert_fail(static_cast<const char *>("allowed_values.test(set_value.value())"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(151), static_cast<const char *>(__extension__"void AnnotatedCell<9>::assert_invariants() const [size = 9]")));
    } 
    
  }
  
  
  private: 
  std::bitset<9> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool hypothesis;
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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 187, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  inline AnnotatedSudoku<size> & current()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 192, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  inline int height() const
  {
    return this->stack.size();
  }
  
  
  public: 
  struct Saved
  {
    inline explicit Saved(const Stack<size> & stack)
    : begin_{std::next(stack.stack.rbegin())}
    , end_{stack.stack.rend()}
    {
    }
    
    inline typename std::vector<AnnotatedSudoku<size> >::const_reverse_iterator begin()
    {
      return this->begin_;
    }
    
    inline typename std::vector<AnnotatedSudoku<size> >::const_reverse_iterator end()
    {
      return this->end_;
    }
    
    
    private: 
    const typename std::vector<AnnotatedSudoku<size> >::const_reverse_iterator begin_;
    const typename std::vector<AnnotatedSudoku<size> >::const_reverse_iterator end_;
  };
  
  inline Saved saved() const
  {
    return Saved(*this);
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(current());
  }
  
  inline void pop()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 220, __extension____PRETTY_FUNCTION__));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<AnnotatedSudoku<size> > stack;
};

/* First instantiated from: html-explainer.cpp:1131 */
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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(187), static_cast<const char *>(__extension__"const AnnotatedSudoku<size> &Stack<4>::current() const [size = 4]")));
    return this->stack.back();
  }
  
  inline Sudoku<AnnotatedCell<4>, 4> & current()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(192), static_cast<const char *>(__extension__"AnnotatedSudoku<size> &Stack<4>::current() [size = 4]")));
    return this->stack.back();
  }
  
  inline int height() const
  {
    return static_cast<int>(this->stack.size());
  }
  
  
  public: 
  struct Saved
  {
    inline explicit Saved(const Stack<4> & stack)
    : begin_{static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >>(std::next<std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > >(stack.stack.rbegin(), static_cast<long>(1)))}
    , end_{static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >>(stack.stack.rend())}
    {
    }
    
    inline std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > begin()
    {
      return std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >(this->begin_);
    }
    
    inline std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > end()
    {
      return std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >(this->end_);
    }
    
    
    private: 
    const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > begin_;
    const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > end_;
    public: 
    // inline Saved & operator=(const Saved &) /* noexcept */ = delete;
    // inline Saved & operator=(Saved &&) /* noexcept */ = delete;
  };
  
  inline Saved saved() const
  {
    return Saved(*this);
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(static_cast<const Sudoku<AnnotatedCell<4>, 4>>(this->current()));
  }
  
  inline void pop()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(220), static_cast<const char *>(__extension__"void Stack<4>::pop() [size = 4]")));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > stack;
  public: 
  // inline constexpr ~Stack() noexcept = default;
};

#endif
/* First instantiated from: html-explainer.cpp:1131 */
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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(187), static_cast<const char *>(__extension__"const AnnotatedSudoku<size> &Stack<9>::current() const [size = 9]")));
    return this->stack.back();
  }
  
  inline Sudoku<AnnotatedCell<9>, 9> & current()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(192), static_cast<const char *>(__extension__"AnnotatedSudoku<size> &Stack<9>::current() [size = 9]")));
    return this->stack.back();
  }
  
  inline int height() const
  {
    return static_cast<int>(this->stack.size());
  }
  
  
  public: 
  struct Saved
  {
    inline explicit Saved(const Stack<9> & stack)
    : begin_{static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >>(std::next<std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > >(stack.stack.rbegin(), static_cast<long>(1)))}
    , end_{static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >>(stack.stack.rend())}
    {
    }
    
    inline std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > begin()
    {
      return std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >(this->begin_);
    }
    
    inline std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > end()
    {
      return std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >(this->end_);
    }
    
    
    private: 
    const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > begin_;
    const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > end_;
    public: 
    // inline Saved & operator=(const Saved &) /* noexcept */ = delete;
    // inline Saved & operator=(Saved &&) /* noexcept */ = delete;
  };
  
  inline Saved saved() const
  {
    return Saved(*this);
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(static_cast<const Sudoku<AnnotatedCell<9>, 9>>(this->current()));
  }
  
  inline void pop()
  {
    (static_cast<bool>(!static_cast<const std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(220), static_cast<const char *>(__extension__"void Stack<9>::pop() [size = 9]")));
    this->stack.pop_back();
  }
  
  
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
  
  
}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
# 12 "src/explanation/explanation.hpp"
# 13 "src/explanation/explanation.hpp"


template<unsigned int size>
struct Explanation
{
  struct SingleValueDeduction
  {
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
  };
  
  struct SinglePlaceDeduction
  {
    unsigned int region;
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
  };
  
  struct PropagationTarget
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<SingleValueDeduction> single_value_deductions;
    std::vector<SinglePlaceDeduction> single_place_deductions;
  };
  
  struct Propagation
  {
    std::pair<unsigned int, unsigned int> source;
    unsigned int value;
    std::vector<PropagationTarget> targets;
  };
  
  struct Exploration;
  struct Hypothesis
  {
    unsigned int value;
    std::vector<Propagation> propagations;
    std::optional<Exploration> exploration;
    bool successful;
  };
  
  struct Exploration
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    std::vector<Hypothesis> explored_hypotheses;
  };
  
  Sudoku<ValueCell, size> inputs;
  std::vector<Propagation> propagations;
  std::optional<Exploration> exploration;
  
  public: 
  class Builder
  {
    
    private: 
    struct Frame
    {
      inline Frame(std::vector<Propagation> * propagations_, std::optional<Exploration> * exploration_, Explanation::Hypothesis * hypothesis_)
      : propagations{propagations_}
      , exploration{exploration_}
      , hypothesis{hypothesis_}
      , sudoku_is_solved{static_cast<bool *>(nullptr)}
      {
        (static_cast<bool>(this->propagations) ? void(0) : __assert_fail("propagations", "src/explanation/explanation.hpp", 78, __extension____PRETTY_FUNCTION__));
        (static_cast<bool>(this->exploration) ? void(0) : __assert_fail("exploration", "src/explanation/explanation.hpp", 79, __extension____PRETTY_FUNCTION__));
        (static_cast<bool>(this->hypothesis) ? void(0) : __assert_fail("hypothesis", "src/explanation/explanation.hpp", 80, __extension____PRETTY_FUNCTION__));
      }
      
      inline Frame(std::vector<Propagation> * propagations_, std::optional<Exploration> * exploration_)
      : propagations{propagations_}
      , exploration{exploration_}
      , hypothesis{nullptr}
      , sudoku_is_solved{static_cast<bool *>(nullptr)}
      {
        (static_cast<bool>(this->propagations) ? void(0) : __assert_fail("propagations", "src/explanation/explanation.hpp", 92, __extension____PRETTY_FUNCTION__));
        (static_cast<bool>(this->exploration) ? void(0) : __assert_fail("exploration", "src/explanation/explanation.hpp", 93, __extension____PRETTY_FUNCTION__));
      }
      
      std::vector<Propagation> * propagations;
      std::optional<Exploration> * exploration;
      Explanation::Hypothesis * hypothesis;
      bool * sudoku_is_solved;
    };
    
    
    public: 
    inline Builder()
    : explanation{}
    , stack{1, {&this->explanation.propagations, &this->explanation.exploration}}
    {
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
    
    
    public: 
    inline Explanation<size> get()
    {
      (static_cast<bool>(this->stack.size() == 1) ? void(0) : __assert_fail("stack.size() == 1", "src/explanation/explanation.hpp", 124, __extension____PRETTY_FUNCTION__));
      return std::move(this->explanation);
    }
    
    
    private: 
    Explanation<size> explanation;
    std::vector<Frame> stack;
  };
  
};

/* First instantiated from: html-explainer.cpp:996 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct Explanation<4>
{
  struct SingleValueDeduction
  {
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
  };
  
  struct SinglePlaceDeduction
  {
    unsigned int region;
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
  };
  
  struct PropagationTarget
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<SingleValueDeduction, std::allocator<SingleValueDeduction> > single_value_deductions;
    std::vector<SinglePlaceDeduction, std::allocator<SinglePlaceDeduction> > single_place_deductions;
  };
  
  struct Propagation
  {
    std::pair<unsigned int, unsigned int> source;
    unsigned int value;
    std::vector<PropagationTarget, std::allocator<PropagationTarget> > targets;
  };
  
  struct Exploration
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    std::vector<Hypothesis, std::allocator<Hypothesis> > explored_hypotheses;
  };
  
  struct Hypothesis
  {
    unsigned int value;
    std::vector<Propagation, std::allocator<Propagation> > propagations;
    std::optional<Exploration> exploration;
    bool successful;
  };
  
  struct Exploration;
  Sudoku<ValueCell, 4> inputs;
  std::vector<Propagation, std::allocator<Propagation> > propagations;
  std::optional<Exploration> exploration;
  
  public: 
  class Builder;
};

#endif
/* First instantiated from: html-explainer.cpp:996 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct Explanation<9>
{
  struct SingleValueDeduction
  {
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
  };
  
  struct SinglePlaceDeduction
  {
    unsigned int region;
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
  };
  
  struct PropagationTarget
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<SingleValueDeduction, std::allocator<SingleValueDeduction> > single_value_deductions;
    std::vector<SinglePlaceDeduction, std::allocator<SinglePlaceDeduction> > single_place_deductions;
  };
  
  struct Propagation
  {
    std::pair<unsigned int, unsigned int> source;
    unsigned int value;
    std::vector<PropagationTarget, std::allocator<PropagationTarget> > targets;
  };
  
  struct Exploration
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    std::vector<Hypothesis, std::allocator<Hypothesis> > explored_hypotheses;
  };
  
  struct Hypothesis
  {
    unsigned int value;
    std::vector<Propagation, std::allocator<Propagation> > propagations;
    std::optional<Exploration> exploration;
    bool successful;
  };
  
  struct Exploration;
  Sudoku<ValueCell, 9> inputs;
  std::vector<Propagation, std::allocator<Propagation> > propagations;
  std::optional<Exploration> exploration;
  
  public: 
  class Builder;
};

#endif



#endif  // EXPLANATION_EXPLANATION_HPP_
# 9 "src/explanation/html-explainer.hpp"


template<unsigned int size>
void explain_as_html(const Explanation<size> &, const std::filesystem::path &, unsigned int width, unsigned int height);
;

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
# 4 "src/explanation/html-explainer.cpp"

#include <cairomm/cairomm.h>

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include <boost/format.hpp>

# 1 "src/explanation/art.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_ART_HPP_
#define EXPLANATION_ART_HPP_

#include <cairomm/cairomm.h>

#include <tuple>
#include <vector>

# 12 "src/explanation/art.hpp"


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
  
  /* First instantiated from: html-explainer.cpp:1093 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<4>(unsigned int);
  #endif
  
  
  /* First instantiated from: html-explainer.cpp:1093 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<9>(unsigned int);
  #endif
  
  struct DrawOptions
  {
    double grid_size;
    bool possible = false;
    bool bold_todo = false;
    bool inputs = true;
    bool hypotheses = true;
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
  
  /* First instantiated from: html-explainer.cpp:1099 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<4>(std::shared_ptr<Cairo::Context>, const Sudoku<AnnotatedCell<4>, 4> &, const DrawOptions &);
  #endif
  
  
  /* First instantiated from: html-explainer.cpp:1099 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<9>(std::shared_ptr<Cairo::Context>, const Sudoku<AnnotatedCell<9>, 9> &, const DrawOptions &);
  #endif
  
  
}  // namespace art

#endif  // EXPLANATION_ART_HPP_
# 15 "src/explanation/html-explainer.cpp"


template<unsigned int size>
class HtmlExplainer
{
  
  public: 
  inline HtmlExplainer(const Explanation<size> & explanation_, const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : explanation{explanation_}
  , directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n"));
  }
  
  inline ~HtmlExplainer()
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("</body></html>\n"));
  }
  
  
  public: 
  inline void explain()
  {
    {
      auto && __range0 = this->explanation.inputs.cells();
      for(; ; ) {
        const auto & cell;
        const std::optional<unsigned int> value = cell.get();
        if(static_cast<bool>(value.operator bool())) {
          this->stack.current().cell(cell.coordinates()).set_input(value.operator*());
        } 
        
      }
      
    }
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Input grid</h1>\n"));
    this->make_image("input.png", {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"input.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Possible values</h1>\n"));
    this->make_image("initial-possible.png", {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"initial-possible.png\"/></p>\n"));
    explain(this->explanation.propagations);
    explain(this->explanation.exploration);
  }
  
  
  private: 
  inline void explain(const std::vector<typename Explanation<size>::Propagation> & propagations)
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Propagation</h1>\n"));
    {
      auto && __range0 = propagations;
      for(; ; ) {
        const auto & propagation;
        const auto __propagation0 = propagation.source;
        (((std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Propagation from (")) << (src_row + 1)) << ", ") << (src_col + 1)) << ")</h2>\n";
        const unsigned int value = propagation.value;
        {
          auto && __range1 = propagation.targets;
          for(; ; ) {
            const auto & target;
            this->stack.current().cell(target.cell).forbid(value);
            const auto __target0 = target.cell;
            const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = str((((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("propagation-%1%-%2%--%3%-%4%.png"))) % (src_row + 1)) % (src_col + 1)) % (tgt_row + 1)) % (tgt_col + 1));
            this->make_image(image_name, {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */, /* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */, /* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */, /* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */, /* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
            std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
            {
              auto && __range2 = target.single_value_deductions;
              for(; ; ) {
                const auto & deduction;
                this->stack.current().cell(deduction.cell).set_deduced(deduction.value);
                if(deduction.solved) {
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
                  this->make_image("solved.png", {}, {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
                } 
                
              }
              
            }
            {
              auto && __range2 = target.single_place_deductions;
              for(; ; ) {
                const auto & deduction;
                this->stack.current().cell(deduction.cell).set_deduced(deduction.value);
                if(deduction.solved) {
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
                  this->make_image("solved.png", {}, {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
                } 
                
              }
              
            }
          }
          
        }
        this->stack.current().cell(propagation.source).set_propagated();
      }
      
    }
  }
  
  inline void explain(const std::optional<typename Explanation<size>::Exploration> & exploration)
  {
    if(exploration.has_value()) {
      explain(*exploration);
    } 
    
  }
  
  inline void explain(const typename Explanation<size>::Exploration & exploration)
  {
    const auto __exploration0 = exploration.cell;
    (((std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Exploration for (")) << (row + 1)) << ", ") << (col + 1)) << ")</h1>\n";
    {
      auto && __range0 = exploration.explored_hypotheses;
      for(; ; ) {
        const auto & hypothesis;
        this->stack.push();
        this->stack.current().cell(exploration.cell).set_hypothesis(hypothesis.value);
        (((((std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Trying ")) << (hypothesis.value + 1)) << " for (") << (row + 1)) << ", ") << (col + 1)) << ")</h2>\n";
        const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = str(((boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("exploration-%1%-%2%--%3%.png"))) % (row + 1)) % (col + 1)) % (hypothesis.value + 1));
        this->make_image(image_name, {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */, /* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */, /* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
        std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
        explain(hypothesis.propagations);
        explain(hypothesis.exploration);
        this->stack.pop();
      }
      
    }
  }
  
  
  private: 
  struct MakeImageOptions
  {
    bool draw_stack = true;
  };
  
  inline void make_image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & name, art::DrawOptions draw_options, const MakeImageOptions & options) const
  {
    (static_cast<bool>(static_cast<const std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >>(this->generated_image_names).count(name) == static_cast<unsigned long>(0)) ? void(0) : __assert_fail("generated_image_names.count(name) == 0", "src/explanation/html-explainer.cpp", 146, __extension____PRETTY_FUNCTION__));
    this->generated_image_names.insert(name);
    std::shared_ptr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width), static_cast<int>(this->frame_height));
    std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(surface))));
    const unsigned int margin = static_cast<const unsigned int>(10);
    const unsigned int viewport_width = this->frame_width - (static_cast<unsigned int>(2) * margin);
    const unsigned int viewport_height = this->frame_height - (static_cast<unsigned int>(2) * margin);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->save();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
    const double grid_size = art::round_grid_size<size>(viewport_height);
    if(options.draw_stack && (this->stack.height() > 1)) {
      {
        Cairo::SaveGuard guard = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
        const double small_grid_size = art::round_grid_size<size>((static_cast<double>(viewport_width) - grid_size) - (static_cast<double>(static_cast<unsigned int>(3) * margin)));
        {
          auto && __range1 = this->stack.saved();
          for(; ; ) {
            const auto & saved;
            art::draw(cr, saved, {/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: DesignatedInitExpr */});
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(0), small_grid_size + static_cast<double>(margin));
          }
          
        }
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate((static_cast<double>(viewport_width) - grid_size), (static_cast<double>(viewport_height) - grid_size) / static_cast<double>(2));
    } else {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate((static_cast<double>(viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(viewport_height) - grid_size) / static_cast<double>(2));
    } 
    
    draw_options.grid_size = grid_size;
    art::draw(cr, this->stack.current(), draw_options);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->restore();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(viewport_width), static_cast<double>(viewport_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgba(static_cast<double>(1), 0.5, 0.5, 0.5);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
    static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path &&>((operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(name, std::filesystem::path::auto_format))))).string()));
  }
  
  
  private: 
  const Explanation<size> & explanation;
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<size> stack;
  mutable std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > generated_image_names;
};

/* First instantiated from: html-explainer.cpp:1144 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class HtmlExplainer<4>
{
  
  public: 
  inline HtmlExplainer(const Explanation<4> & explanation_, const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : explanation{explanation_}
  , directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{Stack<4>()}
  , generated_image_names{std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >()}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n"));
  }
  
  inline ~HtmlExplainer()
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("</body></html>\n"));
  }
  
  
  public: 
  inline void explain()
  {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range0 = static_cast<const SudokuBase<ValueCell, 4>&>(this->explanation.inputs).cells();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
        if(static_cast<bool>(value.operator bool())) {
          static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(this->stack.current()).cell(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()))).set_input(value.operator*());
        } 
        
      }
      
    }
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Input grid</h1>\n"));
    static_cast<const HtmlExplainer<4> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("input.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, {false}, {false}, false, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"input.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Possible values</h1>\n"));
    static_cast<const HtmlExplainer<4> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("initial-possible.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, true, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"initial-possible.png\"/></p>\n"));
    this->explain(this->explanation.propagations);
    this->explain(this->explanation.exploration);
  }
  
  
  private: 
  inline void explain(const std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > & propagations)
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Propagation</h1>\n"));
    {
      const std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > & __range0 = propagations;
      __gnu_cxx::__normal_iterator<const Explanation<4>::Propagation *, std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<const Explanation<4>::Propagation *, std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::Propagation *, std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::Propagation *, std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > >>(__end0)); __begin0.operator++()) {
        const Explanation<4>::Propagation & propagation = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::Propagation *, std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > >>(__begin0).operator*();
        const std::pair<unsigned int, unsigned int> __propagation0 = std::pair<unsigned int, unsigned int>(propagation.source);
        const unsigned int && src_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__propagation0));
        const unsigned int && src_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__propagation0));
        std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Propagation from (")).operator<<(src_row + static_cast<unsigned int>(1)), static_cast<const char *>(", ")).operator<<(src_col + static_cast<unsigned int>(1)), static_cast<const char *>(")</h2>\n"));
        const unsigned int value = propagation.value;
        {
          const std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > & __range1 = propagation.targets;
          __gnu_cxx::__normal_iterator<const Explanation<4>::PropagationTarget *, std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > > __begin0 = __range1.begin();
          __gnu_cxx::__normal_iterator<const Explanation<4>::PropagationTarget *, std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > > __end0 = __range1.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::PropagationTarget *, std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::PropagationTarget *, std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > >>(__end0)); __begin0.operator++()) {
            const Explanation<4>::PropagationTarget & target = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::PropagationTarget *, std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > >>(__begin0).operator*();
            static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(this->stack.current()).cell(target.cell)).forbid(value);
            const std::pair<unsigned int, unsigned int> __target0 = std::pair<unsigned int, unsigned int>(target.cell);
            const unsigned int && tgt_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__target0));
            const unsigned int && tgt_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__target0));
            const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(boost::str<char, std::char_traits<char>, std::allocator<char> >(static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("propagation-%1%-%2%--%3%-%4%.png"))).operator%(static_cast<const unsigned int>((src_row + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((src_col + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((tgt_row + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((tgt_col + static_cast<unsigned int>(1)))))));
            static_cast<const HtmlExplainer<4> *>(this)->make_image(image_name, {0.0, true, true, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(propagation.source)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{target.cell, value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{propagation.source, target.cell, value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
            std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
            {
              const std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > & __range2 = target.single_value_deductions;
              __gnu_cxx::__normal_iterator<const Explanation<4>::SingleValueDeduction *, std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > > __begin0 = __range2.begin();
              __gnu_cxx::__normal_iterator<const Explanation<4>::SingleValueDeduction *, std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > > __end0 = __range2.end();
              for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::SingleValueDeduction *, std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::SingleValueDeduction *, std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > >>(__end0)); __begin0.operator++()) {
                const Explanation<4>::SingleValueDeduction & deduction = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::SingleValueDeduction *, std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > >>(__begin0).operator*();
                static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(this->stack.current()).cell(deduction.cell)).set_deduced(deduction.value);
                if(deduction.solved) {
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
                  static_cast<const HtmlExplainer<4> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solved.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, {false}, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {false});
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
                } 
                
              }
              
            }
            {
              const std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > & __range2 = target.single_place_deductions;
              __gnu_cxx::__normal_iterator<const Explanation<4>::SinglePlaceDeduction *, std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > > __begin0 = __range2.begin();
              __gnu_cxx::__normal_iterator<const Explanation<4>::SinglePlaceDeduction *, std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > > __end0 = __range2.end();
              for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::SinglePlaceDeduction *, std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::SinglePlaceDeduction *, std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > >>(__end0)); __begin0.operator++()) {
                const Explanation<4>::SinglePlaceDeduction & deduction = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::SinglePlaceDeduction *, std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > >>(__begin0).operator*();
                static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(this->stack.current()).cell(deduction.cell)).set_deduced(deduction.value);
                if(deduction.solved) {
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
                  static_cast<const HtmlExplainer<4> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solved.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, {false}, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {false});
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
                } 
                
              }
              
            }
          }
          
        }
        static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(this->stack.current()).cell(propagation.source)).set_propagated();
      }
      
    }
  }
  
  inline void explain(const std::optional<Explanation<4>::Exploration> & exploration)
  {
    if(exploration.has_value()) {
      this->explain(exploration.operator*());
    } 
    
  }
  
  inline void explain(const typename Explanation<4U>::Exploration & exploration)
  {
    const std::pair<unsigned int, unsigned int> __exploration0 = std::pair<unsigned int, unsigned int>(exploration.cell);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__exploration0));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__exploration0));
    std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Exploration for (")).operator<<(row + static_cast<unsigned int>(1)), static_cast<const char *>(", ")).operator<<(col + static_cast<unsigned int>(1)), static_cast<const char *>(")</h1>\n"));
    {
      const std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > & __range0 = exploration.explored_hypotheses;
      __gnu_cxx::__normal_iterator<const Explanation<4>::Hypothesis *, std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<const Explanation<4>::Hypothesis *, std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::Hypothesis *, std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::Hypothesis *, std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > >>(__end0)); __begin0.operator++()) {
        const Explanation<4>::Hypothesis & hypothesis = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<4>::Hypothesis *, std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > >>(__begin0).operator*();
        this->stack.push();
        static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(this->stack.current()).cell(exploration.cell)).set_hypothesis(hypothesis.value);
        std::operator<<(std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Trying ")).operator<<(hypothesis.value + static_cast<unsigned int>(1)), static_cast<const char *>(" for (")).operator<<(row + static_cast<unsigned int>(1)), static_cast<const char *>(", ")).operator<<(col + static_cast<unsigned int>(1)), static_cast<const char *>(")</h2>\n"));
        const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(boost::str<char, std::char_traits<char>, std::allocator<char> >(static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("exploration-%1%-%2%--%3%.png"))).operator%(static_cast<const unsigned int>((row + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((col + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((hypothesis.value + static_cast<unsigned int>(1)))))));
        static_cast<const HtmlExplainer<4> *>(this)->make_image(image_name, {0.0, true, true, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(exploration.cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
        std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
        this->explain(hypothesis.propagations);
        this->explain(hypothesis.exploration);
        this->stack.pop();
      }
      
    }
  }
  
  
  private: 
  struct MakeImageOptions
  {
    bool draw_stack = true;
  };
  
  inline void make_image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & name, art::DrawOptions draw_options, const MakeImageOptions & options) const
  {
    (static_cast<bool>(static_cast<const std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >>(this->generated_image_names).count(name) == static_cast<unsigned long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("generated_image_names.count(name) == 0"), static_cast<const char *>("src/explanation/html-explainer.cpp"), static_cast<unsigned int>(146), static_cast<const char *>(__extension__"void HtmlExplainer<4>::make_image(const std::string &, art::DrawOptions, const MakeImageOptions &) const [size = 4]")));
    this->generated_image_names.insert(name);
    std::shared_ptr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width), static_cast<int>(this->frame_height));
    std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(surface))));
    const unsigned int margin = static_cast<const unsigned int>(10);
    const unsigned int viewport_width = this->frame_width - (static_cast<unsigned int>(2) * margin);
    const unsigned int viewport_height = this->frame_height - (static_cast<unsigned int>(2) * margin);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->save();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
    const double grid_size = art::round_grid_size<4U>(viewport_height);
    if(options.draw_stack && (this->stack.height() > 1)) {
      {
        Cairo::SaveGuard guard = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
        const double small_grid_size = art::round_grid_size<4U>(static_cast<unsigned int>((static_cast<double>(viewport_width) - grid_size) - (static_cast<double>(static_cast<unsigned int>(3) * margin))));
        {
          Saved && __range1 = this->stack.saved();
          std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > __begin0 = __range1.begin();
          std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > > __end0 = __range1.end();
          for(; !std::operator==(static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >>(__begin0), static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >>(__end0)); __begin0.operator++()) {
            const Sudoku<AnnotatedCell<4>, 4> & saved = static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<4>, 4> *, std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > > >>(__begin0).operator*();
            art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(cr)), saved, {small_grid_size, {false}, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(0), small_grid_size + static_cast<double>(margin));
          }
          
        }
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate((static_cast<double>(viewport_width) - grid_size), (static_cast<double>(viewport_height) - grid_size) / static_cast<double>(2));
    } else {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate((static_cast<double>(viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(viewport_height) - grid_size) / static_cast<double>(2));
    } 
    
    draw_options.grid_size = grid_size;
    art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(cr)), this->stack.current(), static_cast<const art::DrawOptions>(draw_options));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->restore();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(viewport_width), static_cast<double>(viewport_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgba(static_cast<double>(1), 0.5, 0.5, 0.5);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
    static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path &&>((operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(name, std::filesystem::path::auto_format))))).string()));
  }
  
  
  private: 
  const Explanation<4> & explanation;
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<4> stack;
  mutable std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > generated_image_names;
  public: 
  // inline HtmlExplainer(const HtmlExplainer<4> &) /* noexcept */ = delete;
  // inline HtmlExplainer<4> & operator=(const HtmlExplainer<4> &) /* noexcept */ = delete;
};

#endif
/* First instantiated from: html-explainer.cpp:1144 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class HtmlExplainer<9>
{
  
  public: 
  inline HtmlExplainer(const Explanation<9> & explanation_, const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : explanation{explanation_}
  , directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{Stack<9>()}
  , generated_image_names{std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >()}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n"));
  }
  
  inline ~HtmlExplainer()
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("</body></html>\n"));
  }
  
  
  public: 
  inline void explain()
  {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range0 = static_cast<const SudokuBase<ValueCell, 9>&>(this->explanation.inputs).cells();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).begin();
      boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range0).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_1, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
        if(static_cast<bool>(value.operator bool())) {
          static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(this->stack.current()).cell(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()))).set_input(value.operator*());
        } 
        
      }
      
    }
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Input grid</h1>\n"));
    static_cast<const HtmlExplainer<9> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("input.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, {false}, {false}, false, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"input.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Possible values</h1>\n"));
    static_cast<const HtmlExplainer<9> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("initial-possible.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, true, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"initial-possible.png\"/></p>\n"));
    this->explain(this->explanation.propagations);
    this->explain(this->explanation.exploration);
  }
  
  
  private: 
  inline void explain(const std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > & propagations)
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Propagation</h1>\n"));
    {
      const std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > & __range0 = propagations;
      __gnu_cxx::__normal_iterator<const Explanation<9>::Propagation *, std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<const Explanation<9>::Propagation *, std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::Propagation *, std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::Propagation *, std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > >>(__end0)); __begin0.operator++()) {
        const Explanation<9>::Propagation & propagation = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::Propagation *, std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > >>(__begin0).operator*();
        const std::pair<unsigned int, unsigned int> __propagation0 = std::pair<unsigned int, unsigned int>(propagation.source);
        const unsigned int && src_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__propagation0));
        const unsigned int && src_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__propagation0));
        std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Propagation from (")).operator<<(src_row + static_cast<unsigned int>(1)), static_cast<const char *>(", ")).operator<<(src_col + static_cast<unsigned int>(1)), static_cast<const char *>(")</h2>\n"));
        const unsigned int value = propagation.value;
        {
          const std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > & __range1 = propagation.targets;
          __gnu_cxx::__normal_iterator<const Explanation<9>::PropagationTarget *, std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > > __begin0 = __range1.begin();
          __gnu_cxx::__normal_iterator<const Explanation<9>::PropagationTarget *, std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > > __end0 = __range1.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::PropagationTarget *, std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::PropagationTarget *, std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > >>(__end0)); __begin0.operator++()) {
            const Explanation<9>::PropagationTarget & target = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::PropagationTarget *, std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > >>(__begin0).operator*();
            static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(this->stack.current()).cell(target.cell)).forbid(value);
            const std::pair<unsigned int, unsigned int> __target0 = std::pair<unsigned int, unsigned int>(target.cell);
            const unsigned int && tgt_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__target0));
            const unsigned int && tgt_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__target0));
            const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(boost::str<char, std::char_traits<char>, std::allocator<char> >(static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("propagation-%1%-%2%--%3%-%4%.png"))).operator%(static_cast<const unsigned int>((src_row + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((src_col + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((tgt_row + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((tgt_col + static_cast<unsigned int>(1)))))));
            static_cast<const HtmlExplainer<9> *>(this)->make_image(image_name, {0.0, true, true, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(propagation.source)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{target.cell, value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{propagation.source, target.cell, value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
            std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
            {
              const std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > & __range2 = target.single_value_deductions;
              __gnu_cxx::__normal_iterator<const Explanation<9>::SingleValueDeduction *, std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > > __begin0 = __range2.begin();
              __gnu_cxx::__normal_iterator<const Explanation<9>::SingleValueDeduction *, std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > > __end0 = __range2.end();
              for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::SingleValueDeduction *, std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::SingleValueDeduction *, std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > >>(__end0)); __begin0.operator++()) {
                const Explanation<9>::SingleValueDeduction & deduction = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::SingleValueDeduction *, std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > >>(__begin0).operator*();
                static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(this->stack.current()).cell(deduction.cell)).set_deduced(deduction.value);
                if(deduction.solved) {
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
                  static_cast<const HtmlExplainer<9> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solved.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, {false}, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {false});
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
                } 
                
              }
              
            }
            {
              const std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > & __range2 = target.single_place_deductions;
              __gnu_cxx::__normal_iterator<const Explanation<9>::SinglePlaceDeduction *, std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > > __begin0 = __range2.begin();
              __gnu_cxx::__normal_iterator<const Explanation<9>::SinglePlaceDeduction *, std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > > __end0 = __range2.end();
              for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::SinglePlaceDeduction *, std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::SinglePlaceDeduction *, std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > >>(__end0)); __begin0.operator++()) {
                const Explanation<9>::SinglePlaceDeduction & deduction = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::SinglePlaceDeduction *, std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > >>(__begin0).operator*();
                static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(this->stack.current()).cell(deduction.cell)).set_deduced(deduction.value);
                if(deduction.solved) {
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
                  static_cast<const HtmlExplainer<9> *>(this)->make_image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solved.png"), static_cast<const std::allocator<char>>(std::allocator<char>())), {0.0, {false}, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {false});
                  std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
                } 
                
              }
              
            }
          }
          
        }
        static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(this->stack.current()).cell(propagation.source)).set_propagated();
      }
      
    }
  }
  
  inline void explain(const std::optional<Explanation<9>::Exploration> & exploration)
  {
    if(exploration.has_value()) {
      this->explain(exploration.operator*());
    } 
    
  }
  
  inline void explain(const typename Explanation<9U>::Exploration & exploration)
  {
    const std::pair<unsigned int, unsigned int> __exploration0 = std::pair<unsigned int, unsigned int>(exploration.cell);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__exploration0));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__exploration0));
    std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Exploration for (")).operator<<(row + static_cast<unsigned int>(1)), static_cast<const char *>(", ")).operator<<(col + static_cast<unsigned int>(1)), static_cast<const char *>(")</h1>\n"));
    {
      const std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > & __range0 = exploration.explored_hypotheses;
      __gnu_cxx::__normal_iterator<const Explanation<9>::Hypothesis *, std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > > __begin0 = __range0.begin();
      __gnu_cxx::__normal_iterator<const Explanation<9>::Hypothesis *, std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > > __end0 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::Hypothesis *, std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::Hypothesis *, std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > >>(__end0)); __begin0.operator++()) {
        const Explanation<9>::Hypothesis & hypothesis = static_cast<const __gnu_cxx::__normal_iterator<const Explanation<9>::Hypothesis *, std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > >>(__begin0).operator*();
        this->stack.push();
        static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(this->stack.current()).cell(exploration.cell)).set_hypothesis(hypothesis.value);
        std::operator<<(std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Trying ")).operator<<(hypothesis.value + static_cast<unsigned int>(1)), static_cast<const char *>(" for (")).operator<<(row + static_cast<unsigned int>(1)), static_cast<const char *>(", ")).operator<<(col + static_cast<unsigned int>(1)), static_cast<const char *>(")</h2>\n"));
        const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(boost::str<char, std::char_traits<char>, std::allocator<char> >(static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("exploration-%1%-%2%--%3%.png"))).operator%(static_cast<const unsigned int>((row + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((col + static_cast<unsigned int>(1)))).operator%(static_cast<const unsigned int>((hypothesis.value + static_cast<unsigned int>(1)))))));
        static_cast<const HtmlExplainer<9> *>(this)->make_image(image_name, {0.0, true, true, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(exploration.cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}}, {{true}});
        std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
        this->explain(hypothesis.propagations);
        this->explain(hypothesis.exploration);
        this->stack.pop();
      }
      
    }
  }
  
  
  private: 
  struct MakeImageOptions
  {
    bool draw_stack = true;
  };
  
  inline void make_image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & name, art::DrawOptions draw_options, const MakeImageOptions & options) const
  {
    (static_cast<bool>(static_cast<const std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >>(this->generated_image_names).count(name) == static_cast<unsigned long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("generated_image_names.count(name) == 0"), static_cast<const char *>("src/explanation/html-explainer.cpp"), static_cast<unsigned int>(146), static_cast<const char *>(__extension__"void HtmlExplainer<9>::make_image(const std::string &, art::DrawOptions, const MakeImageOptions &) const [size = 9]")));
    this->generated_image_names.insert(name);
    std::shared_ptr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width), static_cast<int>(this->frame_height));
    std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(surface))));
    const unsigned int margin = static_cast<const unsigned int>(10);
    const unsigned int viewport_width = this->frame_width - (static_cast<unsigned int>(2) * margin);
    const unsigned int viewport_height = this->frame_height - (static_cast<unsigned int>(2) * margin);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->save();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
    const double grid_size = art::round_grid_size<9U>(viewport_height);
    if(options.draw_stack && (this->stack.height() > 1)) {
      {
        Cairo::SaveGuard guard = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
        const double small_grid_size = art::round_grid_size<9U>(static_cast<unsigned int>((static_cast<double>(viewport_width) - grid_size) - (static_cast<double>(static_cast<unsigned int>(3) * margin))));
        {
          Saved && __range1 = this->stack.saved();
          std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > __begin0 = __range1.begin();
          std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > > __end0 = __range1.end();
          for(; !std::operator==(static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >>(__begin0), static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >>(__end0)); __begin0.operator++()) {
            const Sudoku<AnnotatedCell<9>, 9> & saved = static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const Sudoku<AnnotatedCell<9>, 9> *, std::vector<Sudoku<AnnotatedCell<9>, 9>, std::allocator<Sudoku<AnnotatedCell<9>, 9> > > > >>(__begin0).operator*();
            art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(cr)), saved, {small_grid_size, {false}, {false}, {true}, {true}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(0), small_grid_size + static_cast<double>(margin));
          }
          
        }
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate((static_cast<double>(viewport_width) - grid_size), (static_cast<double>(viewport_height) - grid_size) / static_cast<double>(2));
    } else {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate((static_cast<double>(viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(viewport_height) - grid_size) / static_cast<double>(2));
    } 
    
    draw_options.grid_size = grid_size;
    art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(cr)), this->stack.current(), static_cast<const art::DrawOptions>(draw_options));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->restore();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(viewport_width), static_cast<double>(viewport_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgba(static_cast<double>(1), 0.5, 0.5, 0.5);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
    static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path &&>((operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(name, std::filesystem::path::auto_format))))).string()));
  }
  
  
  private: 
  const Explanation<9> & explanation;
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<9> stack;
  mutable std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > generated_image_names;
  public: 
  // inline HtmlExplainer(const HtmlExplainer<9> &) /* noexcept */ = delete;
  // inline HtmlExplainer<9> & operator=(const HtmlExplainer<9> &) /* noexcept */ = delete;
};

#endif


template<unsigned int size>
void explain_as_html(const Explanation<size> & explanation, const std::filesystem::path & directory_path, unsigned int frame_width, unsigned int frame_height)
{
  HtmlExplainer<size>(explanation, directory_path, frame_width, frame_height).explain();
}


/* First instantiated from: html-explainer.cpp:1147 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void explain_as_html<4>(const Explanation<4> & explanation, const std::filesystem::path & directory_path, unsigned int frame_width, unsigned int frame_height)
{
  HtmlExplainer<4>(explanation, directory_path, frame_width, frame_height).explain();
}
#endif


/* First instantiated from: html-explainer.cpp:1148 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void explain_as_html<9>(const Explanation<9> & explanation, const std::filesystem::path & directory_path, unsigned int frame_width, unsigned int frame_height)
{
  HtmlExplainer<9>(explanation, directory_path, frame_width, frame_height).explain();
}
#endif


template void explain_as_html<4>(const Explanation<4>&, const std::filesystem::path&, unsigned, unsigned);
template void explain_as_html<9>(const Explanation<9>&, const std::filesystem::path&, unsigned, unsigned);
