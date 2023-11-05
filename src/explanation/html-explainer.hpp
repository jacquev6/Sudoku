// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>
#include <fstream>

#include "../exploration/events.hpp"
#include "../exploration/follower.hpp"


class HtmlExplainer : public exploration::EventVisitor {
 public:
  explicit HtmlExplainer(const std::filesystem::path& directory_path_) :
    directory_path(directory_path_),
    index_file(),
    follower()
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
    index_file.open(directory_path / "index.html");
  }

 private:
  void visit(const exploration::CellIsSetInInput&) override;
  void visit(const exploration::InputsAreDone&) override;
  void visit(const exploration::PropagationStartsForSudoku&) override;
  void visit(const exploration::PropagationStartsForCell&) override;
  void visit(const exploration::CellPropagates&) override;
  void visit(const exploration::CellIsDeducedFromSingleAllowedValue&) override;
  void visit(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion&) override;
  void visit(const exploration::PropagationIsDoneForCell&) override;
  void visit(const exploration::PropagationIsDoneForSudoku&) override;
  void visit(const exploration::ExplorationStarts&) override;
  void visit(const exploration::HypothesisIsMade&) override;
  void visit(const exploration::HypothesisIsRejected&) override;
  void visit(const exploration::SudokuIsSolved&) override;
  void visit(const exploration::HypothesisIsAccepted&) override;
  void visit(const exploration::ExplorationIsDone&) override;

 private:
  const AnnotatedSudoku& current() const { return follower.current(); }

 private:
  std::filesystem::path directory_path;
  std::ofstream index_file;
  Follower follower;
};

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
