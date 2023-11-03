// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <string>

#include <boost/format.hpp>

#include "../exploration/events.hpp"


class TextExplainer : public exploration::EventVisitor {
 public:
  explicit TextExplainer(std::ostream& os_) : os(os_), hypotheses_count(0) {}

  ~TextExplainer() {
    assert(hypotheses_count == 0);
  }

 private:
  void visit(const exploration::CellIsSetInInput& event) override {
    print_prefix();
    os << boost::format("(%2%, %3%) is set to %1% in the input\n")
      % (event.value + 1) % (event.cell.first + 1) % (event.cell.second + 1);
  }

  void visit(const exploration::InputsAreDone&) override {
    print_prefix();
    os << "All inputs have been set\n";
  }

  void visit(const exploration::PropagationStartsForSudoku&) override {
    print_prefix();
    os << "Propagation starts\n";
  }

  void visit(const exploration::PropagationStartsForCell& event) override {
    print_prefix();
    os << boost::format("Propagation starts for %1% in (%2%, %3%)\n")
      % (event.value + 1) % (event.cell.first + 1) % (event.cell.second + 1);
  }

  void visit(const exploration::CellPropagates& event) override {
    print_prefix();
    os << boost::format("%1% in (%2%, %3%) forbids %1% in (%4%, %5%)\n")
      % (event.value + 1) % (event.source_cell.first + 1) % (event.source_cell.second + 1)
      % (event.target_cell.first + 1) % (event.target_cell.second + 1);
  }

  void visit(const exploration::CellIsDeducedFromSingleAllowedValue& event) override {
    print_prefix();
    os << boost::format("(%1%, %2%) can only be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion& event) override {
    print_prefix();
    os << boost::format("In region %4%, only (%1%, %2%) can be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1) % (event.region + 1);
  }

  void visit(const exploration::PropagationIsDoneForCell& event) override {
    print_prefix();
    os << boost::format("%1% in (%2%, %3%) has been fully propagated\n")
      % (event.value + 1) % (event.cell.first + 1) % (event.cell.second + 1);
  }

  void visit(const exploration::PropagationIsDoneForSudoku& event) override {
    print_prefix();
    os << "All cells have been fully propagated\n";
  }

  void visit(const exploration::ExplorationStarts& event) override {
    print_prefix();
    os << boost::format("Exploration starts for (%1%, %2%) with %3% possible values\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % event.allowed_values.size();
  }

  void visit(const exploration::HypothesisIsMade& event) override {
    print_prefix();
    ++hypotheses_count;
    std::string spoiler;
    if (event.spoiler) {
      if (*event.spoiler) {
        spoiler = " (spoiler: it can)";
      } else {
        spoiler = " (spoiler: it can't)";
      }
    }
    os << boost::format("(%1%, %2%) may be %3%%4%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1) % spoiler;
  }

  void visit(const exploration::HypothesisIsRejected& event) override {
    assert(hypotheses_count > 0);
    print_prefix();
    --hypotheses_count;
    os << boost::format("Hypothesis that (%1%, %2%) may have been %3% must be back-tracked\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void visit(const exploration::SudokuIsSolved& event) override {
    print_prefix();
    os << "Sudoku is solved\n";
  }

  void visit(const exploration::HypothesisIsAccepted& event) override {
    assert(hypotheses_count > 0);
    print_prefix();
    --hypotheses_count;
    os << boost::format("(%1%, %2%) can indeed be %3%\n")
      % (event.cell.first + 1) % (event.cell.second + 1) % (event.value + 1);
  }

  void visit(const exploration::ExplorationIsDone& event) override {
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
