// Copyright 2023 Vincent Jacques

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <filesystem>
#include <optional>


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
int main_(const Options& options);

#endif  // MAIN_HPP_
