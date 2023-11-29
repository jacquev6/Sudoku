// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_EXPLANATION_HPP_
#define EXPLANATION_EXPLANATION_HPP_

#include <optional>
#include <tuple>
#include <utility>
#include <vector>

#include "../exploration/events.hpp"
#include "../puzzle/sudoku.hpp"


template<unsigned size>
struct Explanation {
  struct SingleValueDeduction {
    Coordinates cell;
    unsigned value;
    bool solved;
  };

  struct SinglePlaceDeduction {
    unsigned region;
    Coordinates cell;
    unsigned value;
    bool solved;
  };

  struct PropagationTarget {
    Coordinates cell;
    std::vector<SingleValueDeduction> single_value_deductions;
    std::vector<SinglePlaceDeduction> single_place_deductions;
  };

  struct Propagation {
    Coordinates source;
    unsigned value;
    std::vector<PropagationTarget> targets;
  };

  struct Exploration;

  struct Hypothesis {
    unsigned value;
    std::vector<Propagation> propagations;
    std::optional<Exploration> exploration;
    bool successful;
  };

  struct Exploration {
    Coordinates cell;
    std::vector<unsigned> allowed_values;
    std::vector<Hypothesis> explored_hypotheses;
  };

  Sudoku<ValueCell, size> inputs;
  std::vector<Propagation> propagations;
  std::optional<Exploration> exploration;

 public:
  class Builder {
    // This is like a parser where the tokens are the events and the AST is the explanation.
    // The grammar is so regular and simple that the AST has very little polymorphism.

   private:
    struct Frame {
      Frame(
        std::vector<Propagation>* propagations_,
        std::optional<Exploration>* exploration_,
        Hypothesis* hypothesis_
      ) :  // NOLINT(whitespace/parens)
        propagations(propagations_),
        exploration(exploration_),
        hypothesis(hypothesis_),
        sudoku_is_solved(nullptr)
      {  // NOLINT(whitespace/braces)
        assert(propagations);
        assert(exploration);
        assert(hypothesis);
      }

      Frame(
        std::vector<Propagation>* propagations_,
        std::optional<Exploration>* exploration_
      ) :  // NOLINT(whitespace/parens)
        propagations(propagations_),
        exploration(exploration_),
        hypothesis(nullptr),
        sudoku_is_solved(nullptr)
      {  // NOLINT(whitespace/braces)
        assert(propagations);
        assert(exploration);
      }

      std::vector<Propagation>* propagations;
      std::optional<Exploration>* exploration;
      Hypothesis* hypothesis;
      bool* sudoku_is_solved;
    };

   public:
    Builder() : explanation(), stack(1, { &explanation.propagations, &explanation.exploration }) {}

   public:
    void operator()(const exploration::CellIsSetInInput<size>&);
    void operator()(const exploration::InputsAreDone<size>&);
    void operator()(const exploration::PropagationStartsForSudoku<size>&);
    void operator()(const exploration::PropagationStartsForCell<size>&);
    void operator()(const exploration::CellPropagates<size>&);
    void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>&);
    void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>&);
    void operator()(const exploration::PropagationIsDoneForCell<size>&);
    void operator()(const exploration::PropagationIsDoneForSudoku<size>&);
    void operator()(const exploration::ExplorationStarts<size>&);
    void operator()(const exploration::HypothesisIsMade<size>&);
    void operator()(const exploration::HypothesisIsRejected<size>&);
    void operator()(const exploration::SudokuIsSolved<size>&);
    void operator()(const exploration::HypothesisIsAccepted<size>&);
    void operator()(const exploration::ExplorationIsDone<size>&);

   public:
    Explanation get() {
      assert(stack.size() == 1);
      return std::move(explanation);
    }

   private:
    Explanation explanation;
    std::vector<Frame> stack;
  };
};


#endif  // EXPLANATION_EXPLANATION_HPP_