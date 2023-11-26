# 1 "src/explanation/video/video-serializer.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/explanation/video/video-serializer.hpp"
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

# 1 "src/explanation/video/serializer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_SERIALIZER_HPP_

#include <cairomm/surface.h>

#include <utility>
#include <vector>


namespace video
{
  struct Serializer
  {
    inline virtual constexpr ~Serializer() noexcept = default;
    virtual void serialize(std::shared_ptr<Cairo::ImageSurface>) = 0;
    
    // inline constexpr Serializer() noexcept = default;
  };
  
  struct MultipleSerializer : public Serializer
  {
    inline explicit MultipleSerializer(std::vector<Serializer *, std::allocator<Serializer *> > serializers_)
    : Serializer()
    , serializers{std::vector<Serializer *, std::allocator<Serializer *> >(std::move<std::vector<Serializer *, std::allocator<Serializer *> > &>(serializers_))}
    {
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      {
        std::vector<Serializer *, std::allocator<Serializer *> > & __range0 = this->serializers;
        __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > > __begin0 = __range0.begin();
        __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > > __end0 = __range0.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__begin0), static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__end0)); __begin0.operator++()) {
          Serializer *& serializer = static_cast<const __gnu_cxx::__normal_iterator<Serializer **, std::vector<Serializer *, std::allocator<Serializer *> > >>(__begin0).operator*();
          serializer->serialize(std::shared_ptr<Cairo::ImageSurface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(surface)));
        }
        
      }
    }
    
    
    private: 
    std::vector<Serializer *, std::allocator<Serializer *> > serializers;
    public: 
    // inline virtual constexpr ~MultipleSerializer() noexcept = default;
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_SERIALIZER_HPP_
# 19 "src/explanation/video/video-serializer.hpp"


namespace video
{
  struct VideoSerializer : public Serializer
  {
    inline explicit VideoSerializer(const std::filesystem::path & video_path_, int frame_width_, int frame_height_)
    : Serializer()
    , frame_index{static_cast<unsigned int>(0)}
    , video_path{std::filesystem::path(video_path_)}
    , frame_width_pixels{frame_width_}
    , frame_height_pixels{frame_height_}
    , codec{avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO)}
    , context{avcodec_alloc_context3(this->codec)}
    , picture{av_frame_alloc()}
    , pkt{av_packet_alloc()}
    , outfile{fopen(static_cast<const std::filesystem::path>(this->video_path).c_str(), static_cast<const char *>("wb"))}
    {
      (static_cast<bool>(this->codec) ? void(0) : __assert_fail(static_cast<const char *>("codec"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(39), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      (static_cast<bool>(this->pkt) ? void(0) : __assert_fail(static_cast<const char *>("pkt"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(40), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      (static_cast<bool>(this->outfile) ? void(0) : __assert_fail(static_cast<const char *>("outfile"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(41), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      this->context->bit_rate = static_cast<long>(400000);
      this->context->width = this->frame_width_pixels;
      this->context->height = this->frame_height_pixels;
      this->context->time_base.operator=(AVRational{1, 25});
      this->context->framerate.operator=(AVRational{25, 1});
      this->context->gop_size = 10;
      this->context->max_b_frames = 1;
      this->context->pix_fmt = AV_PIX_FMT_YUV420P;
      int ret = avcodec_open2(this->context, this->codec, static_cast<AVDictionary **>(NULL));
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(53), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
      this->picture->format = static_cast<int>(this->context->pix_fmt);
      this->picture->width = this->frame_width_pixels;
      this->picture->height = this->frame_height_pixels;
      ret = av_frame_get_buffer(this->picture, 32);
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(60), static_cast<const char *>(__extension__"video::VideoSerializer::VideoSerializer(const std::filesystem::path &, int, int)")));
    }
    
    inline virtual ~VideoSerializer() noexcept
    {
      this->encode(static_cast<AVFrame *>(nullptr));
      uint8_t endcode[4] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(1), static_cast<unsigned char>(183)};
      fwrite(reinterpret_cast<const void *>(static_cast<unsigned char *>(endcode)), static_cast<unsigned long>(1), sizeof(endcode), this->outfile);
      fclose(this->outfile);
      avcodec_free_context(&this->context);
      av_frame_free(&this->picture);
      av_packet_free(&this->pkt);
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      int ret = av_frame_make_writable(this->picture);
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(77), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<const Cairo::ImageSurface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->get_width() == this->frame_width_pixels) ? void(0) : __assert_fail(static_cast<const char *>("surface->get_width() == frame_width_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(79), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<const Cairo::ImageSurface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->get_height() == this->frame_height_pixels) ? void(0) : __assert_fail(static_cast<const char *>("surface->get_height() == frame_height_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(80), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      unsigned char * data = static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->()->get_data();
      (static_cast<bool>(data) ? void(0) : __assert_fail(static_cast<const char *>("data"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(82), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<int *>(this->picture->linesize)[0] == this->frame_width_pixels) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[0] == frame_width_pixels"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(84), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<int *>(this->picture->linesize)[1] == (this->frame_width_pixels / 2)) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[1] == frame_width_pixels / 2"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(85), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      (static_cast<bool>(static_cast<int *>(this->picture->linesize)[2] == (this->frame_width_pixels / 2)) ? void(0) : __assert_fail(static_cast<const char *>("picture->linesize[2] == frame_width_pixels / 2"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(86), static_cast<const char *>(__extension__"virtual void video::VideoSerializer::serialize(Cairo::RefPtr<Cairo::ImageSurface>)")));
      for(int y = 0; y < this->frame_height_pixels; ++y) {
        for(int x = 0; x < this->frame_width_pixels; ++x) {
          static_cast<unsigned char **>(this->picture->data)[0][(y * static_cast<int *>(this->picture->linesize)[0]) + x] = (static_cast<unsigned char>(((static_cast<double>(static_cast<int>(data[(((y * this->frame_width_pixels) * 4) + (x * 4)) + 0])) * 0.29899999999999999) + (static_cast<double>(static_cast<int>(data[(((y * this->frame_width_pixels) * 4) + (x * 4)) + 1])) * 0.58699999999999997)) + (static_cast<double>(static_cast<int>(data[(((y * this->frame_width_pixels) * 4) + (x * 4)) + 2])) * 0.114)));
        }
        
      }
      
      for(int y = 0; y < (this->frame_height_pixels / 2); ++y) {
        for(int x = 0; x < (this->frame_width_pixels / 2); ++x) {
          static_cast<unsigned char **>(this->picture->data)[1][(y * static_cast<int *>(this->picture->linesize)[1]) + x] = (static_cast<unsigned char>((((static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 0])) * -0.16900000000000001) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 1])) * -0.33100000000000002)) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 2])) * 0.5)) + static_cast<double>(128)));
          static_cast<unsigned char **>(this->picture->data)[2][(y * static_cast<int *>(this->picture->linesize)[2]) + x] = (static_cast<unsigned char>((((static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 0])) * 0.5) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 1])) * -0.41899999999999998)) + (static_cast<double>(static_cast<int>(data[((((y * 2) * this->frame_width_pixels) * 4) + ((x * 2) * 4)) + 2])) * -0.081000000000000003)) + static_cast<double>(128)));
        }
        
      }
      
      this->picture->pts = static_cast<long>(this->frame_index);
      this->encode(this->picture);
      ++this->frame_index;
    }
    
    
    private: 
    inline void encode(AVFrame * picture)
    {
      int ret = avcodec_send_frame(this->context, static_cast<const AVFrame *>(picture));
      (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(131), static_cast<const char *>(__extension__"void video::VideoSerializer::encode(AVFrame *)")));
      while(ret >= 0) {
        ret = avcodec_receive_packet(this->context, this->pkt);
        if((ret == (-(11))) || (ret == (-static_cast<int>(((static_cast<unsigned int>((static_cast<int>(('E')) | (static_cast<int>(('O')) << 8)) | (static_cast<int>(('F')) << 16))) | (static_cast<unsigned int>((' ')) << 24)))))) {
          return;
        } 
        
        (static_cast<bool>(ret >= 0) ? void(0) : __assert_fail(static_cast<const char *>("ret >= 0"), static_cast<const char *>("src/explanation/video/video-serializer.hpp"), static_cast<unsigned int>(138), static_cast<const char *>(__extension__"void video::VideoSerializer::encode(AVFrame *)")));
        fwrite(reinterpret_cast<const void *>(this->pkt->data), static_cast<unsigned long>(1), static_cast<unsigned long>(this->pkt->size), this->outfile);
        av_packet_unref(this->pkt);
      }
      
    }
    
    
    private: 
    unsigned int frame_index;
    std::filesystem::path video_path;
    int frame_width_pixels;
    int frame_height_pixels;
    const AVCodec * codec;
    AVCodecContext * context;
    AVFrame * picture;
    AVPacket * pkt;
    FILE * outfile;
    public: 
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_VIDEO_SERIALIZER_HPP_
# 4 "src/explanation/video/video-serializer.cpp"
