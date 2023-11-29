// Copyright 2023 Vincent Jacques

#include "text-explainer.hpp"

#include <algorithm>
#include <vector>

#include <boost/format.hpp>


template<unsigned size>
class TextExplainer {
 public:
  TextExplainer(const Explanation<size>& explanation_, std::ostream& os_, const bool reordered_) :
    explanation(explanation_), os(os_), reordered(reordered_)
  {}

 public:
  void explain() {
    for (const auto& cell : explanation.inputs.cells()) {
      const std::optional<unsigned> value = cell.get();
      if (value) {
        const auto [row, col] = cell.coordinates();
        prefix() << boost::format("(%1%, %2%) is set to %3% in the input\n") % (row + 1) % (col + 1) % (*value + 1);
      }
    }
    prefix() << "All inputs have been set\n";
    explain(explanation.propagations);
    explain(explanation.exploration);
  }

 private:
  void explain(const std::vector<typename Explanation<size>::Propagation>& propagations) {
    prefix() << "Propagation starts\n";
    for (const auto& propagation : propagations) {
      const auto [src_row, src_col] = propagation.source;
      prefix() << boost::format("Propagation starts for %1% in (%2%, %3%)\n")
        % (propagation.value + 1) % (src_row + 1) % (src_col + 1);
      bool solved = false;
      for (const auto& target : propagation.targets) {
        const auto [tgt_row, tgt_col] = target.cell;
        prefix() << boost::format("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n")
          % (propagation.value + 1) % (src_row + 1) % (src_col + 1) % (tgt_row + 1) % (tgt_col + 1);
        solved |= std::any_of(
          target.single_value_deductions.begin(),
          target.single_value_deductions.end(),
          [](const auto& deduction) { return deduction.solved; });
        solved |= std::any_of(
          target.single_place_deductions.begin(),
          target.single_place_deductions.end(),
          [](const auto& deduction) { return deduction.solved; });
        if (!reordered || solved) {
          for (const auto& deduction : target.single_value_deductions) {
            const auto [row, col] = deduction.cell;
            prefix() << boost::format("(%1%, %2%) can only be %3%\n") % (row + 1) % (col + 1) % (deduction.value + 1);
            if (deduction.solved) {
              prefix() << "Sudoku is solved\n";
            }
          }
          for (const auto& deduction : target.single_place_deductions) {
            const auto [row, col] = deduction.cell;
            prefix() << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
              % (row + 1) % (col + 1) % (deduction.value + 1) % (deduction.region + 1);
            if (deduction.solved) {
              prefix() << "Sudoku is solved\n";
            }
          }
        }
      }
      prefix() << boost::format("%1% in (%2%, %3%) has been fully propagated\n")
        % (propagation.value + 1) % (src_row + 1) % (src_col + 1);
      if (reordered && !solved) {
        for (const auto& target : propagation.targets) {
          for (const auto& deduction : target.single_value_deductions) {
            assert(!deduction.solved);
            const auto [row, col] = deduction.cell;
            prefix() << boost::format("(%1%, %2%) can only be %3%\n") % (row + 1) % (col + 1) % (deduction.value + 1);
          }
        }
        for (const auto& target : propagation.targets) {
          for (const auto& deduction : target.single_place_deductions) {
            assert(!deduction.solved);
            const auto [row, col] = deduction.cell;
            prefix() << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
              % (row + 1) % (col + 1) % (deduction.value + 1) % (deduction.region + 1);
          }
        }
      }
    }
    prefix() << "All cells have been fully propagated\n";
  }

  void explain(const std::optional<typename Explanation<size>::Exploration>& exploration) {
    if (exploration.has_value()) {
      explain(*exploration);
    }
  }

  void explain(const typename Explanation<size>::Exploration& exploration) {
    const auto [row, col] = exploration.cell;
    prefix() << boost::format("Exploration starts for (%1%, %2%) with %3% possible values\n")
      % (row + 1) % (col + 1) % exploration.allowed_values.size();

    for (const auto& hypothesis : exploration.explored_hypotheses) {
      prefix() << boost::format("(%1%, %2%) may be %3%\n") % (row + 1) % (col + 1) % (hypothesis.value + 1);
      ++hypotheses_count;
      explain(hypothesis.propagations);
      explain(hypothesis.exploration);
      if (hypothesis.successful) {
        prefix() << boost::format("(%1%, %2%) can indeed be %3%\n")
          % (row + 1) % (col + 1) % (hypothesis.value + 1);
      } else {
        prefix() << boost::format("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n")
          % (row + 1) % (col + 1) % (hypothesis.value + 1);
      }
      --hypotheses_count;
    }

    prefix() << boost::format("Exploration is done for (%1%, %2%)\n") % (row + 1) % (col + 1);
  }

 private:
  std::ostream& prefix() {
    for (unsigned i = 0; i < hypotheses_count; ++i) {
      os << "  ";
    }
    return os;
  }

 private:
  const Explanation<size>& explanation;
  std::ostream& os;
  const bool reordered;
  unsigned hypotheses_count = 0;
};

template<unsigned size>
void explain_as_text(const Explanation<size>& explanation, std::ostream& os, const bool reordered) {
  TextExplainer(explanation, os, reordered).explain();
}

template void explain_as_text<4>(const Explanation<4>&, std::ostream&, bool);
template void explain_as_text<9>(const Explanation<9>&, std::ostream&, bool);
