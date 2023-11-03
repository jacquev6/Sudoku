// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_FRAMES_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_FRAMES_VIDEO_SERIALIZER_HPP_

#include <filesystem>
#include <iomanip>
#include <string>

#include "video-serializer.hpp"


struct FramesVideoSerializer : VideoSerializer {
  explicit FramesVideoSerializer(const std::filesystem::path& directory_path_) :
    frame_index(0),
    directory_path(directory_path_)
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
  }

  void serialize(Cairo::RefPtr<Cairo::ImageSurface> surface) override {
    surface->write_to_png((directory_path / next_frame_name()).string());
  }

  std::string next_frame_name() {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(6) << frame_index << ".png";
    ++frame_index;
    return oss.str();
  }

 private:
  unsigned frame_index;
  std::filesystem::path directory_path;
};

#endif  // EXPLANATION_VIDEO_FRAMES_VIDEO_SERIALIZER_HPP_
