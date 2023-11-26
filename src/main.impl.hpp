// Copyright 2023 Vincent Jacques

#ifndef MAIN_IMPL_HPP_
#define MAIN_IMPL_HPP_

#include "main.hpp"

#include <memory>
#include <vector>

#include "explanation/html-explainer.hpp"
#include "explanation/reorder.hpp"
#include "explanation/text-explainer.hpp"
#include "explanation/video/frames-serializer.hpp"
#include "explanation/video-explainer.hpp"
#include "explanation/video/video-serializer.hpp"
#include "exploration/sudoku-solver.hpp"
#include "puzzle/check.hpp"
#include "sat/sudoku-solver.hpp"


template<unsigned size>
int main_(const Options& options) {
  const auto sudoku = ([&options](){
    if (options.input_path == "-") {
      return Sudoku<ValueCell, size>::load(std::cin);
    } else {
      // Race condition: the input file could have been deleted since 'CLI11_PARSE' checked. Risk accepted.
      std::ifstream input(options.input_path);
      assert(input.is_open());
      return Sudoku<ValueCell, size>::load(input);
    }
  })();

  if (options.solve) {
    if (options.use_sat) {
      const auto solved = solve_using_sat(sudoku);

      if (is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::cerr << "FAILED to solve this Sudoku using SAT" << std::endl;
        return 1;
      }
    } else {
      const auto solved = solve_using_exploration(sudoku);

      if (is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::cerr << "FAILED to solve this Sudoku using exploration" << std::endl;
        return 1;
      }
    }
  } else if (options.explain) {
    unsigned stdout_users = 0;

    std::optional<std::ofstream> text_output;
    std::optional<TextExplainer<size>> text_explainer;
    if (options.text_path == "-") {
      ++stdout_users;
      text_explainer.emplace(std::cout);
    } else if (options.text_path) {
      text_output.emplace(*options.text_path);
      assert(text_output->is_open());
      text_explainer.emplace(*text_output);
    }

    std::optional<HtmlExplainer<size>> html_explainer;
    if (options.html_path) {
      html_explainer.emplace(*options.html_path, options.width, options.height);
    }

    if (options.html_text_path == "-") {
      ++stdout_users;
    }

    std::optional<std::ofstream> video_text_output;
    std::optional<TextExplainer<size>> video_text_explainer_;
    std::optional<Reorder<size, TextExplainer<size>>> video_text_explainer;
    if (options.video_text_path) {
      if (options.video_text_path == "-") {
        ++stdout_users;
        video_text_explainer_.emplace(std::cout);
      } else {
        video_text_output.emplace(*options.video_text_path);
        assert(video_text_output->is_open());
        video_text_explainer_.emplace(*video_text_output);
      }
      video_text_explainer.emplace(&*video_text_explainer_);
    }

    std::vector<std::unique_ptr<video::Serializer>> video_serializers;
    std::optional<VideoExplainer<size>> video_explainer_;
    std::optional<Reorder<size, VideoExplainer<size>>> video_explainer;
    if (options.video_frames_path) {
      video_serializers.push_back(std::make_unique<video::FramesSerializer>(*options.video_frames_path));
    }
    if (options.video_path) {
      video_serializers.push_back(std::make_unique<video::VideoSerializer>(
        *options.video_path, options.width, options.height));
    }
    if (video_serializers.size() > 1) {
      assert(video_serializers.size() == 2);
      video_serializers.push_back(std::make_unique<video::MultipleSerializer>(
        std::vector<video::Serializer*>{video_serializers[0].get(), video_serializers[1].get()}));
    }
    if (!video_serializers.empty()) {
      video_explainer_.emplace(video_serializers.back().get(), options.quick_video, options.width, options.height);
      video_explainer.emplace(&*video_explainer_);
    }

    if (stdout_users > 1) {
      std::cerr << "WARNING: several explanations are interleaved on stdout." << std::endl;
    }

    const auto solved = solve_using_exploration<size>(
      sudoku,
      [&](const auto& event) {
        if (text_explainer) (*text_explainer)(event);
        if (html_explainer) (*html_explainer)(event);
        if (video_text_explainer) (*video_text_explainer)(event);
        if (video_explainer) (*video_explainer)(event);
      });

    if (is_solved(solved)) {
      return 0;
    } else {
      std::cerr << "FAILED to solve this Sudoku using exploration" << std::endl;
      return 1;
    }
  } else {
    __builtin_unreachable();
  }
}

#endif  // MAIN_IMPL_HPP_
