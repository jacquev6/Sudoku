// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>
#include <fstream>
#include <set>
#include <string>

#include "art.hpp"
#include "explanation.hpp"


template<unsigned size>
class HtmlExplainer {
 public:
  explicit HtmlExplainer(const std::filesystem::path& directory_path_, unsigned frame_width_, unsigned frame_height_) :
    directory_path(directory_path_),
    frame_width(frame_width_),
    frame_height(frame_height_),
    index_file()
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
    index_file.open(directory_path / "index.html");
    index_file << "<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n";
  }

  ~HtmlExplainer() {
    index_file << "</body></html>\n";
  }

 public:
  void inputs(
    const Stack<ExplainableSudoku<size>>&,
    const Sudoku<ValueCell, size>&) const;

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
    const typename Explanation<size>::PropagationTarget&) const {}

  void propagation_target_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Propagation&,
    const typename Explanation<size>::PropagationTarget&) const;

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
    const typename Explanation<size>::Propagation&) const;

  void propagations_end(
    const Stack<ExplainableSudoku<size>>&) const {}

  void exploration_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&) const;

  void hypothesis_begin(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const {}

  void hypothesis_before_propagations(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const;

  void hypothesis_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&,
    const typename Explanation<size>::Hypothesis&) const {}

  void exploration_end(
    const Stack<ExplainableSudoku<size>>&,
    const typename Explanation<size>::Exploration&) const {}

 private:
  struct MakeImageOptions {
    bool draw_stack = true;
  };

  void make_image(
    const Stack<ExplainableSudoku<size>>&,
    const std::string&,
    art::DrawOptions,
    const MakeImageOptions& = {}) const;

 private:
  std::filesystem::path directory_path;
  unsigned frame_width;
  unsigned frame_height;
  mutable std::ofstream index_file;
  #ifndef NDEBUG
  mutable std::set<std::string> generated_image_names;
  #endif
};

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
