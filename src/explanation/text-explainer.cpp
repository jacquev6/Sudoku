// Copyright 2023 Vincent Jacques

#include "text-explainer.hpp"

#include <boost/format.hpp>


template<unsigned size>
std::ostream& TextExplainer<size>::prefix(const Stack<ExplainableSudoku<size>>& stack) const {
  assert(stack.size() >= 1);
  for (unsigned i = 0; i < stack.size() - 1; ++i) {
    os << "  ";
  }
  return os;
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
      prefix(stack) << boost::format("(%1%, %2%) is set to %3% in the input\n") % (row + 1) % (col + 1) % (*value + 1);
    }
  }
  prefix(stack) << "All inputs have been set\n";
}

template<unsigned size>
void TextExplainer<size>::propagations_begin(const Stack<ExplainableSudoku<size>>& stack) const {
  prefix(stack) << "Propagation starts\n";
}

template<unsigned size>
void TextExplainer<size>::propagation_targets_begin(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  const auto [row, col] = propagation.source;
  prefix(stack) << boost::format("Propagation starts for %1% in (%2%, %3%)\n")
    % (propagation.value + 1) % (row + 1) % (col + 1);
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
    % (propagation.value + 1) % (src_row + 1) % (src_col + 1) % (tgt_row + 1) % (tgt_col + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_targets_end(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation& propagation
) const {
  const auto [row, col] = propagation.source;
  prefix(stack) << boost::format("%1% in (%2%, %3%) has been fully propagated\n")
    % (propagation.value + 1) % (row + 1) % (col + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_single_value_deduction_end(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation&,
  const typename Explanation<size>::PropagationTarget&,
  const typename Explanation<size>::SingleValueDeduction& deduction
) const {
  const auto [row, col] = deduction.cell;
  prefix(stack) << boost::format("(%1%, %2%) can only be %3%\n") % (row + 1) % (col + 1) % (deduction.value + 1);
}

template<unsigned size>
void TextExplainer<size>::propagation_single_place_deduction_end(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation&,
  const typename Explanation<size>::PropagationTarget&,
  const typename Explanation<size>::SinglePlaceDeduction& deduction
) const {
  const auto [row, col] = deduction.cell;
  prefix(stack) << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
    % (row + 1) % (col + 1) % (deduction.value + 1) % (deduction.region + 1);
}

template<unsigned size>
void TextExplainer<size>::solved(
  const Stack<ExplainableSudoku<size>>& stack,
  const typename Explanation<size>::Propagation&
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
  prefix(stack) << boost::format("(%1%, %2%) may be %3%\n") % (row + 1) % (col + 1) % (hypothesis.value + 1);
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
      % (row + 1) % (col + 1) % (hypothesis.value + 1);
  } else {
    prefix(stack) << boost::format("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n")
      % (row + 1) % (col + 1) % (hypothesis.value + 1);
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
