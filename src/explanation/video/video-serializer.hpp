// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_

extern "C" {

#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>

}  // extern "C"

#include <cassert>
#include <filesystem>
#include <memory>

#include "serializer.hpp"


namespace video {

struct VideoSerializer : Serializer {
  explicit VideoSerializer(
    const std::filesystem::path& video_path_,
    int frame_width_,
    int frame_height_
  ) :  // NOLINT(whitespace/parens)
    frame_index(0),
    video_path(video_path_),
    frame_width_pixels(frame_width_),
    frame_height_pixels(frame_height_),
    codec(avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO)),
    context(avcodec_alloc_context3(codec)),
    picture(av_frame_alloc()),
    pkt(av_packet_alloc()),
    outfile(fopen(video_path.c_str(), "wb"))
  {  // NOLINT(whitespace/braces)
    assert(codec);
    assert(pkt);
    assert(outfile);

    context->bit_rate = 400000;
    context->width = frame_width_pixels;
    context->height = frame_height_pixels;
    context->time_base = AVRational{1, 25};
    context->framerate = AVRational{25, 1};
    context->gop_size = 10;
    context->max_b_frames = 1;
    context->pix_fmt = AV_PIX_FMT_YUV420P;

    int ret = avcodec_open2(context, codec, NULL);
    assert(ret >= 0);

    picture->format = context->pix_fmt;
    picture->width = frame_width_pixels;
    picture->height = frame_height_pixels;

    ret = av_frame_get_buffer(picture, 32);
    assert(ret >= 0);
  }

  ~VideoSerializer() {
    encode(nullptr);

    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    fwrite(endcode, 1, sizeof(endcode), outfile);
    fclose(outfile);

    avcodec_free_context(&context);
    av_frame_free(&picture);
    av_packet_free(&pkt);
  }

  void serialize(Cairo::RefPtr<Cairo::ImageSurface> surface) override {
    int ret = av_frame_make_writable(picture);
    assert(ret >= 0);

    assert(surface->get_width() == frame_width_pixels);
    assert(surface->get_height() == frame_height_pixels);
    unsigned char* data = surface->get_data();
    assert(data);

    assert(picture->linesize[0] == frame_width_pixels);
    assert(picture->linesize[1] == frame_width_pixels / 2);
    assert(picture->linesize[2] == frame_width_pixels / 2);

    // Bugs in the following conversion:
    // - red becomes blue
    // - blue becomes red
    // - light grey disappears as white

    /* Y */
    for (int y = 0; y < frame_height_pixels; ++y) {
      for (int x = 0; x < frame_width_pixels; ++x) {
        // Magic suggested by Copilot
        picture->data[0][y * picture->linesize[0] + x] =
          data[y * frame_width_pixels * 4 + x * 4 + 0] * 0.299
          + data[y * frame_width_pixels * 4 + x * 4 + 1] * 0.587
          + data[y * frame_width_pixels * 4 + x * 4 + 2] * 0.114;
      }
    }

    /* Cb and Cr */
    for (int y = 0; y < frame_height_pixels / 2; ++y) {
      for (int x = 0; x < frame_width_pixels / 2; ++x) {
        // Magic suggested by Copilot
        picture->data[1][y * picture->linesize[1] + x] =
          data[(y * 2) * frame_width_pixels * 4 + (x * 2) * 4 + 0] * -0.169
          + data[(y * 2) * frame_width_pixels * 4 + (x * 2) * 4 + 1] * -0.331
          + data[(y * 2) * frame_width_pixels * 4 + (x * 2) * 4 + 2] * 0.5
          + 128;
        picture->data[2][y * picture->linesize[2] + x] =
          data[(y * 2) * frame_width_pixels * 4 + (x * 2) * 4 + 0] * 0.5
          + data[(y * 2) * frame_width_pixels * 4 + (x * 2) * 4 + 1] * -0.419
          + data[(y * 2) * frame_width_pixels * 4 + (x * 2) * 4 + 2] * -0.081
          + 128;
      }
    }

    picture->pts = frame_index;

    encode(picture);

    ++frame_index;
  }

 private:
  void encode(AVFrame* picture) {
    int ret = avcodec_send_frame(context, picture);
    assert(ret >= 0);

    while (ret >= 0) {
      ret = avcodec_receive_packet(context, pkt);
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        return;
      }
      assert(ret >= 0);

      fwrite(pkt->data, 1, pkt->size, outfile);
      av_packet_unref(pkt);
    }
  }

 private:
  unsigned frame_index;
  std::filesystem::path video_path;
  int frame_width_pixels;
  int frame_height_pixels;
  const AVCodec* codec;
  AVCodecContext* context;
  AVFrame* picture;
  AVPacket* pkt;
  FILE* outfile;
};

}  // namespace video

#endif  // EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
