# 1 "src/explanation/video/frames-serializer.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/explanation/video/frames-serializer.hpp"
// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
#define EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_

#include <filesystem>
#include <iomanip>
#include <string>

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
# 11 "src/explanation/video/frames-serializer.hpp"


namespace video
{
  struct FramesSerializer : public Serializer
  {
    inline explicit FramesSerializer(const std::filesystem::path & directory_path_, const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & file_name_prefix_)
    : Serializer()
    , frame_index{static_cast<unsigned int>(0)}
    , directory_path{std::filesystem::path(directory_path_)}
    , file_name_prefix{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(file_name_prefix_)}
    {
      std::filesystem::create_directories(this->directory_path);
    }
    
    inline virtual void serialize(std::shared_ptr<Cairo::ImageSurface> surface)
    {
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path &&>((operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(this->next_frame_name(), std::filesystem::path::auto_format))))).string()));
    }
    
    inline std::basic_string<char, std::char_traits<char>, std::allocator<char> > next_frame_name()
    {
      std::basic_ostringstream<char> oss = std::basic_ostringstream<char>();
      std::operator<<(std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(oss), this->file_name_prefix), std::setfill<char>('0')), std::setw(6)).operator<<(this->frame_index), static_cast<const char *>(".png"));
      ++this->frame_index;
      return static_cast<const std::basic_ostringstream<char>>(oss).str();
    }
    
    
    private: 
    unsigned int frame_index;
    const std::filesystem::path directory_path;
    const std::basic_string<char, std::char_traits<char>, std::allocator<char> > file_name_prefix;
    public: 
    // inline FramesSerializer & operator=(const FramesSerializer &) /* noexcept */ = delete;
    // inline FramesSerializer & operator=(FramesSerializer &&) /* noexcept */ = delete;
    // inline virtual ~FramesSerializer() noexcept = default;
  };
  
  
}  // namespace video

#endif  // EXPLANATION_VIDEO_FRAMES_SERIALIZER_HPP_
# 4 "src/explanation/video/frames-serializer.cpp"
