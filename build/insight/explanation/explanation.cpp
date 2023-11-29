# 1 "src/explanation/explanation.cpp"
// Copyright 2023 Vincent Jacques

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

/* First instantiated from: explanation.cpp:387 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<ValueCell, 4>
{
  
  public: 
  class Cell : public ValueCell
  {
    
    public: 
    inline Cell(const SudokuBase<ValueCell, 4> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_)
    : ValueCell()
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(coords_)}
    {
    }
    
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
    
    inline std::pair<unsigned int, unsigned int> coordinates() const;
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<ValueCell, 4> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
  public: 
  inline SudokuBase()
  : _cells{this->make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<ValueCell, 4> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
  SudokuBase<ValueCell, 4> & operator=(const SudokuBase<ValueCell, 4> &);
  
  // inline SudokuBase(SudokuBase<ValueCell, 4> &&) = delete;
  // inline SudokuBase<ValueCell, 4> & operator=(SudokuBase<ValueCell, 4> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, 4>, 4>;
  inline std::array<std::array<Cell, 4>, 4> make_cells()
  {
    return this->make_cells<0, 1, 2, 3>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()));
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 4>, 4> make_cells(const std::integer_sequence<unsigned int, row...> &);
  
  /* First instantiated from: explanation.cpp:258 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: explanation.cpp:263 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 4> make_row<0, 1, 2, 3>(unsigned int row, const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{static_cast<const SudokuBase<ValueCell, 4> *>(this)->make_cell(row, 0U), static_cast<const SudokuBase<ValueCell, 4> *>(this)->make_cell(row, 1U), static_cast<const SudokuBase<ValueCell, 4> *>(this)->make_cell(row, 2U), static_cast<const SudokuBase<ValueCell, 4> *>(this)->make_cell(row, 3U)}};
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
  
  /* First instantiated from: explanation.cpp:277 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: explanation.cpp:282 */
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
  
  inline auto cells();
  
  inline auto regions() const;
  
  
  protected: 
  std::array<std::array<Cell, 4>, 4> _cells;
  public: 
};

#endif
/* First instantiated from: explanation.cpp:387 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class SudokuBase<ValueCell, 9>
{
  
  public: 
  class Cell : public ValueCell
  {
    
    public: 
    inline Cell(const SudokuBase<ValueCell, 9> * sudoku_, const std::pair<unsigned int, unsigned int> & coords_)
    : ValueCell()
    , sudoku{sudoku_}
    , coords{std::pair<unsigned int, unsigned int>(coords_)}
    {
    }
    
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
    
    inline std::pair<unsigned int, unsigned int> coordinates() const;
    
    auto regions() const;
    
    
    private: 
    const SudokuBase<ValueCell, 9> * sudoku;
    const std::pair<unsigned int, unsigned int> coords;
    public: 
  };
  
  class Region;
  
  public: 
  inline SudokuBase()
  : _cells{this->make_cells()}
  {
  }
  
  inline SudokuBase(const SudokuBase<ValueCell, 9> & other)
  : _cells{this->copy_cells(other._cells)}
  {
  }
  
  SudokuBase<ValueCell, 9> & operator=(const SudokuBase<ValueCell, 9> &);
  
  // inline SudokuBase(SudokuBase<ValueCell, 9> &&) = delete;
  // inline SudokuBase<ValueCell, 9> & operator=(SudokuBase<ValueCell, 9> &&) = delete;
  
  private: 
  using CellsArray = std::array<std::array<Cell, 9>, 9>;
  inline std::array<std::array<Cell, 9>, 9> make_cells()
  {
    return this->make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()));
  }
  
  template<unsigned int ...row>
  inline std::array<std::array<Cell, 9>, 9> make_cells(const std::integer_sequence<unsigned int, row...> &);
  
  /* First instantiated from: explanation.cpp:258 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> make_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: explanation.cpp:263 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<Cell, 9> make_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(unsigned int row, const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &)
  {
    return {{static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 0U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 1U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 2U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 3U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 4U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 5U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 6U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 7U), static_cast<const SudokuBase<ValueCell, 9> *>(this)->make_cell(row, 8U)}};
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
  
  /* First instantiated from: explanation.cpp:277 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 9>, 9> copy_cells<0, 1, 2, 3, 4, 5, 6, 7, 8>(const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8> &, const std::array<std::array<Cell, 9>, 9> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(4U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(5U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(6U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(7U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>())), this->copy_row<0, 1, 2, 3, 4, 5, 6, 7, 8>(8U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>>(std::integer_sequence<unsigned int, 0, 1, 2, 3, 4, 5, 6, 7, 8>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 9> copy_row(unsigned int row, const std::array<std::array<Cell, 9>, 9> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: explanation.cpp:282 */
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

/* First instantiated from: explanation.cpp:777 */
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
  // inline Sudoku() noexcept(false) = default;
};

#endif
/* First instantiated from: explanation.cpp:777 */
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
  // inline Sudoku() noexcept(false) = default;
};

#endif


class ValueCell
{
  
  public: 
  inline constexpr ValueCell() noexcept = default;
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
  
  /* First instantiated from: explanation.cpp:860 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: explanation.cpp:860 */
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
  
  /* First instantiated from: explanation.cpp:875 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: explanation.cpp:875 */
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
  
  /* First instantiated from: explanation.cpp:890 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: explanation.cpp:890 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
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
  
  /* First instantiated from: explanation.cpp:900 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  #endif
  /* First instantiated from: explanation.cpp:900 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  #endif
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
  
  /* First instantiated from: explanation.cpp:917 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  #endif
  /* First instantiated from: explanation.cpp:917 */
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
  
  /* First instantiated from: explanation.cpp:925 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: explanation.cpp:925 */
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




#endif  // EXPLANATION_EXPLANATION_HPP_
# 4 "src/explanation/explanation.cpp"

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::CellIsSetInInput<size>& event) {
  explanation.inputs.cell(event.cell).set(event.value);
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::InputsAreDone<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationStartsForSudoku<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationStartsForCell<size>& event) {
  assert(!stack.empty());
  assert(stack.back().propagations != nullptr);
  stack.back().propagations->push_back({event.cell, event.value});
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::CellPropagates<size>& event) {
  assert(!stack.empty());
  assert(stack.back().propagations != nullptr);
  assert(!stack.back().propagations->empty());
  assert(stack.back().propagations->back().source == event.source_cell);
  assert(stack.back().propagations->back().value == event.value);
  stack.back().propagations->back().targets.push_back({event.target_cell});
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  stack.back().propagations->back().targets.back().single_value_deductions.push_back({event.cell, event.value});
  stack.back().sudoku_is_solved =
    &stack.back().propagations->back().targets.back().single_value_deductions.back().solved;
}

template<unsigned size>
void Explanation<size>::Builder::operator()(
  const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event
) {
  stack.back().propagations->back().targets.back().single_place_deductions.push_back(
    {event.region, event.cell, event.value});
  stack.back().sudoku_is_solved =
    &stack.back().propagations->back().targets.back().single_place_deductions.back().solved;
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationIsDoneForCell<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::PropagationIsDoneForSudoku<size>&) {
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::ExplorationStarts<size>& event) {
  assert(stack.back().exploration != nullptr);
  assert(!stack.back().exploration->has_value());
  stack.back().exploration->emplace(Exploration{event.cell, event.allowed_values, {}});
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::HypothesisIsMade<size>& event) {
  assert(stack.back().exploration != nullptr);
  assert(stack.back().exploration->has_value());
  Exploration& exploration = **stack.back().exploration;
  Hypothesis& hypothesis = exploration.explored_hypotheses.emplace_back(Hypothesis{event.value});
  stack.push_back({&hypothesis.propagations, &hypothesis.exploration, &hypothesis });
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::HypothesisIsRejected<size>&) {
  assert(stack.back().hypothesis != nullptr);
  stack.back().hypothesis->successful = false;
  stack.pop_back();
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::SudokuIsSolved<size>&) {
  *stack.back().sudoku_is_solved = true;
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::HypothesisIsAccepted<size>&) {
  assert(stack.back().hypothesis != nullptr);
  stack.back().hypothesis->successful = true;
  stack.pop_back();
}

template<unsigned size>
void Explanation<size>::Builder::operator()(const exploration::ExplorationIsDone<size>&) {
}



template<>
struct Explanation<static_cast<unsigned int>(4)>
{
  struct SingleValueDeduction
  {
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
    // inline constexpr SingleValueDeduction(SingleValueDeduction &&) noexcept = default;
  };
  
  struct SinglePlaceDeduction
  {
    unsigned int region;
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
    // inline constexpr SinglePlaceDeduction(SinglePlaceDeduction &&) noexcept = default;
  };
  
  struct PropagationTarget
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> > single_value_deductions;
    std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> > single_place_deductions;
    // inline constexpr PropagationTarget(PropagationTarget &&) noexcept = default;
    // inline constexpr ~PropagationTarget() noexcept = default;
  };
  
  struct Propagation
  {
    std::pair<unsigned int, unsigned int> source;
    unsigned int value;
    std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> > targets;
    // inline constexpr Propagation(Propagation &&) noexcept = default;
    // inline constexpr ~Propagation() noexcept = default;
  };
  
  struct Exploration
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> > explored_hypotheses;
    // inline constexpr Exploration(Exploration &&) noexcept = default;
    // inline constexpr ~Exploration() noexcept = default;
  };
  
  struct Hypothesis
  {
    unsigned int value;
    std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > propagations;
    std::optional<Explanation<4>::Exploration> exploration;
    bool successful;
    // inline constexpr Hypothesis(Hypothesis &&) noexcept = default;
    // inline constexpr ~Hypothesis() noexcept = default;
  };
  
  struct Exploration;
  Sudoku<ValueCell, 4> inputs;
  std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > propagations;
  std::optional<Explanation<4>::Exploration> exploration;
  
  public: 
  class Builder
  {
    
    private: 
    struct Frame
    {
      inline Frame(std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > * propagations_, std::optional<Explanation<4>::Exploration> * exploration_, Hypothesis * hypothesis_)
      : propagations{propagations_}
      , exploration{exploration_}
      , hypothesis{hypothesis_}
      , sudoku_is_solved{static_cast<bool *>(nullptr)}
      {
        (static_cast<bool>(this->propagations) ? void(0) : __assert_fail(static_cast<const char *>("propagations"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(78), static_cast<const char *>(__extension__"Explanation<4>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *, Hypothesis *) [size = 4]")));
        (static_cast<bool>(this->exploration) ? void(0) : __assert_fail(static_cast<const char *>("exploration"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"Explanation<4>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *, Hypothesis *) [size = 4]")));
        (static_cast<bool>(this->hypothesis) ? void(0) : __assert_fail(static_cast<const char *>("hypothesis"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(80), static_cast<const char *>(__extension__"Explanation<4>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *, Hypothesis *) [size = 4]")));
      }
      
      inline Frame(std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > * propagations_, std::optional<Explanation<4>::Exploration> * exploration_)
      : propagations{propagations_}
      , exploration{exploration_}
      , hypothesis{static_cast<Explanation<4>::Hypothesis *>(nullptr)}
      , sudoku_is_solved{static_cast<bool *>(nullptr)}
      {
        (static_cast<bool>(this->propagations) ? void(0) : __assert_fail(static_cast<const char *>("propagations"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(92), static_cast<const char *>(__extension__"Explanation<4>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *) [size = 4]")));
        (static_cast<bool>(this->exploration) ? void(0) : __assert_fail(static_cast<const char *>("exploration"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(93), static_cast<const char *>(__extension__"Explanation<4>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *) [size = 4]")));
      }
      
      std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > * propagations;
      std::optional<Explanation<4>::Exploration> * exploration;
      Hypothesis * hypothesis;
      bool * sudoku_is_solved;
      // inline constexpr Frame(const Frame &) noexcept = default;
      // inline constexpr Frame(Frame &&) noexcept = default;
    };
    
    
    public: 
    inline Builder()
    : explanation{Explanation<static_cast<unsigned int>(4)>()}
    , stack{std::vector<Explanation<4>::Builder::Frame, std::allocator<Explanation<4>::Builder::Frame> >(static_cast<unsigned long>(1), std::vector<Explanation<4>::Builder::Frame>::value_type{&this->explanation.propagations, &this->explanation.exploration}, static_cast<const std::allocator<Explanation<4>::Builder::Frame>>(std::allocator<Explanation<4>::Builder::Frame>()))}
    {
    }
    
    
    public: 
    void operator()(const exploration::CellIsSetInInput<4> & event)
    {
      static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 4>&>(this->explanation.inputs).cell(event.cell)).set(event.value);
    }
    
    void operator()(const exploration::InputsAreDone<4> &)
    {
    }
    
    void operator()(const exploration::PropagationStartsForSudoku<4> &)
    {
    }
    
    void operator()(const exploration::PropagationStartsForCell<4> & event)
    {
      (static_cast<bool>(!static_cast<const std::vector<Explanation<4>::Builder::Frame, std::allocator<Explanation<4>::Builder::Frame> >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(20), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::PropagationStartsForCell<size> &) [size = 4]")));
      (static_cast<bool>(this->stack.back().propagations != static_cast<std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(21), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::PropagationStartsForCell<size> &) [size = 4]")));
      this->stack.back().propagations->push_back({std::pair<unsigned int, unsigned int>(event.cell), event.value, std::vector<Explanation<4>::PropagationTarget, std::allocator<Explanation<4>::PropagationTarget> >{}});
    }
    
    void operator()(const exploration::CellPropagates<4> & event)
    {
      (static_cast<bool>(!static_cast<const std::vector<Explanation<4>::Builder::Frame, std::allocator<Explanation<4>::Builder::Frame> >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(27), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 4]")));
      (static_cast<bool>(this->stack.back().propagations != static_cast<std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(28), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 4]")));
      (static_cast<bool>(!static_cast<const std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > *>(this->stack.back().propagations)->empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.back().propagations->empty()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(29), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 4]")));
      (static_cast<bool>(std::operator==(static_cast<const std::pair<unsigned int, unsigned int>>(this->stack.back().propagations->back().source), event.source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations->back().source == event.source_cell"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(30), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 4]")));
      (static_cast<bool>(this->stack.back().propagations->back().value == event.value) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations->back().value == event.value"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(31), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 4]")));
      this->stack.back().propagations->back().targets.push_back({std::pair<unsigned int, unsigned int>(event.target_cell), std::vector<Explanation<4>::SingleValueDeduction, std::allocator<Explanation<4>::SingleValueDeduction> >{}, std::vector<Explanation<4>::SinglePlaceDeduction, std::allocator<Explanation<4>::SinglePlaceDeduction> >{}});
    }
    
    void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
    {
      this->stack.back().propagations->back().targets.back().single_value_deductions.push_back({std::pair<unsigned int, unsigned int>(event.cell), event.value, false});
      this->stack.back().sudoku_is_solved = &this->stack.back().propagations->back().targets.back().single_value_deductions.back().solved;
    }
    
    void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
    {
      this->stack.back().propagations->back().targets.back().single_place_deductions.push_back({event.region, std::pair<unsigned int, unsigned int>(event.cell), event.value, false});
      this->stack.back().sudoku_is_solved = &this->stack.back().propagations->back().targets.back().single_place_deductions.back().solved;
    }
    
    void operator()(const exploration::PropagationIsDoneForCell<4> &)
    {
    }
    
    void operator()(const exploration::PropagationIsDoneForSudoku<4> &)
    {
    }
    
    void operator()(const exploration::ExplorationStarts<4> & event)
    {
      (static_cast<bool>(this->stack.back().exploration != static_cast<std::optional<Explanation<4>::Exploration> *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().exploration != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(62), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::ExplorationStarts<size> &) [size = 4]")));
      (static_cast<bool>(!static_cast<const std::optional<Explanation<4>::Exploration> *>(this->stack.back().exploration)->has_value()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.back().exploration->has_value()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(63), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::ExplorationStarts<size> &) [size = 4]")));
      this->stack.back().exploration->emplace<Explanation<4>::Exploration>(Explanation<4>::Exploration{std::pair<unsigned int, unsigned int>(event.cell), std::vector<unsigned int, std::allocator<unsigned int> >(event.allowed_values), std::vector<Explanation<4>::Hypothesis, std::allocator<Explanation<4>::Hypothesis> >{}});
    }
    
    void operator()(const exploration::HypothesisIsMade<4> & event)
    {
      (static_cast<bool>(this->stack.back().exploration != static_cast<std::optional<Explanation<4>::Exploration> *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().exploration != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(69), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::HypothesisIsMade<size> &) [size = 4]")));
      (static_cast<bool>(static_cast<const std::optional<Explanation<4>::Exploration> *>(this->stack.back().exploration)->has_value()) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().exploration->has_value()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(70), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::HypothesisIsMade<size> &) [size = 4]")));
      Exploration & exploration = (*this->stack.back().exploration).operator*();
      Hypothesis & hypothesis = exploration.explored_hypotheses.emplace_back<Explanation<4>::Hypothesis>(Explanation<4>::Hypothesis{event.value, std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> >{}, std::optional<Explanation<4>::Exploration>{}, false});
      this->stack.push_back(std::vector<Explanation<4>::Builder::Frame>::value_type{&hypothesis.propagations, &hypothesis.exploration, &hypothesis});
    }
    
    void operator()(const exploration::HypothesisIsRejected<4> &)
    {
      (static_cast<bool>(this->stack.back().hypothesis != static_cast<Explanation<4>::Hypothesis *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().hypothesis != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(78), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::HypothesisIsRejected<size> &) [size = 4]")));
      this->stack.back().hypothesis->successful = false;
      this->stack.pop_back();
    }
    
    void operator()(const exploration::SudokuIsSolved<4> &)
    {
      *this->stack.back().sudoku_is_solved = true;
    }
    
    void operator()(const exploration::HypothesisIsAccepted<4> &)
    {
      (static_cast<bool>(this->stack.back().hypothesis != static_cast<Explanation<4>::Hypothesis *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().hypothesis != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(90), static_cast<const char *>(__extension__"void Explanation<4>::Builder::operator()(const exploration::HypothesisIsAccepted<size> &) [size = 4]")));
      this->stack.back().hypothesis->successful = true;
      this->stack.pop_back();
    }
    
    void operator()(const exploration::ExplorationIsDone<4> &)
    {
    }
    
    
    public: 
    inline Explanation<static_cast<unsigned int>(4)> get()
    {
      (static_cast<bool>(static_cast<const std::vector<Explanation<4>::Builder::Frame, std::allocator<Explanation<4>::Builder::Frame> >>(this->stack).size() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("stack.size() == 1"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(124), static_cast<const char *>(__extension__"Explanation<size> Explanation<4>::Builder::get() [size = 4]")));
      return Explanation<static_cast<unsigned int>(4)>(std::move<Explanation<static_cast<unsigned int>(4)> &>(this->explanation));
    }
    
    
    private: 
    Explanation<static_cast<unsigned int>(4)> explanation;
    std::vector<Explanation<4>::Builder::Frame, std::allocator<Explanation<4>::Builder::Frame> > stack;
    public: 
  };
  
  // inline Explanation(Explanation<static_cast<unsigned int>(4)> &&) noexcept(false) = default;
  // inline constexpr ~Explanation() noexcept = default;
  // inline Explanation() noexcept(false) = default;
};





template<>
struct Explanation<static_cast<unsigned int>(9)>
{
  struct SingleValueDeduction
  {
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
    // inline constexpr SingleValueDeduction(SingleValueDeduction &&) noexcept = default;
  };
  
  struct SinglePlaceDeduction
  {
    unsigned int region;
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    bool solved;
    // inline constexpr SinglePlaceDeduction(SinglePlaceDeduction &&) noexcept = default;
  };
  
  struct PropagationTarget
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> > single_value_deductions;
    std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> > single_place_deductions;
    // inline constexpr PropagationTarget(PropagationTarget &&) noexcept = default;
    // inline constexpr ~PropagationTarget() noexcept = default;
  };
  
  struct Propagation
  {
    std::pair<unsigned int, unsigned int> source;
    unsigned int value;
    std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> > targets;
    // inline constexpr Propagation(Propagation &&) noexcept = default;
    // inline constexpr ~Propagation() noexcept = default;
  };
  
  struct Exploration
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> > explored_hypotheses;
    // inline constexpr Exploration(Exploration &&) noexcept = default;
    // inline constexpr ~Exploration() noexcept = default;
  };
  
  struct Hypothesis
  {
    unsigned int value;
    std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > propagations;
    std::optional<Explanation<9>::Exploration> exploration;
    bool successful;
    // inline constexpr Hypothesis(Hypothesis &&) noexcept = default;
    // inline constexpr ~Hypothesis() noexcept = default;
  };
  
  struct Exploration;
  Sudoku<ValueCell, 9> inputs;
  std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > propagations;
  std::optional<Explanation<9>::Exploration> exploration;
  
  public: 
  class Builder
  {
    
    private: 
    struct Frame
    {
      inline Frame(std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > * propagations_, std::optional<Explanation<9>::Exploration> * exploration_, Hypothesis * hypothesis_)
      : propagations{propagations_}
      , exploration{exploration_}
      , hypothesis{hypothesis_}
      , sudoku_is_solved{static_cast<bool *>(nullptr)}
      {
        (static_cast<bool>(this->propagations) ? void(0) : __assert_fail(static_cast<const char *>("propagations"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(78), static_cast<const char *>(__extension__"Explanation<9>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *, Hypothesis *) [size = 9]")));
        (static_cast<bool>(this->exploration) ? void(0) : __assert_fail(static_cast<const char *>("exploration"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"Explanation<9>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *, Hypothesis *) [size = 9]")));
        (static_cast<bool>(this->hypothesis) ? void(0) : __assert_fail(static_cast<const char *>("hypothesis"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(80), static_cast<const char *>(__extension__"Explanation<9>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *, Hypothesis *) [size = 9]")));
      }
      
      inline Frame(std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > * propagations_, std::optional<Explanation<9>::Exploration> * exploration_)
      : propagations{propagations_}
      , exploration{exploration_}
      , hypothesis{static_cast<Explanation<9>::Hypothesis *>(nullptr)}
      , sudoku_is_solved{static_cast<bool *>(nullptr)}
      {
        (static_cast<bool>(this->propagations) ? void(0) : __assert_fail(static_cast<const char *>("propagations"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(92), static_cast<const char *>(__extension__"Explanation<9>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *) [size = 9]")));
        (static_cast<bool>(this->exploration) ? void(0) : __assert_fail(static_cast<const char *>("exploration"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(93), static_cast<const char *>(__extension__"Explanation<9>::Builder::Frame::Frame(std::vector<Propagation> *, std::optional<Exploration> *) [size = 9]")));
      }
      
      std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > * propagations;
      std::optional<Explanation<9>::Exploration> * exploration;
      Hypothesis * hypothesis;
      bool * sudoku_is_solved;
      // inline constexpr Frame(const Frame &) noexcept = default;
      // inline constexpr Frame(Frame &&) noexcept = default;
    };
    
    
    public: 
    inline Builder()
    : explanation{Explanation<static_cast<unsigned int>(9)>()}
    , stack{std::vector<Explanation<9>::Builder::Frame, std::allocator<Explanation<9>::Builder::Frame> >(static_cast<unsigned long>(1), std::vector<Explanation<9>::Builder::Frame>::value_type{&this->explanation.propagations, &this->explanation.exploration}, static_cast<const std::allocator<Explanation<9>::Builder::Frame>>(std::allocator<Explanation<9>::Builder::Frame>()))}
    {
    }
    
    
    public: 
    void operator()(const exploration::CellIsSetInInput<9> & event)
    {
      static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 9>&>(this->explanation.inputs).cell(event.cell)).set(event.value);
    }
    
    void operator()(const exploration::InputsAreDone<9> &)
    {
    }
    
    void operator()(const exploration::PropagationStartsForSudoku<9> &)
    {
    }
    
    void operator()(const exploration::PropagationStartsForCell<9> & event)
    {
      (static_cast<bool>(!static_cast<const std::vector<Explanation<9>::Builder::Frame, std::allocator<Explanation<9>::Builder::Frame> >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(20), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::PropagationStartsForCell<size> &) [size = 9]")));
      (static_cast<bool>(this->stack.back().propagations != static_cast<std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(21), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::PropagationStartsForCell<size> &) [size = 9]")));
      this->stack.back().propagations->push_back({std::pair<unsigned int, unsigned int>(event.cell), event.value, std::vector<Explanation<9>::PropagationTarget, std::allocator<Explanation<9>::PropagationTarget> >{}});
    }
    
    void operator()(const exploration::CellPropagates<9> & event)
    {
      (static_cast<bool>(!static_cast<const std::vector<Explanation<9>::Builder::Frame, std::allocator<Explanation<9>::Builder::Frame> >>(this->stack).empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.empty()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(27), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 9]")));
      (static_cast<bool>(this->stack.back().propagations != static_cast<std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(28), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 9]")));
      (static_cast<bool>(!static_cast<const std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> > *>(this->stack.back().propagations)->empty()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.back().propagations->empty()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(29), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 9]")));
      (static_cast<bool>(std::operator==(static_cast<const std::pair<unsigned int, unsigned int>>(this->stack.back().propagations->back().source), event.source_cell)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations->back().source == event.source_cell"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(30), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 9]")));
      (static_cast<bool>(this->stack.back().propagations->back().value == event.value) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().propagations->back().value == event.value"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(31), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::CellPropagates<size> &) [size = 9]")));
      this->stack.back().propagations->back().targets.push_back({std::pair<unsigned int, unsigned int>(event.target_cell), std::vector<Explanation<9>::SingleValueDeduction, std::allocator<Explanation<9>::SingleValueDeduction> >{}, std::vector<Explanation<9>::SinglePlaceDeduction, std::allocator<Explanation<9>::SinglePlaceDeduction> >{}});
    }
    
    void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
    {
      this->stack.back().propagations->back().targets.back().single_value_deductions.push_back({std::pair<unsigned int, unsigned int>(event.cell), event.value, false});
      this->stack.back().sudoku_is_solved = &this->stack.back().propagations->back().targets.back().single_value_deductions.back().solved;
    }
    
    void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
    {
      this->stack.back().propagations->back().targets.back().single_place_deductions.push_back({event.region, std::pair<unsigned int, unsigned int>(event.cell), event.value, false});
      this->stack.back().sudoku_is_solved = &this->stack.back().propagations->back().targets.back().single_place_deductions.back().solved;
    }
    
    void operator()(const exploration::PropagationIsDoneForCell<9> &)
    {
    }
    
    void operator()(const exploration::PropagationIsDoneForSudoku<9> &)
    {
    }
    
    void operator()(const exploration::ExplorationStarts<9> & event)
    {
      (static_cast<bool>(this->stack.back().exploration != static_cast<std::optional<Explanation<9>::Exploration> *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().exploration != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(62), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::ExplorationStarts<size> &) [size = 9]")));
      (static_cast<bool>(!static_cast<const std::optional<Explanation<9>::Exploration> *>(this->stack.back().exploration)->has_value()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.back().exploration->has_value()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(63), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::ExplorationStarts<size> &) [size = 9]")));
      this->stack.back().exploration->emplace<Explanation<9>::Exploration>(Explanation<9>::Exploration{std::pair<unsigned int, unsigned int>(event.cell), std::vector<unsigned int, std::allocator<unsigned int> >(event.allowed_values), std::vector<Explanation<9>::Hypothesis, std::allocator<Explanation<9>::Hypothesis> >{}});
    }
    
    void operator()(const exploration::HypothesisIsMade<9> & event)
    {
      (static_cast<bool>(this->stack.back().exploration != static_cast<std::optional<Explanation<9>::Exploration> *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().exploration != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(69), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::HypothesisIsMade<size> &) [size = 9]")));
      (static_cast<bool>(static_cast<const std::optional<Explanation<9>::Exploration> *>(this->stack.back().exploration)->has_value()) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().exploration->has_value()"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(70), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::HypothesisIsMade<size> &) [size = 9]")));
      Exploration & exploration = (*this->stack.back().exploration).operator*();
      Hypothesis & hypothesis = exploration.explored_hypotheses.emplace_back<Explanation<9>::Hypothesis>(Explanation<9>::Hypothesis{event.value, std::vector<Explanation<9>::Propagation, std::allocator<Explanation<9>::Propagation> >{}, std::optional<Explanation<9>::Exploration>{}, false});
      this->stack.push_back(std::vector<Explanation<9>::Builder::Frame>::value_type{&hypothesis.propagations, &hypothesis.exploration, &hypothesis});
    }
    
    void operator()(const exploration::HypothesisIsRejected<9> &)
    {
      (static_cast<bool>(this->stack.back().hypothesis != static_cast<Explanation<9>::Hypothesis *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().hypothesis != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(78), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::HypothesisIsRejected<size> &) [size = 9]")));
      this->stack.back().hypothesis->successful = false;
      this->stack.pop_back();
    }
    
    void operator()(const exploration::SudokuIsSolved<9> &)
    {
      *this->stack.back().sudoku_is_solved = true;
    }
    
    void operator()(const exploration::HypothesisIsAccepted<9> &)
    {
      (static_cast<bool>(this->stack.back().hypothesis != static_cast<Explanation<9>::Hypothesis *>(nullptr)) ? void(0) : __assert_fail(static_cast<const char *>("stack.back().hypothesis != nullptr"), static_cast<const char *>("src/explanation/explanation.cpp"), static_cast<unsigned int>(90), static_cast<const char *>(__extension__"void Explanation<9>::Builder::operator()(const exploration::HypothesisIsAccepted<size> &) [size = 9]")));
      this->stack.back().hypothesis->successful = true;
      this->stack.pop_back();
    }
    
    void operator()(const exploration::ExplorationIsDone<9> &)
    {
    }
    
    
    public: 
    inline Explanation<static_cast<unsigned int>(9)> get()
    {
      (static_cast<bool>(static_cast<const std::vector<Explanation<9>::Builder::Frame, std::allocator<Explanation<9>::Builder::Frame> >>(this->stack).size() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("stack.size() == 1"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(124), static_cast<const char *>(__extension__"Explanation<size> Explanation<9>::Builder::get() [size = 9]")));
      return Explanation<static_cast<unsigned int>(9)>(std::move<Explanation<static_cast<unsigned int>(9)> &>(this->explanation));
    }
    
    
    private: 
    Explanation<static_cast<unsigned int>(9)> explanation;
    std::vector<Explanation<9>::Builder::Frame, std::allocator<Explanation<9>::Builder::Frame> > stack;
    public: 
  };
  
  // inline Explanation(Explanation<static_cast<unsigned int>(9)> &&) noexcept(false) = default;
  // inline constexpr ~Explanation() noexcept = default;
  // inline Explanation() noexcept(false) = default;
};



