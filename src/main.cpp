// Copyright 2023 Vincent Jacques

#include <CLI11.hpp>

#include "explanation/html-explainer.hpp"
#include "explanation/text-explainer.hpp"
#include "explanation/video/frames-video-serializer.hpp"
#include "explanation/video/video-explainer.hpp"
#include "explanation/video/video-video-serializer.hpp"
#include "exploration/sudoku-solver.hpp"
#include "sat/sudoku-solver.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


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

  const io::Sudoku sudoku = ([input_path](){
    if (input_path == "-") {
      return io::Sudoku::load(std::cin);
    } else {
      // Race condition: the input file could have been deleted since 'CLI11_PARSE' checked. Risk accepted.
      std::ifstream input(input_path);
      assert(input.is_open());
      return io::Sudoku::load(input);
    }
  })();

  if (solve->parsed()) {
    if (use_sat) {
      const io::Sudoku solved = solve_using_sat(sudoku);

      if (solved.is_all_set()) {
        solved.dump(std::cout);
      } else {
        std::cerr << "FAILED to solve this Sudoku using SAT" << std::endl;
        return 1;
      }
    } else {
      const io::Sudoku solved = solve_using_exploration(sudoku);

      if (solved.is_all_set()) {
        solved.dump(std::cout);
      } else {
        std::cerr << "FAILED to solve this Sudoku using exploration" << std::endl;
        return 1;
      }
    }
  } else if (explain->parsed()) {
    std::vector<std::unique_ptr<exploration::Event>> events;
    const io::Sudoku solved = solve_using_exploration(
      sudoku,
      [&events](std::unique_ptr<exploration::Event> event) {
        events.push_back(std::move(event));
      });

    if (solved.is_all_set()) {
      std::vector<std::unique_ptr<exploration::EventVisitor>> event_visitors;

      if (!text_path && !html_path && !html_text_path && !video_path && !video_frames_path && !video_text_path) {
        text_path = "-";
      }

      unsigned stdout_users = 0;
      std::unique_ptr<std::ofstream> text_output;
      if (text_path == "-") {
        event_visitors.push_back(std::make_unique<TextExplainer>(std::cout));
        ++stdout_users;
      } else if (text_path) {
        text_output = std::make_unique<std::ofstream>(*text_path);
        assert(text_output->is_open());
        event_visitors.push_back(std::make_unique<TextExplainer>(*text_output));
      }

      if (html_path) {
        event_visitors.push_back(std::make_unique<HtmlExplainer>(*html_path));
      }

      if (html_text_path == "-") {
        ++stdout_users;
      }

      std::vector<std::unique_ptr<VideoSerializer>> video_serializers;
      std::unique_ptr<std::ofstream> video_text_output;
      std::ostream* video_text_output_ptr;
      if (video_text_path == "-") {
        video_text_output_ptr = &std::cout;
        ++stdout_users;
      } else {
        if (video_text_path) {
          video_text_output = std::make_unique<std::ofstream>(*video_text_path);
        } else {
          video_text_output = std::make_unique<std::ofstream>("/dev/null");
        }
        assert(video_text_output->is_open());
        video_text_output_ptr = video_text_output.get();
      }
      TextExplainer video_text_explainer(*video_text_output_ptr);
      if (video_frames_path) {
        video_serializers.push_back(std::make_unique<FramesVideoSerializer>(*video_frames_path));
      }
      if (video_path) {
        video_serializers.push_back(std::make_unique<VideoVideoSerializer>(*video_path));
      }
      if (video_serializers.size() >= 2) {
        assert(video_serializers.size() == 2);
        video_serializers.push_back(std::make_unique<MultipleVideoSerializer>(
          std::vector<VideoSerializer*>{video_serializers[0].get(), video_serializers[1].get()}));
      }
      if (video_serializers.empty()) {
        event_visitors.push_back(std::make_unique<Follower>());  // Only to check asserts when not generating video
      } else {
        event_visitors.push_back(
          std::make_unique<VideoExplainer>(video_serializers.back().get(), &video_text_explainer, quick_video));
      }

      if (stdout_users > 1) {
        std::cerr << "WARNING: several explanations are interleaved on stdout." << std::endl;
      }

      for (const auto& event : events) {
        for (const auto& event_visitor : event_visitors) {
          event->accept(*event_visitor);
        }
      }
    } else {
      std::cerr << "FAILED to solve this Sudoku using exploration" << std::endl;
      return 1;
    }
  } else {
    __builtin_unreachable();
  }
}
