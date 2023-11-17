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

#include "../puzzle/sudoku.hpp"


template<unsigned size>
class AnnotatedCell {
 public:
  AnnotatedCell() :
    allowed_values(),
    set_value(),
    input(false),
    propagated(false)
  {  // NOLINT(whitespace/braces)
    allowed_values.set();
    assert_invariants();
  }

 public:
  bool is_input() const {
    assert_invariants();
    return input;
  }

  bool is_set() const {
    assert_invariants();
    return set_value.has_value();
  }

  unsigned get() const {
    assert_invariants();
    assert(is_set());

    return set_value.value();
  }

  bool is_allowed(const unsigned value) const {
    assert_invariants();
    assert(value < size);

    return allowed_values.test(value);
  }

  void set_input(const unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(value));
    assert(!is_set());

    allowed_values.reset();
    allowed_values.set(value);
    set_value = value;
    input = true;

    assert_invariants();
  }

  void set_deduced(const unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(value));
    assert(!is_set());

    allowed_values.reset();
    allowed_values.set(value);
    set_value = value;

    assert_invariants();
  }

  void set_propagated() {
    assert_invariants();
    assert(is_set());

    propagated = true;

    assert_invariants();
  }

  bool is_propagated() const {
    assert_invariants();

    return propagated;
  }

  void forbid(const unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(value));

    allowed_values.reset(value);

    assert_invariants();
  }

  unsigned allowed_count() const {
    assert_invariants();

    return allowed_values.count();
  }

 private:
  void assert_invariants() const {
    // At least one value is always allowed
    assert(allowed_values.any());

    // 'input' forces 'set_value'
    if (input) {
      assert(set_value.has_value());
    }

    // 'propagated' forces 'set_value'
    if (propagated) {
      assert(set_value.has_value());
    }

    // 'set_value' forces 'allowed_values'
    if (set_value.has_value()) {
      assert(allowed_values.count() == 1);
      assert(allowed_values.test(set_value.value()));
    }
  }

 private:
  std::bitset<size> allowed_values;
  std::optional<unsigned> set_value;
  bool input;
  bool propagated;
};

template<unsigned size>
class Sudoku<AnnotatedCell<size>, size> : public SudokuBase<AnnotatedCell<size>, size> {
 public:
  bool is_solved() const {
    for (const auto& cell : this->cells()) {
      if (!cell.is_set()) {
        return false;
      }
    }
    return true;
  }
};

template<unsigned size>
using AnnotatedSudoku = Sudoku<AnnotatedCell<size>, size>;


template<unsigned size>
class Stack {
 public:
  Stack() : stack(1) {}

 public:
  const AnnotatedSudoku<size>& current() const {
    assert(!stack.empty());
    return stack.back();
  }

  AnnotatedSudoku<size>& current() {
    assert(!stack.empty());
    return stack.back();
  }

//  public:
//   struct Saved {
//     Saved(const Stack& stack) : begin_(std::next(stack.stack.rbegin())), end_(stack.stack.rend()) {}

//     std::vector<AnnotatedSudoku<size>>::const_reverse_iterator begin() { return begin_; }
//     std::vector<AnnotatedSudoku<size>>::const_reverse_iterator end() { return end_; }

//    private:
//     const std::vector<AnnotatedSudoku<size>>::const_reverse_iterator begin_;
//     const std::vector<AnnotatedSudoku<size>>::const_reverse_iterator end_;
//   };

//   Saved saved() const;

 public:
  void push() {
    stack.push_back(current());
  }

  void pop() {
    assert(!stack.empty());
    stack.pop_back();
  }

 private:
  std::vector<AnnotatedSudoku<size>> stack;
};

#endif  // EXPLORATION_ANNOTATIONS_HPP_
