// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_ANNOTATIONS_HPP_
#define EXPLORATION_ANNOTATIONS_HPP_

#include <utility>
#include <vector>

// @todo Move AnnotatedSudoku into this file
#include "sudoku.hpp"


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
