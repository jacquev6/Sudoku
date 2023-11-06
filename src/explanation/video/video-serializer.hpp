// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_

#include <cairomm/surface.h>

#include <utility>
#include <vector>


struct VideoSerializer {
  virtual ~VideoSerializer() = default;
  virtual void serialize(Cairo::RefPtr<Cairo::ImageSurface>) = 0;
};


struct MultipleVideoSerializer : VideoSerializer {
  explicit MultipleVideoSerializer(std::vector<VideoSerializer*> serializers_) : serializers(std::move(serializers_)) {}

  void serialize(Cairo::RefPtr<Cairo::ImageSurface> surface) override {
    for (auto& serializer : serializers) {
      serializer->serialize(surface);
    }
  }

 private:
  std::vector<VideoSerializer*> serializers;
};

struct NullVideoSerializer : VideoSerializer {
  void serialize(Cairo::RefPtr<Cairo::ImageSurface>) override {}
};

#endif  // EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
