// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>
#include <fstream>
#include <string>

#include "../exploration/events.hpp"


template<unsigned size>
class HtmlExplainer {
 public:
  explicit HtmlExplainer(const std::filesystem::path& directory_path_, unsigned frame_width_, unsigned frame_height_) :
    directory_path(directory_path_),
    frame_width(frame_width_),
    frame_height(frame_height_),
    index_file(),
    stack()
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
    index_file.open(directory_path / "index.html");
  }

 public:
  void operator()(const exploration::CellIsSetInInput<size>&);
  void operator()(const exploration::InputsAreDone<size>&);
  void operator()(const exploration::PropagationStartsForSudoku<size>&);
  void operator()(const exploration::PropagationStartsForCell<size>&);
  void operator()(const exploration::CellPropagates<size>&);
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>&);
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>&);
  void operator()(const exploration::PropagationIsDoneForCell<size>&);
  void operator()(const exploration::PropagationIsDoneForSudoku<size>&);
  void operator()(const exploration::ExplorationStarts<size>&);
  void operator()(const exploration::HypothesisIsMade<size>&);
  void operator()(const exploration::HypothesisIsRejected<size>&);
  void operator()(const exploration::SudokuIsSolved<size>&);
  void operator()(const exploration::HypothesisIsAccepted<size>&);
  void operator()(const exploration::ExplorationIsDone<size>&);

 private:
  const AnnotatedSudoku<size>& current() const { return stack.current(); }
  struct Image;
  Image image(const std::string&) const;

 private:
  std::filesystem::path directory_path;
  unsigned frame_width;
  unsigned frame_height;
  std::ofstream index_file;
  Stack<size> stack;
};

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
