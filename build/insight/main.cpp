// Copyright 2023 Vincent Jacques

#include <CLI11.hpp>

#include "explanation/html-explainer.hpp"
#include "explanation/reorder.hpp"
#include "explanation/text-explainer.hpp"
#include "explanation/video/frames-serializer.hpp"
#include "explanation/video-explainer.hpp"
#include "explanation/video/video-serializer.hpp"
#include "exploration/sudoku-solver.hpp"
#include "puzzle/check.hpp"
#include "sat/sudoku-solver.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


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
int main_(const Options & options)
{
      
  class __lambda_38_24
  {
    public: 
    inline auto operator()() const
    {
      if(operator==(options.input_path, std::filesystem::path("-", std::filesystem::path::auto_format))) {
        return Sudoku<ValueCell, size>::load(std::cin);
      } else {
        std::basic_ifstream<char> input = std::basic_ifstream<char>(options.input_path, std::ios_base::in);
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail("input.is_open()", "/wd/src/main.cpp", 44, __extension____PRETTY_FUNCTION__));
        return Sudoku<ValueCell, size>::load(input);
      } 
      
    }
    
    private: 
    const Options & options;
    
    public:
    __lambda_38_24(const Options & _options)
    : options{_options}
    {}
    
  };
  
  const auto sudoku = (__lambda_38_24{options})();
  if(options.solve) {
    if(options.use_sat) {
      const auto solved = solve_using_sat(sudoku);
      if(is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using SAT")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      const auto solved = solve_using_exploration(sudoku);
      if(is_solved(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } 
    
  } else {
    if(options.explain) {
      unsigned int stdout_users = static_cast<unsigned int>(0);
      std::optional<std::basic_ofstream<char> > text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<size> > text_explainer;
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        text_explainer.emplace(std::cout);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          text_output.emplace<const std::filesystem::path &>(options.text_path.operator*());
          (static_cast<bool>(text_output.operator->()->is_open()) ? void(0) : __assert_fail("text_output->is_open()", "/wd/src/main.cpp", 81, __extension____PRETTY_FUNCTION__));
          text_explainer.emplace(text_output.operator*());
        } 
        
      } 
      
      std::optional<HtmlExplainer<size> > html_explainer;
      if(static_cast<bool>(options.html_path.operator bool())) {
        html_explainer.emplace(options.html_path.operator*(), options.width, options.height);
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      std::optional<std::basic_ofstream<char> > video_text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<size> > video_text_explainer_;
      std::optional<Reorder<size> > video_text_explainer;
      if(static_cast<bool>(options.video_text_path.operator bool())) {
        if(std::operator==(options.video_text_path, "-")) {
          ++stdout_users;
          video_text_explainer_.emplace(std::cout);
        } else {
          video_text_output.emplace<const std::filesystem::path &>(options.video_text_path.operator*());
          (static_cast<bool>(video_text_output.operator->()->is_open()) ? void(0) : __assert_fail("video_text_output->is_open()", "/wd/src/main.cpp", 103, __extension____PRETTY_FUNCTION__));
          video_text_explainer_.emplace(video_text_output.operator*());
        } 
        
                
        class __lambda_106_36
        {
          public: 
          inline auto operator()(const exploration::Event<size> & event) const
          {
            std::visit(*video_text_explainer_, event);
          }
          
          private: 
          std::optional<TextExplainer<size> > & video_text_explainer_;
          
          public:
          __lambda_106_36(optional<TextExplainer<size> > & _video_text_explainer_)
          : video_text_explainer_{_video_text_explainer_}
          {}
          
        };
        
        video_text_explainer.emplace(__lambda_106_36{video_text_explainer_});
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      std::optional<VideoExplainer<size> > video_explainer_;
      std::optional<Reorder<size> > video_explainer;
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail("video_serializers.size() == 2", "/wd/src/main.cpp", 122, __extension____PRETTY_FUNCTION__));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >{std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>())})));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        video_explainer_.emplace(static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
                
        class __lambda_128_31
        {
          public: 
          inline auto operator()(const exploration::Event<size> & event) const
          {
            std::visit(*video_explainer_, event);
          }
          
          private: 
          std::optional<VideoExplainer<size> > & video_explainer_;
          
          public:
          __lambda_128_31(optional<VideoExplainer<size> > & _video_explainer_)
          : video_explainer_{_video_explainer_}
          {}
          
        };
        
        video_explainer.emplace(__lambda_128_31{video_explainer_});
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
                  
      class __lambda_139_7
      {
        public: 
        inline auto operator()(exploration::Event<size> && event) const
        {
          if(text_explainer) {
            std::visit(*text_explainer, event);
          } 
          
          if(html_explainer) {
            std::visit(*html_explainer, event);
          } 
          
          if(video_text_explainer) {
            std::visit(*video_text_explainer, event);
          } 
          
          if(video_explainer) {
            std::visit(*video_explainer, event);
          } 
          
        }
        
        
      };
      
      const auto solved = solve_using_exploration<size>(sudoku, __lambda_139_7{});
      if(is_solved(solved)) {
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      __builtin_unreachable();
    } 
    
  } 
  
}


/* First instantiated from: main.cpp:278 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int main_<4>(const Options & options)
{
      
  class __lambda_38_24
  {
    public: 
    inline Sudoku<ValueCell, 4> operator()() const
    {
      if(operator==(options.input_path, std::filesystem::path("-", std::filesystem::path::auto_format))) {
        return Sudoku<ValueCell, 4>::load(std::cin);
      } else {
        std::basic_ifstream<char> input = std::basic_ifstream<char>(options.input_path, std::ios_base::in);
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("input.is_open()"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(44), static_cast<const char *>(__extension__"auto main_(const Options &)::(anonymous class)::operator()() const")));
        return Sudoku<ValueCell, 4>::load(static_cast<std::basic_istream<char>&>(input));
      } 
      
    }
    
    private: 
    const Options & options;
    
    public:
    __lambda_38_24(const Options & _options)
    : options{_options}
    {}
    
  } __lambda_38_24{options};
  
  const Sudoku<ValueCell, 4> sudoku = static_cast<const Sudoku<ValueCell, 4>>(static_cast<const __lambda_38_24>((__lambda_38_24)).operator()());
  if(options.solve) {
    if(options.use_sat) {
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_sat<4>(Sudoku<ValueCell, 4>(sudoku)));
      if(is_solved<4>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using SAT")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
                  
      class __lambda_16_60
      {
        public: 
        inline /*constexpr */ void operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&) const
        {
        }
        
        using retType_16_60 = void (*)(exploration::Event<4U> &&);
        inline constexpr operator retType_16_60 () const noexcept
        {
          return __invoke;
        };
        
        private: 
        static inline /*constexpr */ void __invoke(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && __param0)
        {
          __lambda_16_60{}.operator()(__param0);
        }
        
        public: 
        // inline /*constexpr */ __lambda_16_60(const __lambda_16_60 &) noexcept = default;
        // inline /*constexpr */ __lambda_16_60(__lambda_16_60 &&) noexcept = default;
        // /*constexpr */ __lambda_16_60() = default;
        
      };
      
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_exploration<4>(Sudoku<ValueCell, 4>(sudoku), static_cast<const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)>>(std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)>(__lambda_16_60{}))));
      if(is_solved<4>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } 
    
  } else {
    if(options.explain) {
      unsigned int stdout_users = static_cast<unsigned int>(0);
      std::optional<std::basic_ofstream<char> > text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<4> > text_explainer = std::optional<TextExplainer<4> >();
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        text_explainer.emplace<std::basic_ostream<char> &>(std::cout);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          text_output.emplace<const std::filesystem::path &>(options.text_path.operator*());
          (static_cast<bool>(text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("text_output->is_open()"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(81), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
          text_explainer.emplace<std::basic_ofstream<char> &>(text_output.operator*());
        } 
        
      } 
      
      std::optional<HtmlExplainer<4> > html_explainer = std::optional<HtmlExplainer<4> >();
      if(static_cast<bool>(options.html_path.operator bool())) {
        html_explainer.emplace<const std::filesystem::path &, const unsigned int &, const unsigned int &>(options.html_path.operator*(), options.width, options.height);
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      std::optional<std::basic_ofstream<char> > video_text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<4> > video_text_explainer_ = std::optional<TextExplainer<4> >();
      std::optional<Reorder<4> > video_text_explainer = std::optional<Reorder<4> >();
      if(static_cast<bool>(options.video_text_path.operator bool())) {
        if(std::operator==(options.video_text_path, "-")) {
          ++stdout_users;
          video_text_explainer_.emplace<std::basic_ostream<char> &>(std::cout);
        } else {
          video_text_output.emplace<const std::filesystem::path &>(options.video_text_path.operator*());
          (static_cast<bool>(video_text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("video_text_output->is_open()"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(103), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
          video_text_explainer_.emplace<std::basic_ofstream<char> &>(video_text_output.operator*());
        } 
        
                
        class __lambda_106_36
        {
          public: 
          inline /*constexpr */ void operator()(const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > & event) const
          {
            std::visit<TextExplainer<4> &, const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(video_text_explainer_.operator*(), event);
          }
          
          private: 
          std::optional<TextExplainer<4> > & video_text_explainer_;
          public: 
          // inline /*constexpr */ __lambda_106_36(const __lambda_106_36 &) noexcept = default;
          // inline /*constexpr */ __lambda_106_36(__lambda_106_36 &&) noexcept = default;
          __lambda_106_36(std::optional<TextExplainer<4> > & _video_text_explainer_)
          : video_text_explainer_{_video_text_explainer_}
          {}
          
        };
        
        video_text_explainer.emplace<__lambda_106_36>(__lambda_106_36{video_text_explainer_});
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      std::optional<VideoExplainer<4> > video_explainer_ = std::optional<VideoExplainer<4> >();
      std::optional<Reorder<4> > video_explainer = std::optional<Reorder<4> >();
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail(static_cast<const char *>("video_serializers.size() == 2"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(122), static_cast<const char *>(__extension__"int main_(const Options &) [size = 4U]")));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>()))))));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        video_explainer_.emplace<video::Serializer *, const bool &, const unsigned int &, const unsigned int &>(static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
                
        class __lambda_128_31
        {
          public: 
          inline /*constexpr */ void operator()(const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > & event) const
          {
            std::visit<VideoExplainer<4> &, const std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(video_explainer_.operator*(), event);
          }
          
          private: 
          std::optional<VideoExplainer<4> > & video_explainer_;
          public: 
          // inline /*constexpr */ __lambda_128_31(const __lambda_128_31 &) noexcept = default;
          // inline /*constexpr */ __lambda_128_31(__lambda_128_31 &&) noexcept = default;
          __lambda_128_31(std::optional<VideoExplainer<4> > & _video_explainer_)
          : video_explainer_{_video_explainer_}
          {}
          
        };
        
        video_explainer.emplace<__lambda_128_31>(__lambda_128_31{video_explainer_});
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
                  
      class __lambda_139_7
      {
        public: 
        inline /*constexpr */ void operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<4> >>(text_explainer).operator bool())) {
            std::visit<TextExplainer<4> &, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(text_explainer.operator*(), event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<4> >>(html_explainer).operator bool())) {
            std::visit<HtmlExplainer<4> &, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(html_explainer.operator*(), event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4> >>(video_text_explainer).operator bool())) {
            std::visit<Reorder<4> &, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(video_text_explainer.operator*(), event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<4> >>(video_explainer).operator bool())) {
            std::visit<Reorder<4> &, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(video_explainer.operator*(), event);
          } 
          
        }
        
        private: 
        std::optional<TextExplainer<4> > & text_explainer;
        std::optional<HtmlExplainer<4> > & html_explainer;
        std::optional<Reorder<4> > & video_text_explainer;
        std::optional<Reorder<4> > & video_explainer;
        public: 
        // inline /*constexpr */ __lambda_139_7(const __lambda_139_7 &) noexcept = default;
        // inline /*constexpr */ __lambda_139_7(__lambda_139_7 &&) noexcept = default;
        __lambda_139_7(std::optional<TextExplainer<4> > & _text_explainer, std::optional<HtmlExplainer<4> > & _html_explainer, std::optional<Reorder<4> > & _video_text_explainer, std::optional<Reorder<4> > & _video_explainer)
        : text_explainer{_text_explainer}
        , html_explainer{_html_explainer}
        , video_text_explainer{_video_text_explainer}
        , video_explainer{_video_explainer}
        {}
        
      };
      
      const Sudoku<ValueCell, 4> solved = static_cast<const Sudoku<ValueCell, 4>>(solve_using_exploration<4U>(Sudoku<ValueCell, 4>(sudoku), static_cast<const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)>>(std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)>(__lambda_139_7{text_explainer, html_explainer, video_text_explainer, video_explainer}))));
      if(is_solved<4>(solved)) {
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      __builtin_unreachable();
    } 
    
  } 
  
}
#endif


/* First instantiated from: main.cpp:280 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int main_<9>(const Options & options)
{
      
  class __lambda_38_24
  {
    public: 
    inline Sudoku<ValueCell, 9> operator()() const
    {
      if(operator==(options.input_path, std::filesystem::path("-", std::filesystem::path::auto_format))) {
        return Sudoku<ValueCell, 9>::load(std::cin);
      } else {
        std::basic_ifstream<char> input = std::basic_ifstream<char>(options.input_path, std::ios_base::in);
        (static_cast<bool>(input.is_open()) ? void(0) : __assert_fail(static_cast<const char *>("input.is_open()"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(44), static_cast<const char *>(__extension__"auto main_(const Options &)::(anonymous class)::operator()() const")));
        return Sudoku<ValueCell, 9>::load(static_cast<std::basic_istream<char>&>(input));
      } 
      
    }
    
    private: 
    const Options & options;
    
    public:
    __lambda_38_24(const Options & _options)
    : options{_options}
    {}
    
  } __lambda_38_24{options};
  
  const Sudoku<ValueCell, 9> sudoku = static_cast<const Sudoku<ValueCell, 9>>(static_cast<const __lambda_38_24>((__lambda_38_24)).operator()());
  if(options.solve) {
    if(options.use_sat) {
      const Sudoku<ValueCell, 9> solved = static_cast<const Sudoku<ValueCell, 9>>(solve_using_sat<9>(Sudoku<ValueCell, 9>(sudoku)));
      if(is_solved<9>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using SAT")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
                  
      class __lambda_16_60
      {
        public: 
        inline /*constexpr */ void operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&) const
        {
        }
        
        using retType_16_60 = void (*)(exploration::Event<9U> &&);
        inline constexpr operator retType_16_60 () const noexcept
        {
          return __invoke;
        };
        
        private: 
        static inline /*constexpr */ void __invoke(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && __param0)
        {
          __lambda_16_60{}.operator()(__param0);
        }
        
        public: 
        // inline /*constexpr */ __lambda_16_60(const __lambda_16_60 &) noexcept = default;
        // inline /*constexpr */ __lambda_16_60(__lambda_16_60 &&) noexcept = default;
        // /*constexpr */ __lambda_16_60() = default;
        
      };
      
      const Sudoku<ValueCell, 9> solved = static_cast<const Sudoku<ValueCell, 9>>(solve_using_exploration<9>(Sudoku<ValueCell, 9>(sudoku), static_cast<const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)>>(std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)>(__lambda_16_60{}))));
      if(is_solved<9>(solved)) {
        solved.dump(std::cout);
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } 
    
  } else {
    if(options.explain) {
      unsigned int stdout_users = static_cast<unsigned int>(0);
      std::optional<std::basic_ofstream<char> > text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<9> > text_explainer = std::optional<TextExplainer<9> >();
      if(std::operator==(options.text_path, "-")) {
        ++stdout_users;
        text_explainer.emplace<std::basic_ostream<char> &>(std::cout);
      } else {
        if(static_cast<bool>(options.text_path.operator bool())) {
          text_output.emplace<const std::filesystem::path &>(options.text_path.operator*());
          (static_cast<bool>(text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("text_output->is_open()"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(81), static_cast<const char *>(__extension__"int main_(const Options &) [size = 9U]")));
          text_explainer.emplace<std::basic_ofstream<char> &>(text_output.operator*());
        } 
        
      } 
      
      std::optional<HtmlExplainer<9> > html_explainer = std::optional<HtmlExplainer<9> >();
      if(static_cast<bool>(options.html_path.operator bool())) {
        html_explainer.emplace<const std::filesystem::path &, const unsigned int &, const unsigned int &>(options.html_path.operator*(), options.width, options.height);
      } 
      
      if(std::operator==(options.html_text_path, "-")) {
        ++stdout_users;
      } 
      
      std::optional<std::basic_ofstream<char> > video_text_output = std::optional<std::basic_ofstream<char> >();
      std::optional<TextExplainer<9> > video_text_explainer_ = std::optional<TextExplainer<9> >();
      std::optional<Reorder<9> > video_text_explainer = std::optional<Reorder<9> >();
      if(static_cast<bool>(options.video_text_path.operator bool())) {
        if(std::operator==(options.video_text_path, "-")) {
          ++stdout_users;
          video_text_explainer_.emplace<std::basic_ostream<char> &>(std::cout);
        } else {
          video_text_output.emplace<const std::filesystem::path &>(options.video_text_path.operator*());
          (static_cast<bool>(video_text_output.operator->()->is_open()) ? void(0) : __assert_fail(static_cast<const char *>("video_text_output->is_open()"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(103), static_cast<const char *>(__extension__"int main_(const Options &) [size = 9U]")));
          video_text_explainer_.emplace<std::basic_ofstream<char> &>(video_text_output.operator*());
        } 
        
                
        class __lambda_106_36
        {
          public: 
          inline /*constexpr */ void operator()(const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > & event) const
          {
            std::visit<TextExplainer<9> &, const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(video_text_explainer_.operator*(), event);
          }
          
          private: 
          std::optional<TextExplainer<9> > & video_text_explainer_;
          public: 
          // inline /*constexpr */ __lambda_106_36(const __lambda_106_36 &) noexcept = default;
          // inline /*constexpr */ __lambda_106_36(__lambda_106_36 &&) noexcept = default;
          __lambda_106_36(std::optional<TextExplainer<9> > & _video_text_explainer_)
          : video_text_explainer_{_video_text_explainer_}
          {}
          
        };
        
        video_text_explainer.emplace<__lambda_106_36>(__lambda_106_36{video_text_explainer_});
      } 
      
      std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > > video_serializers = std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >();
      std::optional<VideoExplainer<9> > video_explainer_ = std::optional<VideoExplainer<9> >();
      std::optional<Reorder<9> > video_explainer = std::optional<Reorder<9> >();
      if(static_cast<bool>(options.video_frames_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::FramesSerializer>(options.video_frames_path.operator*())));
      } 
      
      if(static_cast<bool>(options.video_path.operator bool())) {
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::VideoSerializer>(options.video_path.operator*(), options.width, options.height)));
      } 
      
      if(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() > static_cast<unsigned long>(1)) {
        (static_cast<bool>(static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).size() == static_cast<unsigned long>(2)) ? void(0) : __assert_fail(static_cast<const char *>("video_serializers.size() == 2"), static_cast<const char *>("/wd/src/main.cpp"), static_cast<unsigned int>(122), static_cast<const char *>(__extension__"int main_(const Options &) [size = 9U]")));
        video_serializers.push_back(std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >(std::make_unique<video::MultipleSerializer>(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::vector<video::Serializer *, std::allocator<video::Serializer *> >(std::initializer_list<video::Serializer *>{static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(0))).get(), static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.operator[](static_cast<unsigned long>(1))).get()}, static_cast<const std::allocator<video::Serializer *>>(std::allocator<video::Serializer *>()))))));
      } 
      
      if(!static_cast<const std::vector<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >, std::allocator<std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> > > >>(video_serializers).empty()) {
        video_explainer_.emplace<video::Serializer *, const bool &, const unsigned int &, const unsigned int &>(static_cast<const std::unique_ptr<video::Serializer, std::default_delete<video::Serializer> >>(video_serializers.back()).get(), options.quick_video, options.width, options.height);
                
        class __lambda_128_31
        {
          public: 
          inline /*constexpr */ void operator()(const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > & event) const
          {
            std::visit<VideoExplainer<9> &, const std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(video_explainer_.operator*(), event);
          }
          
          private: 
          std::optional<VideoExplainer<9> > & video_explainer_;
          public: 
          // inline /*constexpr */ __lambda_128_31(const __lambda_128_31 &) noexcept = default;
          // inline /*constexpr */ __lambda_128_31(__lambda_128_31 &&) noexcept = default;
          __lambda_128_31(std::optional<VideoExplainer<9> > & _video_explainer_)
          : video_explainer_{_video_explainer_}
          {}
          
        };
        
        video_explainer.emplace<__lambda_128_31>(__lambda_128_31{video_explainer_});
      } 
      
      if(stdout_users > static_cast<unsigned int>(1)) {
        std::operator<<(std::cerr, static_cast<const char *>("WARNING: several explanations are interleaved on stdout.")).operator<<(std::endl);
      } 
      
                  
      class __lambda_139_7
      {
        public: 
        inline /*constexpr */ void operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && event) const
        {
          if(static_cast<bool>(static_cast<const std::optional<TextExplainer<9> >>(text_explainer).operator bool())) {
            std::visit<TextExplainer<9> &, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(text_explainer.operator*(), event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<HtmlExplainer<9> >>(html_explainer).operator bool())) {
            std::visit<HtmlExplainer<9> &, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(html_explainer.operator*(), event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9> >>(video_text_explainer).operator bool())) {
            std::visit<Reorder<9> &, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(video_text_explainer.operator*(), event);
          } 
          
          if(static_cast<bool>(static_cast<const std::optional<Reorder<9> >>(video_explainer).operator bool())) {
            std::visit<Reorder<9> &, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(video_explainer.operator*(), event);
          } 
          
        }
        
        private: 
        std::optional<TextExplainer<9> > & text_explainer;
        std::optional<HtmlExplainer<9> > & html_explainer;
        std::optional<Reorder<9> > & video_text_explainer;
        std::optional<Reorder<9> > & video_explainer;
        public: 
        // inline /*constexpr */ __lambda_139_7(const __lambda_139_7 &) noexcept = default;
        // inline /*constexpr */ __lambda_139_7(__lambda_139_7 &&) noexcept = default;
        __lambda_139_7(std::optional<TextExplainer<9> > & _text_explainer, std::optional<HtmlExplainer<9> > & _html_explainer, std::optional<Reorder<9> > & _video_text_explainer, std::optional<Reorder<9> > & _video_explainer)
        : text_explainer{_text_explainer}
        , html_explainer{_html_explainer}
        , video_text_explainer{_video_text_explainer}
        , video_explainer{_video_explainer}
        {}
        
      };
      
      const Sudoku<ValueCell, 9> solved = static_cast<const Sudoku<ValueCell, 9>>(solve_using_exploration<9U>(Sudoku<ValueCell, 9>(sudoku), static_cast<const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)>>(std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)>(__lambda_139_7{text_explainer, html_explainer, video_text_explainer, video_explainer}))));
      if(is_solved<9>(solved)) {
        return 0;
      } else {
        std::operator<<(std::cerr, static_cast<const char *>("FAILED to solve this Sudoku using exploration")).operator<<(std::endl);
        return 1;
      } 
      
    } else {
      __builtin_unreachable();
    } 
    
  } 
  
}
#endif


struct ExistingFileOrStdinValidator : public CLI::Validator
{
  inline ExistingFileOrStdinValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE(or - for stdin)"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_159_13
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
      
      using retType_159_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_159_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_159_13{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_159_13(const __lambda_159_13 &) noexcept = default;
      // inline /*constexpr */ __lambda_159_13(__lambda_159_13 &&) noexcept = default;
      // /*constexpr */ __lambda_159_13() = default;
      
    } __lambda_159_13{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_159_13);
  }
  
  // inline ~ExistingFileOrStdinValidator() noexcept = default;
};



const ExistingFileOrStdinValidator ExistingFileOrStdin = ExistingFileOrStdinValidator();


struct FileOrStdoutValidator : public CLI::Validator
{
  inline FileOrStdoutValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE(or - for stdout)"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_173_13
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str) const
      {
        return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
      }
      
      using retType_173_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_173_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_173_13{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_173_13(const __lambda_173_13 &) noexcept = default;
      // inline /*constexpr */ __lambda_173_13(__lambda_173_13 &&) noexcept = default;
      // /*constexpr */ __lambda_173_13() = default;
      
    } __lambda_173_13{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_173_13);
  }
  
  // inline ~FileOrStdoutValidator() noexcept = default;
};



const FileOrStdoutValidator FileOrStdout = FileOrStdoutValidator();


struct FileValidator : public CLI::Validator
{
  inline FileValidator()
  : CLI::Validator{CLI::Validator(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("FILE"), static_cast<const std::allocator<char>>(std::allocator<char>())))}
  {
        
    class __lambda_181_13
    {
      public: 
      inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > operator()(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str) const
      {
        return std::basic_string<char, std::char_traits<char>, std::allocator<char> >();
      }
      
      using retType_181_13 = std::string (*)(const std::string &);
      inline constexpr operator retType_181_13 () const noexcept
      {
        return __invoke;
      };
      
      private: 
      static inline /*constexpr */ std::basic_string<char, std::char_traits<char>, std::allocator<char> > __invoke(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & str)
      {
        return __lambda_181_13{}.operator()(str);
      }
      
      public: 
      // inline /*constexpr */ __lambda_181_13(const __lambda_181_13 &) noexcept = default;
      // inline /*constexpr */ __lambda_181_13(__lambda_181_13 &&) noexcept = default;
      // /*constexpr */ __lambda_181_13() = default;
      
    } __lambda_181_13{};
    
    /* static_cast<CLI::Validator *>(this)-> */ func_.operator=(__lambda_181_13);
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
    std::initializer_list<CLI::App *> && __range1 = std::initializer_list<CLI::App *>{solve, explain};
    CLI::App *const * __begin1 = static_cast<const std::initializer_list<CLI::App *>>(__range1).begin();
    CLI::App *const * __end1 = static_cast<const std::initializer_list<CLI::App *>>(__range1).end();
    for(; __begin1 != __end1; ++__begin1) {
      CLI::App * subcommand = *__begin1;
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

