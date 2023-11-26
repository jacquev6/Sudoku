# 1 "src/explanation/video-explainer.cpp"
// Copyright 2023 Vincent Jacques

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

/* First instantiated from: video-explainer.cpp:530 */
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
  
  /* First instantiated from: video-explainer.cpp:262 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: video-explainer.cpp:267 */
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
  
  inline auto cells() const;
  
  inline auto cells();
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: video-explainer.cpp:530 */
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
  
  /* First instantiated from: video-explainer.cpp:262 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: video-explainer.cpp:267 */
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

/* First instantiated from: alloc_traits.h:850 */
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
/* First instantiated from: alloc_traits.h:850 */
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
    (static_cast<bool>(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(this->value).operator bool()) || (this->value.operator*() == value_)) ? void(0) : __assert_fail(static_cast<const char *>("!value || *value == value_"), static_cast<const char *>("src/puzzle/sudoku.hpp"), static_cast<unsigned int>(222), static_cast<const char *>(__extension__"void ValueCell::set(unsigned int)")));
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
  
  inline bool is_set() const;
  
  inline unsigned int get() const;
  
  inline bool is_allowed(const unsigned int value) const;
  
  inline void set_input(const unsigned int value);
  
  inline void set_deduced(const unsigned int value);
  
  inline void set_propagated();
  
  inline bool is_propagated() const;
  
  inline void forbid(const unsigned int value);
  
  inline unsigned int allowed_count() const;
  
  
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
  
  inline bool is_set() const;
  
  inline unsigned int get() const;
  
  inline bool is_allowed(const unsigned int value) const;
  
  inline void set_input(const unsigned int value);
  
  inline void set_deduced(const unsigned int value);
  
  inline void set_propagated();
  
  inline bool is_propagated() const;
  
  inline void forbid(const unsigned int value);
  
  inline unsigned int allowed_count() const;
  
  
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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "src/exploration/annotations.hpp", 199, __extension____PRETTY_FUNCTION__));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<AnnotatedSudoku<size> > stack;
};

/* First instantiated from: video-explainer.cpp:1040 */
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
  
  inline Sudoku<AnnotatedCell<4>, 4> & current();
  
  inline int height() const;
  
  
  public: 
  struct Saved;
  inline Saved saved() const;
  
  
  public: 
  inline void push();
  
  inline void pop();
  
  
  private: 
  std::vector<Sudoku<AnnotatedCell<4>, 4>, std::allocator<Sudoku<AnnotatedCell<4>, 4> > > stack;
  public: 
  // inline constexpr ~Stack() noexcept = default;
};

#endif
/* First instantiated from: video-explainer.cpp:1040 */
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
  
  inline Sudoku<AnnotatedCell<9>, 9> & current();
  
  inline int height() const;
  
  
  public: 
  struct Saved;
  inline Saved saved() const;
  
  
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
  
  /* First instantiated from: video-explainer.cpp:1136 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsSetInInput(const CellIsSetInInput<4> &) noexcept = default;
    // inline constexpr CellIsSetInInput(CellIsSetInInput<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1136 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr CellIsSetInInput(const CellIsSetInInput<9> &) noexcept = default;
    // inline constexpr CellIsSetInInput(CellIsSetInInput<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct InputsAreDone
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: video-explainer.cpp:1141 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr InputsAreDone(const InputsAreDone<4> &) noexcept = default;
    // inline constexpr InputsAreDone(InputsAreDone<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1141 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr InputsAreDone(const InputsAreDone<9> &) noexcept = default;
    // inline constexpr InputsAreDone(InputsAreDone<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: video-explainer.cpp:1207 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr PropagationStartsForSudoku(const PropagationStartsForSudoku<4> &) noexcept = default;
    // inline constexpr PropagationStartsForSudoku(PropagationStartsForSudoku<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1207 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr PropagationStartsForSudoku(const PropagationStartsForSudoku<9> &) noexcept = default;
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
  
  /* First instantiated from: video-explainer.cpp:1214 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationStartsForCell(const PropagationStartsForCell<4> &) noexcept = default;
    // inline constexpr PropagationStartsForCell(PropagationStartsForCell<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1214 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationStartsForCell(const PropagationStartsForCell<9> &) noexcept = default;
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
  
  /* First instantiated from: stl_vector.h:367 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellPropagates<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
    // inline constexpr CellPropagates(const CellPropagates<4> &) noexcept = default;
    // inline constexpr CellPropagates(CellPropagates<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: stl_vector.h:367 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellPropagates<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
    // inline constexpr CellPropagates(const CellPropagates<9> &) noexcept = default;
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
  
  /* First instantiated from: stl_vector.h:367 */
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
  /* First instantiated from: stl_vector.h:367 */
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
  
  /* First instantiated from: stl_vector.h:367 */
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
  /* First instantiated from: stl_vector.h:367 */
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
  
  /* First instantiated from: video-explainer.cpp:1340 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationIsDoneForCell(const PropagationIsDoneForCell<4> &) noexcept = default;
    // inline constexpr PropagationIsDoneForCell(PropagationIsDoneForCell<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1340 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr PropagationIsDoneForCell(const PropagationIsDoneForCell<9> &) noexcept = default;
    // inline constexpr PropagationIsDoneForCell(PropagationIsDoneForCell<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct PropagationIsDoneForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: video-explainer.cpp:1558 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(const PropagationIsDoneForSudoku<4> &) noexcept = default;
    // inline constexpr PropagationIsDoneForSudoku(PropagationIsDoneForSudoku<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1558 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(const PropagationIsDoneForSudoku<9> &) noexcept = default;
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
  
  /* First instantiated from: video-explainer.cpp:1565 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    // inline constexpr ExplorationStarts(const ExplorationStarts<4> &) noexcept(false) = default;
    // inline constexpr ExplorationStarts(ExplorationStarts<4> &&) noexcept = default;
    // inline constexpr ~ExplorationStarts() noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1565 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    // inline constexpr ExplorationStarts(const ExplorationStarts<9> &) noexcept(false) = default;
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
  
  /* First instantiated from: video-explainer.cpp:1572 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsMade(const HypothesisIsMade<4> &) noexcept = default;
    // inline constexpr HypothesisIsMade(HypothesisIsMade<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1572 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsMade(const HypothesisIsMade<9> &) noexcept = default;
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
  
  /* First instantiated from: video-explainer.cpp:1579 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsRejected(const HypothesisIsRejected<4> &) noexcept = default;
    // inline constexpr HypothesisIsRejected(HypothesisIsRejected<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1579 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsRejected(const HypothesisIsRejected<9> &) noexcept = default;
    // inline constexpr HypothesisIsRejected(HypothesisIsRejected<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct SudokuIsSolved
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: video-explainer.cpp:1586 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr SudokuIsSolved(const SudokuIsSolved<4> &) noexcept = default;
    // inline constexpr SudokuIsSolved(SudokuIsSolved<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1586 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<9>
  {
    void apply(Stack<9> *) const;
    
    // inline constexpr SudokuIsSolved(const SudokuIsSolved<9> &) noexcept = default;
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
  
  /* First instantiated from: video-explainer.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsAccepted(const HypothesisIsAccepted<4> &) noexcept = default;
    // inline constexpr HypothesisIsAccepted(HypothesisIsAccepted<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    // inline constexpr HypothesisIsAccepted(const HypothesisIsAccepted<9> &) noexcept = default;
    // inline constexpr HypothesisIsAccepted(HypothesisIsAccepted<9> &&) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct ExplorationIsDone
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  /* First instantiated from: video-explainer.cpp:1614 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(const ExplorationIsDone<4> &) noexcept = default;
    // inline constexpr ExplorationIsDone(ExplorationIsDone<4> &&) noexcept = default;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1614 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(const ExplorationIsDone<9> &) noexcept = default;
    // inline constexpr ExplorationIsDone(ExplorationIsDone<9> &&) noexcept = default;
  };
  
  #endif
  
}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
# 16 "src/explanation/video-explainer.hpp"
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
        __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > > __begin0 = __range0.begin();
        __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > > __end0 = __range0.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__end0)); __begin0.operator++()) {
          Serializer *& serializer = static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__begin0).operator*();
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



#endif  // EXPLANATION_VIDEO_EXPLAINER_HPP_
# 4 "src/explanation/video-explainer.cpp"

#include <tuple>
#include <vector>

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
  
  /* First instantiated from: video-explainer.cpp:1153 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<4>(std::shared_ptr<Cairo::Context>, const Sudoku<AnnotatedCell<4>, 4> &, const DrawOptions &);
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1153 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<9>(std::shared_ptr<Cairo::Context>, const Sudoku<AnnotatedCell<9>, 9> &, const DrawOptions &);
  #endif
  
  
}  // namespace art

#endif  // EXPLANATION_ART_HPP_
# 9 "src/explanation/video-explainer.cpp"


template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellIsSetInInput<size>& event) {
  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::InputsAreDone<size>& event) {
  VisitEventsGuard visit(this, event);

  Layout title{.above = {
    {"How to solve this Sudoku?", 40, Text::Bold},
    {"An automated explanation by @jacquev6", 20},
    {"https://github.com/jacquev6/Sudoku", 20},
  }};

  for (unsigned index = 0; index != quicken(75); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(title);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size
      });
  }

  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const unsigned transition_duration = quicken(12);
  for (unsigned index = 0; index != transition_duration; ++index) {
    const double ratio = (index + 1.) / (transition_duration + 1);

    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout_transition(title, propagate, ratio);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size
      });
  }

  for (unsigned index = 0; index != quicken(12); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size
      });
  }

  for (unsigned index = 0; index != quicken(12); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.before.current(),
      {
        .grid_size = grid_size,
        .possible = true,
        .bold_todo = true
      });
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationStartsForSudoku<size>& event) {
  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationStartsForCell<size>& event) {
  flush_pending_cell_is_deduced_from_single_allowed_value_events();
  flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  VisitEventsGuard visit(this, event);

  Layout propagate{.below = {{"Propagate constraints", 20}}};

  if (cell_propagations_handled < quicken(3)) {
    const double widths[] = {2, 4, 5, 3, 2};
    const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);
    for (unsigned index = 0; index != quicken(3) * widths_count; ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);
      art::draw(
        context,
        visit.before.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {event.cell},
          .circled_cells_line_width = widths[index % widths_count],
        });
    }
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellPropagates<size>& event) {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (cell_propagations_handled < quicken(3)) {
    VisitEventsGuard visit(this, event);

    if (single_propagations_handled < quicken(6)) {
      for (unsigned index = 0; index != quicken(3) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.before.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
            .circled_values = {{event.target_cell, event.value}},
            .circled_values_line_width = widths[index % widths_count],
            .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
            .links_from_cell_to_value_line_width = widths[index % widths_count],
          });
      }

      for (unsigned index = 0; index != quicken(6); ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
          });
      }
    } else {
      for (unsigned index = 0; index != quicken(1) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.before.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
            .circled_values = {{event.target_cell, event.value}},
            .circled_values_line_width = widths[index % widths_count],
            .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
            .links_from_cell_to_value_line_width = widths[index % widths_count],
          });
      }

      for (unsigned index = 0; index != quicken(4); ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);
        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = {event.source_cell},
            .circled_values = {{event.target_cell, event.value}},
            .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
          });
      }
    }
    ++single_propagations_handled;
  } else {
    pending_cell_propagates_events.push_back(event);
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationIsDoneForCell<size>& event) {
  flush_pending_cell_propagates_events();

  VisitEventsGuard visit(this, event);

  ++cell_propagations_handled;
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_cell_propagates_events() {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (!pending_cell_propagates_events.empty()) {
    VisitEventsGuard visit(this, pending_cell_propagates_events);

    for (unsigned index = 0; index != quicken(1) * widths_count; ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);

      const Coordinates source_cell = pending_cell_propagates_events.front().source_cell;
      std::vector<std::tuple<Coordinates, unsigned>> circled_values;
      std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
      for (const auto& event : pending_cell_propagates_events) {
        assert(event.source_cell == source_cell);
        circled_values.push_back({event.target_cell, event.value});
        links_from_cell_to_value.push_back({event.source_cell, event.target_cell, event.value});
      }

      art::draw(
        context,
        visit.before.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source_cell},
          .circled_cells_line_width = widths[index % widths_count],
          .circled_values = circled_values,
          .circled_values_line_width = widths[index % widths_count],
          .links_from_cell_to_value = links_from_cell_to_value,
          .links_from_cell_to_value_line_width = widths[index % widths_count],
        });
    }

    for (unsigned index = 0; index != quicken(4); ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);

      const Coordinates source_cell = pending_cell_propagates_events.front().source_cell;
      std::vector<std::tuple<Coordinates, unsigned>> circled_values;
      std::vector<std::tuple<Coordinates, Coordinates, unsigned>> links_from_cell_to_value;
      for (const auto& event : pending_cell_propagates_events) {
        assert(event.source_cell == source_cell);
        circled_values.push_back({event.target_cell, event.value});
        links_from_cell_to_value.push_back({event.source_cell, event.target_cell, event.value});
      }

      art::draw(
        context,
        visit.after.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {source_cell},
          .circled_values = circled_values,
          .links_from_cell_to_value = links_from_cell_to_value,
        });
    }

    for (unsigned index = 0; index != quicken(4); ++index) {
      FrameGuard frame(this);
      const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
      cr.translate(grid_x, grid_y);
      art::draw(
        context,
        visit.after.current(),
        {
          .grid_size = grid_size,
          .possible = true,
          .bold_todo = true,
          .circled_cells = {pending_cell_propagates_events.front().source_cell},
        });
    }
  }
  pending_cell_propagates_events.clear();
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_cell_is_deduced_from_single_allowed_value_events() {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (!pending_cell_is_deduced_from_single_allowed_value_events.empty()) {
    VisitEventsGuard visit(this, pending_cell_is_deduced_from_single_allowed_value_events);

    if (deductions_handled < quicken(4)) {
      for (unsigned index = 0; index != quicken(6) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> circled_cells;
        for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
          circled_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = circled_cells,
            .circled_cells_line_width = widths[index % widths_count],
            .circled_cells_color = {0, 1, 0},
          });
      }
    } else {
      for (unsigned index = 0; index != quicken(2) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> circled_cells;
        for (const auto& event : pending_cell_is_deduced_from_single_allowed_value_events) {
          circled_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .circled_cells = circled_cells,
            .circled_cells_line_width = widths[index % widths_count],
            .circled_cells_color = {0, 1, 0},
          });
      }
    }
    ++deductions_handled;
  }
  pending_cell_is_deduced_from_single_allowed_value_events.clear();
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events() {
  Layout propagate{.below = {{"Propagate constraints", 20}}};

  const double widths[] = {2, 4, 5, 3, 2};
  const unsigned widths_count = sizeof(widths) / sizeof(widths[0]);

  if (!pending_cell_is_deduced_as_single_place_for_value_in_region_events.empty()) {
    VisitEventsGuard visit(this, pending_cell_is_deduced_as_single_place_for_value_in_region_events);

    if (deductions_handled < quicken(4)) {
      for (unsigned index = 0; index != quicken(6) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> boxed_cells;
        for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
          boxed_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .boxed_cells = boxed_cells,
            .boxed_cells_line_width = widths[index % widths_count],
            .boxed_cells_color = {0, 1, 0},
          });
      }
    } else {
      for (unsigned index = 0; index != quicken(2) * widths_count; ++index) {
        FrameGuard frame(this);
        const auto [grid_x, grid_y, grid_size] = draw_layout(propagate);
        cr.translate(grid_x, grid_y);

        std::vector<Coordinates> boxed_cells;
        for (const auto& event : pending_cell_is_deduced_as_single_place_for_value_in_region_events) {
          boxed_cells.push_back(event.cell);
        }

        art::draw(
          context,
          visit.after.current(),
          {
            .grid_size = grid_size,
            .possible = true,
            .bold_todo = true,
            .boxed_cells = boxed_cells,
            .boxed_cells_line_width = widths[index % widths_count],
            .boxed_cells_color = {0, 1, 0},
          });
      }
    }
    ++deductions_handled;
  }
  pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::PropagationIsDoneForSudoku<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::ExplorationStarts<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::HypothesisIsMade<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::HypothesisIsRejected<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::SudokuIsSolved<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);

  Layout done{.below = {{"Solved!", 20}}};

  for (unsigned index = 0; index != quicken(75); ++index) {
    FrameGuard frame(this);
    const auto [grid_x, grid_y, grid_size] = draw_layout(done);
    cr.translate(grid_x, grid_y);
    art::draw(
      context,
      visit.after.current(),
      {
        .grid_size = grid_size,
      });
  }
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::HypothesisIsAccepted<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::operator()(const exploration::ExplorationIsDone<size>& event) {
  flush_pending_events();

  VisitEventsGuard visit(this, event);
}

template<unsigned size>
void VideoExplainer<size>::flush_pending_events() {
  flush_pending_cell_propagates_events();
  flush_pending_cell_is_deduced_from_single_allowed_value_events();
  flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
}



template<>
class VideoExplainer<static_cast<unsigned int>(4)>
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  inline static constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  inline static constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  
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
  /* First instantiated from: video-explainer.cpp:1136 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellIsSetInInput<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::CellIsSetInInput<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<4> *, std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<4> *, std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<4> *, std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<4> *, std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsSetInInput<4> & event = static_cast<const exploration::CellIsSetInInput<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<4> *, std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::CellIsSetInInput<4>, std::allocator<exploration::CellIsSetInInput<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1141 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::InputsAreDone<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::InputsAreDone<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::InputsAreDone<4> *, std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::InputsAreDone<4> *, std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::InputsAreDone<4> *, std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::InputsAreDone<4> *, std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::InputsAreDone<4> & event = static_cast<const exploration::InputsAreDone<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::InputsAreDone<4> *, std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::InputsAreDone<4>, std::allocator<exploration::InputsAreDone<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1207 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationStartsForSudoku<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::PropagationStartsForSudoku<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<4> *, std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<4> *, std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<4> *, std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<4> *, std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationStartsForSudoku<4> & event = static_cast<const exploration::PropagationStartsForSudoku<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<4> *, std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::PropagationStartsForSudoku<4>, std::allocator<exploration::PropagationStartsForSudoku<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1214 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationStartsForCell<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::PropagationStartsForCell<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<4> *, std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<4> *, std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<4> *, std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<4> *, std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationStartsForCell<4> & event = static_cast<const exploration::PropagationStartsForCell<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<4> *, std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::PropagationStartsForCell<4>, std::allocator<exploration::PropagationStartsForCell<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1247 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellPropagates<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::CellPropagates<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range1 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellPropagates<4> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellPropagates<4> & event = static_cast<const exploration::CellPropagates<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1340 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationIsDoneForCell<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::PropagationIsDoneForCell<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<4> *, std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<4> *, std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<4> *, std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<4> *, std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationIsDoneForCell<4> & event = static_cast<const exploration::PropagationIsDoneForCell<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<4> *, std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::PropagationIsDoneForCell<4>, std::allocator<exploration::PropagationIsDoneForCell<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1438 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::CellIsDeducedFromSingleAllowedValue<4> & event);
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range1 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1500 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event);
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range1 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1558 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::PropagationIsDoneForSudoku<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<4> *, std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<4> *, std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<4> *, std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<4> *, std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationIsDoneForSudoku<4> & event = static_cast<const exploration::PropagationIsDoneForSudoku<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<4> *, std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::PropagationIsDoneForSudoku<4>, std::allocator<exploration::PropagationIsDoneForSudoku<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1565 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::ExplorationStarts<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::ExplorationStarts<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<4> *, std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<4> *, std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<4> *, std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<4> *, std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::ExplorationStarts<4> & event = static_cast<const exploration::ExplorationStarts<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<4> *, std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::ExplorationStarts<4>, std::allocator<exploration::ExplorationStarts<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1572 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::HypothesisIsMade<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::HypothesisIsMade<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<4> *, std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<4> *, std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<4> *, std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<4> *, std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::HypothesisIsMade<4> & event = static_cast<const exploration::HypothesisIsMade<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<4> *, std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::HypothesisIsMade<4>, std::allocator<exploration::HypothesisIsMade<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1579 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::HypothesisIsRejected<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::HypothesisIsRejected<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<4> *, std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<4> *, std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<4> *, std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<4> *, std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::HypothesisIsRejected<4> & event = static_cast<const exploration::HypothesisIsRejected<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<4> *, std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::HypothesisIsRejected<4>, std::allocator<exploration::HypothesisIsRejected<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1586 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::SudokuIsSolved<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::SudokuIsSolved<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<4> *, std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<4> *, std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<4> *, std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<4> *, std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::SudokuIsSolved<4> & event = static_cast<const exploration::SudokuIsSolved<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<4> *, std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::SudokuIsSolved<4>, std::allocator<exploration::SudokuIsSolved<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::HypothesisIsAccepted<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::HypothesisIsAccepted<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<4> *, std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<4> *, std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<4> *, std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<4> *, std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::HypothesisIsAccepted<4> & event = static_cast<const exploration::HypothesisIsAccepted<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<4> *, std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::HypothesisIsAccepted<4>, std::allocator<exploration::HypothesisIsAccepted<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1614 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::ExplorationIsDone<4> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const exploration::ExplorationIsDone<4> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > >()}
    , before{static_cast<const Stack<4>>(this->explainer.before)}
    , after{static_cast<const Stack<4>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_, const std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > & operator=(VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<4> *, std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<4> *, std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<4> *, std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<4> *, std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > >>(__end1)); __begin1.operator++()) {
          const exploration::ExplorationIsDone<4> & event = static_cast<const exploration::ExplorationIsDone<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<4> *, std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
    std::vector<exploration::ExplorationIsDone<4>, std::allocator<exploration::ExplorationIsDone<4> > > events;
    
    public: 
    const Stack<4> & before;
    const Stack<4> & after;
  };
  
  #endif
  public: 
  private: 
  template<typename Event>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const Event &) -> VisitEventsGuard<Event>;
  
  /* First instantiated from: video-explainer.cpp:1136 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::CellIsSetInInput<4> &) -> VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1141 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::InputsAreDone<4> &) -> VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1207 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::PropagationStartsForSudoku<4> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1214 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::PropagationStartsForCell<4> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1247 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::CellPropagates<4> &) -> VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1340 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::PropagationIsDoneForCell<4> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1558 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::PropagationIsDoneForSudoku<4> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1565 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::ExplorationStarts<4> &) -> VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1572 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::HypothesisIsMade<4> &) -> VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1579 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::HypothesisIsRejected<4> &) -> VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1586 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::SudokuIsSolved<4> &) -> VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::HypothesisIsAccepted<4> &) -> VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1614 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const exploration::ExplorationIsDone<4> &) -> VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> >;
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > &) -> VideoExplainer::VisitEventsGuard<std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >;
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > &) -> VideoExplainer::VisitEventsGuard<std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >;
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > &) -> VideoExplainer::VisitEventsGuard<std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >;
  #endif
  
  template<typename Event>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<Event> &) -> VisitEventsGuard<Event>;
  
  /* First instantiated from: video-explainer.cpp:1353 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > &) -> VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1438 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > &) -> VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1500 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(4)> *, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > &) -> VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >;
  #endif
  
  class FrameGuard
  {
    
    public: 
    inline explicit FrameGuard(VideoExplainer<static_cast<unsigned int>(4)> * explainer_)
    : explainer{*explainer_}
    , cr{this->explainer.cr}
    {
      {
        CairoSaveGuard saver = CairoSaveGuard(this->cr);
        this->cr.set_source_rgb(1.0, 0.80000000000000004, 0.80000000000000004);
        this->cr.paint();
        this->cr.set_source_rgb(1.0, 1.0, 1.0);
        this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
        this->cr.fill();
      };
      this->cr.save();
      this->cr.translate(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels));
    }
    
    // inline FrameGuard(const FrameGuard &) = delete;
    // inline FrameGuard & operator=(const FrameGuard &) = delete;
    // inline FrameGuard(FrameGuard &&) = delete;
    // inline FrameGuard & operator=(FrameGuard &&) = delete;
    inline ~FrameGuard() noexcept
    {
      this->cr.restore();
      CairoSaveGuard saver = CairoSaveGuard(this->cr);
      this->cr.rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->explainer.frame_width_pixels), static_cast<double>(this->explainer.frame_height_pixels));
      this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
      this->cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      this->cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      this->cr.fill();
      this->explainer.video_serializer->serialize(std::shared_ptr<Cairo::ImageSurface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->explainer.surface)));
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(4)> & explainer;
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
    
    VideoExplainer<4>::Text::(unnamed) weight;
    // inline constexpr Text(const Text &) noexcept(false) = default;
    // inline constexpr ~Text() noexcept = default;
  };
  
  struct Layout
  {
    std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > above = std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{};
    std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > below = std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{};
    // inline constexpr ~Layout() noexcept = default;
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
  void operator()(const exploration::CellIsSetInInput<4> & event)
  {
    VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> > visit = VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<4> >(this, event);
  }
  
  void operator()(const exploration::InputsAreDone<4> & event)
  {
    VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> > visit = VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<4> >(this, event);
    VideoExplainer<4>::Layout title = {std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("How to solve this Sudoku?"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(40), Text::Bold}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("An automated explanation by @jacquev6"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("https://github.com/jacquev6/Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}, {std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __title0 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(title)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title0));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title0));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title0));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const unsigned int transition_duration = this->quicken(static_cast<unsigned int>(12));
    for(unsigned int index = static_cast<unsigned int>(0); index != transition_duration; ++index) {
      const double ratio = (static_cast<double>(index) + 1.0) / static_cast<double>((transition_duration + static_cast<unsigned int>(1)));
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __title1 = static_cast<const std::tuple<double, double, double>>(this->draw_layout_transition(static_cast<const VideoExplainer<4>::Layout>(title), static_cast<const VideoExplainer<4>::Layout>(propagate), ratio));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title1));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title1));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title1));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate0 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate0));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate0));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate0));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate1 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate1));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate1));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate1));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::PropagationStartsForSudoku<4> & event)
  {
    VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<4> >(this, event);
  }
  
  void operator()(const exploration::PropagationStartsForCell<4> & event)
  {
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
    VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<4> >(this, event);
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
      const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate2 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate2));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate2));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate2));
        this->cr.translate(grid_x, grid_y);
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
  }
  
  void operator()(const exploration::CellPropagates<4> & event)
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > visit = VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> >(this, event);
      if(this->single_propagations_handled < this->quicken(static_cast<unsigned int>(6))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate3 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate3));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate3));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate3));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(6)); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate4 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate4));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate4));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate4));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate5 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate5));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate5));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate5));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate6 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate6));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate6));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate6));
          this->cr.translate(grid_x, grid_y);
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->single_propagations_handled;
    } else {
      this->pending_cell_propagates_events.push_back(event);
    } 
    
  }
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  void operator()(const exploration::PropagationIsDoneForCell<4> & event)
  {
    this->flush_pending_cell_propagates_events();
    VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<4> >(this, event);
    ++this->cell_propagations_handled;
  }
  
  void operator()(const exploration::PropagationIsDoneForSudoku<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<4> >(this, event);
  }
  
  void operator()(const exploration::ExplorationStarts<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> > visit = VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<4> >(this, event);
  }
  
  void operator()(const exploration::HypothesisIsMade<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> > visit = VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<4> >(this, event);
  }
  
  void operator()(const exploration::HypothesisIsRejected<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> > visit = VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<4> >(this, event);
  }
  
  void operator()(const exploration::SudokuIsSolved<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> > visit = VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<4> >(this, event);
    VideoExplainer<4>::Layout done = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Solved!"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
      const std::tuple<double, double, double> __done0 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(done)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__done0));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__done0));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__done0));
      this->cr.translate(grid_x, grid_y);
      art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::HypothesisIsAccepted<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> > visit = VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<4> >(this, event);
  }
  
  void operator()(const exploration::ExplorationIsDone<4> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> > visit = VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<4> >(this, event);
  }
  
  void flush_pending_cell_propagates_events()
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >>(this->pending_cell_propagates_events).empty()) {
      VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> > visit = VideoExplainer::VisitEventsGuard<exploration::CellPropagates<4> >(this, static_cast<const std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > >>(this->pending_cell_propagates_events));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate7 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate7));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate7));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate7));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range1 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin1 = __range1.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end1 = __range1.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end1)); __begin1.operator++()) {
            const exploration::CellPropagates<4> & event = static_cast<const exploration::CellPropagates<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("src/explanation/video-explainer.cpp"), static_cast<unsigned int>(241), static_cast<const char *>(__extension__"void VideoExplainer<4>::flush_pending_cell_propagates_events() [size = 4]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate8 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate8));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate8));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate8));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > & __range1 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __begin1 = __range1.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > > __end1 = __range1.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__end1)); __begin1.operator++()) {
            const exploration::CellPropagates<4> & event = static_cast<const exploration::CellPropagates<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<4> *, std::vector<exploration::CellPropagates<4>, std::allocator<exploration::CellPropagates<4> > > >>(__begin1).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("src/explanation/video-explainer.cpp"), static_cast<unsigned int>(271), static_cast<const char *>(__extension__"void VideoExplainer<4>::flush_pending_cell_propagates_events() [size = 4]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate9 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate9));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate9));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate9));
        this->cr.translate(grid_x, grid_y);
        art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
    this->pending_cell_propagates_events.clear();
  }
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events()
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events).empty()) {
      VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> > visit = VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<4> >(this, static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate10 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate10));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate10));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate10));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range2 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate11 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate11));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate11));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate11));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > & __range2 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<4> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<4> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<4>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<4> > > >>(__begin1).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
  }
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events()
  {
    VideoExplainer<4>::Layout propagate = {{std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{}}, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> >{std::initializer_list<VideoExplainer<4>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<4>::Text>>(std::allocator<VideoExplainer<4>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events).empty()) {
      VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > visit = VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(this, static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate12 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate12));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate12));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate12));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range2 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<4>::FrameGuard frame = VideoExplainer<4>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate13 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<4>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate13));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate13));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate13));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > & __range2 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> > > >>(__begin1).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  void flush_pending_events()
  {
    this->flush_pending_cell_propagates_events();
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  }
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double above_height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > & __range0 = layout.above;
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __begin1 = __range0.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __end1 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__end1)); __begin1.operator++()) {
        const VideoExplainer<4>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin1).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, above_height - extents.y_bearing);
        this->cr.show_text(text.text);
        above_height = above_height + extents.height;
      }
      
    }
    double below_height = static_cast<double>(0);
    {
      std::ranges::reverse_view<std::ranges::ref_view<const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > > && __range0 = operator|(layout.below, std::ranges::views::reverse);
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > > __begin1 = __range0.begin();
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > > __end1 = __range0.end();
      for(; !std::operator==(static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > >>(__begin1), static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > >>(__end1)); __begin1.operator++()) {
        const VideoExplainer<4>::Text & text = static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > >>(__begin1).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        below_height = below_height + extents.height;
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, (static_cast<double>(this->viewport_height_pixels) - below_height) - extents.y_bearing);
        this->cr.show_text(text.text);
      }
      
    }
    const unsigned int available_height = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height) - below_height);
    const unsigned int grid_size = (((available_height - thick_line_width) / 4U) * 4U) + thick_line_width;
    const unsigned int grid_x = (this->viewport_width_pixels - grid_size) / static_cast<unsigned int>(2);
    const unsigned int grid_y = static_cast<const unsigned int>(above_height + (static_cast<double>((available_height - grid_size) / static_cast<unsigned int>(2))));
    return std::tuple<double, double, double>(std::make_tuple<const unsigned int &, const unsigned int &, const unsigned int &>(grid_x, grid_y, grid_size));
  }
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    const double above_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(before.above);
    const double below_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(before.below);
    const unsigned int available_height_before = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_before) - below_height_before);
    const unsigned int grid_size_before = (((available_height_before - thick_line_width) / 4U) * 4U) + thick_line_width;
    const double grid_x_before = static_cast<const double>((this->viewport_width_pixels - grid_size_before) / static_cast<unsigned int>(2));
    const double grid_y_before = above_height_before + (static_cast<double>((available_height_before - grid_size_before) / static_cast<unsigned int>(2)));
    const double above_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(after.above);
    const double below_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(4)> *>(this)->compute_text_height(after.below);
    const unsigned int available_height_after = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_after) - below_height_after);
    const unsigned int grid_size_after = (((available_height_after - thick_line_width) / 4U) * 4U) + thick_line_width;
    const double grid_x_after = static_cast<const double>((this->viewport_width_pixels - grid_size_after) / static_cast<unsigned int>(2));
    const double grid_y_after = above_height_after + (static_cast<double>((available_height_after - grid_size_after) / static_cast<unsigned int>(2)));
    const double grid_size = static_cast<double>(grid_size_before) + (ratio * static_cast<double>((grid_size_after - grid_size_before)));
    const double grid_x = grid_x_before + (ratio * (grid_x_after - grid_x_before));
    const double grid_y = grid_y_before + (ratio * (grid_y_after - grid_y_before));
    return std::make_tuple<const double &, const double &, const double &>(grid_x, grid_y, grid_size);
  }
  
  inline double compute_text_height(const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > & texts) const
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > & __range0 = texts;
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __begin1 = __range0.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > > __end1 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__end1)); __begin1.operator++()) {
        const VideoExplainer<4>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<4>::Text *, std::vector<VideoExplainer<4>::Text, std::allocator<VideoExplainer<4>::Text> > >>(__begin1).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        height = height + extents.height;
      }
      
    }
    return height;
  }
  
  
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
  // inline VideoExplainer<static_cast<unsigned int>(4)> & operator=(const VideoExplainer<static_cast<unsigned int>(4)> &) /* noexcept */ = delete;
  // inline VideoExplainer<static_cast<unsigned int>(4)> & operator=(VideoExplainer<static_cast<unsigned int>(4)> &&) /* noexcept */ = delete;
};





template<>
class VideoExplainer<static_cast<unsigned int>(9)>
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  inline static constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  inline static constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  
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
  /* First instantiated from: video-explainer.cpp:1136 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellIsSetInInput<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::CellIsSetInInput<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<9> *, std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<9> *, std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<9> *, std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<9> *, std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsSetInInput<9> & event = static_cast<const exploration::CellIsSetInInput<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsSetInInput<9> *, std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::CellIsSetInInput<9>, std::allocator<exploration::CellIsSetInInput<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1141 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::InputsAreDone<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::InputsAreDone<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::InputsAreDone<9> *, std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::InputsAreDone<9> *, std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::InputsAreDone<9> *, std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::InputsAreDone<9> *, std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::InputsAreDone<9> & event = static_cast<const exploration::InputsAreDone<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::InputsAreDone<9> *, std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::InputsAreDone<9>, std::allocator<exploration::InputsAreDone<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1207 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationStartsForSudoku<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::PropagationStartsForSudoku<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<9> *, std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<9> *, std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<9> *, std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<9> *, std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationStartsForSudoku<9> & event = static_cast<const exploration::PropagationStartsForSudoku<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForSudoku<9> *, std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::PropagationStartsForSudoku<9>, std::allocator<exploration::PropagationStartsForSudoku<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1214 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationStartsForCell<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::PropagationStartsForCell<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<9> *, std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<9> *, std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<9> *, std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<9> *, std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationStartsForCell<9> & event = static_cast<const exploration::PropagationStartsForCell<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationStartsForCell<9> *, std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::PropagationStartsForCell<9>, std::allocator<exploration::PropagationStartsForCell<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1247 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellPropagates<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::CellPropagates<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range1 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellPropagates<9> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellPropagates<9> & event = static_cast<const exploration::CellPropagates<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1340 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationIsDoneForCell<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::PropagationIsDoneForCell<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<9> *, std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<9> *, std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<9> *, std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<9> *, std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationIsDoneForCell<9> & event = static_cast<const exploration::PropagationIsDoneForCell<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForCell<9> *, std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::PropagationIsDoneForCell<9>, std::allocator<exploration::PropagationIsDoneForCell<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1438 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::CellIsDeducedFromSingleAllowedValue<9> & event);
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range1 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1500 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event);
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & events_)
    : explainer{*explainer_}
    , events{std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      {
        const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range1 = events_;
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const __gnu_cxx::__normal_iterator<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1).operator*();
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1558 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::PropagationIsDoneForSudoku<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<9> *, std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<9> *, std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<9> *, std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<9> *, std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::PropagationIsDoneForSudoku<9> & event = static_cast<const exploration::PropagationIsDoneForSudoku<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::PropagationIsDoneForSudoku<9> *, std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::PropagationIsDoneForSudoku<9>, std::allocator<exploration::PropagationIsDoneForSudoku<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1565 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::ExplorationStarts<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::ExplorationStarts<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<9> *, std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<9> *, std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<9> *, std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<9> *, std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::ExplorationStarts<9> & event = static_cast<const exploration::ExplorationStarts<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationStarts<9> *, std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::ExplorationStarts<9>, std::allocator<exploration::ExplorationStarts<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1572 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::HypothesisIsMade<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::HypothesisIsMade<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<9> *, std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<9> *, std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<9> *, std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<9> *, std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::HypothesisIsMade<9> & event = static_cast<const exploration::HypothesisIsMade<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsMade<9> *, std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::HypothesisIsMade<9>, std::allocator<exploration::HypothesisIsMade<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1579 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::HypothesisIsRejected<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::HypothesisIsRejected<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<9> *, std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<9> *, std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<9> *, std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<9> *, std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::HypothesisIsRejected<9> & event = static_cast<const exploration::HypothesisIsRejected<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsRejected<9> *, std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::HypothesisIsRejected<9>, std::allocator<exploration::HypothesisIsRejected<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1586 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::SudokuIsSolved<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::SudokuIsSolved<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<9> *, std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<9> *, std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<9> *, std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<9> *, std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::SudokuIsSolved<9> & event = static_cast<const exploration::SudokuIsSolved<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::SudokuIsSolved<9> *, std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::SudokuIsSolved<9>, std::allocator<exploration::SudokuIsSolved<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::HypothesisIsAccepted<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::HypothesisIsAccepted<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<9> *, std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<9> *, std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<9> *, std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<9> *, std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::HypothesisIsAccepted<9> & event = static_cast<const exploration::HypothesisIsAccepted<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::HypothesisIsAccepted<9> *, std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::HypothesisIsAccepted<9>, std::allocator<exploration::HypothesisIsAccepted<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  /* First instantiated from: video-explainer.cpp:1614 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  class VisitEventsGuard<exploration::ExplorationIsDone<9> >
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const exploration::ExplorationIsDone<9> & event)
    : explainer{*explainer_}
    , events{std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > >()}
    , before{static_cast<const Stack<9>>(this->explainer.before)}
    , after{static_cast<const Stack<9>>(this->explainer.after)}
    {
      event.apply(&this->explainer.after);
      this->events.push_back(event);
    }
    
    inline VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_, const std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > & events_);
    
    // inline VisitEventsGuard(const VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > &) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > & operator=(const VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > &) = delete;
    // inline VisitEventsGuard(VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > &&) = delete;
    // inline VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > & operator=(VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > &&) = delete;
    inline ~VisitEventsGuard() noexcept
    {
      {
        std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > & __range1 = this->events;
        __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<9> *, std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > > __begin1 = __range1.begin();
        __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<9> *, std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > > __end1 = __range1.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<9> *, std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<9> *, std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > >>(__end1)); __begin1.operator++()) {
          const exploration::ExplorationIsDone<9> & event = static_cast<const exploration::ExplorationIsDone<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::ExplorationIsDone<9> *, std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > >>(__begin1).operator*());
          event.apply(&this->explainer.before);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
    std::vector<exploration::ExplorationIsDone<9>, std::allocator<exploration::ExplorationIsDone<9> > > events;
    
    public: 
    const Stack<9> & before;
    const Stack<9> & after;
  };
  
  #endif
  public: 
  private: 
  template<typename Event>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const Event &) -> VisitEventsGuard<Event>;
  
  /* First instantiated from: video-explainer.cpp:1136 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::CellIsSetInInput<9> &) -> VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1141 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::InputsAreDone<9> &) -> VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1207 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::PropagationStartsForSudoku<9> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1214 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::PropagationStartsForCell<9> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1247 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::CellPropagates<9> &) -> VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1340 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::PropagationIsDoneForCell<9> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1558 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::PropagationIsDoneForSudoku<9> &) -> VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1565 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::ExplorationStarts<9> &) -> VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1572 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::HypothesisIsMade<9> &) -> VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1579 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::HypothesisIsRejected<9> &) -> VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1586 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::SudokuIsSolved<9> &) -> VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1607 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::HypothesisIsAccepted<9> &) -> VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1614 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const exploration::ExplorationIsDone<9> &) -> VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> >;
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > &) -> VideoExplainer::VisitEventsGuard<std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >;
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > &) -> VideoExplainer::VisitEventsGuard<std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >;
  #endif
  
  
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > &) -> VideoExplainer::VisitEventsGuard<std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >;
  #endif
  
  template<typename Event>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<Event> &) -> VisitEventsGuard<Event>;
  
  /* First instantiated from: video-explainer.cpp:1353 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > &) -> VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1438 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > &) -> VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> >;
  #endif
  
  
  /* First instantiated from: video-explainer.cpp:1500 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  VisitEventsGuard(VideoExplainer<static_cast<unsigned int>(9)> *, const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > &) -> VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >;
  #endif
  
  class FrameGuard
  {
    
    public: 
    inline explicit FrameGuard(VideoExplainer<static_cast<unsigned int>(9)> * explainer_)
    : explainer{*explainer_}
    , cr{this->explainer.cr}
    {
      {
        CairoSaveGuard saver = CairoSaveGuard(this->cr);
        this->cr.set_source_rgb(1.0, 0.80000000000000004, 0.80000000000000004);
        this->cr.paint();
        this->cr.set_source_rgb(1.0, 1.0, 1.0);
        this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
        this->cr.fill();
      };
      this->cr.save();
      this->cr.translate(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels));
    }
    
    // inline FrameGuard(const FrameGuard &) = delete;
    // inline FrameGuard & operator=(const FrameGuard &) = delete;
    // inline FrameGuard(FrameGuard &&) = delete;
    // inline FrameGuard & operator=(FrameGuard &&) = delete;
    inline ~FrameGuard() noexcept
    {
      this->cr.restore();
      CairoSaveGuard saver = CairoSaveGuard(this->cr);
      this->cr.rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->explainer.frame_width_pixels), static_cast<double>(this->explainer.frame_height_pixels));
      this->cr.rectangle(static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.margin_pixels), static_cast<double>(this->explainer.viewport_width_pixels), static_cast<double>(this->explainer.viewport_height_pixels));
      this->cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      this->cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      this->cr.fill();
      this->explainer.video_serializer->serialize(std::shared_ptr<Cairo::ImageSurface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->explainer.surface)));
    }
    
    
    private: 
    VideoExplainer<static_cast<unsigned int>(9)> & explainer;
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
    
    VideoExplainer<9>::Text::(unnamed) weight;
    // inline constexpr Text(const Text &) noexcept(false) = default;
    // inline constexpr ~Text() noexcept = default;
  };
  
  struct Layout
  {
    std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > above = std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{};
    std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > below = std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{};
    // inline constexpr ~Layout() noexcept = default;
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
  void operator()(const exploration::CellIsSetInInput<9> & event)
  {
    VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> > visit = VideoExplainer::VisitEventsGuard<exploration::CellIsSetInInput<9> >(this, event);
  }
  
  void operator()(const exploration::InputsAreDone<9> & event)
  {
    VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> > visit = VideoExplainer::VisitEventsGuard<exploration::InputsAreDone<9> >(this, event);
    VideoExplainer<9>::Layout title = {std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("How to solve this Sudoku?"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(40), Text::Bold}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("An automated explanation by @jacquev6"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}, {std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("https://github.com/jacquev6/Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}, {std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __title0 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(title)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title0));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title0));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title0));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const unsigned int transition_duration = this->quicken(static_cast<unsigned int>(12));
    for(unsigned int index = static_cast<unsigned int>(0); index != transition_duration; ++index) {
      const double ratio = (static_cast<double>(index) + 1.0) / static_cast<double>((transition_duration + static_cast<unsigned int>(1)));
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __title1 = static_cast<const std::tuple<double, double, double>>(this->draw_layout_transition(static_cast<const VideoExplainer<9>::Layout>(title), static_cast<const VideoExplainer<9>::Layout>(propagate), ratio));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__title1));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__title1));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__title1));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate0 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate0));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate0));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate0));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(12)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __propagate1 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate1));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate1));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate1));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::PropagationStartsForSudoku<9> & event)
  {
    VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForSudoku<9> >(this, event);
  }
  
  void operator()(const exploration::PropagationStartsForCell<9> & event)
  {
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
    VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationStartsForCell<9> >(this, event);
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
      const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate2 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate2));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate2));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate2));
        this->cr.translate(grid_x, grid_y);
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
  }
  
  void operator()(const exploration::CellPropagates<9> & event)
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(this->cell_propagations_handled < this->quicken(static_cast<unsigned int>(3))) {
      VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > visit = VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> >(this, event);
      if(this->single_propagations_handled < this->quicken(static_cast<unsigned int>(6))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(3)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate3 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate3));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate3));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate3));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(6)); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate4 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate4));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate4));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate4));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate5 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate5));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate5));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate5));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
        for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate6 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate6));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate6));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate6));
          this->cr.translate(grid_x, grid_y);
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->single_propagations_handled;
    } else {
      this->pending_cell_propagates_events.push_back(event);
    } 
    
  }
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
  {
    this->pending_cell_is_deduced_from_single_allowed_value_events.push_back(event);
  }
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
  {
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.push_back(event);
  }
  
  void operator()(const exploration::PropagationIsDoneForCell<9> & event)
  {
    this->flush_pending_cell_propagates_events();
    VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForCell<9> >(this, event);
    ++this->cell_propagations_handled;
  }
  
  void operator()(const exploration::PropagationIsDoneForSudoku<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> > visit = VideoExplainer::VisitEventsGuard<exploration::PropagationIsDoneForSudoku<9> >(this, event);
  }
  
  void operator()(const exploration::ExplorationStarts<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> > visit = VideoExplainer::VisitEventsGuard<exploration::ExplorationStarts<9> >(this, event);
  }
  
  void operator()(const exploration::HypothesisIsMade<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> > visit = VideoExplainer::VisitEventsGuard<exploration::HypothesisIsMade<9> >(this, event);
  }
  
  void operator()(const exploration::HypothesisIsRejected<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> > visit = VideoExplainer::VisitEventsGuard<exploration::HypothesisIsRejected<9> >(this, event);
  }
  
  void operator()(const exploration::SudokuIsSolved<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> > visit = VideoExplainer::VisitEventsGuard<exploration::SudokuIsSolved<9> >(this, event);
    VideoExplainer<9>::Layout done = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Solved!"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(75)); ++index) {
      VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
      const std::tuple<double, double, double> __done0 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(done)));
      const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__done0));
      const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__done0));
      const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__done0));
      this->cr.translate(grid_x, grid_y);
      art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    }
    
  }
  
  void operator()(const exploration::HypothesisIsAccepted<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> > visit = VideoExplainer::VisitEventsGuard<exploration::HypothesisIsAccepted<9> >(this, event);
  }
  
  void operator()(const exploration::ExplorationIsDone<9> & event)
  {
    this->flush_pending_events();
    VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> > visit = VideoExplainer::VisitEventsGuard<exploration::ExplorationIsDone<9> >(this, event);
  }
  
  void flush_pending_cell_propagates_events()
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >>(this->pending_cell_propagates_events).empty()) {
      VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> > visit = VideoExplainer::VisitEventsGuard<exploration::CellPropagates<9> >(this, static_cast<const std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > >>(this->pending_cell_propagates_events));
      for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(1)) * widths_count); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate7 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate7));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate7));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate7));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range1 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin1 = __range1.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end1 = __range1.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end1)); __begin1.operator++()) {
            const exploration::CellPropagates<9> & event = static_cast<const exploration::CellPropagates<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("src/explanation/video-explainer.cpp"), static_cast<unsigned int>(241), static_cast<const char *>(__extension__"void VideoExplainer<9>::flush_pending_cell_propagates_events() [size = 9]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.before.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), static_cast<const double *>(widths)[index % widths_count], {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate8 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate8));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate8));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate8));
        this->cr.translate(grid_x, grid_y);
        const std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell));
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
        std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
        {
          std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > & __range1 = this->pending_cell_propagates_events;
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __begin1 = __range1.begin();
          __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > > __end1 = __range1.end();
          for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__end1)); __begin1.operator++()) {
            const exploration::CellPropagates<9> & event = static_cast<const exploration::CellPropagates<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellPropagates<9> *, std::vector<exploration::CellPropagates<9>, std::allocator<exploration::CellPropagates<9> > > >>(__begin1).operator*());
            (static_cast<bool>(std::operator==(event.source_cell, source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("event.source_cell == source_cell"), static_cast<const char *>("src/explanation/video-explainer.cpp"), static_cast<unsigned int>(271), static_cast<const char *>(__extension__"void VideoExplainer<9>::flush_pending_cell_propagates_events() [size = 9]")));
            circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value});
            links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value});
          }
          
        }
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
      for(unsigned int index = static_cast<unsigned int>(0); index != this->quicken(static_cast<unsigned int>(4)); ++index) {
        VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
        const std::tuple<double, double, double> __propagate9 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
        const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate9));
        const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate9));
        const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate9));
        this->cr.translate(grid_x, grid_y);
        art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->pending_cell_propagates_events.front().source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    } 
    
    this->pending_cell_propagates_events.clear();
  }
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events()
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events).empty()) {
      VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> > visit = VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedFromSingleAllowedValue<9> >(this, static_cast<const std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > >>(this->pending_cell_is_deduced_from_single_allowed_value_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate10 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate10));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate10));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate10));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range2 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate11 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate11));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate11));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate11));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > circled_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > & __range2 = this->pending_cell_is_deduced_from_single_allowed_value_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedFromSingleAllowedValue<9> & event = static_cast<const exploration::CellIsDeducedFromSingleAllowedValue<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedFromSingleAllowedValue<9> *, std::vector<exploration::CellIsDeducedFromSingleAllowedValue<9>, std::allocator<exploration::CellIsDeducedFromSingleAllowedValue<9> > > >>(__begin1).operator*());
              circled_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(circled_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_from_single_allowed_value_events.clear();
  }
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events()
  {
    VideoExplainer<9>::Layout propagate = {{std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{}}, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> >{std::initializer_list<VideoExplainer<9>::Text>{{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Propagate constraints"), static_cast<const std::allocator<char>>(std::allocator<char>())), static_cast<double>(20), 0}}, static_cast<const std::allocator<VideoExplainer<9>::Text>>(std::allocator<VideoExplainer<9>::Text>())}};
    const double widths[5] = {static_cast<const double>(2), static_cast<const double>(4), static_cast<const double>(5), static_cast<const double>(3), static_cast<const double>(2)};
    const unsigned int widths_count = static_cast<const unsigned int>(sizeof(widths) / sizeof(static_cast<const double *>(widths)[0]));
    if(!static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events).empty()) {
      VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > visit = VideoExplainer::VisitEventsGuard<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(this, static_cast<const std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > >>(this->pending_cell_is_deduced_as_single_place_for_value_in_region_events));
      if(this->deductions_handled < this->quicken(static_cast<unsigned int>(4))) {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(6)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate12 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate12));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate12));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate12));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range2 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } else {
        for(unsigned int index = static_cast<unsigned int>(0); index != (this->quicken(static_cast<unsigned int>(2)) * widths_count); ++index) {
          VideoExplainer<9>::FrameGuard frame = VideoExplainer<9>::FrameGuard(this);
          const std::tuple<double, double, double> __propagate13 = static_cast<const std::tuple<double, double, double>>(this->draw_layout(static_cast<const VideoExplainer<9>::Layout>(propagate)));
          const double && grid_x = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate13));
          const double && grid_y = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate13));
          const double && grid_size = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__propagate13));
          this->cr.translate(grid_x, grid_y);
          std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > boxed_cells = std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >();
          {
            std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > & __range2 = this->pending_cell_is_deduced_as_single_place_for_value_in_region_events;
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __begin1 = __range2.begin();
            __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > > __end1 = __range2.end();
            for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__end1)); __begin1.operator++()) {
              const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event = static_cast<const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>>(static_cast<const __gnu_cxx::__normal_iterator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> *, std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, std::allocator<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> > > >>(__begin1).operator*());
              boxed_cells.push_back(event.cell);
            }
            
          }
          art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(this->context)), visit.after.current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >(static_cast<const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(boxed_cells)), static_cast<const double *>(widths)[index % widths_count], std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
        }
        
      } 
      
      ++this->deductions_handled;
    } 
    
    this->pending_cell_is_deduced_as_single_place_for_value_in_region_events.clear();
  }
  
  void flush_pending_events()
  {
    this->flush_pending_cell_propagates_events();
    this->flush_pending_cell_is_deduced_from_single_allowed_value_events();
    this->flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  }
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double above_height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > & __range0 = layout.above;
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __begin1 = __range0.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __end1 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__end1)); __begin1.operator++()) {
        const VideoExplainer<9>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin1).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, above_height - extents.y_bearing);
        this->cr.show_text(text.text);
        above_height = above_height + extents.height;
      }
      
    }
    double below_height = static_cast<double>(0);
    {
      std::ranges::reverse_view<std::ranges::ref_view<const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > > && __range0 = operator|(layout.below, std::ranges::views::reverse);
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > > __begin1 = __range0.begin();
      std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > > __end1 = __range0.end();
      for(; !std::operator==(static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > >>(__begin1), static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > >>(__end1)); __begin1.operator++()) {
        const VideoExplainer<9>::Text & text = static_cast<const std::reverse_iterator<__gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > >>(__begin1).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        below_height = below_height + extents.height;
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, (static_cast<double>(this->viewport_height_pixels) - below_height) - extents.y_bearing);
        this->cr.show_text(text.text);
      }
      
    }
    const unsigned int available_height = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height) - below_height);
    const unsigned int grid_size = (((available_height - thick_line_width) / 9U) * 9U) + thick_line_width;
    const unsigned int grid_x = (this->viewport_width_pixels - grid_size) / static_cast<unsigned int>(2);
    const unsigned int grid_y = static_cast<const unsigned int>(above_height + (static_cast<double>((available_height - grid_size) / static_cast<unsigned int>(2))));
    return std::tuple<double, double, double>(std::make_tuple<const unsigned int &, const unsigned int &, const unsigned int &>(grid_x, grid_y, grid_size));
  }
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    const double above_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(before.above);
    const double below_height_before = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(before.below);
    const unsigned int available_height_before = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_before) - below_height_before);
    const unsigned int grid_size_before = (((available_height_before - thick_line_width) / 9U) * 9U) + thick_line_width;
    const double grid_x_before = static_cast<const double>((this->viewport_width_pixels - grid_size_before) / static_cast<unsigned int>(2));
    const double grid_y_before = above_height_before + (static_cast<double>((available_height_before - grid_size_before) / static_cast<unsigned int>(2)));
    const double above_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(after.above);
    const double below_height_after = static_cast<const VideoExplainer<static_cast<unsigned int>(9)> *>(this)->compute_text_height(after.below);
    const unsigned int available_height_after = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_after) - below_height_after);
    const unsigned int grid_size_after = (((available_height_after - thick_line_width) / 9U) * 9U) + thick_line_width;
    const double grid_x_after = static_cast<const double>((this->viewport_width_pixels - grid_size_after) / static_cast<unsigned int>(2));
    const double grid_y_after = above_height_after + (static_cast<double>((available_height_after - grid_size_after) / static_cast<unsigned int>(2)));
    const double grid_size = static_cast<double>(grid_size_before) + (ratio * static_cast<double>((grid_size_after - grid_size_before)));
    const double grid_x = grid_x_before + (ratio * (grid_x_after - grid_x_before));
    const double grid_y = grid_y_before + (ratio * (grid_y_after - grid_y_before));
    return std::make_tuple<const double &, const double &, const double &>(grid_x, grid_y, grid_size);
  }
  
  inline double compute_text_height(const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > & texts) const
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double height = static_cast<double>(0);
    {
      const std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > & __range0 = texts;
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __begin1 = __range0.begin();
      __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > > __end1 = __range0.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__end1)); __begin1.operator++()) {
        const VideoExplainer<9>::Text & text = static_cast<const __gnu_cxx::__normal_iterator<const VideoExplainer<9>::Text *, std::vector<VideoExplainer<9>::Text, std::allocator<VideoExplainer<9>::Text> > >>(__begin1).operator*();
        this->cr.set_font_size(text.font_size);
        switch(static_cast<int>(text.weight)) {
          case static_cast<int>(Text::Normal): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case static_cast<int>(Text::Bold): this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        static_cast<const Cairo::Context>(this->cr).get_text_extents(text.text, extents);
        height = height + extents.height;
      }
      
    }
    return height;
  }
  
  
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
  // inline VideoExplainer<static_cast<unsigned int>(9)> & operator=(const VideoExplainer<static_cast<unsigned int>(9)> &) /* noexcept */ = delete;
  // inline VideoExplainer<static_cast<unsigned int>(9)> & operator=(VideoExplainer<static_cast<unsigned int>(9)> &&) /* noexcept */ = delete;
};



