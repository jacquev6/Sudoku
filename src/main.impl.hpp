// Copyright 2023 Vincent Jacques

#ifndef MAIN_IMPL_HPP_
#define MAIN_IMPL_HPP_

#include "main.hpp"

#include <fstream>
#include <memory>
#include <vector>

#include "explanation/explanation.hpp"
#include "explanation/html-explainer.hpp"
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
    typename Explanation<size>::Builder explanation_builder;
    const auto solved = solve_using_exploration<size>(sudoku, explanation_builder);
    const Explanation<size> explanation = explanation_builder.get();

    if (options.text_path == "-") {
      explain_as_text(explanation, std::cout);
    } else if (options.text_path) {
      std::ofstream out(*options.text_path);
      assert(out.is_open());
      explain_as_text(explanation, out);
    }

    if (options.html_path) {
      explain_as_html(explanation, *options.html_path, options.width, options.height);
    }

    std::vector<std::unique_ptr<video::Serializer>> video_serializers;
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
      explain_as_video(explanation, video_serializers.back().get(), options.width, options.height);
    }

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
