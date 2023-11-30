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

#include "sudoku-constants.hpp"


template<typename CellBase, unsigned size>
class SudokuBase {
 public:
  class Cell : public CellBase {
   public:
    Cell(SudokuBase* sudoku_, const Coordinates& coords_) :
      CellBase(),
      sudoku(sudoku_),
      coords(coords_)
    {}

    Cell(SudokuBase* sudoku_, const Cell& other) :
      CellBase(other),
      sudoku(sudoku_),
      coords(other.coords)
    {}

    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;
    Cell(Cell&&) = delete;
    Cell& operator=(Cell&&) = delete;

   public:
    bool operator==(const Cell& other) const {
      assert(sudoku == other.sudoku);
      return coords == other.coords;
    }

    Coordinates coordinates() const { return coords; }

    auto regions() const {
      const auto convert = [this](const unsigned region_index) -> const Region& {
        return sudoku->_regions[region_index];
      };

      return boost::make_iterator_range(
        boost::make_transform_iterator(SudokuConstants<size>::regions_of[coords.first][coords.second].begin(), convert),
        boost::make_transform_iterator(SudokuConstants<size>::regions_of[coords.first][coords.second].end(), convert));
    }

    auto regions() {
      const auto convert = [this](const unsigned region_index) -> Region& {
        return sudoku->_regions[region_index];
      };

      return boost::make_iterator_range(
        boost::make_transform_iterator(SudokuConstants<size>::regions_of[coords.first][coords.second].begin(), convert),
        boost::make_transform_iterator(SudokuConstants<size>::regions_of[coords.first][coords.second].end(), convert));
    }

   private:
    SudokuBase* sudoku;
    const Coordinates coords;
  };

  class Region {
   public:
    Region(SudokuBase* sudoku_, const unsigned index_) :
      sudoku(sudoku_), _index(index_)
    {}

    Region(const Region&) = delete;
    Region& operator=(const Region&) = delete;
    Region(Region&&) = delete;
    Region& operator=(Region&&) = delete;

   public:
    unsigned index() const { return _index; }

    auto cells() const {
      const auto convert = [this](const auto& coords) -> const Cell& {
        const auto [row, col] = coords;
        return sudoku->_cells[row][col];
      };

      return boost::make_iterator_range(
        boost::make_transform_iterator(SudokuConstants<size>::regions[_index].begin(), convert),
        boost::make_transform_iterator(SudokuConstants<size>::regions[_index].end(), convert));
    }

    auto cells() {
      const auto convert = [this](const auto& coords) -> Cell& {
        const auto [row, col] = coords;
        return sudoku->_cells[row][col];
      };

      return boost::make_iterator_range(
        boost::make_transform_iterator(SudokuConstants<size>::regions[_index].begin(), convert),
        boost::make_transform_iterator(SudokuConstants<size>::regions[_index].end(), convert));
    }

   private:
    SudokuBase* sudoku;
    const unsigned _index;
  };

 public:
  SudokuBase() :
    _cells(make_cells()),
    _regions(make_regions())
  {}

  SudokuBase(const SudokuBase& other) :
    _cells(copy_cells(other._cells)),
    _regions(make_regions())
  {};

  SudokuBase& operator=(const SudokuBase&);
  SudokuBase(SudokuBase&&) = delete;
  SudokuBase& operator=(SudokuBase&&) = delete;

 private:
  typedef std::array<std::array<Cell, size>, size> CellsArray;

  CellsArray make_cells() {
    return make_cells(std::make_integer_sequence<unsigned, size>());
  }

  template<unsigned... row>
  CellsArray make_cells(const std::integer_sequence<unsigned, row...>&) {
    return {make_row(row, std::make_integer_sequence<unsigned, size>())...};
  }

  template<unsigned... col>
  std::array<Cell, size> make_row(unsigned row, const std::integer_sequence<unsigned, col...>&) {
    return {make_cell(row, col)...};
  }

  Cell make_cell(unsigned row, unsigned col) {
    return Cell(this, {row, col});
  }

 private:
  CellsArray copy_cells(const CellsArray& other_cells) {
    return copy_cells(std::make_integer_sequence<unsigned, size>(), other_cells);
  }

  template<unsigned... row>
  CellsArray copy_cells(const std::integer_sequence<unsigned, row...>&, const CellsArray& other_cells) {
    return {copy_row(row, other_cells, std::make_integer_sequence<unsigned, size>())...};
  }

  template<unsigned... col>
  std::array<Cell, size> copy_row(
    unsigned row,
    const CellsArray& other_cells,
    const std::integer_sequence<unsigned, col...>&
  ) {
    return {copy_cell(row, col, other_cells)...};
  }

  Cell copy_cell(unsigned row, unsigned col, const CellsArray& other_cells) {
    return Cell(this, other_cells[row][col]);
  }

 private:
  typedef std::array<Region, 3 * size> RegionsArray;

  RegionsArray make_regions() {
    return make_regions(std::make_integer_sequence<unsigned, 3 * size>());
  }

  template<unsigned... index>
  RegionsArray make_regions(const std::integer_sequence<unsigned, index...>&) {
    return {make_region(index)...};
  }

  Region make_region(unsigned index) {
    return Region(this, index);
  }

 public:
  Cell& cell(const Coordinates& coords) {
    const auto [row, col] = coords;
    assert(row < size);
    assert(col < size);
    return _cells[row][col];
  }

  const Cell& cell(const Coordinates& coords) const {
    const auto [row, col] = coords;
    assert(row < size);
    assert(col < size);
    return _cells[row][col];
  }

  auto cells() const {
    const auto convert = [this](const auto& cell) -> const Cell& {
      const auto [row, col] = cell;
      return _cells[row][col];
    };

    return boost::make_iterator_range(
      boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert),
      boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }

  auto cells() {
    const auto convert = [this](const auto& cell) -> Cell& {
      const auto [row, col] = cell;
      return _cells[row][col];
    };

    return boost::make_iterator_range(
      boost::make_transform_iterator(SudokuConstants<size>::cells.begin(), convert),
      boost::make_transform_iterator(SudokuConstants<size>::cells.end(), convert));
  }

  auto regions() const {
    const auto convert = [this](const unsigned index) -> const Region& {
      return _regions[index];
    };

    return boost::make_iterator_range(
      boost::make_transform_iterator(SudokuConstants<size>::region_indexes.begin(), convert),
      boost::make_transform_iterator(SudokuConstants<size>::region_indexes.end(), convert));
  }

  auto regions() {
    const auto convert = [this](const unsigned index) -> Region& {
      return _regions[index];
    };

    return boost::make_iterator_range(
      boost::make_transform_iterator(SudokuConstants<size>::region_indexes.begin(), convert),
      boost::make_transform_iterator(SudokuConstants<size>::region_indexes.end(), convert));
  }

 protected:
  CellsArray _cells;
  RegionsArray _regions;
};

template<typename Cell, unsigned size>
class Sudoku : public SudokuBase<Cell, size> {};

class ValueCell {
 public:
  ValueCell() = default;

  ValueCell(const ValueCell&) = default;
  ValueCell& operator=(const ValueCell&) = default;
  ValueCell(ValueCell&&) = default;
  ValueCell& operator=(ValueCell&&) = default;

 public:
  void set(unsigned value_) {
    assert(!value || *value == value_);
    value = value_;
  }

  std::optional<unsigned> get() const {
    return value;
  }

 private:
  std::optional<unsigned> value;
};

template<unsigned size>
class Sudoku<ValueCell, size> : public SudokuBase<ValueCell, size> {
 public:
  static Sudoku<ValueCell, size> load(std::istream&);
  void dump(std::ostream&) const;

  static Sudoku<ValueCell, size> from_string(const std::string&);
  std::string to_string() const;
};


template<typename Sudoku>
class Stack {
 public:
  Stack() : stack(1) {}

 public:
  const Sudoku& current() const {
    assert(!stack.empty());
    return stack.back();
  }

  Sudoku& current() {
    assert(!stack.empty());
    return stack.back();
  }

  int height() const {
    return stack.size();
  }

 public:
  struct Saved {
    explicit Saved(const Stack& stack) : begin_(std::next(stack.stack.rbegin())), end_(stack.stack.rend()) {}

    std::vector<Sudoku>::const_reverse_iterator begin() { return begin_; }
    std::vector<Sudoku>::const_reverse_iterator end() { return end_; }

   private:
    const std::vector<Sudoku>::const_reverse_iterator begin_;
    const std::vector<Sudoku>::const_reverse_iterator end_;
  };

  Saved saved() const { return Saved(*this); }

 public:
  void push() {
    stack.push_back(current());
  }

  void pop() {
    assert(!stack.empty());
    stack.pop_back();
  }

 private:
  std::vector<Sudoku> stack;
};

#endif  // PUZZLE_SUDOKU_HPP_
