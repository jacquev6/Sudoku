// Copyright 2023 Vincent Jacques

#include <CLI11.hpp>

#include "explanation/html-explainer.hpp"
#include "explanation/text-explainer.hpp"
#include "explanation/video/frames-video-serializer.hpp"
#include "explanation/video/video-explainer.hpp"
#include "explanation/video/video-video-serializer.hpp"
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
};

template<unsigned size>
int main_(const Options& options) {
  const io::Sudoku<size> sudoku = ([&options](){
    if (options.input_path == "-") {
      return io::Sudoku<size>::load(std::cin);
    } else {
      // Race condition: the input file could have been deleted since 'CLI11_PARSE' checked. Risk accepted.
      std::ifstream input(options.input_path);
      assert(input.is_open());
      return io::Sudoku<size>::load(input);
    }
  })();

  if (options.solve) {
    if (options.use_sat) {
      const io::Sudoku solved = solve_using_sat(sudoku);

      if (is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::cerr << "FAILED to solve this Sudoku using SAT" << std::endl;
        return 1;
      }
    } else {
      const io::Sudoku solved = solve_using_exploration(sudoku);

      if (is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::cerr << "FAILED to solve this Sudoku using exploration" << std::endl;
        return 1;
      }
    }
  } else if (options.explain) {
    std::vector<std::unique_ptr<exploration::Event<size>>> events;
    const io::Sudoku<size> solved = solve_using_exploration<size>(
      sudoku,
      [&events](std::unique_ptr<exploration::Event<size>> event) {
        events.push_back(std::move(event));
      });

    if (is_solved(solved)) {
      std::vector<std::unique_ptr<exploration::EventVisitor<size>>> event_visitors;

      unsigned stdout_users = 0;
      std::unique_ptr<std::ofstream> text_output;
      if (options.text_path == "-") {
        event_visitors.push_back(std::make_unique<TextExplainer<size>>(std::cout));
        ++stdout_users;
      } else if (options.text_path) {
        text_output = std::make_unique<std::ofstream>(*options.text_path);
        assert(text_output->is_open());
        event_visitors.push_back(std::make_unique<TextExplainer<size>>(*text_output));
      }

      if (options.html_path) {
        event_visitors.push_back(std::make_unique<HtmlExplainer<size>>(*options.html_path));
      }

      if (options.html_text_path == "-") {
        ++stdout_users;
      }

      std::vector<std::unique_ptr<VideoSerializer>> video_serializers;
      std::unique_ptr<std::ofstream> video_text_output;
      std::ostream* video_text_output_ptr;
      if (options.video_text_path == "-") {
        video_text_output_ptr = &std::cout;
        ++stdout_users;
      } else {
        if (options.video_text_path) {
          video_text_output = std::make_unique<std::ofstream>(*options.video_text_path);
        } else {
          video_text_output = std::make_unique<std::ofstream>("/dev/null");
        }
        assert(video_text_output->is_open());
        video_text_output_ptr = video_text_output.get();
      }
      TextExplainer<size> video_text_explainer(*video_text_output_ptr);
      if (options.video_frames_path) {
        video_serializers.push_back(std::make_unique<FramesVideoSerializer>(*options.video_frames_path));
      }
      if (options.video_path) {
        video_serializers.push_back(std::make_unique<VideoVideoSerializer>(*options.video_path));
      }
      if (video_serializers.size() >= 2) {
        assert(video_serializers.size() == 2);
        video_serializers.push_back(std::make_unique<MultipleVideoSerializer>(
          std::vector<VideoSerializer*>{video_serializers[0].get(), video_serializers[1].get()}));
      }
      if (!video_serializers.empty()) {
        event_visitors.push_back(
          std::make_unique<VideoExplainer<size>>(
            video_serializers.back().get(), &video_text_explainer, options.quick_video));
      }

      if (stdout_users > 1) {
        std::cerr << "WARNING: several explanations are interleaved on stdout." << std::endl;
      }

      for (const auto& event : events) {
        for (const auto& event_visitor : event_visitors) {
          event->accept(*event_visitor);
        }
      }

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

  // unsigned size = 9;
  // app
  //   .add_option("--size", size, "Size of the Sudoku")
  //   ->option_text("4, 9 (default)), 16, 25 or 36");

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
  };

  return main_<9>(options);
}
