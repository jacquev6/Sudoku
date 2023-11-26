// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <string>

#include <boost/format.hpp>

#include "../exploration/events.hpp"


template<unsigned size>
class TextExplainer {
 public:
  explicit TextExplainer(std::ostream& os_) : os(os_), hypotheses_count(0) {}

  ~TextExplainer() {
    assert(hypotheses_count == 0);
  }

 public:
  void operator()(const exploration::CellIsSetInInput<size>& event) {
    print_prefix();
    os << boost::format("(%2%, %3%) is set to %1% in the input\n")
      % (event.value + 1) % (event.cell.first + 1) % (event.cell.second + 1);
  }

  void operator()(const exploration::InputsAreDone<size>&) {
    print_prefix();
    os << "All inputs have been set\n";
  }

  void operator()(const exploration::PropagationStartsForSudoku<size>&) {
    print_prefix();
    os << "Propagation starts\n";
  }

  void operator()(const exploration::PropagationStartsForCell<size>& event) {
    print_prefix();
    os << boost::format("Propagation starts for %1% in (%2%, %3%)\n")
      % (event.value + 1) % (event.cell.first + 1) % (event.cell.second + 1);
  }

  void operator()(const exploration::CellPropagates<size>& event) {
    print_prefix();
    os << boost::format("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n")
      % (event.value + 1) % (event.source_cell.first + 1) % (event.source_cell.second + 1)
      % (event.target_cell.first + 1) % (event.target_cell.second + 1);
  }

  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
    print_prefix();
    os << boost::format("(%1%, %2%) can only be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
    print_prefix();
    os << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1) % (event.region + 1);
  }

  void operator()(const exploration::PropagationIsDoneForCell<size>& event) {
    print_prefix();
    os << boost::format("%1% in (%2%, %3%) has been fully propagated\n")
      % (event.value + 1) % (event.cell.first + 1) % (event.cell.second + 1);
  }

  void operator()(const exploration::PropagationIsDoneForSudoku<size>&) {
    print_prefix();
    os << "All cells have been fully propagated\n";
  }

  void operator()(const exploration::ExplorationStarts<size>& event) {
    print_prefix();
    os << boost::format("Exploration starts for (%1%, %2%) with %3% possible values\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % event.allowed_values.size();
  }

  void operator()(const exploration::HypothesisIsMade<size>& event) {
    print_prefix();
    ++hypotheses_count;
    os << boost::format("(%1%, %2%) may be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void operator()(const exploration::HypothesisIsRejected<size>& event) {
    assert(hypotheses_count > 0);
    print_prefix();
    --hypotheses_count;
    os << boost::format("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void operator()(const exploration::SudokuIsSolved<size>&) {
    print_prefix();
    os << "Sudoku is solved\n";
  }

  void operator()(const exploration::HypothesisIsAccepted<size>& event) {
    assert(hypotheses_count > 0);
    print_prefix();
    --hypotheses_count;
    os << boost::format("(%1%, %2%) can indeed be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void operator()(const exploration::ExplorationIsDone<size>& event) {
    print_prefix();
    os << boost::format("Exploration is done for (%1%, %2%)\n")
      % (event.cell.first + 1) % (event.cell.second + 1);
  }

 private:
  void print_prefix() {
    for (unsigned i = 0; i < hypotheses_count; ++i) {
      os << "  ";
    }
  }

 private:
  std::ostream& os;
  unsigned hypotheses_count;
};

#endif  // EXPLANATION_TEXT_EXPLAINER_HPP_
