# 1 "src/main.cpp"
// Copyright 2023 Vincent Jacques

# 1 "src/main.hpp"
// Copyright 2023 Vincent Jacques

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <filesystem>
#include <optional>


struct Options
{
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
  unsigned int width;
  unsigned int height;
  // inline ~Options() noexcept = default;
};



template<unsigned int size>
int main_(const Options & options);
;

#endif  // MAIN_HPP_
# 4 "src/main.cpp"

#include <string>

#include <CLI11.hpp>

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


struct ExistingFileOrStdinValidator : public CLI::Validator
{
  inline ExistingFileOrStdinValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE(or - for stdin)"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_0
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str) const
      {
        if(std::operator==(str, static_cast<const char *>("-"))) {
          return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
        } else {
          return static_cast<const CLI::Validator&>(CLI::ExistingFile).operator()(str);
        } 
        
      }
      
      using retType_47_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_47_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_0{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_0(const __lambda_0 &) noexcept = default;
      // inline /*constexpr */ __lambda_0(__lambda_0 &&) noexcept = default;
      // /*constexpr */ __lambda_0() = default;
      
    } __lambda_0{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_0);
  }
  
  // inline ~ExistingFileOrStdinValidator() noexcept = default;
};



const ExistingFileOrStdinValidator ExistingFileOrStdin = ExistingFileOrStdinValidator();


struct FileOrStdoutValidator : public CLI::Validator
{
  inline FileOrStdoutValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE(or - for stdout)"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_1
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &) const
      {
        return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
      }
      
      using retType_61_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_61_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & __param0)
      {
        return __lambda_1{}.operator()(__param0);
      }
      
      public: 
      // inline /*constexpr */ __lambda_1(const __lambda_1 &) noexcept = default;
      // inline /*constexpr */ __lambda_1(__lambda_1 &&) noexcept = default;
      // /*constexpr */ __lambda_1() = default;
      
    } __lambda_1{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_1);
  }
  
  // inline ~FileOrStdoutValidator() noexcept = default;
};



const FileOrStdoutValidator FileOrStdout = FileOrStdoutValidator();


struct FileValidator : public CLI::Validator
{
  inline FileValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_2
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &) const
      {
        return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
      }
      
      using retType_69_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_69_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & __param0)
      {
        return __lambda_2{}.operator()(__param0);
      }
      
      public: 
      // inline /*constexpr */ __lambda_2(const __lambda_2 &) noexcept = default;
      // inline /*constexpr */ __lambda_2(__lambda_2 &&) noexcept = default;
      // /*constexpr */ __lambda_2() = default;
      
    } __lambda_2{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_2);
  }
  
  // inline ~FileValidator() noexcept = default;
};



const FileValidator File = FileValidator();



int main(int argc, char ** argv)
{
  CLI::App app = CLI::App{std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Solve a Sudoku, and explain how!"), static_cast<const std::allocator<char>>(std::allocator<char>())), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>()))};
  unsigned int size = static_cast<unsigned int>(9);
  app.add_option<unsigned int, unsigned int, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--size"), static_cast<const std::allocator<char>>(std::allocator<char>())), size, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Size of the Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())))->option_text(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("4, 9 (default), 16..."), static_cast<const std::allocator<char>>(std::allocator<char>())));
  app.require_subcommand(1);
  CLI::App * solve = app.add_subcommand(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solve"), static_cast<const std::allocator<char>>(std::allocator<char>())), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Just solve a Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())));
  CLI::App * explain = app.add_subcommand(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("explain"), static_cast<const std::allocator<char>>(std::allocator<char>())), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Explain how to solve a Sudoku"), static_cast<const std::allocator<char>>(std::allocator<char>())));
  bool use_sat = false;
  solve->add_flag<bool, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--sat"), static_cast<const std::allocator<char>>(std::allocator<char>())), use_sat, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Use the 'Minisat' SAT solver instead of the default exploration algorithm"), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> text_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--text"), static_cast<const std::allocator<char>>(std::allocator<char>())), text_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate detailed textual explanation in the given file"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(FileOrStdout)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> html_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--html"), static_cast<const std::allocator<char>>(std::allocator<char>())), html_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate HTML explanation in the given directory"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(CLI::NonexistentPath)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> html_text_path = std::optional<std::filesystem::path>();
  std::optional<std::filesystem::path> video_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--video"), static_cast<const std::allocator<char>>(std::allocator<char>())), video_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate video explanation in the given '.mpg' file"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(File)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  bool quick_video = false;
  static_cast<CLI::OptionBase<CLI::Option> *>(explain->add_flag<bool, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--quick-video"), static_cast<const std::allocator<char>>(std::allocator<char>())), quick_video, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Make the video explanation quick (for testing)"), static_cast<const std::allocator<char>>(std::allocator<char>()))))->group(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> video_frames_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--video-frames"), static_cast<const std::allocator<char>>(std::allocator<char>())), video_frames_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate PNG frames from the video explanation in the given directory"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(CLI::NonexistentPath)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  std::optional<std::filesystem::path> video_text_path = std::optional<std::filesystem::path>();
  explain->add_option<std::optional<std::filesystem::path>, std::optional<std::filesystem::path>, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--video-text"), static_cast<const std::allocator<char>>(std::allocator<char>())), video_text_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Generate textual explanation in the given file, reordered to match the video explanation"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(FileOrStdout)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>())));
  unsigned int width = static_cast<unsigned int>(640);
  explain->add_option<unsigned int, unsigned int, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--width"), static_cast<const std::allocator<char>>(std::allocator<char>())), width, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Width of the images in the HTML and video explanations"), static_cast<const std::allocator<char>>(std::allocator<char>())))->default_val<char[4]>("640");
  unsigned int height = static_cast<unsigned int>(480);
  explain->add_option<unsigned int, unsigned int, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("--height"), static_cast<const std::allocator<char>>(std::allocator<char>())), height, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Height of the images in the HTML and video explanations"), static_cast<const std::allocator<char>>(std::allocator<char>())))->default_val<char[4]>("480");
  std::filesystem::path input_path = std::filesystem::path();
  {
    std::initializer_list<CLI::App *> && __range0 = std::initializer_list<CLI::App *>{solve, explain};
    CLI::App *const * __begin0 = static_cast<const std::initializer_list<CLI::App *>>(__range0).begin();
    CLI::App *const * __end0 = static_cast<const std::initializer_list<CLI::App *>>(__range0).end();
    for(; __begin0 != __end0; ++__begin0) {
      CLI::App * subcommand = *__begin0;
      static_cast<CLI::OptionBase<CLI::Option> *>(subcommand->add_option<std::filesystem::path, std::filesystem::path, 0>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("INPUT"), static_cast<const std::allocator<char>>(std::allocator<char>())), input_path, std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("Input file"), static_cast<const std::allocator<char>>(std::allocator<char>())))->check(CLI::Validator(static_cast<const CLI::Validator&>(ExistingFileOrStdin)), std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>(""), static_cast<const std::allocator<char>>(std::allocator<char>()))))->required(true);
    }
    
  }
  try 
  {
    (app).parse((argc), static_cast<const char *const *>((argv)));
  } catch(const CLI::ParseError & e) {
    return static_cast<const CLI::App>((app)).exit(static_cast<const CLI::Error&>(e), std::cout, std::cerr);
  }
  ;
  ;
  if(((((!static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(text_path).operator bool()) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(html_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(html_text_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(video_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(video_frames_path).operator bool())) && !static_cast<bool>(static_cast<const std::optional<std::filesystem::path>>(video_text_path).operator bool())) {
    text_path.operator=("-");
  } 
  
  Options options = {static_cast<const CLI::App *>(solve)->parsed(), use_sat, static_cast<const CLI::App *>(explain)->parsed(), std::filesystem::path(static_cast<const std::filesystem::path>(input_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(text_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(html_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(html_text_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(video_path)), quick_video, std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(video_frames_path)), std::optional<std::filesystem::path>(static_cast<const std::optional<std::filesystem::path>>(video_text_path)), width, height};
  switch(size) {
    case static_cast<unsigned int>(4): return main_<4>(static_cast<const Options>(options));
    case static_cast<unsigned int>(9): return main_<9>(static_cast<const Options>(options));
    default: std::operator<<(std::cerr, static_cast<const char *>("ERROR: unsupported size: ")).operator<<(size).operator<<(std::endl);
    return 1;
  }
  return 0;
}

