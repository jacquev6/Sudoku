// Copyright 2023 Vincent Jacques

#include <CLI11.hpp>

#include "explanation/html-explainer.hpp"
#include "explanation/reorder.hpp"
#include "explanation/text-explainer.hpp"
#include "explanation/video/frames-serializer.hpp"
#include "explanation/video-explainer.hpp"
#include "explanation/video/video-serializer.hpp"
#include "exploration/sudoku-solver.hpp"
#include "puzzle/check.hpp"
#include "sat/sudoku-solver.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


struct Options {
  bool solve;
  bool use_sat;

  bool explain;
  std::filesystem::path input_path;
  std::optional<std::filesystem::path> text_path;
  std::optional<std::filesystem::path> html_path;
  std::optional<std::filesystem::path> html_text_path;
  std::optional<std::filesystem::path> video_path;
  bool quick_video;
  std::optional<std::filesystem::path> video_frames_path;
  std::optional<std::filesystem::path> video_text_path;
  unsigned width;
  unsigned height;
};

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
      [&](exploration::Event<size>&& event) {
        if (text_explainer) std::visit(*text_explainer, event);
        if (html_explainer) std::visit(*html_explainer, event);
        if (video_text_explainer) std::visit(*video_text_explainer, event);
        if (video_explainer) std::visit(*video_explainer, event);
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

struct ExistingFileOrStdinValidator : public CLI::Validator {
  ExistingFileOrStdinValidator() : CLI::Validator("FILE(or - for stdin)") {
    func_ = [](const std::string &str) {
      if (str == "-") {
        return std::string();
      } else {
        return CLI::ExistingFile(str);
      }
    };
  }
};

const ExistingFileOrStdinValidator ExistingFileOrStdin;

struct FileOrStdoutValidator : public CLI::Validator {
  FileOrStdoutValidator() : CLI::Validator("FILE(or - for stdout)") {
    func_ = [](const std::string &str) { return std::string(); };
  }
};

const FileOrStdoutValidator FileOrStdout;

struct FileValidator : public CLI::Validator {
  FileValidator() : CLI::Validator("FILE") {
    func_ = [](const std::string &str) { return std::string(); };
  }
};

const FileValidator File;


int main(int argc, char* argv[]) {
  CLI::App app{"Solve a Sudoku, and explain how!"};

  unsigned size = 9;
  app
    .add_option("--size", size, "Size of the Sudoku")
    ->option_text("4, 9 (default), 16...");

  app.require_subcommand(1);
  CLI::App* solve = app.add_subcommand("solve", "Just solve a Sudoku");
  CLI::App* explain = app.add_subcommand("explain", "Explain how to solve a Sudoku");

  bool use_sat = false;
  solve->add_flag("--sat", use_sat, "Use the 'Minisat' SAT solver instead of the default exploration algorithm");

  std::optional<std::filesystem::path> text_path;
  explain
    ->add_option("--text", text_path, "Generate detailed textual explanation in the given file")
    ->check(FileOrStdout);

  std::optional<std::filesystem::path> html_path;
  explain
    ->add_option("--html", html_path, "Generate HTML explanation in the given directory")
    ->check(CLI::NonexistentPath);

  std::optional<std::filesystem::path> html_text_path;
  // @todo explain->add_option("--html-text", html_text_path,
  //   "Generate textual explanation in the given file, reordered to match the html explanation");

  std::optional<std::filesystem::path> video_path;
  explain
    ->add_option("--video", video_path, "Generate video explanation in the given '.mpg' file")
    ->check(File);

  bool quick_video = false;
  explain
    ->add_flag("--quick-video", quick_video, "Make the video explanation quick (for testing)")
    ->group("");  // Hidden

  std::optional<std::filesystem::path> video_frames_path;
  explain
    ->add_option("--video-frames", video_frames_path,
      "Generate PNG frames from the video explanation in the given directory")
    ->check(CLI::NonexistentPath);

  std::optional<std::filesystem::path> video_text_path;
  explain->add_option(
    "--video-text", video_text_path,
      "Generate textual explanation in the given file, reordered to match the video explanation")
    ->check(FileOrStdout);

  unsigned width = 640;
  explain->add_option("--width", width, "Width of the images in the HTML and video explanations")
    ->default_val("640");
  unsigned height = 480;
  explain->add_option("--height", height, "Height of the images in the HTML and video explanations")
    ->default_val("480");

  std::filesystem::path input_path;
  for (auto* subcommand : {solve, explain}) {
    subcommand
      ->add_option("INPUT", input_path, "Input file")
      ->check(ExistingFileOrStdin)
      ->required();
  }

  CLI11_PARSE(app, argc, argv);

  if (!text_path && !html_path && !html_text_path && !video_path && !video_frames_path && !video_text_path) {
    text_path = "-";
  }

  Options options {
    .solve = solve->parsed(),
    .use_sat = use_sat,
    .explain = explain->parsed(),
    .input_path = input_path,
    .text_path = text_path,
    .html_path = html_path,
    .html_text_path = html_text_path,
    .video_path = video_path,
    .quick_video = quick_video,
    .video_frames_path = video_frames_path,
    .video_text_path = video_text_path,
    .width = width,
    .height = height,
  };

  switch (size) {
    case 4:
      return main_<4>(options);
    case 9:
      return main_<9>(options);
    default:
      std::cerr << "ERROR: unsupported size: " << size << std::endl;
      return 1;
  }
}
