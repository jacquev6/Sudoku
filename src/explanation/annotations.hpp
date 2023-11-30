// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_ANNOTATIONS_HPP_
#define EXPLANATION_ANNOTATIONS_HPP_

#include <array>
#include <bitset>
#include <cassert>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "../puzzle/sudoku.hpp"


template<unsigned size>
class ExplainableCell {
 public:
  ExplainableCell() :
    allowed_values(),
    set_value(),
    input(false),
    hypothesis(false),
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

  bool is_hypothesis() const {
    assert_invariants();
    return hypothesis;
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

  void set_hypothesis(const unsigned value) {
    assert_invariants();
    assert(value < size);
    assert(is_allowed(value));
    assert(!is_set());

    allowed_values.reset();
    allowed_values.set(value);
    set_value = value;
    hypothesis = true;

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
  bool hypothesis;
  bool propagated;
};

template<unsigned size>
class Sudoku<ExplainableCell<size>, size> : public SudokuBase<ExplainableCell<size>, size> {
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
using ExplainableSudoku = Sudoku<ExplainableCell<size>, size>;

#endif  // EXPLANATION_ANNOTATIONS_HPP_
