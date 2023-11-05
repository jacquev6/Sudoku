// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>
#include <fstream>

#include "../exploration/events.hpp"


template<unsigned size>
class HtmlExplainer : public exploration::EventVisitor<size> {
 public:
  explicit HtmlExplainer(const std::filesystem::path& directory_path_) :
    directory_path(directory_path_),
    index_file(),
    stack()
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
    index_file.open(directory_path / "index.html");
  }

 private:
  void visit(const exploration::CellIsSetInInput<size>&) override;
  void visit(const exploration::InputsAreDone<size>&) override;
  void visit(const exploration::PropagationStartsForSudoku<size>&) override;
  void visit(const exploration::PropagationStartsForCell<size>&) override;
  void visit(const exploration::CellPropagates<size>&) override;
  void visit(const exploration::CellIsDeducedFromSingleAllowedValue<size>&) override;
  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>&) override;
  void visit(const exploration::PropagationIsDoneForCell<size>&) override;
  void visit(const exploration::PropagationIsDoneForSudoku<size>&) override;
  void visit(const exploration::ExplorationStarts<size>&) override;
  void visit(const exploration::HypothesisIsMade<size>&) override;
  void visit(const exploration::HypothesisIsRejected<size>&) override;
  void visit(const exploration::SudokuIsSolved<size>&) override;
  void visit(const exploration::HypothesisIsAccepted<size>&) override;
  void visit(const exploration::ExplorationIsDone<size>&) override;

 private:
  const AnnotatedSudoku<size>& current() const { return stack.current(); }

 private:
  std::filesystem::path directory_path;
  std::ofstream index_file;
  Stack<size> stack;
};

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
