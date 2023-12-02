// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_EXPLANATION_HPP_
#define EXPLANATION_EXPLANATION_HPP_

#include <optional>
#include <tuple>
#include <utility>
#include <vector>

#include "../exploration/events.hpp"
#include "annotations.hpp"


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
    void operator()(const CellIsSetInInput<size>&);
    void operator()(const InputsAreDone<size>&);
    void operator()(const PropagationStartsForSudoku<size>&);
    void operator()(const PropagationStartsForCell<size>&);
    void operator()(const CellPropagates<size>&);
    void operator()(const CellIsDeducedFromSingleAllowedValue<size>&);
    void operator()(const CellIsDeducedAsSinglePlaceForValueInRegion<size>&);
    void operator()(const PropagationIsDoneForCell<size>&);
    void operator()(const PropagationIsDoneForSudoku<size>&);
    void operator()(const ExplorationStarts<size>&);
    void operator()(const HypothesisIsMade<size>&);
    void operator()(const HypothesisIsRejected<size>&);
    void operator()(const SudokuIsSolved<size>&);
    void operator()(const HypothesisIsAccepted<size>&);
    void operator()(const ExplorationIsDone<size>&);

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


template<unsigned size, typename Explainer>
class ExplanationWalker {
 public:
  ExplanationWalker(
    const Explanation<size>& explanation_,
    Explainer& explainer_
  ) :  // NOLINT(whitespace/parens)
    explanation(explanation_),
    explainer(explainer_),
    stack()
  {  // NOLINT(whitespace/braces)
    for (const auto& cell : explanation.inputs.cells()) {
      const std::optional<unsigned> value = cell.get();
      if (value) {
        stack.current().cell(cell.coordinates()).set_input(*value);
      }
    }
  }

 public:
  void walk() {
    explainer.inputs(stack, explanation.inputs);
    walk(explanation.propagations);
    walk(explanation.exploration);
  }

 private:
  void walk(const std::vector<typename Explanation<size>::Propagation>& propagations) {
    explainer.propagations_begin(stack);
    for (const auto& propagation : propagations) {
      if (propagation.targets.empty()) {
        explainer.propagation_empty_begin(stack, propagation);
        stack.current().cell(propagation.source).set_propagated();
        explainer.propagation_empty_end(stack, propagation);
      } else {
        walk(propagation);
      }
    }
    explainer.propagations_end(stack);
  }

  void walk(const typename Explanation<size>::Propagation& propagation) {
    explainer.propagation_begin(stack, propagation);

    if (propagation_targets_count < 3) {
      explainer.propagation_targets_begin(stack, propagation);
      for (const auto& target : propagation.targets) {
        explainer.propagation_target_begin(stack, propagation, target);
        stack.current().cell(target.cell).forbid(propagation.value);
        explainer.propagation_target_end(stack, propagation, target);
        ++propagation_targets_count;
      }
      explainer.propagation_targets_end(stack, propagation);
    } else {
      explainer.propagation_targets_condensed_begin(stack, propagation);
      for (const auto& target : propagation.targets) {
        stack.current().cell(target.cell).forbid(propagation.value);
      }
      explainer.propagation_targets_condensed_end(stack, propagation);
    }

    bool solved = false;
    explainer.propagation_single_value_deductions_begin(stack, propagation);
    for (const auto& target : propagation.targets) {
      for (const auto& deduction : target.single_value_deductions) {
        explainer.propagation_single_value_deduction_begin(stack, propagation, target, deduction);
        stack.current().cell(deduction.cell).set_deduced(deduction.value);
        solved |= deduction.solved;
        explainer.propagation_single_value_deduction_end(stack, propagation, target, deduction);
      }
    }
    explainer.propagation_single_value_deductions_end(stack, propagation);

    explainer.propagation_single_place_deductions_begin(stack, propagation);
    for (const auto& target : propagation.targets) {
      for (const auto& deduction : target.single_place_deductions) {
        explainer.propagation_single_place_deduction_begin(stack, propagation, target, deduction);
        stack.current().cell(deduction.cell).set_deduced(deduction.value);
        solved |= deduction.solved;
        explainer.propagation_single_place_deduction_end(stack, propagation, target, deduction);
      }
    }
    explainer.propagation_single_place_deductions_end(stack, propagation);

    stack.current().cell(propagation.source).set_propagated();

    if (solved) {
      explainer.solved(stack, propagation);
    }

    explainer.propagation_end(stack, propagation);
  }

  void walk(const std::optional<typename Explanation<size>::Exploration>& exploration) {
    if (exploration) {
      walk(*exploration);
    }
  }

  void walk(const typename Explanation<size>::Exploration& exploration) {
    explainer.exploration_begin(stack, exploration);
    for (const auto& hypothesis : exploration.explored_hypotheses) {
      explainer.hypothesis_begin(stack, exploration, hypothesis);

      stack.push();
      stack.current().cell(exploration.cell).set_hypothesis(hypothesis.value);

      explainer.hypothesis_before_propagations(stack, exploration, hypothesis);

      walk(hypothesis.propagations);
      walk(hypothesis.exploration);
      explainer.hypothesis_end(stack, exploration, hypothesis);

      stack.pop();
    }
    explainer.exploration_end(stack, exploration);
  }

 private:
  const Explanation<size>& explanation;
  Explainer& explainer;
  Stack<ExplainableSudoku<size>> stack;
  unsigned propagation_targets_count = 0;
};

template<unsigned size, typename Explainer>
void explain(
  const Explanation<size>& explanation,
  Explainer& explainer  // NOLINT(runtime/references)
) {
  ExplanationWalker(explanation, explainer).walk();
}

template<unsigned size, typename Explainer>
void explain(const Explanation<size>& explanation, const Explainer& explainer) {
  ExplanationWalker(explanation, explainer).walk();
}

#endif  // EXPLANATION_EXPLANATION_HPP_
