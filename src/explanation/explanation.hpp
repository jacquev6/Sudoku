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


template<unsigned size>
struct NullExplainer {
  void inputs(
    const Stack<ExplainableSudoku<size>>&,
    const Sudoku<ValueCell, size>&) const {}

  void propagations_begin(
    const Stack<ExplainableSudoku<size>>&) const {}

  void propagation_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_targets_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_target_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&) const {}

  void propagation_target_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&) const {}

  void propagation_targets_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_value_deductions_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_value_deduction_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SingleValueDeduction&) const {}

  void propagation_single_value_deduction_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SingleValueDeduction&) const {}

  void propagation_single_value_deductions_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_place_deductions_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_place_deduction_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SinglePlaceDeduction&) const {}

  void propagation_single_place_deduction_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SinglePlaceDeduction&) const {}

  void propagation_single_place_deductions_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void solved(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagations_end(
    const Stack<ExplainableSudoku<size>>&) const {}

  void exploration_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&) const {}

  void hypothesis_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const {}

  void hypothesis_before_propagations(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const {}

  void hypothesis_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const {}

  void exploration_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&) const {}
};

template<unsigned size, typename Explainer>
void explain(
  Explainer& explainer,  // NOLINT(runtime/references)
  Stack<ExplainableSudoku<size>>* stack,
  const std::vector<typename Explanation<size>::Propagation>& propagations
) {
  explainer.propagations_begin(*stack);
  for (const auto& propagation : propagations) {
    explainer.propagation_begin(*stack, propagation);

    explainer.propagation_targets_begin(*stack, propagation);
    for (const auto& target : propagation.targets) {
      explainer.propagation_target_begin(*stack, propagation, target);
      stack->current().cell(target.cell).forbid(propagation.value);
      explainer.propagation_target_end(*stack, propagation, target);
    }
    explainer.propagation_targets_end(*stack, propagation);

    bool solved = false;
    explainer.propagation_single_value_deductions_begin(*stack, propagation);
    for (const auto& target : propagation.targets) {
      for (const auto& deduction : target.single_value_deductions) {
        explainer.propagation_single_value_deduction_begin(*stack, propagation, target, deduction);
        stack->current().cell(deduction.cell).set_deduced(deduction.value);
        solved |= deduction.solved;
        explainer.propagation_single_value_deduction_end(*stack, propagation, target, deduction);
      }
    }
    explainer.propagation_single_value_deductions_end(*stack, propagation);

    explainer.propagation_single_place_deductions_begin(*stack, propagation);
    for (const auto& target : propagation.targets) {
      for (const auto& deduction : target.single_place_deductions) {
        explainer.propagation_single_place_deduction_begin(*stack, propagation, target, deduction);
        stack->current().cell(deduction.cell).set_deduced(deduction.value);
        solved |= deduction.solved;
        explainer.propagation_single_place_deduction_end(*stack, propagation, target, deduction);
      }
    }
    explainer.propagation_single_place_deductions_end(*stack, propagation);

    stack->current().cell(propagation.source).set_propagated();

    if (solved) {
      explainer.solved(*stack, propagation);
    }

    explainer.propagation_end(*stack, propagation);
  }
  explainer.propagations_end(*stack);
}

template<unsigned size, typename Explainer>
void explain(
  Explainer& explainer,  // NOLINT(runtime/references)
  Stack<ExplainableSudoku<size>>* stack,
  const std::optional<typename Explanation<size>::Exploration>& exploration
) {
  if (exploration) {
    explainer.exploration_begin(*stack, *exploration);
    for (const auto& hypothesis : exploration->explored_hypotheses) {
      explainer.hypothesis_begin(*stack, *exploration, hypothesis);

      stack->push();
      stack->current().cell(exploration->cell).set_hypothesis(hypothesis.value);

      explainer.hypothesis_before_propagations(*stack, *exploration, hypothesis);

      explain(explainer, stack, hypothesis.propagations);
      explain(explainer, stack, hypothesis.exploration);
      explainer.hypothesis_end(*stack, *exploration, hypothesis);

      stack->pop();
    }
    explainer.exploration_end(*stack, *exploration);
  }
}

template<unsigned size, typename Explainer>
void explain(
  Explainer& explainer,  // NOLINT(runtime/references)
  const Explanation<size>& explanation
) {
  Stack<ExplainableSudoku<size>> stack;

  for (const auto& cell : explanation.inputs.cells()) {
    const std::optional<unsigned> value = cell.get();
    if (value) {
      stack.current().cell(cell.coordinates()).set_input(*value);
    }
  }

  explainer.inputs(stack, explanation.inputs);

  explain(explainer, &stack, explanation.propagations);
  explain(explainer, &stack, explanation.exploration);
}

template<unsigned size, typename Explainer>
void explain(
  const Explanation<size>& explanation,
  Explainer& explainer  // NOLINT(runtime/references)
) {
  explain(explainer, explanation);
}

template<unsigned size, typename Explainer>
void explain(const Explanation<size>& explanation, const Explainer& explainer) {
  explain(explainer, explanation);
}

#endif  // EXPLANATION_EXPLANATION_HPP_
