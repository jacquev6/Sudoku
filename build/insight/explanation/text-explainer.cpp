// Copyright 2023 Vincent Jacques

// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <string>

#include <boost/format.hpp>

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
      (static_cast<bool>(this->sudoku == other.sudoku) ? void(0) : __assert_fail("sudoku == other.sudoku", "/wd/src/explanation/text-explainer.cpp", 193, __extension____PRETTY_FUNCTION__));
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
            
      class __lambda_221_28
      {
        public: 
        template<class type_parameter_1_0>
        inline const SudokuBase::Cell & operator()(const type_parameter_1_0 & coords) const
        {
          const auto __coords222 = coords;
          return __this->sudoku->_cells[row][col];
        }
        private: 
        const SudokuBase::Region * __this;
        
        public:
        __lambda_221_28(const SudokuBase::Region * _this)
        : __this{_this}
        {}
        
      };
      
      const auto convert = __lambda_221_28{this};
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
    const std::pair<unsigned int, unsigned int> __coords295 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords295));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords295));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "/wd/src/explanation/text-explainer.cpp", 296, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "/wd/src/explanation/text-explainer.cpp", 297, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline const Cell & cell(const std::pair<unsigned int, unsigned int> & coords) const
  {
    const std::pair<unsigned int, unsigned int> __coords302 = std::pair<unsigned int, unsigned int>(coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords302));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords302));
    (static_cast<bool>(row < size) ? void(0) : __assert_fail("row < size", "/wd/src/explanation/text-explainer.cpp", 303, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(col < size) ? void(0) : __assert_fail("col < size", "/wd/src/explanation/text-explainer.cpp", 304, __extension____PRETTY_FUNCTION__));
    return this->_cells[row][col];
  }
  
  inline auto cells() const
  {
        
    class __lambda_309_26
    {
      public: 
      template<class type_parameter_1_0>
      inline const Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell310 = cell;
        return __this->_cells[row][col];
      }
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_309_26(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_309_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto cells()
  {
        
    class __lambda_320_26
    {
      public: 
      template<class type_parameter_1_0>
      inline Cell & operator()(const type_parameter_1_0 & cell) const
      {
        const auto __cell321 = cell;
        return __this->_cells[row][col];
      }
      private: 
      SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_320_26(SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_320_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }
  
  inline auto regions() const
  {
        
    class __lambda_331_26
    {
      public: 
      inline const Region operator()(const unsigned int index) const
      {
        return Region(__this, index);
      }
      
      private: 
      const SudokuBase<CellBase, size> * __this;
      
      public:
      __lambda_331_26(const SudokuBase<CellBase, size> * _this)
      : __this{_this}
      {}
      
    };
    
    const auto convert = __lambda_331_26{this};
    return boost::make_iterator_range(boost::make_transform_iterator(SudokuConstants<size>::region_indexes.begin(), convert), boost::make_transform_iterator(SudokuConstants<size>::region_indexes.end(), convert));
  }
  
  
  protected: 
  CellsArray _cells;
};



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
    (static_cast<bool>(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(this->value).operator bool()) || (this->value.operator*() == value_)) ? void(0) : __assert_fail(static_cast<const char *>("!value || *value == value_"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(369), static_cast<const char *>(__extension__"void ValueCell::set(unsigned int)")));
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
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "/wd/src/explanation/text-explainer.cpp", 420, __extension____PRETTY_FUNCTION__));
    return this->set_value.value();
  }
  
  inline bool is_allowed(const unsigned int value) const
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/text-explainer.cpp", 427, __extension____PRETTY_FUNCTION__));
    return this->allowed_values.test(value);
  }
  
  inline void set_input(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/text-explainer.cpp", 434, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/explanation/text-explainer.cpp", 435, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "/wd/src/explanation/text-explainer.cpp", 436, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->input = true;
    this->assert_invariants();
  }
  
  inline void set_deduced(const unsigned int value)
  {
    this->assert_invariants();
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/text-explainer.cpp", 448, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/explanation/text-explainer.cpp", 449, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!this->is_set()) ? void(0) : __assert_fail("!is_set()", "/wd/src/explanation/text-explainer.cpp", 450, __extension____PRETTY_FUNCTION__));
    this->allowed_values.reset();
    this->allowed_values.set(value);
    this->set_value.operator=(std::optional<unsigned int>(value));
    this->assert_invariants();
  }
  
  inline void set_propagated()
  {
    this->assert_invariants();
    (static_cast<bool>(this->is_set()) ? void(0) : __assert_fail("is_set()", "/wd/src/explanation/text-explainer.cpp", 461, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(value < size) ? void(0) : __assert_fail("value < size", "/wd/src/explanation/text-explainer.cpp", 476, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(this->is_allowed(value)) ? void(0) : __assert_fail("is_allowed(value)", "/wd/src/explanation/text-explainer.cpp", 477, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(this->allowed_values.any()) ? void(0) : __assert_fail("allowed_values.any()", "/wd/src/explanation/text-explainer.cpp", 493, __extension____PRETTY_FUNCTION__));
    if(this->input) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "/wd/src/explanation/text-explainer.cpp", 497, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->propagated) {
      (static_cast<bool>(this->set_value.has_value()) ? void(0) : __assert_fail("set_value.has_value()", "/wd/src/explanation/text-explainer.cpp", 502, __extension____PRETTY_FUNCTION__));
    } 
    
    if(this->set_value.has_value()) {
      (static_cast<bool>(this->allowed_values.count() == 1) ? void(0) : __assert_fail("allowed_values.count() == 1", "/wd/src/explanation/text-explainer.cpp", 507, __extension____PRETTY_FUNCTION__));
      (static_cast<bool>(this->allowed_values.test(this->set_value.value())) ? void(0) : __assert_fail("allowed_values.test(set_value.value())", "/wd/src/explanation/text-explainer.cpp", 508, __extension____PRETTY_FUNCTION__));
    } 
    
  }
  
  
  private: 
  std::bitset<size> allowed_values;
  std::optional<unsigned int> set_value;
  bool input;
  bool propagated;
};



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
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/explanation/text-explainer.cpp", 543, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  inline AnnotatedSudoku<size> & current()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/explanation/text-explainer.cpp", 548, __extension____PRETTY_FUNCTION__));
    return this->stack.back();
  }
  
  
  public: 
  inline void push()
  {
    this->stack.push_back(current());
  }
  
  inline void pop()
  {
    (static_cast<bool>(!this->stack.empty()) ? void(0) : __assert_fail("!stack.empty()", "/wd/src/explanation/text-explainer.cpp", 572, __extension____PRETTY_FUNCTION__));
    this->stack.pop_back();
  }
  
  
  private: 
  std::vector<AnnotatedSudoku<size> > stack;
};



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
  
  /* First instantiated from: text-explainer.cpp:732 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsSetInInput<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:732 */
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
  
  /* First instantiated from: text-explainer.cpp:748 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationStartsForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:748 */
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
  
  /* First instantiated from: text-explainer.cpp:754 */
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
  /* First instantiated from: text-explainer.cpp:754 */
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
  
  /* First instantiated from: text-explainer.cpp:761 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct CellIsDeducedFromSingleAllowedValue<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:761 */
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
  
  /* First instantiated from: text-explainer.cpp:767 */
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
  /* First instantiated from: text-explainer.cpp:767 */
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
  
  /* First instantiated from: text-explainer.cpp:773 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:773 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct PropagationIsDoneForCell<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
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
  
  /* First instantiated from: text-explainer.cpp:784 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationStarts<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:784 */
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
  
  /* First instantiated from: text-explainer.cpp:791 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsMade<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:791 */
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
  
  /* First instantiated from: text-explainer.cpp:799 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsRejected<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:799 */
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
  
  template<unsigned int size>
  struct HypothesisIsAccepted
  {
    void apply(Stack<size> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  /* First instantiated from: text-explainer.cpp:812 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct HypothesisIsAccepted<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:812 */
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
  
  /* First instantiated from: text-explainer.cpp:818 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<4>
  {
    void apply(Stack<4> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  #endif
  /* First instantiated from: text-explainer.cpp:818 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct ExplorationIsDone<9>
  {
    void apply(Stack<9> *) const;
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  #endif
  template<unsigned int size>
  using Event = std::variant<CellIsSetInInput<size>, InputsAreDone<size>, PropagationStartsForSudoku<size>, PropagationStartsForCell<size>, CellPropagates<size>, CellIsDeducedFromSingleAllowedValue<size>, CellIsDeducedAsSinglePlaceForValueInRegion<size>, PropagationIsDoneForCell<size>, PropagationIsDoneForSudoku<size>, ExplorationStarts<size>, HypothesisIsMade<size>, HypothesisIsRejected<size>, SudokuIsSolved<size>, HypothesisIsAccepted<size>, ExplorationIsDone<size> >;
  
}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_


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
    (static_cast<bool>(this->hypotheses_count == static_cast<unsigned int>(0)) ? void(0) : __assert_fail("hypotheses_count == 0", "/wd/src/explanation/text-explainer.cpp", 725, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail("hypotheses_count > 0", "/wd/src/explanation/text-explainer.cpp", 795, __extension____PRETTY_FUNCTION__));
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
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail("hypotheses_count > 0", "/wd/src/explanation/text-explainer.cpp", 808, __extension____PRETTY_FUNCTION__));
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



#endif  // EXPLANATION_TEXT_EXPLAINER_HPP_




template<>
class TextExplainer<static_cast<unsigned int>(4)>
{
  
  public: 
  inline explicit TextExplainer(std::basic_ostream<char> & os_)
  : os{os_}
  , hypotheses_count{static_cast<unsigned int>(0)}
  {
  }
  
  inline ~TextExplainer() noexcept
  {
    (static_cast<bool>(this->hypotheses_count == static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count == 0"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(725), static_cast<const char *>(__extension__"TextExplainer<4>::~TextExplainer() [size = 4]")));
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
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(795), static_cast<const char *>(__extension__"void TextExplainer<4>::operator()(const exploration::HypothesisIsRejected<size> &) [size = 4]")));
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
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(808), static_cast<const char *>(__extension__"void TextExplainer<4>::operator()(const exploration::HypothesisIsAccepted<size> &) [size = 4]")));
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
};





template<>
class TextExplainer<static_cast<unsigned int>(9)>
{
  
  public: 
  inline explicit TextExplainer(std::basic_ostream<char> & os_)
  : os{os_}
  , hypotheses_count{static_cast<unsigned int>(0)}
  {
  }
  
  inline ~TextExplainer() noexcept
  {
    (static_cast<bool>(this->hypotheses_count == static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count == 0"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(725), static_cast<const char *>(__extension__"TextExplainer<9>::~TextExplainer() [size = 9]")));
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
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(795), static_cast<const char *>(__extension__"void TextExplainer<9>::operator()(const exploration::HypothesisIsRejected<size> &) [size = 9]")));
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
    (static_cast<bool>(this->hypotheses_count > static_cast<unsigned int>(0)) ? void(0) : __assert_fail(static_cast<const char *>("hypotheses_count > 0"), static_cast<const char *>("/wd/src/explanation/text-explainer.cpp"), static_cast<unsigned int>(808), static_cast<const char *>(__extension__"void TextExplainer<9>::operator()(const exploration::HypothesisIsAccepted<size> &) [size = 9]")));
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
};



