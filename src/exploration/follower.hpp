// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_FOLLOWER_HPP_
#define EXPLORATION_FOLLOWER_HPP_

#include <list>
#include <set>
#include <vector>

#include "../exploration/events.hpp"


// @todo Remove this class: this should be a feature of the events themselves, not done through the visitor.
// Apply events to a Sudoku and keep track of the state.
class Follower : public exploration::EventVisitor {
 public:
  Follower() : stack(1) {}

 public:
  struct State {
    Sudoku sudoku;
    std::set<Sudoku::Coordinates> inputs;
    std::set<Sudoku::Coordinates> processed;
  };

 public:
  const State& current() const {
    assert(!stack.empty());
    return stack.back();
  }

  std::vector<const State*> saved() const {
    std::vector<const State*> result;
    for (auto it = std::next(stack.rbegin()); it != stack.rend(); ++it) {
      result.push_back(&(*it));
    }
    return result;
  }

 private:
  State& current() {
    assert(!stack.empty());
    return stack.back();
  }

  void push() {
    stack.push_back(current());
  }

  void pop() {
    assert(!stack.empty());
    stack.pop_back();
  }

 public:
  void visit(const exploration::CellIsSetInInput& event) override {
    current().sudoku.set(event.cell, event.value);
    current().inputs.insert(event.cell);
  }

  void visit(const exploration::InputsAreDone&) override {}

  void visit(const exploration::PropagationStartsForSudoku&) override {}

  void visit(const exploration::PropagationStartsForCell&) override {}

  void visit(const exploration::CellPropagates& event) override {
    assert(current().sudoku.is_set(event.source_cell));
    assert(current().sudoku.get(event.source_cell) == event.value);
    assert(!current().sudoku.is_set(event.target_cell));
    assert(current().sudoku.is_allowed(event.target_cell, event.value));
    assert(current().processed.count(event.source_cell) == 0);

    current().sudoku.forbid(event.target_cell, event.value);
  }

  void visit(const exploration::CellIsDeducedFromSingleAllowedValue& event) override {
    assert(!current().sudoku.is_set(event.cell));
    assert(current().processed.count(event.cell) == 0);

    current().sudoku.set(event.cell, event.value);
  }

  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion& event) override {
    assert(!current().sudoku.is_set(event.cell));
    assert(current().processed.count(event.cell) == 0);

    current().sudoku.set(event.cell, event.value);
  }

  void visit(const exploration::PropagationIsDoneForCell& event) override {
    assert(current().sudoku.is_set(event.cell));
    assert(current().sudoku.get(event.cell) == event.value);
    assert(current().processed.count(event.cell) == 0);

    current().processed.insert(event.cell);
  }

  void visit(const exploration::PropagationIsDoneForSudoku&) override {}

  void visit(const exploration::ExplorationStarts&) override {}

  void visit(const exploration::HypothesisIsMade& event) override {
    assert(!current().sudoku.is_set(event.cell));
    assert(current().sudoku.is_allowed(event.cell, event.value));
    assert(current().processed.count(event.cell) == 0);

    push();
    current().sudoku.set(event.cell, event.value);
  }

  void visit(const exploration::HypothesisIsRejected& event) override {
    pop();
  }

  void visit(const exploration::SudokuIsSolved& event) override {
    assert(current().sudoku.is_solved());
  }

  void visit(const exploration::HypothesisIsAccepted&) override {}

  void visit(const exploration::ExplorationIsDone&) override {}

 private:
  std::list<State> stack;
};

#endif  // EXPLORATION_FOLLOWER_HPP_
