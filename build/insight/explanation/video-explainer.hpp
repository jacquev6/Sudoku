// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_EXPLAINER_HPP_
#define EXPLANATION_VIDEO_EXPLAINER_HPP_

#include <cairomm/cairomm.h>

#include <filesystem>
#include <iomanip>
#include <ranges>  // NOLINT(build/include_order)
#include <string>
#include <tuple>
#include <vector>

#include "../exploration/events.hpp"
#include "video/serializer.hpp"


// Like Cairo::SaveGuard
class CairoSaveGuard
{
  
  public: 
  inline explicit CairoSaveGuard(Cairo::Context & cr_)
  : cr{cr_}
  {
    this->cr.save();
  }
  
  inline ~CairoSaveGuard() noexcept
  {
    this->cr.restore();
  }
  
  
  private: 
  Cairo::Context & cr;
  public: 
};



template<unsigned int size>
class VideoExplainer
{
  inline static constexpr const unsigned int margin_pixels = static_cast<const unsigned int>(10);
  inline static constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  inline static constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  
  public: 
  inline VideoExplainer(video::Serializer * video_serializer_, const bool quick_, unsigned int frame_width_, unsigned int frame_height_)
  : before{}
  , after{}
  , frame_width_pixels{frame_width_}
  , frame_height_pixels{frame_height_}
  , viewport_height_pixels{this->frame_height_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , viewport_width_pixels{this->frame_width_pixels - (static_cast<unsigned int>(2) * margin_pixels)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width_pixels), static_cast<int>(this->frame_height_pixels))}
  , context{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  , cr{static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->context).operator*()}
  , video_serializer{video_serializer_}
  , quick{quick_}
  {
  }
  
  
  private: 
  class VisitEventsGuard
  {
    
    public: 
    inline VisitEventsGuard(VideoExplainer<size> * explainer_, const exploration::Event<size> & event)
    : explainer{*explainer_}
    , events{}
    , before{this->explainer.before}
    , after{this->explainer.after}
    {
            
      class __lambda_64_18
      {
        public: 
        template<class type_parameter_1_0>
        inline auto operator()(const type_parameter_1_0 & e) const
        {
          e.apply(&__this->explainer.after);
        }
        private: 
        VideoExplainer::VisitEventsGuard * __this;
        
        public:
        __lambda_64_18(VideoExplainer::VisitEventsGuard * _this)
        : __this{_this}
        {}
        
      };
      
      std::visit(__lambda_64_18{this}, event);
      this->events.push_back(event);
    }
    
    template<typename T>
    inline VisitEventsGuard(VideoExplainer<size> * explainer_, const std::vector<T> & events_)
    : explainer{*explainer_}
    , events{}
    , before{this->explainer.before}
    , after{this->explainer.after}
    {
      {
        auto && __range3 = events_;
        for(; ; ) {
          const T & event;
          event.apply(&this->explainer.after);
          this->events.push_back(event);
        }
        
      }
    }
    
    // inline VisitEventsGuard(const VisitEventsGuard &) = delete;
    // inline VisitEventsGuard & operator=(const VisitEventsGuard &) = delete;
    // inline VisitEventsGuard(VisitEventsGuard &&) = delete;
    // inline VisitEventsGuard & operator=(VisitEventsGuard &&) = delete;
    inline ~VisitEventsGuard()
    {
      {
        auto && __range2 = this->events;
        for(; ; ) {
          const auto & event;
                    
          class __lambda_88_20
          {
            public: 
            template<class type_parameter_1_0>
            inline auto operator()(const type_parameter_1_0 & e) const
            {
              e.apply(&__this->explainer.before);
            }
            private: 
            VideoExplainer::VisitEventsGuard * __this;
            
            public:
            __lambda_88_20(VideoExplainer::VisitEventsGuard * _this)
            : __this{_this}
            {}
            
          };
          
          std::visit(__lambda_88_20{this}, event);
        }
        
      }
    }
    
    
    private: 
    VideoExplainer<size> & explainer;
    std::vector<exploration::Event<size> > events;
    
    public: 
    const Stack<size> & before;
    const Stack<size> & after;
  };
  
  class FrameGuard
  {
    
    public: 
    inline explicit FrameGuard(VideoExplainer<size> * explainer_)
    : explainer{*explainer_}
    , cr{this->explainer.cr}
    {
      {
        CairoSaveGuard saver = CairoSaveGuard(this->cr);
        this->cr.set_source_rgb(1.0, 0.80000000000000004, 0.80000000000000004);
        this->cr.paint();
        this->cr.set_source_rgb(1.0, 1.0, 1.0);
        this->cr.rectangle(this->explainer.margin_pixels, this->explainer.margin_pixels, this->explainer.viewport_width_pixels, this->explainer.viewport_height_pixels);
        this->cr.fill();
      };
      this->cr.save();
      this->cr.translate(this->explainer.margin_pixels, this->explainer.margin_pixels);
    }
    
    // inline FrameGuard(const FrameGuard &) = delete;
    // inline FrameGuard & operator=(const FrameGuard &) = delete;
    // inline FrameGuard(FrameGuard &&) = delete;
    // inline FrameGuard & operator=(FrameGuard &&) = delete;
    inline ~FrameGuard()
    {
      this->cr.restore();
      CairoSaveGuard saver = CairoSaveGuard(this->cr);
      this->cr.rectangle(0, 0, this->explainer.frame_width_pixels, this->explainer.frame_height_pixels);
      this->cr.rectangle(this->explainer.margin_pixels, this->explainer.margin_pixels, this->explainer.viewport_width_pixels, this->explainer.viewport_height_pixels);
      this->cr.set_source_rgba(0.5, 0.5, 0.5, 0.5);
      this->cr.set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      this->cr.fill();
      this->explainer.video_serializer->serialize(this->explainer.surface);
    }
    
    
    private: 
    VideoExplainer<size> & explainer;
    Cairo::Context & cr;
  };
  
  struct Text
  {
    std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
    double font_size;
    enum 
    {
      Normal, 
      Bold
    };
    
    enum (unnamed) weight;
  };
  
  struct Layout
  {
    std::vector<Text> above = {};
    std::vector<Text> below = {};
  };
  
  
  private: 
  inline unsigned int quicken(unsigned int n)
  {
    if(this->quick) {
      return static_cast<unsigned int>(1);
    } else {
      return n;
    } 
    
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<size> &);
  
  void operator()(const exploration::InputsAreDone<size> &);
  
  void operator()(const exploration::PropagationStartsForSudoku<size> &);
  
  void operator()(const exploration::PropagationStartsForCell<size> &);
  
  void operator()(const exploration::CellPropagates<size> &);
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size> &);
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> &);
  
  void operator()(const exploration::PropagationIsDoneForCell<size> &);
  
  void operator()(const exploration::PropagationIsDoneForSudoku<size> &);
  
  void operator()(const exploration::ExplorationStarts<size> &);
  
  void operator()(const exploration::HypothesisIsMade<size> &);
  
  void operator()(const exploration::HypothesisIsRejected<size> &);
  
  void operator()(const exploration::SudokuIsSolved<size> &);
  
  void operator()(const exploration::HypothesisIsAccepted<size> &);
  
  void operator()(const exploration::ExplorationIsDone<size> &);
  
  void flush_pending_cell_propagates_events();
  
  void flush_pending_cell_is_deduced_from_single_allowed_value_events();
  
  void flush_pending_cell_is_deduced_as_single_place_for_value_in_region_events();
  
  void flush_pending_events();
  
  
  private: 
  inline std::tuple<double, double, double> draw_layout(const Layout & layout)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double above_height = static_cast<double>(0);
    {
      auto && __range2 = layout.above;
      for(; ; ) {
        const auto & text;
        this->cr.set_font_size(text.font_size);
        switch(text.weight) {
          case Text::Normal: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case Text::Bold: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        this->cr.get_text_extents(text.text, extents);
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, above_height - extents.y_bearing);
        this->cr.show_text(text.text);
        above_height = above_height + extents.height;
      }
      
    }
    double below_height = static_cast<double>(0);
    {
      auto && __range2 = layout.below | std::ranges::views::reverse;
      for(; ; ) {
        const auto & text;
        this->cr.set_font_size(text.font_size);
        switch(text.weight) {
          case Text::Normal: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case Text::Bold: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        this->cr.get_text_extents(text.text, extents);
        below_height = below_height + extents.height;
        this->cr.move_to(((static_cast<double>(this->viewport_width_pixels) - extents.width) / static_cast<double>(2)) - extents.x_bearing, (static_cast<double>(this->viewport_height_pixels) - below_height) - extents.y_bearing);
        this->cr.show_text(text.text);
      }
      
    }
    const unsigned int available_height = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height) - below_height);
    const unsigned int grid_size = (((available_height - thick_line_width) / size) * size) + thick_line_width;
    const unsigned int grid_x = (this->viewport_width_pixels - grid_size) / static_cast<unsigned int>(2);
    const unsigned int grid_y = static_cast<const unsigned int>(above_height + (static_cast<double>((available_height - grid_size) / static_cast<unsigned int>(2))));
    return std::tuple<double, double, double>(std::make_tuple<const unsigned int &, const unsigned int &, const unsigned int &>(grid_x, grid_y, grid_size));
  }
  
  inline std::tuple<double, double, double> draw_layout_transition(const Layout & before, const Layout & after, const double ratio)
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    const double above_height_before = this->compute_text_height(before.above);
    const double below_height_before = this->compute_text_height(before.below);
    const unsigned int available_height_before = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_before) - below_height_before);
    const unsigned int grid_size_before = (((available_height_before - thick_line_width) / size) * size) + thick_line_width;
    const double grid_x_before = static_cast<const double>((this->viewport_width_pixels - grid_size_before) / static_cast<unsigned int>(2));
    const double grid_y_before = above_height_before + (static_cast<double>((available_height_before - grid_size_before) / static_cast<unsigned int>(2)));
    const double above_height_after = this->compute_text_height(after.above);
    const double below_height_after = this->compute_text_height(after.below);
    const unsigned int available_height_after = static_cast<const unsigned int>((static_cast<double>(this->viewport_height_pixels) - above_height_after) - below_height_after);
    const unsigned int grid_size_after = (((available_height_after - thick_line_width) / size) * size) + thick_line_width;
    const double grid_x_after = static_cast<const double>((this->viewport_width_pixels - grid_size_after) / static_cast<unsigned int>(2));
    const double grid_y_after = above_height_after + (static_cast<double>((available_height_after - grid_size_after) / static_cast<unsigned int>(2)));
    const double grid_size = static_cast<double>(grid_size_before) + (ratio * static_cast<double>((grid_size_after - grid_size_before)));
    const double grid_x = grid_x_before + (ratio * (grid_x_after - grid_x_before));
    const double grid_y = grid_y_before + (ratio * (grid_y_after - grid_y_before));
    return std::make_tuple<const double &, const double &, const double &>(grid_x, grid_y, grid_size);
  }
  
  inline double compute_text_height(const std::vector<Text> & texts) const
  {
    CairoSaveGuard saver = CairoSaveGuard(this->cr);
    double height = static_cast<double>(0);
    {
      auto && __range2 = texts;
      for(; ; ) {
        const auto & text;
        this->cr.set_font_size(text.font_size);
        switch(text.weight) {
          case Text::Normal: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          break;
          case Text::Bold: this->cr.select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          break;
        }
        __anon_1193_9 extents;
        this->cr.get_text_extents(text.text, extents);
        height = height + extents.height;
      }
      
    }
    return height;
  }
  
  
  private: 
  Stack<size> before;
  Stack<size> after;
  unsigned int frame_width_pixels;
  unsigned int frame_height_pixels;
  unsigned int viewport_height_pixels;
  unsigned int viewport_width_pixels;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> context;
  Cairo::Context & cr;
  video::Serializer * video_serializer;
  const bool quick;
  
  private: 
  unsigned int single_propagations_handled;
  unsigned int cell_propagations_handled;
  unsigned int deductions_handled;
  std::vector<exploration::CellPropagates<size> > pending_cell_propagates_events;
  std::vector<exploration::CellIsDeducedFromSingleAllowedValue<size> > pending_cell_is_deduced_from_single_allowed_value_events;
  std::vector<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size> > pending_cell_is_deduced_as_single_place_for_value_in_region_events;
};



#endif  // EXPLANATION_VIDEO_EXPLAINER_HPP_
