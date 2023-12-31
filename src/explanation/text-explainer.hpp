// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <iostream>
#include <vector>

#include "explanation.hpp"


template<unsigned size>
class TextExplainer {
 public:
  explicit TextExplainer(std::ostream& os_) : os(os_) {}

 public:
  void inputs(
    const Stack<ExplainableSudoku<size>>&,
    const Sudoku<ValueCell, size>&) const;

  void initial_deductions_begin(
    const Stack<ExplainableSudoku<size>>&,
    const std::vector<typename Explanation<size>::SinglePlaceDeduction>&) const {}

  void initial_deduction_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::SinglePlaceDeduction&) const;

  void initial_deduction_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::SinglePlaceDeduction&) const {}

  void initial_deductions_end(
    const Stack<ExplainableSudoku<size>>&,
    const std::vector<typename Explanation<size>::SinglePlaceDeduction>&) const {}

  void propagations_begin(
    const Stack<ExplainableSudoku<size>>&) const;

  void propagation_empty_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_empty_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_targets_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_target_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&) const;

  void propagation_target_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&) const {}

  void propagation_targets_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_targets_condensed_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_targets_condensed_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_value_deductions_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_value_deduction_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SingleValueDeduction&) const;

  void propagation_single_value_deduction_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SingleValueDeduction&) const {}

  void propagation_single_value_deductions_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_value_deductions_condensed_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_single_value_deductions_condensed_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_place_deductions_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_place_deduction_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SinglePlaceDeduction&) const;

  void propagation_single_place_deduction_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&,
    const typename Explanation<size>::SinglePlaceDeduction&) const {}

  void propagation_single_place_deductions_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_single_place_deductions_condensed_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_single_place_deductions_condensed_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_all_deductions_condensed_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const;

  void propagation_all_deductions_condensed_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void propagation_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&) const {}

  void solved(
    const Stack<ExplainableSudoku<size>>& stack) const;

  void propagations_end(
    const Stack<ExplainableSudoku<size>>&) const;

  void exploration_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&) const;

  void hypothesis_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const;

  void hypothesis_before_propagations(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const {}

  void hypothesis_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const;

  void exploration_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&) const;

 private:
  std::ostream& prefix(
    const Stack<ExplainableSudoku<size>>&) const;

  char symbol(unsigned value) const;

 private:
  std::ostream& os;
};

#endif  // EXPLANATION_TEXT_EXPLAINER_HPP_
