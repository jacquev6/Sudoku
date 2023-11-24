// Copyright 2023 Vincent Jacques

#include "html-explainer.hpp"

#include <cairomm/cairomm.h>

#include <string>

#include <boost/format.hpp>

#include "art.hpp"


template<unsigned int size>
struct HtmlExplainer<size>::Image
{
  inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
  inline explicit HtmlExplainer<size>::Image(const std::filesystem::path & path_, unsigned int frame_width_, unsigned int frame_height_)
  : path{std::filesystem::path(path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * HtmlExplainer::Image::margin)}
  , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * HtmlExplainer::Image::margin)}
  , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width), static_cast<int>(this->frame_height))}
  , cr{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
  {
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->paint();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->save();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->translate(static_cast<double>(HtmlExplainer::Image::margin), static_cast<double>(HtmlExplainer::Image::margin));
  }
  
  inline ~HtmlExplainer<size>::Image()
  {
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->restore();
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->rectangle(static_cast<double>(HtmlExplainer::Image::margin), static_cast<double>(HtmlExplainer::Image::margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_source_rgba(static_cast<double>(1), 0.5, 0.5, 0.5);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->fill();
    static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
  }
  
  std::filesystem::path path;
  unsigned int frame_width;
  unsigned int frame_height;
  unsigned int viewport_width;
  unsigned int viewport_height;
  std::shared_ptr<Cairo::ImageSurface> surface;
  std::shared_ptr<Cairo::Context> cr;
};



template<unsigned size>
HtmlExplainer<size>::Image HtmlExplainer<size>::image(const std::string& name) const {
  return Image(directory_path / name, frame_width, frame_height);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellIsSetInInput<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::InputsAreDone<size>& event) {
  event.apply(&stack);

  index_file << "<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n";
  index_file << "<h1>Input grid</h1>\n";
  Image input = image("input.png");
  const double grid_size = art::round_grid_size<size>(input.viewport_height);
  input.cr->translate((input.viewport_width - grid_size) / 2, (input.viewport_height - grid_size) / 2);
  art::draw(input.cr, current(), {.grid_size = grid_size});
  index_file << "<p><img src=\"input.png\"/></p>\n";

  index_file << "<h1>Possible values</h1>\n";
  Image possible = image("initial-possible.png");
  possible.cr->translate((possible.viewport_width - grid_size) / 2, (possible.viewport_height - grid_size) / 2);
  art::draw(possible.cr, current(), {.grid_size = grid_size, .possible = true});
  index_file << "<p><img src=\"initial-possible.png\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationStartsForSudoku<size>& event) {
  index_file << "<h1>Propagation</h1>\n";

  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationStartsForCell<size>& event) {
  const auto [row, col] = event.cell;
  index_file << "<h2>Propagation from (" << row << ", " << col << ")</h2>\n";

  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellPropagates<size>& event) {
  event.apply(&stack);

  const auto [src_row, src_col] = event.source_cell;
  const auto [tgt_row, tgt_col] = event.target_cell;
  const std::string image_name =
    str(boost::format("propagation-%1%-%2%--%3%-%4%.png") % src_row % src_col % tgt_row % tgt_col);
  Image propagation = image(image_name);
  const double grid_size = art::round_grid_size<size>(propagation.viewport_height);
  propagation.cr->translate(
    (propagation.viewport_width - grid_size) / 2,
    (propagation.viewport_height - grid_size) / 2);
  art::draw(
    propagation.cr,
    current(),
    {
      .grid_size = grid_size,
      .possible = true,
      .bold_todo = true,
      .circled_cells = {event.source_cell},
      .circled_values = {{event.target_cell, event.value}},
      .links_from_cell_to_value = {{event.source_cell, event.target_cell, event.value}},
    });
  index_file << "<p><img src=\"" << image_name << "\"/></p>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellIsDeducedFromSingleAllowedValue<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationIsDoneForCell<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::PropagationIsDoneForSudoku<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::ExplorationStarts<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::HypothesisIsMade<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::HypothesisIsRejected<size>& event) {
  event.apply(&stack);
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::SudokuIsSolved<size>& event) {
  event.apply(&stack);

  index_file << "<h1>Solved grid</h1>\n";
  Image solved = image("solved.png");
  const double grid_size = art::round_grid_size<size>(solved.viewport_height);
  solved.cr->translate((solved.viewport_width - grid_size) / 2, (solved.viewport_height - grid_size) / 2);
  art::draw(
    solved.cr,
    current(),
    {
      .grid_size = grid_size,
    });
  index_file << "<p><img src=\"solved.png\"/></p>\n";
  index_file << "</body></html>\n";
}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::HypothesisIsAccepted<size>& event) {}

template<unsigned size>
void HtmlExplainer<size>::operator()(const exploration::ExplorationIsDone<size>& event) {}



template<>
class HtmlExplainer<static_cast<unsigned int>(4)>
{
  
  public: 
  inline explicit HtmlExplainer(const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{Stack<4>()}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::InputsAreDone<4> & event)
  {
    event.apply(&this->stack);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Input grid</h1>\n"));
    HtmlExplainer<4>::Image input = static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("input.png"), static_cast<const std::allocator<char>>(std::allocator<char>())));
    const double grid_size = art::round_grid_size<4U>(input.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(input.cr).operator->()->translate((static_cast<double>(input.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(input.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(input.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"input.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Possible values</h1>\n"));
    HtmlExplainer<4>::Image possible = static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("initial-possible.png"), static_cast<const std::allocator<char>>(std::allocator<char>())));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(possible.cr).operator->()->translate((static_cast<double>(possible.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(possible.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(possible.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->current(), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"initial-possible.png\"/></p>\n"));
  }
  
  void operator()(const exploration::PropagationStartsForSudoku<4> & event)
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Propagation</h1>\n"));
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::PropagationStartsForCell<4> & event)
  {
    const std::pair<unsigned int, unsigned int> __event92 = std::pair<unsigned int, unsigned int>(event.cell);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event92));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event92));
    std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Propagation from (")).operator<<(row), static_cast<const char *>(", ")).operator<<(col), static_cast<const char *>(")</h2>\n"));
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::CellPropagates<4> & event)
  {
    event.apply(&this->stack);
    const std::pair<unsigned int, unsigned int> __event102 = std::pair<unsigned int, unsigned int>(event.source_cell);
    const unsigned int && src_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event102));
    const unsigned int && src_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event102));
    const std::pair<unsigned int, unsigned int> __event103 = std::pair<unsigned int, unsigned int>(event.target_cell);
    const unsigned int && tgt_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event103));
    const unsigned int && tgt_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event103));
    const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(boost::str<char, std::char_traits<char>, std::allocator<char> >(static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("propagation-%1%-%2%--%3%-%4%.png"))).operator%(src_row).operator%(src_col).operator%(tgt_row).operator%(tgt_col))));
    HtmlExplainer<4>::Image propagation = static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->image(image_name);
    const double grid_size = art::round_grid_size<4U>(propagation.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(propagation.cr).operator->()->translate((static_cast<double>(propagation.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(propagation.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(propagation.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
  }
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::PropagationIsDoneForCell<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::PropagationIsDoneForSudoku<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::ExplorationStarts<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::HypothesisIsMade<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::HypothesisIsRejected<4> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::SudokuIsSolved<4> & event)
  {
    event.apply(&this->stack);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
    HtmlExplainer<4>::Image solved = static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solved.png"), static_cast<const std::allocator<char>>(std::allocator<char>())));
    const double grid_size = art::round_grid_size<4U>(solved.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(solved.cr).operator->()->translate((static_cast<double>(solved.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(solved.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(solved.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(4)> *>(this)->current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("</body></html>\n"));
  }
  
  void operator()(const exploration::HypothesisIsAccepted<4> & event)
  {
  }
  
  void operator()(const exploration::ExplorationIsDone<4> & event)
  {
  }
  
  
  private: 
  inline const Sudoku<AnnotatedCell<4>, 4> & current() const
  {
    return this->stack.current();
  }
  
  struct Image
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit Image(const std::filesystem::path & path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(path_)}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width), static_cast<int>(this->frame_height))}
    , cr{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->paint();
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->save();
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
    }
    
    inline ~Image() noexcept
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->restore();
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_source_rgba(static_cast<double>(1), 0.5, 0.5, 0.5);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->fill();
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::shared_ptr<Cairo::Context> cr;
  };
  
  HtmlExplainer<4>::Image image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & name) const
  {
    return HtmlExplainer<4>::Image(static_cast<const std::filesystem::path>(operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(name, std::filesystem::path::auto_format)))), this->frame_width, this->frame_height);
  }
  
  
  private: 
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<4> stack;
  public: 
  // inline HtmlExplainer(const HtmlExplainer<static_cast<unsigned int>(4)> &) /* noexcept */ = delete;
  // inline HtmlExplainer<static_cast<unsigned int>(4)> & operator=(const HtmlExplainer<static_cast<unsigned int>(4)> &) /* noexcept */ = delete;
};





template<>
class HtmlExplainer<static_cast<unsigned int>(9)>
{
  
  public: 
  inline explicit HtmlExplainer(const std::filesystem::path & directory_path_, unsigned int frame_width_, unsigned int frame_height_)
  : directory_path{std::filesystem::path(directory_path_)}
  , frame_width{frame_width_}
  , frame_height{frame_height_}
  , index_file{std::basic_ofstream<char>()}
  , stack{Stack<9>()}
  {
    std::filesystem::create_directories(static_cast<const std::filesystem::path>(this->directory_path));
    this->index_file.open<std::filesystem::path>(static_cast<const std::filesystem::path>(operator/(static_cast<const std::filesystem::path>(this->directory_path), std::filesystem::path("index.html", std::filesystem::path::auto_format))), std::ios_base::out);
  }
  
  
  public: 
  void operator()(const exploration::CellIsSetInInput<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::InputsAreDone<9> & event)
  {
    event.apply(&this->stack);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Input grid</h1>\n"));
    HtmlExplainer<9>::Image input = static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("input.png"), static_cast<const std::allocator<char>>(std::allocator<char>())));
    const double grid_size = art::round_grid_size<9U>(input.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(input.cr).operator->()->translate((static_cast<double>(input.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(input.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(input.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"input.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Possible values</h1>\n"));
    HtmlExplainer<9>::Image possible = static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("initial-possible.png"), static_cast<const std::allocator<char>>(std::allocator<char>())));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(possible.cr).operator->()->translate((static_cast<double>(possible.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(possible.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(possible.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->current(), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"initial-possible.png\"/></p>\n"));
  }
  
  void operator()(const exploration::PropagationStartsForSudoku<9> & event)
  {
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Propagation</h1>\n"));
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::PropagationStartsForCell<9> & event)
  {
    const std::pair<unsigned int, unsigned int> __event92 = std::pair<unsigned int, unsigned int>(event.cell);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event92));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event92));
    std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h2>Propagation from (")).operator<<(row), static_cast<const char *>(", ")).operator<<(col), static_cast<const char *>(")</h2>\n"));
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::CellPropagates<9> & event)
  {
    event.apply(&this->stack);
    const std::pair<unsigned int, unsigned int> __event102 = std::pair<unsigned int, unsigned int>(event.source_cell);
    const unsigned int && src_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event102));
    const unsigned int && src_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event102));
    const std::pair<unsigned int, unsigned int> __event103 = std::pair<unsigned int, unsigned int>(event.target_cell);
    const unsigned int && tgt_row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event103));
    const unsigned int && tgt_col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__event103));
    const std::basic_string<char, std::char_traits<char>, std::allocator<char> > image_name = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(boost::str<char, std::char_traits<char>, std::allocator<char> >(static_cast<const boost::basic_format<char, std::char_traits<char>, std::allocator<char> >>(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(boost::basic_format<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("propagation-%1%-%2%--%3%-%4%.png"))).operator%(src_row).operator%(src_col).operator%(tgt_row).operator%(tgt_col))));
    HtmlExplainer<9>::Image propagation = static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->image(image_name);
    const double grid_size = art::round_grid_size<9U>(propagation.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(propagation.cr).operator->()->translate((static_cast<double>(propagation.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(propagation.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(propagation.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->current(), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(event.source_cell)}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{std::initializer_list<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >{std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{event.source_cell, event.target_cell, event.value}}, static_cast<const std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >>(std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(std::operator<<(std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"")), image_name), static_cast<const char *>("\"/></p>\n"));
  }
  
  void operator()(const exploration::CellIsDeducedFromSingleAllowedValue<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::PropagationIsDoneForCell<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::PropagationIsDoneForSudoku<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::ExplorationStarts<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::HypothesisIsMade<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::HypothesisIsRejected<9> & event)
  {
    event.apply(&this->stack);
  }
  
  void operator()(const exploration::SudokuIsSolved<9> & event)
  {
    event.apply(&this->stack);
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<h1>Solved grid</h1>\n"));
    HtmlExplainer<9>::Image solved = static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->image(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("solved.png"), static_cast<const std::allocator<char>>(std::allocator<char>())));
    const double grid_size = art::round_grid_size<9U>(solved.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(solved.cr).operator->()->translate((static_cast<double>(solved.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(solved.viewport_height) - grid_size) / static_cast<double>(2));
    art::draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(solved.cr)), static_cast<const HtmlExplainer<static_cast<unsigned int>(9)> *>(this)->current(), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("<p><img src=\"solved.png\"/></p>\n"));
    std::operator<<(static_cast<std::basic_ostream<char>&>(this->index_file), static_cast<const char *>("</body></html>\n"));
  }
  
  void operator()(const exploration::HypothesisIsAccepted<9> & event)
  {
  }
  
  void operator()(const exploration::ExplorationIsDone<9> & event)
  {
  }
  
  
  private: 
  inline const Sudoku<AnnotatedCell<9>, 9> & current() const
  {
    return this->stack.current();
  }
  
  struct Image
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit Image(const std::filesystem::path & path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(path_)}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(this->frame_width), static_cast<int>(this->frame_height))}
    , cr{Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))))}
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->paint();
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->save();
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
    }
    
    inline ~Image() noexcept
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->restore();
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->set_source_rgba(static_cast<double>(1), 0.5, 0.5, 0.5);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->cr).operator->()->fill();
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::shared_ptr<Cairo::Context> cr;
  };
  
  HtmlExplainer<9>::Image image(const std::basic_string<char, std::char_traits<char>, std::allocator<char> > & name) const
  {
    return HtmlExplainer<9>::Image(static_cast<const std::filesystem::path>(operator/(this->directory_path, static_cast<const std::filesystem::path>(std::filesystem::path(name, std::filesystem::path::auto_format)))), this->frame_width, this->frame_height);
  }
  
  
  private: 
  std::filesystem::path directory_path;
  unsigned int frame_width;
  unsigned int frame_height;
  std::basic_ofstream<char> index_file;
  Stack<9> stack;
  public: 
  // inline HtmlExplainer(const HtmlExplainer<static_cast<unsigned int>(9)> &) /* noexcept */ = delete;
  // inline HtmlExplainer<static_cast<unsigned int>(9)> & operator=(const HtmlExplainer<static_cast<unsigned int>(9)> &) /* noexcept */ = delete;
};



