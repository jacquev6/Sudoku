// Copyright 2023 Vincent Jacques

#include "text-explainer.hpp"

#include <sstream>

#include <boost/format.hpp>

#include "../puzzle/sudoku-alphabet.hpp"


template<unsigned size>
std::ostream& TextExplainer<size>::prefix(const Stack<ExplainableSudoku<size>>& stack) const {
  assert(stack.size() >= 1);
  for (unsigned i = 0; i < stack.size() - 1; ++i) {
    os << "  ";
  }
  return os;
}

template<unsigned size>
char TextExplainer<size>::symbol(unsigned value) const {
  return SudokuAlphabet<size>::get_symbol(value);
}

template<unsigned size>
void TextExplainer<size>::inputs(
  const Stack<ExplainableSudoku<size>>& stack,
  const Sudoku<ValueCell, size>& inputs
) const {
  for (const auto& cell : inputs.cells()) {
    const std::optional<unsigned> value = cell.get();
    if (value) {
      const auto [row, col] = cell.coordinates();
      prefix(stack) << boost::format("(%1%, %2%) is set to %3% in the input\n")
        % (row + 1) % (col + 1) % symbol(*value);
    }
  }
  prefix(stack) << "All inputs have been set\n";
}

template<unsigned size>
void TextExplainer<size>::initial_deduction_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::SinglePlaceDeduction& deduction
) const {
  const auto [row, col] = deduction.cell;
  prefix(stack) << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
    % (row + 1) % (col + 1) % symbol(deduction.value) % (deduction.region + 1);
}

template<unsigned size>
void TextExplainer<size>::propagations_begin(const Stack<ExplainableSudoku<size>>& stack) const {
  prefix(stack) << "Propagation starts\n";
}

template<unsigned size>
void TextExplainer<size>::propagation_empty_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  const auto [row, col] = propagation.source;
  prefix(stack) << boost::format("%1% in (%2%, %3%) has no effect\n")
    % symbol(propagation.value) % (row + 1) % (col + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_targets_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  const auto [row, col] = propagation.source;
  prefix(stack) << boost::format("Propagation starts for %1% in (%2%, %3%)\n")
    % symbol(propagation.value) % (row + 1) % (col + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_target_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation,
  const typename Explanation<size>::PropagationTarget& target
) const {
  const auto [src_row, src_col] = propagation.source;
  const auto [tgt_row, tgt_col] = target.cell;
  prefix(stack) << boost::format("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n")
    % symbol(propagation.value) % (src_row + 1) % (src_col + 1) % (tgt_row + 1) % (tgt_col + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_targets_end(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  const auto [row, col] = propagation.source;
  prefix(stack) << boost::format("%1% in (%2%, %3%) has been fully propagated\n")
    % symbol(propagation.value) % (row + 1) % (col + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_targets_condensed_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  std::ostringstream targets;
  if (propagation.targets.size() >= 3) {
    for (auto target = propagation.targets.begin(); target != std::prev(propagation.targets.end()); ++target) {
      const auto [row, col] = target->cell;
      targets << boost::format("(%1%, %2%), ") % (row + 1) % (col + 1);
    }
    const auto [row, col] = propagation.targets.back().cell;
    targets << boost::format("and (%1%, %2%)") % (row + 1) % (col + 1);
  } else if (propagation.targets.size() == 2) {
    const auto [row1, col1] = propagation.targets.front().cell;
    const auto [row2, col2] = propagation.targets.back().cell;
    targets << boost::format("(%1%, %2%) and (%3%, %4%)") % (row1 + 1) % (col1 + 1) % (row2 + 1) % (col2 + 1);
  } else {
    assert(propagation.targets.size() == 1);
    const auto [row, col] = propagation.targets.front().cell;
    targets << boost::format("(%1%, %2%)") % (row + 1) % (col + 1);
  }
  const auto [row, col] = propagation.source;
  prefix(stack) << boost::format("%1% in (%2%, %3%) propagates to forbid %1% in %4%\n")
    % symbol(propagation.value) % (row + 1) % (col + 1) % targets.str();
}

template<unsigned size>
void TextExplainer<size>::propagation_single_value_deduction_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation&,
  const typename Explanation<size>::PropagationTarget&,
  const typename Explanation<size>::SingleValueDeduction& deduction
) const {
  const auto [row, col] = deduction.cell;
  prefix(stack) << boost::format("(%1%, %2%) can only be %3%\n") % (row + 1) % (col + 1) % symbol(deduction.value);
}

template<unsigned size>
void TextExplainer<size>::propagation_single_value_deductions_condensed_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  for (const auto& target : propagation.targets) {
    for (const auto& deduction : target.single_value_deductions) {
      propagation_single_value_deduction_begin(stack, propagation, target, deduction);
    }
  }
}

template<unsigned size>
void TextExplainer<size>::propagation_single_place_deduction_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation&,
  const typename Explanation<size>::PropagationTarget&,
  const typename Explanation<size>::SinglePlaceDeduction& deduction
) const {
  const auto [row, col] = deduction.cell;
  prefix(stack) << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
    % (row + 1) % (col + 1) % symbol(deduction.value) % (deduction.region + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_single_place_deductions_condensed_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  for (const auto& target : propagation.targets) {
    for (const auto& deduction : target.single_place_deductions) {
      propagation_single_place_deduction_begin(stack, propagation, target, deduction);
    }
  }
}

template<unsigned size>
void TextExplainer<size>::propagation_all_deductions_condensed_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  propagation_single_value_deductions_condensed_begin(stack, propagation);
  propagation_single_place_deductions_condensed_begin(stack, propagation);
}

template<unsigned size>
void TextExplainer<size>::solved(
  const Stack<ExplainableSudoku<size>>& stack
) const {
  prefix(stack) << "Sudoku is solved\n";
}


template<unsigned size>
void TextExplainer<size>::propagations_end(const Stack<ExplainableSudoku<size>>& stack) const {
  prefix(stack) << "All cells have been fully propagated\n";
}

template<unsigned size>
void TextExplainer<size>::exploration_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Exploration& exploration
) const {
  const auto [row, col] = exploration.cell;
  prefix(stack) << boost::format("Exploration starts for (%1%, %2%) with %3% possible values\n")
    % (row + 1) % (col + 1) % exploration.allowed_values.size();
}

template<unsigned size>
void TextExplainer<size>::hypothesis_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Exploration& exploration,
  const typename Explanation<size>::Hypothesis& hypothesis
) const {
  const auto [row, col] = exploration.cell;
  prefix(stack) << boost::format("(%1%, %2%) may be %3%\n") % (row + 1) % (col + 1) % symbol(hypothesis.value);
}

template<unsigned size>
void TextExplainer<size>::hypothesis_end(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Exploration& exploration,
  const typename Explanation<size>::Hypothesis& hypothesis
) const {
  const auto [row, col] = exploration.cell;
  if (hypothesis.successful) {
    prefix(stack) << boost::format("(%1%, %2%) can indeed be %3%\n")
      % (row + 1) % (col + 1) % symbol(hypothesis.value);
  } else {
    prefix(stack) << boost::format("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n")
      % (row + 1) % (col + 1) % symbol(hypothesis.value);
  }
}

template<unsigned size>
void TextExplainer<size>::exploration_end(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Exploration& exploration
) const {
  const auto [row, col] = exploration.cell;
  prefix(stack) << boost::format("Exploration is done for (%1%, %2%)\n") % (row + 1) % (col + 1);
}

template class TextExplainer<4>;
template class TextExplainer<9>;
template class TextExplainer<16>;
template class TextExplainer<25>;
