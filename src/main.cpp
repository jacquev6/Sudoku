// Copyright 2023 Vincent Jacques

#include "main.hpp"

#include <string>

#include <chrones.hpp>
#include <CLI11.hpp>

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


CHRONABLE("sudoku");

struct ExistingFileOrStdinValidator : public CLI::Validator {
  ExistingFileOrStdinValidator() : CLI::Validator("FILE(or - for stdin)") {
    func_ = [](const std::string& str) {
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
    func_ = [](const std::string&) { return std::string(); };
  }
};

const FileOrStdoutValidator FileOrStdout;

struct FileValidator : public CLI::Validator {
  FileValidator() : CLI::Validator("FILE") {
    func_ = [](const std::string&) { return std::string(); };
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
  CLI::App* benchmark = app.add_subcommand("benchmark", "Benchmark the Sudoku solvers");

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

  std::optional<std::filesystem::path> video_path;
  explain
    ->add_option("--video", video_path, "Generate video explanation in the given '.mpg' file")
    ->check(File);

  std::optional<std::filesystem::path> video_frames_path;
  explain
    ->add_option("--video-frames", video_frames_path,
      "Generate PNG frames from the video explanation in the given directory")
    ->check(CLI::NonexistentPath);

  unsigned width = 640;
  explain->add_option("--width", width, "Width of the images in the HTML and video explanations")
    ->default_val("640");
  unsigned height = 480;
  explain->add_option("--height", height, "Height of the images in the HTML and video explanations")
    ->default_val("480");

  std::filesystem::path input_path;
  for (auto* subcommand : {solve, explain, benchmark}) {
    subcommand
      ->add_option("INPUT", input_path, "Input file")
      ->check(ExistingFileOrStdin)
      ->required();
  }

  CLI11_PARSE(app, argc, argv);

  if (!text_path && !html_path && !video_path && !video_frames_path) {
    text_path = "-";
  }

  Options options {
    .solve = solve->parsed(),
    .use_sat = use_sat,
    .explain = explain->parsed(),
    .input_path = input_path,
    .text_path = text_path,
    .html_path = html_path,
    .video_path = video_path,
    .video_frames_path = video_frames_path,
    .width = width,
    .height = height,
    .benchmark = benchmark->parsed(),
  };

  switch (size) {
    case 4:
      return main_<4>(options);
    case 9:
      return main_<9>(options);
    case 16:
      return main_<16>(options);
    case 25:
      return main_<25>(options);
    default:
      std::cerr << "ERROR: unsupported size: " << size << std::endl;
      return 1;
  }
}
