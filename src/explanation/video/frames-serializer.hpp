// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_

#include <filesystem>
#include <iomanip>
#include <string>

#include "serializer.hpp"


namespace video {

struct FramesSerializer : Serializer {
  explicit FramesSerializer(const std::filesystem::path& directory_path_, const std::string& file_name_prefix_ = "") :
    frame_index(0),
    directory_path(directory_path_),
    file_name_prefix(file_name_prefix_)
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
  }

  void serialize(Cairo::RefPtr<Cairo::ImageSurface> surface) override {
    surface->write_to_png((directory_path / next_frame_name()).string());
  }

  std::string next_frame_name() {
    std::ostringstream oss;
    oss << file_name_prefix << std::setfill('0') << std::setw(6) << frame_index << ".png";
    ++frame_index;
    return oss.str();
  }

 private:
  unsigned frame_index;
  const std::filesystem::path directory_path;
  const std::string file_name_prefix;
};

}  // namespace video

#endif  // EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
