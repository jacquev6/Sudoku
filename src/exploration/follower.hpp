// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_FOLLOWER_HPP_
#define EXPLORATION_FOLLOWER_HPP_

#include <list>
#include <set>
#include <vector>

#include "events.hpp"


// @todo Remove this class: this should be a feature of the events themselves, not done through the visitor.
// Apply events to a Sudoku and keep track of the state.
class Follower : public exploration::EventVisitor {
 public:
  const AnnotatedSudoku& current() const {
    return stack.current();
  }

 private:
  AnnotatedSudoku& current() {
    return stack.current();
  }

  void push() {
    stack.push();
  }

  void pop() {
    stack.pop();
  }

 public:
  void visit(const exploration::CellIsSetInInput& event) override {
    current().set_input(event.cell, event.value);
  }

  void visit(const exploration::InputsAreDone&) override {}

  void visit(const exploration::PropagationStartsForSudoku&) override {}

  void visit(const exploration::PropagationStartsForCell&) override {}

  void visit(const exploration::CellPropagates& event) override {
    assert(current().is_set(event.source_cell));
    assert(current().get(event.source_cell) == event.value);
    assert(!current().is_set(event.target_cell));
    assert(current().is_allowed(event.target_cell, event.value));
    assert(!current().is_propagated(event.source_cell));

    current().forbid(event.target_cell, event.value);
  }

  void visit(const exploration::CellIsDeducedFromSingleAllowedValue& event) override {
    assert(!current().is_set(event.cell));
    assert(!current().is_propagated(event.cell));

    current().set_deduced(event.cell, event.value);
  }

  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion& event) override {
    assert(!current().is_set(event.cell));
    assert(!current().is_propagated(event.cell));

    current().set_deduced(event.cell, event.value);
  }

  void visit(const exploration::PropagationIsDoneForCell& event) override {
    assert(current().is_set(event.cell));
    assert(current().get(event.cell) == event.value);
    assert(!current().is_propagated(event.cell));

    current().set_propagated(event.cell);
  }

  void visit(const exploration::PropagationIsDoneForSudoku&) override {}

  void visit(const exploration::ExplorationStarts&) override {}

  void visit(const exploration::HypothesisIsMade& event) override {
    assert(!current().is_set(event.cell));
    assert(current().is_allowed(event.cell, event.value));
    assert(!current().is_propagated(event.cell));

    push();
    current().set_deduced(event.cell, event.value);
  }

  void visit(const exploration::HypothesisIsRejected& event) override {
    pop();
  }

  void visit(const exploration::SudokuIsSolved& event) override {
    assert(current().is_solved());
  }

  void visit(const exploration::HypothesisIsAccepted&) override {}

  void visit(const exploration::ExplorationIsDone&) override {}

 private:
  Stack stack;
};

#endif  // EXPLORATION_FOLLOWER_HPP_
