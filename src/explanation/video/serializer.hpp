// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_SERIALIZER_HPP_

#include <cairomm/surface.h>

#include <utility>
#include <vector>


namespace video {

struct Serializer {
  virtual ~Serializer() = default;
  virtual void serialize(Cairo::RefPtr<Cairo::ImageSurface>) = 0;
};


struct MultipleSerializer : Serializer {
  explicit MultipleSerializer(std::vector<Serializer*> serializers_) : serializers(std::move(serializers_)) {}

  void serialize(Cairo::RefPtr<Cairo::ImageSurface> surface) override {
    for (auto& serializer : serializers) {
      serializer->serialize(surface);
    }
  }

 private:
  std::vector<Serializer*> serializers;
};

}  // namespace video

#endif  // EXPLANATION_VIDEO_SERIALIZER_HPP_
