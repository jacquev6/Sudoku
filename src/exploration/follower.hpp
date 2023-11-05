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
  void visit(const exploration::CellIsSetInInput& event) override { event.apply(&stack); }

  void visit(const exploration::InputsAreDone& event) override { event.apply(&stack); }

  void visit(const exploration::PropagationStartsForSudoku& event) override { event.apply(&stack); }

  void visit(const exploration::PropagationStartsForCell& event) override { event.apply(&stack); }

  void visit(const exploration::CellPropagates& event) override { event.apply(&stack); }

  void visit(const exploration::CellIsDeducedFromSingleAllowedValue& event) override { event.apply(&stack); }

  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion& event) override { event.apply(&stack); }

  void visit(const exploration::PropagationIsDoneForCell& event) override { event.apply(&stack); }

  void visit(const exploration::PropagationIsDoneForSudoku& event) override { event.apply(&stack); }

  void visit(const exploration::ExplorationStarts& event) override { event.apply(&stack); }

  void visit(const exploration::HypothesisIsMade& event) override { event.apply(&stack); }

  void visit(const exploration::HypothesisIsRejected& event) override { event.apply(&stack); }

  void visit(const exploration::SudokuIsSolved& event) override { event.apply(&stack); }

  void visit(const exploration::HypothesisIsAccepted& event) override { event.apply(&stack); }

  void visit(const exploration::ExplorationIsDone& event) override { event.apply(&stack); }

 private:
  Stack stack;
};

#endif  // EXPLORATION_FOLLOWER_HPP_
