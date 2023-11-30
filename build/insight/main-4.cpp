# 1 "src/main-4.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/main.impl.hpp"
// Copyright 2023 Vincent Jacques

#ifndef MAIN_IMPL_HPP_
#define MAIN_IMPL_HPP_

# 1 "src/main.hpp"
// Copyright 2023 Vincent Jacques

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <filesystem>
#include <optional>


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
};



template<unsigned int size>
int main_(const Options & options);
;

#endif  // MAIN_HPP_
# 7 "src/main.impl.hpp"

#include <fstream>
#include <memory>
#include <vector>

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

/* First instantiated from: main-4.cpp:374 */
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

/* First instantiated from: main-4.cpp:430 */
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
  
  /* First instantiated from: main-4.cpp:301 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main-4.cpp:306 */
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
  
  /* First instantiated from: main-4.cpp:320 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> copy_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &, const std::array<std::array<Cell, 4>, 4> & other_cells)
  {
    return {{this->copy_row<0, 1, 2, 3>(0U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(1U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(2U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->copy_row<0, 1, 2, 3>(3U, other_cells, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> copy_row(unsigned int row, const std::array<std::array<Cell, 4>, 4> & other_cells, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main-4.cpp:325 */
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
/* First instantiated from: main-4.cpp:590 */
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
  
  /* First instantiated from: main-4.cpp:301 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline std::array<std::array<Cell, 4>, 4> make_cells<0, 1, 2, 3>(const std::integer_sequence<unsigned int, 0, 1, 2, 3> &)
  {
    return {{this->make_row<0, 1, 2, 3>(0U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(1U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(2U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>())), this->make_row<0, 1, 2, 3>(3U, static_cast<const std::integer_sequence<unsigned int, 0, 1, 2, 3>>(std::integer_sequence<unsigned int, 0, 1, 2, 3>()))}};
  }
  #endif
  
  template<unsigned int ...col>
  inline std::array<Cell, 4> make_row(unsigned int row, const std::integer_sequence<unsigned int, col...> &);
  
  /* First instantiated from: main-4.cpp:306 */
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

/* First instantiated from: main-4.cpp:1496 */
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
  
  inline unsigned int get() const
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail(static_cast<const char *>("is_set()"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(49), static_cast<const char *>(__extension__"unsigned int AnnotatedCell<4>::get() const [size = 4]")));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < 4U) ? void(0) : __assert_fail(static_cast<const char *>("value < size"), static_cast<const char *>("src/exploration/annotations.hpp"), static_cast<unsigned int>(56), static_cast<const char *>(__extension__"bool AnnotatedCell<4>::is_allowed(const unsigned int) const [size = 4]")));
    return this->allowed_values.test(static_cast<unsigned long>(value));
  }
  
  inline void set_input(const unsigned int value);
  
  inline void set_hypothesis(const unsigned int value);
  
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

/* First instantiated from: main-4.cpp:1432 */
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
  
  /* First instantiated from: main-4.cpp:1439 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct InputsAreDone
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main-4.cpp:1444 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct InputsAreDone<4>
  {
    void apply(Stack<4> *) const;
    
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main-4.cpp:1261 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
  };
  
  #endif
  template<unsigned int size>
  struct PropagationStartsForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main-4.cpp:1273 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<4>
  {
    void apply(Stack<4> *) const;
    
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
  
  /* First instantiated from: main-4.cpp:1287 */
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
  template<unsigned int size>
  struct CellIsDeducedFromSingleAllowedValue
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main-4.cpp:1292 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<4>
  {
    void apply(Stack<4> *) const;
    
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
  
  /* First instantiated from: main-4.cpp:1321 */
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
  template<unsigned int size>
  struct PropagationIsDoneForCell
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main-4.cpp:1274 */
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
  template<unsigned int size>
  struct PropagationIsDoneForSudoku
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main-4.cpp:1262 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForSudoku<4>
  {
    void apply(Stack<4> *) const;
    
    // inline constexpr PropagationIsDoneForSudoku(const PropagationIsDoneForSudoku<4> &) noexcept = default;
  };
  
  #endif
  template<unsigned int size>
  struct ExplorationStarts
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  /* First instantiated from: main-4.cpp:1391 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<4>
  {
    void apply(Stack<4> *) const;
    
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
  
  /* First instantiated from: main-4.cpp:1396 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<4>
  {
    void apply(Stack<4> *) const;
    
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
  
  /* First instantiated from: main-4.cpp:1401 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  template<unsigned int size>
  struct SudokuIsSolved
  {
    void apply(Stack<size> *) const;
    
  };
  
  /* First instantiated from: main-4.cpp:1299 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct SudokuIsSolved<4>
  {
    void apply(Stack<4> *) const;
    
  };
  
  #endif
  template<unsigned int size>
  struct HypothesisIsAccepted
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: main-4.cpp:1398 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<4>
  {
    void apply(Stack<4> *) const;
    
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
  
  /* First instantiated from: main-4.cpp:1392 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    // inline constexpr ExplorationIsDone(const ExplorationIsDone<4> &) noexcept = default;
  };
  
  #endif
  
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

/* First instantiated from: main-4.cpp:1530 */
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
    // inline constexpr ~PropagationTarget() noexcept = default;
  };
  
  struct Propagation
  {
    std::pair<unsigned int, unsigned int> source;
    unsigned int value;
    std::vector<PropagationTarget, std::allocator<PropagationTarget> > targets;
    // inline constexpr ~Propagation() noexcept = default;
  };
  
  struct Exploration
  {
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
    std::vector<Hypothesis, std::allocator<Hypothesis> > explored_hypotheses;
    // inline constexpr Exploration(Exploration &&) noexcept = default;
    // inline constexpr ~Exploration() noexcept = default;
  };
  
  struct Hypothesis
  {
    unsigned int value;
    std::vector<Propagation, std::allocator<Propagation> > propagations;
    std::optional<Exploration> exploration;
    bool successful;
    // inline constexpr ~Hypothesis() noexcept = default;
  };
  
  struct Exploration;
  Sudoku<ValueCell, 4> inputs;
  std::vector<Propagation, std::allocator<Propagation> > propagations;
  std::optional<Exploration> exploration;
  
  public: 
  class Builder
  {
    
    private: 
    struct Frame
    {
      inline Frame(std::vector<Explanation<4>::Propagation, std::allocator<Explanation<4>::Propagation> > * propagations_, std::optional<Explanation<4>::Exploration> * exploration_, Hypothesis * hypothesis_);
      
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
    };
    
    
    public: 
    inline Builder()
    : explanation{Explanation<4>()}
    , stack{std::vector<Frame, std::allocator<Frame> >(static_cast<unsigned long>(1), std::vector<Frame>::value_type{&this->explanation.propagations, &this->explanation.exploration}, static_cast<const std::allocator<Frame>>(std::allocator<Frame>()))}
    {
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
    
    
    public: 
    inline Explanation<4> get()
    {
      (static_cast<bool>(static_cast<const std::vector<Frame, std::allocator<Frame> >>(this->stack).size() == static_cast<unsigned long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("stack.size() == 1"), static_cast<const char *>("src/explanation/explanation.hpp"), static_cast<unsigned int>(124), static_cast<const char *>(__extension__"Explanation<size> Explanation<4>::Builder::get() [size = 4]")));
      return Explanation<4>(std::move<Explanation<4> &>(this->explanation));
    }
    
    
    private: 
    Explanation<4> explanation;
    std::vector<Frame, std::allocator<Frame> > stack;
    public: 
    // inline constexpr ~Builder() noexcept = default;
  };
  
  // inline Explanation(Explanation<4> &&) noexcept(false) = default;
  // inline constexpr ~Explanation() noexcept = default;
  // inline Explanation() noexcept(false) = default;
};

#endif



#endif  // EXPLANATION_EXPLANATION_HPP_
# 13 "src/main.impl.hpp"
# 1 "src/explanation/html-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>

# 9 "src/explanation/html-explainer.hpp"


template<unsigned int size>
void explain_as_html(const Explanation<size> &, const std::filesystem::path &, unsigned int width, unsigned int height);
;

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
# 14 "src/main.impl.hpp"
# 1 "src/explanation/text-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <iostream>

# 9 "src/explanation/text-explainer.hpp"


template<unsigned int size>
void explain_as_text(const Explanation<size> &, std::basic_ostream<char> &, bool);
;

#endif  // EXPLANATION_TEXT_EXPLAINER_HPP_
# 15 "src/main.impl.hpp"
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
    inline explicit FramesSerializer(const std::filesystem::path & directory_path_, const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & file_name_prefix_)
    : Serializer()
    , frame_index{static_cast<unsigned int>(0)}
    , directory_path{std::filesystem::path(directory_path_)}
    , file_name_prefix{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(file_name_prefix_)}
    {
      std::filesystem::create_directories(this->directory_path);
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path &&>((operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(this->next_frame_name(), std::filesystem::path::auto_format))))).string()));
    }
    
    inline std::basic_string<char, std::char_traits<char>, std::allocator<char> > next_frame_name()
    {
      std::basic_ostringstream<char> oss = std::basic_ostringstream<char>();
      std::operator<<(std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(oss), this->file_name_prefix), std::setfill<char>('0')), std::setw(6)).operator<<(this->frame_index), static_cast<const char *>(".png"));
      ++this->frame_index;
      return static_cast<const std::basic_ostringstream<char>>(oss).str();
    }
    
    
    private: 
    unsigned int frame_index;
    const std::filesystem::path directory_path;
    const std::basic_string<char, std::char_traits<char>, std::allocator<char> > file_name_prefix;
    public: 
    // inline FramesSerializer & operator=(const FramesSerializer &) /* noexcept */ = delete;
    // inline FramesSerializer & operator=(FramesSerializer &&) /* noexcept */ = delete;
    // inline virtual ~FramesSerializer() noexcept = default;
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
# 16 "src/main.impl.hpp"
# 1 "src/explanation/video-explainer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_EXPLAINER_HPP_
#define EXPLANATION_VIDEO_EXPLAINER_HPP_

# 7 "src/explanation/video-explainer.hpp"
# 8 "src/explanation/video-explainer.hpp"


template<unsigned int size>
void explain_as_video(const Explanation<size> &, video::Serializer *, bool quick, unsigned int width, unsigned int height);
;

#endif  // EXPLANATION_VIDEO_EXPLAINER_HPP_
# 17 "src/main.impl.hpp"
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
    inline explicit VideoSerializer(const std::filesystem::path & video_path_, int frame_width_, int frame_height_)
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
      (static_cast<bool>(this->codec) ? void(0) : __assert_fail(static_cast<const char *>("codec"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(39), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      (static_cast<bool>(this->pkt) ? void(0) : __assert_fail(static_cast<const char *>("pkt"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(40), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      (static_cast<bool>(this->outfile) ? void(0) : __assert_fail(static_cast<const char *>("outfile"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(41), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      this->context->bit_rate = static_cast<long>(400000);
      this->context->width = this->frame_width_pixels;
      this->context->height = this->frame_height_pixels;
      this->context->time_base.operator=(AVRational{1, 25});
      this->context->framerate.operator=(AVRational{25, 1});
      this->context->gop_size = 10;
      this->context->max_b_frames = 1;
      this->context->pix_fmt = AV_PIX_FMT_YUV420P;
      int ret = avcodec_open2(this->context, this->codec, static_cast<AVDictionary **>(NULL));
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(53), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      this->picture->format = static_cast<int>(this->context->pix_fmt);
      this->picture->width = this->frame_width_pixels;
      this->picture->height = this->frame_height_pixels;
      ret = av_frame_get_buffer(this->picture, 32);
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(60), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
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
      (static_cast<bool>(static_cast<const Cairo::ImageSurface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->get_width() == this->frame_width_pixels) ? void(0) : __assert_fail(static_cast<const char *>("surface->get_width() == frame_width_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<const Cairo::ImageSurface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->get_height() == this->frame_height_pixels) ? void(0) : __assert_fail(static_cast<const char *>("surface->get_height() == frame_height_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(80), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      unsigned char * data = static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->()->get_data();
      (static_cast<bool>(data) ? void(0) : __assert_fail(static_cast<const char *>("data"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(82), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<int *>(this->picture->linesize)[0] == this->frame_width_pixels) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[0] == frame_width_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(84), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<int *>(this->picture->linesize)[1] == (this->frame_width_pixels / 2)) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[1] == frame_width_pixels / 2"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(85), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<int *>(this->picture->linesize)[2] == (this->frame_width_pixels / 2)) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[2] == frame_width_pixels / 2"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(86), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      for(int y = 0; y < this->frame_height_pixels; ++y) {
        for(int x = 0; x < this->frame_width_pixels; ++x) {
          static_cast<unsigned char **>(this->picture->data)[0][(y * static_cast<int *>(this->picture->linesize)[0]) + x] = (static_cast<unsigned char>(((static_cast<double>(static_cast<int>(data[(((y * this->frame_width_pixels) * 4) + (x * 4)) + 0])) * 0.29899999999999999) + (static_cast<double>(static_cast<int>(data[(((y * this->frame_width_pixels) * 4) + (x * 4)) + 1])) * 0.58699999999999997)) + (static_cast<double>(static_cast<int>(data[(((y * this->frame_width_pixels) * 4) + (x * 4)) + 2])) * 0.114)));
        }
        
      }
      
      for(int y = 0; y < (this->frame_height_pixels / 2); ++y) {
        for(int x = 0; x < (this->frame_width_pixels / 2); ++x) {
          static_cast<unsigned char **>(this->picture->data)[1][(y * static_cast<int *>(this->picture->linesize)[1]) + x] = (static_cast<unsigned char>((((static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 0])) * -0.16900000000000001) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 1])) * -0.33100000000000002)) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 2])) * 0.5)) + static_cast<double>(128)));
          static_cast<unsigned char **>(this->picture->data)[2][(y * static_cast<int *>(this->picture->linesize)[2]) + x] = (static_cast<unsigned char>((((static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 0])) * 0.5) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 1])) * -0.41899999999999998)) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 2])) * -0.081000000000000003)) + static_cast<double>(128)));
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
    int frame_width_pixels;
    int frame_height_pixels;
    const AVCodec * codec;
    AVCodecContext * context;
    AVFrame * picture;
    AVPacket * pkt;
    FILE * outfile;
    public: 
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
# 18 "src/main.impl.hpp"
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

/* First instantiated from: main-4.cpp:1433 */
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
  
  /* First instantiated from: main-4.cpp:1439 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1444 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1287 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1292 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1299 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1321 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1237 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1241 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1237 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1241 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1396 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1398 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1401 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1237 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1241 */
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
/* First instantiated from: main-4.cpp:1433 */
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
  
  /* First instantiated from: main-4.cpp:1439 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1444 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1287 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1292 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1299 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1321 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1237 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1241 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1237 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1241 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1396 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1398 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1401 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1237 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  inline void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & event) const
  {
    event.apply(this->stack);
    this->add_event.operator()(event);
  }
  #endif
  
  
  /* First instantiated from: main-4.cpp:1241 */
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

/* First instantiated from: main-4.cpp:1259 */
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
/* First instantiated from: main-4.cpp:1259 */
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
/* First instantiated from: main-4.cpp:1271 */
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
/* First instantiated from: main-4.cpp:1271 */
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
/* First instantiated from: main-4.cpp:1389 */
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
/* First instantiated from: main-4.cpp:1389 */
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



/* First instantiated from: main-4.cpp:1259 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::PropagationStartsForSudoku<4> & in, const exploration::PropagationIsDoneForSudoku<4> & out_) -> EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >;
#endif


/* First instantiated from: main-4.cpp:1271 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::PropagationStartsForCell<4> & in, const exploration::PropagationIsDoneForCell<4> & out_) -> EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >;
#endif


/* First instantiated from: main-4.cpp:1389 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_5> & add_event_, const exploration::ExplorationStarts<4> & in, const exploration::ExplorationIsDone<4> & out_) -> EventsPairGuard<4, __lambda_5, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >;
#endif


/* First instantiated from: main-4.cpp:1259 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::PropagationStartsForSudoku<4> & in, const exploration::PropagationIsDoneForSudoku<4> & out_) -> EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >;
#endif


/* First instantiated from: main-4.cpp:1271 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::PropagationStartsForCell<4> & in, const exploration::PropagationIsDoneForCell<4> & out_) -> EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >;
#endif


/* First instantiated from: main-4.cpp:1389 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
EventsPairGuard(const EventAdder<4, __lambda_6> & add_event_, const exploration::ExplorationStarts<4> & in, const exploration::ExplorationIsDone<4> & out_) -> EventsPairGuard<4, __lambda_6, exploration::ExplorationStarts<4>, exploration::ExplorationIsDone<4> >;
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
                (static_cast<bool>(target_cell.allowed_count() > 1) ? void(0) : __assert_fail("target_cell.allowed_count() > 1", "src/exploration/sudoku-solver.hpp", 96, __extension____PRETTY_FUNCTION__));
                if(target_cell.is_allowed(value)) {
                  add_event(exploration::CellPropagates<size>(source_coords, target_coords, value));
                  if(target_cell.allowed_count() == 1) {
                    {
                      auto && __range3 = SudokuConstants<size>::values;
                      for(; ; ) {
                        unsigned int value;
                        if(target_cell.is_allowed(value)) {
                          add_event(exploration::CellIsDeducedFromSingleAllowedValue<size>(target_coords, value));
                          if(stack.current().is_solved()) {
                            add_event(exploration::SudokuIsSolved<size>());
                          } 
                          
                          (static_cast<bool>(std::count(todo.begin(), todo.end(), target_coords) == 0) ? void(0) : __assert_fail("std::count(todo.begin(), todo.end(), target_coords) == 0", "src/exploration/sudoku-solver.hpp", 113, __extension____PRETTY_FUNCTION__));
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
                        if(stack.current().is_solved()) {
                          add_event(exploration::SudokuIsSolved<size>());
                        } 
                        
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail("std::count(todo.begin(), todo.end(), single_coords) == 0", "src/exploration/sudoku-solver.hpp", 139, __extension____PRETTY_FUNCTION__));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
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


/* First instantiated from: main-4.cpp:1415 */
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
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), coords) == 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(67), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:269:42)]")));
    }
    
  }
  EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> > guard = EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >(add_event, static_cast<const exploration::PropagationStartsForSudoku<4>>(exploration::PropagationStartsForSudoku<4>()), static_cast<const exploration::PropagationIsDoneForSudoku<4>>(exploration::PropagationIsDoneForSudoku<4>()));
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:269:42)]")));
    const unsigned int value = static_cast<const AnnotatedCell<4>&>(source_cell).get();
    EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> > guard = EventsPairGuard<4, __lambda_5, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >(add_event, static_cast<const exploration::PropagationStartsForCell<4>>(exploration::PropagationStartsForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::PropagationIsDoneForCell<4>>(exploration::PropagationIsDoneForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
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
                (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(96), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:269:42)]")));
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
                          if(stack.current().is_solved()) {
                            add_event.operator()(static_cast<const exploration::SudokuIsSolved<4>>(exploration::SudokuIsSolved<4>()));
                          } 
                          
                          (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), target_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), target_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(113), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:269:42)]")));
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
                        if(stack.current().is_solved()) {
                          add_event.operator()(static_cast<const exploration::SudokuIsSolved<4>>(exploration::SudokuIsSolved<4>()));
                        } 
                        
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), single_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(139), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:269:42)]")));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
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


/* First instantiated from: main-4.cpp:1415 */
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
      (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), coords) == static_cast<long>(1)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), coords) == 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(67), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.impl.hpp:65:7)]")));
    }
    
  }
  EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> > guard = EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForSudoku<4>, exploration::PropagationIsDoneForSudoku<4> >(add_event, static_cast<const exploration::PropagationStartsForSudoku<4>>(exploration::PropagationStartsForSudoku<4>()), static_cast<const exploration::PropagationIsDoneForSudoku<4>>(exploration::PropagationIsDoneForSudoku<4>()));
  while(!static_cast<const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(todo.front()));
    todo.pop_front();
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.impl.hpp:65:7)]")));
    const unsigned int value = static_cast<const AnnotatedCell<4>&>(source_cell).get();
    EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> > guard = EventsPairGuard<4, __lambda_6, exploration::PropagationStartsForCell<4>, exploration::PropagationIsDoneForCell<4> >(add_event, static_cast<const exploration::PropagationStartsForCell<4>>(exploration::PropagationStartsForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), static_cast<const exploration::PropagationIsDoneForCell<4>>(exploration::PropagationIsDoneForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
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
                (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(96), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.impl.hpp:65:7)]")));
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
                          if(stack.current().is_solved()) {
                            add_event.operator()(static_cast<const exploration::SudokuIsSolved<4>>(exploration::SudokuIsSolved<4>()));
                          } 
                          
                          (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), target_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), target_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(113), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.impl.hpp:65:7)]")));
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
                        if(stack.current().is_solved()) {
                          add_event.operator()(static_cast<const exploration::SudokuIsSolved<4>>(exploration::SudokuIsSolved<4>()));
                        } 
                        
                        (static_cast<bool>(std::count<std::_Deque_iterator<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int> &, std::pair<unsigned int, unsigned int> *>, std::pair<unsigned int, unsigned int> >(todo.begin(), todo.end(), single_coords) == static_cast<long>(0)) ? void(0) : __assert_fail(static_cast<const char *>("std::count(todo.begin(), todo.end(), single_coords) == 0"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(139), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, std::deque<Coordinates>, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.impl.hpp:65:7)]")));
                        todo.push_back(single_coords);
                      } 
                      
                    }
                    
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


/* First instantiated from: main-4.cpp:1380 */
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



template<unsigned int size, typename AddEvent>
bool propagate_and_explore(const Stack<size> &, const std::deque<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size, AddEvent> &);
;


template<unsigned int size, typename AddEvent>
bool explore(const Stack<size> & stack, const EventAdder<size, AddEvent> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail("!stack.current().is_solved()", "src/exploration/sudoku-solver.hpp", 189, __extension____PRETTY_FUNCTION__));
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


/* First instantiated from: main-4.cpp:1419 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<4, __lambda_5>(const Stack<4> & stack, const EventAdder<4, __lambda_5> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(189), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/exploration/sudoku-solver.hpp:269:42)]")));
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


/* First instantiated from: main-4.cpp:1419 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<4, __lambda_6>(const Stack<4> & stack, const EventAdder<4, __lambda_6> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("src/exploration/sudoku-solver.hpp"), static_cast<unsigned int>(189), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size, AddEvent> &) [size = 4U, AddEvent = (lambda at src/main.impl.hpp:65:7)]")));
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


/* First instantiated from: main-4.cpp:1446 */
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


/* First instantiated from: main-4.cpp:1446 */
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


/* First instantiated from: main-4.cpp:1532 */
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


/* First instantiated from: main-4.cpp:1458 */
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


/* First instantiated from: main-4.cpp:1517 */
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
    inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> &) const
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


#endif  // EXPLORATION_SUDOKU_SOLVER_HPP_
# 19 "src/main.impl.hpp"
# 1 "src/puzzle/check.hpp"
// Copyright 2023 Vincent Jacques

#ifndef PUZZLE_CHECK_HPP_
#define PUZZLE_CHECK_HPP_

# 7 "src/puzzle/check.hpp"

template<unsigned int size>
bool is_solved(const Sudoku<ValueCell, size> &);
;

#endif  // PUZZLE_CHECK_HPP_
# 20 "src/main.impl.hpp"
# 1 "src/sat/sudoku-solver.hpp"
// Copyright 2023 Vincent Jacques

#ifndef SAT_SUDOKU_SOLVER_HPP_
#define SAT_SUDOKU_SOLVER_HPP_

# 7 "src/sat/sudoku-solver.hpp"


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_sat(Sudoku<ValueCell, size>);
;

#endif  // SAT_SUDOKU_SOLVER_HPP_
# 21 "src/main.impl.hpp"


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
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail("input.is_open()", "src/main.impl.hpp", 31, __extension____PRETTY_FUNCTION__));
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
      typename Explanation<size>::Builder explanation_builder;
                  
      class __lambda_6
      {
        public: 
        template<class type_parameter_1_0>
        inline auto operator()(const type_parameter_1_0 & event) const
        {
          explanation_builder(event);
        }
        
      };
      
      const auto solved = solve_using_exploration<size>(sudoku, __lambda_6{});
      const Explanation<size> explanation = explanation_builder.get();
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        explain_as_text(explanation, std::cout, false);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          std::basic_ofstream<char> out = std::basic_ofstream<char>(options.text_path.operator*(), std::ios_base::out);
          (static_cast<bool>(out.is_open()) ? void(0) : __assert_fail("out.is_open()", "src/main.impl.hpp", 76, __extension____PRETTY_FUNCTION__));
          explain_as_text(explanation, out, false);
        } 
        
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      if(std::operator==(options.video_text_path, "-")) {
        ++stdout_users;
        explain_as_text(explanation, std::cout, true);
      } else {
        if(static_cast<bool>(options.video_text_path.operator bool())) {
          std::basic_ofstream<char> out = std::basic_ofstream<char>(options.video_text_path.operator*(), std::ios_base::out);
          (static_cast<bool>(out.is_open()) ? void(0) : __assert_fail("out.is_open()", "src/main.impl.hpp", 89, __extension____PRETTY_FUNCTION__));
          explain_as_text(explanation, out, true);
        } 
        
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
      if(static_cast<bool>(options.html_path.operator bool())) {
        explain_as_html(explanation, options.html_path.operator*(), options.width, options.height);
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail("video_serializers.size() == 2", "src/main.impl.hpp", 110, __extension____PRETTY_FUNCTION__));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >{std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>())})));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        explain_as_video(explanation, static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
      } 
      
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


/* First instantiated from: main-4.cpp:1601 */
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
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("input.is_open()"), static_cast<const char *>("src/main.impl.hpp"), static_cast<unsigned int>(31), static_cast<const char *>(__extension__"auto main_(const Options &)::(anonymous class)::operator()() const")));
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
      typename Explanation<4U>::Builder explanation_builder = typename Explanation<4U>::Builder();
                  
      class __lambda_6
      {
        public: 
        template<class type_parameter_0_0>
        inline /*constexpr */ auto operator()(const type_parameter_0_0 & event) const
        {
          explanation_builder(event);
        }
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        
        #ifdef INSIGHTS_USE_TEMPLATE
        template<>
        inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & event) const
        {
          explanation_builder.operator()(event);
        }
        #endif
        
        private: 
        typename Explanation<4U>::Builder & explanation_builder;
        
        public:
        __lambda_6(Explanation<4>::Builder & _explanation_builder)
        : explanation_builder{_explanation_builder}
        {}
        
      };
      
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_exploration<4U>(Sudoku<ValueCell, 4>(sudoku), static_cast<const __lambda_6>(__lambda_6{explanation_builder})));
      const Explanation<4> explanation = static_cast<const Explanation<4>>(explanation_builder.get());
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        explain_as_text<4>(explanation, std::cout, false);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          std::basic_ofstream<char> out = std::basic_ofstream<char>(options.text_path.operator*(), std::ios_base::out);
          (static_cast<bool>(out.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("out.is_open()"), static_cast<const char *>("src/main.impl.hpp"), static_cast<unsigned int>(76), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
          explain_as_text<4>(explanation, static_cast<std::basic_ostream<char>&>(out), false);
        } 
        
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      if(std::operator==(options.video_text_path, "-")) {
        ++stdout_users;
        explain_as_text<4>(explanation, std::cout, true);
      } else {
        if(static_cast<bool>(options.video_text_path.operator bool())) {
          std::basic_ofstream<char> out = std::basic_ofstream<char>(options.video_text_path.operator*(), std::ios_base::out);
          (static_cast<bool>(out.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("out.is_open()"), static_cast<const char *>("src/main.impl.hpp"), static_cast<unsigned int>(89), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
          explain_as_text<4>(explanation, static_cast<std::basic_ostream<char>&>(out), true);
        } 
        
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
      if(static_cast<bool>(options.html_path.operator bool())) {
        explain_as_html<4>(explanation, options.html_path.operator*(), options.width, options.height);
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail(static_cast<const char *>("video_serializers.size() == 2"), static_cast<const char *>("src/main.impl.hpp"), static_cast<unsigned int>(110), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>()))))));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        explain_as_video<4>(explanation, static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
      } 
      
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


#endif  // MAIN_IMPL_HPP_
# 4 "src/main-4.cpp"

template int main_<4>(const Options& options);
