// Copyright 2023 Vincent Jacques

#include "art.hpp"

#include <filesystem>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <doctest.h>  // NOLINT(build/include_order): keep last because it defines really common names like CHECK


namespace art
{
  constexpr const unsigned int thick_line_width = static_cast<const unsigned int>(4);
  constexpr const unsigned int thin_line_width = static_cast<const unsigned int>(2);
  template<unsigned int size>
  double round_grid_size(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / size) * size) + thick_line_width);
  }
  
  /* First instantiated from: art.cpp:199 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<4>(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / 4U) * 4U) + thick_line_width);
  }
  #endif
  
  
  /* First instantiated from: art.cpp:200 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  double round_grid_size<9>(unsigned int available_size)
  {
    return static_cast<double>((((available_size - thick_line_width) / 9U) * 9U) + thick_line_width);
  }
  #endif
  
  template<unsigned int size>
  void draw(std::shared_ptr<Cairo::Context> cr, const AnnotatedSudoku<size> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(size);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_33_28
    {
      public: 
      inline auto operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell34 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell34));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell34));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_33_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const auto cell_center = __lambda_33_28{cell_size};
        
    class __lambda_38_29
    {
      public: 
      inline auto operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell39 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell39));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell39));
        const unsigned int value_x = value % SudokuConstants<size>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<size>::sqrt_size;
        return std::make_pair((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / SudokuConstants<size>::sqrt_size), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / SudokuConstants<size>::sqrt_size));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_38_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const auto value_center = __lambda_38_29{cell_size};
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      auto && __range2 = sudoku.cells();
      for(; ; ) {
        const auto & cell;
        if(cell.is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = std::to_string(cell.get() + 1);
          if(options.bold_todo && !cell.is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(cell.is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const auto __cell_center63 = cell_center(cell.coordinates());
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const auto __cell_center72 = cell_center(cell.coordinates());
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        auto && __range3 = sudoku.cells();
        for(; ; ) {
          const auto & cell;
          if(!cell.is_set()) {
            (static_cast<bool>(!cell.is_propagated()) ? void(0) : __assert_fail("!cell.is_propagated()", "/wd/src/explanation/art.cpp", 86, __extension____PRETTY_FUNCTION__));
            {
              auto && __range5 = SudokuConstants<size>::values;
              for(; ; ) {
                unsigned int value;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const auto __value_center95 = value_center(cell.coordinates(), value);
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(cell.is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[] = {1, SudokuConstants<size>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= size; i = static_cast<unsigned int>(static_cast<<dependent type>>(i) + strides[k])) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const auto __cell_center129 = cell_center(cell);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), 0, static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options133 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const auto __cell_center141 = cell_center(cell);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options145 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator152 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator152));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator152));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const auto __value_center154 = value_center(cell, value);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / SudokuConstants<size>::sqrt_size, 0, static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options158 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options170 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator175 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const auto __cell_center178 = cell_center(source_cell);
          const auto __value_center179 = value_center(target_cell, value);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), 0, static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / SudokuConstants<size>::sqrt_size, 0, static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  
  /* First instantiated from: art.cpp:202 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<4>(std::shared_ptr<Cairo::Context> cr, const Sudoku<AnnotatedCell<4>, 4> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(4U);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_33_28
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell34 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell34));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell34));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_33_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_33_28 cell_center = static_cast<const __lambda_33_28>(__lambda_33_28{cell_size});
        
    class __lambda_38_29
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell39 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell39));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell39));
        const unsigned int value_x = value % SudokuConstants<4>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<4>::sqrt_size;
        return std::make_pair<double, double>((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size)), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size)));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_38_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_38_29 value_center = static_cast<const __lambda_38_29>(__lambda_38_29{cell_size});
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(static_cast<const AnnotatedCell<4>&>(cell).get() + static_cast<unsigned int>(1)));
          if(options.bold_todo && !static_cast<const AnnotatedCell<4>&>(cell).is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(static_cast<const AnnotatedCell<4>&>(cell).is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const std::pair<double, double> __operator63 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator63));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator63));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const std::pair<double, double> __operator72 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator72));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator72));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
        boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
          if(!static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
            (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(cell).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!cell.is_propagated()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(86), static_cast<const char *>(__extension__"void art::draw(Cairo::RefPtr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &) [size = 4U]")));
            {
              const std::array<unsigned int, 4> & __range5 = SudokuConstants<4>::values;
              const unsigned int * __begin0 = __range5.begin();
              const unsigned int * __end0 = __range5.end();
              for(; __begin0 != __end0; ++__begin0) {
                unsigned int value = *__begin0;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const std::pair<double, double> __operator95 = static_cast<const std::pair<double, double>>(value_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()), value));
                  const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator95));
                  const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator95));
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[2] = {static_cast<const unsigned int>(1), SudokuConstants<4>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= 4U; i = i + static_cast<const unsigned int *>(strides)[k]) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator129 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator129));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator129));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options133 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const std::pair<double, double> __operator141 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator141));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator141));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options145 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator152 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator152));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator152));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator154 = static_cast<const std::pair<double, double>>(value_center.operator()(cell, value));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator154));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator154));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options158 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options170 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator175 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const std::pair<double, double> __operator178 = static_cast<const std::pair<double, double>>(cell_center.operator()(source_cell));
          const double && x1 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator178));
          const double && y1 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator178));
          const std::pair<double, double> __operator179 = static_cast<const std::pair<double, double>>(value_center.operator()(target_cell, value));
          const double && x2 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator179));
          const double && y2 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator179));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<4>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  #endif
  
  
  /* First instantiated from: art.cpp:203 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  void draw<9>(std::shared_ptr<Cairo::Context> cr, const Sudoku<AnnotatedCell<9>, 9> & sudoku, const DrawOptions & options)
  {
    Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->translate(static_cast<double>(thick_line_width / static_cast<unsigned int>(2)), static_cast<double>(thick_line_width / static_cast<unsigned int>(2)));
    const double cell_size = (options.grid_size - static_cast<double>(thick_line_width)) / static_cast<double>(9U);
    const double cell_interior_size = cell_size - static_cast<double>(thick_line_width);
        
    class __lambda_33_28
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell) const
      {
        const std::pair<unsigned int, unsigned int> __cell34 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell34));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell34));
        return std::make_pair<double, double>((static_cast<double>(col) + 0.5) * cell_size, (static_cast<double>(row) + 0.5) * cell_size);
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_33_28(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_33_28 cell_center = static_cast<const __lambda_33_28>(__lambda_33_28{cell_size});
        
    class __lambda_38_29
    {
      public: 
      inline /*constexpr */ std::pair<double, double> operator()(const std::pair<unsigned int, unsigned int> & cell, unsigned int value) const
      {
        const std::pair<unsigned int, unsigned int> __cell39 = std::pair<unsigned int, unsigned int>(cell);
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell39));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell39));
        const unsigned int value_x = value % SudokuConstants<9>::sqrt_size;
        const unsigned int value_y = value / SudokuConstants<9>::sqrt_size;
        return std::make_pair<double, double>((static_cast<double>(col) * cell_size) + (((static_cast<double>(value_x) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size)), (static_cast<double>(row) * cell_size) + (((static_cast<double>(value_y) + 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size)));
      }
      
      private: 
      const double cell_size;
      
      public:
      __lambda_38_29(const double & _cell_size)
      : cell_size{_cell_size}
      {}
      
    };
    
    const __lambda_38_29 value_center = static_cast<const __lambda_38_29>(__lambda_38_29{cell_size});
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size((static_cast<double>(3) * cell_interior_size) / static_cast<double>(4));
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
          const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(static_cast<const AnnotatedCell<9>&>(cell).get() + static_cast<unsigned int>(1)));
          if(options.bold_todo && !static_cast<const AnnotatedCell<9>&>(cell).is_propagated()) {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::BOLD);
          } else {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
          } 
          
          if(static_cast<const AnnotatedCell<9>&>(cell).is_input()) {
            Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
            const std::pair<double, double> __operator63 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator63));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator63));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - (cell_size / static_cast<double>(2)), y - (cell_size / static_cast<double>(2)), cell_size, cell_size);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.84999999999999998, 0.84999999999999998, 0.84999999999999998);
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->fill();
          } 
          
          __anon_1193_9 extents;
          static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
          {
            const std::pair<double, double> __operator72 = static_cast<const std::pair<double, double>>(cell_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates())));
            const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator72));
            const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator72));
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
        } 
        
      }
      
    }
    if(options.possible) {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_font_size(cell_interior_size / static_cast<double>(4));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->select_font_face(std::basic_string<char, std::char_traits<char>, std::allocator<char> >(static_cast<const char *>("sans-serif"), static_cast<const std::allocator<char>>(std::allocator<char>())), Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
        boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
          if(!static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
            (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(cell).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!cell.is_propagated()"), static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(86), static_cast<const char *>(__extension__"void art::draw(Cairo::RefPtr<Cairo::Context>, const AnnotatedSudoku<size> &, const DrawOptions &) [size = 9U]")));
            {
              const std::array<unsigned int, 9> & __range5 = SudokuConstants<9>::values;
              const unsigned int * __begin0 = __range5.begin();
              const unsigned int * __end0 = __range5.end();
              for(; __begin0 != __end0; ++__begin0) {
                unsigned int value = *__begin0;
                Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
                const std::basic_string<char, std::char_traits<char>, std::allocator<char> > text = static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(std::to_string(value + static_cast<unsigned int>(1)));
                __anon_1193_9 extents;
                static_cast<const Cairo::Context *>(static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->())->get_text_extents(text, extents);
                {
                  const std::pair<double, double> __operator95 = static_cast<const std::pair<double, double>>(value_center.operator()(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()), value));
                  const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator95));
                  const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator95));
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to((x - (extents.width / static_cast<double>(2))) - extents.x_bearing, (y - (extents.height / static_cast<double>(2))) - extents.y_bearing);
                };
                if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(value)) {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
                } else {
                  static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.80000000000000004, 0.80000000000000004, 0.80000000000000004);
                } 
                
                static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->show_text(text);
              }
              
            }
          } 
          
        }
        
      }
    } 
    
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(0.0, 0.0, 0.0);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_cap(Cairo::Context::LineCap::SQUARE);
    const double line_widths[2] = {static_cast<const double>(thin_line_width), static_cast<const double>(thick_line_width)};
    const unsigned int strides[2] = {static_cast<const unsigned int>(1), SudokuConstants<9>::sqrt_size};
    {
      std::initializer_list<int> && __range2 = std::initializer_list<int>{0, 1};
      const int * __begin2 = static_cast<const std::initializer_list<int>>(__range2).begin();
      const int * __end2 = static_cast<const std::initializer_list<int>>(__range2).end();
      for(; __begin2 != __end2; ++__begin2) {
        unsigned int k = static_cast<unsigned int>(*__begin2);
        for(unsigned int i = static_cast<unsigned int>(0); i <= 9U; i = i + static_cast<const unsigned int *>(strides)[k]) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(i) * cell_size, static_cast<double>(0));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(static_cast<double>(i) * cell_size, options.grid_size - static_cast<double>(thick_line_width));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(static_cast<double>(0), static_cast<double>(i) * cell_size);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(options.grid_size - static_cast<double>(thick_line_width), static_cast<double>(i) * cell_size);
        }
        
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(static_cast<const double *>(line_widths)[k]);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
      }
      
    }
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.circled_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator129 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator129));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator129));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options133 = std::tuple<double, double, double>(options.circled_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options133));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > & __range2 = options.boxed_cells;
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::pair<unsigned int, unsigned int> *, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > >>(__begin2).operator*());
        const std::pair<double, double> __operator141 = static_cast<const std::pair<double, double>>(cell_center.operator()(cell));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator141));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator141));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(x - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), y - ((0.80000000000000004 * cell_size) / static_cast<double>(2)), 0.80000000000000004 * cell_size, 0.80000000000000004 * cell_size);
      }
      
    }
    {
      const std::tuple<double, double, double> __options145 = std::tuple<double, double, double>(options.boxed_cells_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options145));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.boxed_cells_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.circled_values;
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
      __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
      for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
        const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> __operator152 = std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
        const std::pair<unsigned int, unsigned int> && cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator152));
        const unsigned int && value = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator152));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
        const std::pair<double, double> __operator154 = static_cast<const std::pair<double, double>>(value_center.operator()(cell, value));
        const double && x = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator154));
        const double && y = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator154));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x, y, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
      }
      
    }
    {
      const std::tuple<double, double, double> __options158 = std::tuple<double, double, double>(options.circled_values_color);
      const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options158));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
    };
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.circled_values_line_width);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
    {
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
      {
        const std::tuple<double, double, double> __options170 = std::tuple<double, double, double>(options.links_from_cell_to_value_color);
        const double && r = std::get<0UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        const double && g = std::get<1UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        const double && b = std::get<2UL>(static_cast<const std::tuple<double, double, double> &&>(__options170));
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(r, g, b);
      };
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_line_width(options.links_from_cell_to_value_line_width);
      {
        const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > & __range2 = options.links_from_cell_to_value;
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __begin2 = __range2.begin();
        __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > > __end2 = __range2.end();
        for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2), static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__end2)); __begin2.operator++()) {
          const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> __operator175 = std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>(static_cast<const __gnu_cxx::__normal_iterator<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> *, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > >>(__begin2).operator*());
          const std::pair<unsigned int, unsigned int> && source_cell = std::get<0UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          const std::pair<unsigned int, unsigned int> && target_cell = std::get<1UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          const unsigned int && value = std::get<2UL>(static_cast<const std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> &&>(__operator175));
          Cairo::SaveGuard saver = Cairo::SaveGuard(static_cast<const std::shared_ptr<Cairo::Context>>(cr));
          const std::pair<double, double> __operator178 = static_cast<const std::pair<double, double>>(cell_center.operator()(source_cell));
          const double && x1 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator178));
          const double && y1 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator178));
          const std::pair<double, double> __operator179 = static_cast<const std::pair<double, double>>(value_center.operator()(target_cell, value));
          const double && x2 = std::get<0UL>(static_cast<const std::pair<double, double> &&>(__operator179));
          const double && y2 = std::get<1UL>(static_cast<const std::pair<double, double> &&>(__operator179));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), options.grid_size, options.grid_size);
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x1, y1, (0.80000000000000004 * cell_size) / static_cast<double>(2), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          {
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->begin_new_sub_path();
            static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->arc(x2, y2, ((0.80000000000000004 * 0.5) * cell_size) / static_cast<double>(SudokuConstants<9>::sqrt_size), static_cast<double>(0), static_cast<double>(2) * 3.1415926535897931);
          };
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->clip();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->move_to(x1, y1);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->line_to(x2, y2);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->stroke();
        }
        
      }
    };
  }
  #endif
  
  template<unsigned int cols, unsigned int rows>
  struct TestImage
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit TestImage(std::filesystem::path path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(static_cast<const std::filesystem::path>(path_))}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(cols * this->frame_width), static_cast<int>(rows * this->frame_height))}
    , crs{}
    {
      std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
      for(unsigned int col = static_cast<unsigned int>(0); col != cols; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != rows; ++row) {
          this->crs[col][row] = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
          this->crs[col][row]->translate(col * this->frame_width, row * this->frame_height);
          this->crs[col][row]->save();
          this->crs[col][row]->translate(margin, margin);
        }
        
      }
      
    }
    
    inline ~TestImage()
    {
      for(unsigned int col = static_cast<unsigned int>(0); col != cols; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != rows; ++row) {
          this->crs[col][row]->restore();
          this->crs[col][row]->rectangle(0, 0, this->frame_width, this->frame_height);
          this->crs[col][row]->rectangle(margin, margin, this->viewport_width, this->viewport_height);
          this->crs[col][row]->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
          this->crs[col][row]->set_source_rgba(1, 0, 0, 0.5);
          this->crs[col][row]->fill();
        }
        
      }
      
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::array<std::array<Cairo::RefPtr<Cairo::Context>, rows>, cols> crs;
  };
  
  /* First instantiated from: art.cpp:261 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct TestImage<2, 1>
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit TestImage(std::filesystem::path path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(static_cast<const std::filesystem::path>(path_))}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(2U * this->frame_width), static_cast<int>(1U * this->frame_height))}
    , crs{std::array<std::array<std::shared_ptr<Cairo::Context>, 1>, 2>()}
    {
      std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
      for(unsigned int col = static_cast<unsigned int>(0); col != 2U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 1U; ++row) {
          this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row)).operator=(Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface)))));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(col * this->frame_width), static_cast<double>(row * this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->save();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
        }
        
      }
      
    }
    
    inline ~TestImage() noexcept
    {
      for(unsigned int col = static_cast<unsigned int>(0); col != 2U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 1U; ++row) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->restore();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_source_rgba(static_cast<double>(1), static_cast<double>(0), static_cast<double>(0), 0.5);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->fill();
        }
        
      }
      
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::array<std::array<std::shared_ptr<Cairo::Context>, 1>, 2> crs;
  };
  
  #endif
  /* First instantiated from: art.cpp:281 */
  #ifdef INSIGHTS_USE_TEMPLATE
  template<>
  struct TestImage<3, 2>
  {
    inline static constexpr const unsigned int margin = static_cast<const unsigned int>(10);
    inline explicit TestImage(std::filesystem::path path_, unsigned int frame_width_, unsigned int frame_height_)
    : path{std::filesystem::path(static_cast<const std::filesystem::path>(path_))}
    , frame_width{frame_width_}
    , frame_height{frame_height_}
    , viewport_width{this->frame_width - (static_cast<unsigned int>(2) * margin)}
    , viewport_height{this->frame_height - (static_cast<unsigned int>(2) * margin)}
    , surface{Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, static_cast<int>(3U * this->frame_width), static_cast<int>(2U * this->frame_height))}
    , crs{std::array<std::array<std::shared_ptr<Cairo::Context>, 2>, 3>()}
    {
      std::shared_ptr<Cairo::Context> cr = Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface))));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->set_source_rgb(static_cast<double>(1), static_cast<double>(1), static_cast<double>(1));
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(cr).operator->()->paint();
      for(unsigned int col = static_cast<unsigned int>(0); col != 3U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 2U; ++row) {
          this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row)).operator=(Cairo::Context::create(static_cast<const std::shared_ptr<Cairo::Surface>>(std::shared_ptr<Cairo::Surface>(static_cast<const std::shared_ptr<Cairo::ImageSurface>>(this->surface)))));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(col * this->frame_width), static_cast<double>(row * this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->save();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate(static_cast<double>(margin), static_cast<double>(margin));
        }
        
      }
      
    }
    
    inline ~TestImage() noexcept
    {
      for(unsigned int col = static_cast<unsigned int>(0); col != 3U; ++col) {
        for(unsigned int row = static_cast<unsigned int>(0); row != 2U; ++row) {
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->restore();
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(0), static_cast<double>(0), static_cast<double>(this->frame_width), static_cast<double>(this->frame_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->rectangle(static_cast<double>(margin), static_cast<double>(margin), static_cast<double>(this->viewport_width), static_cast<double>(this->viewport_height));
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->set_source_rgba(static_cast<double>(1), static_cast<double>(0), static_cast<double>(0), 0.5);
          static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(this->crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->fill();
        }
        
      }
      
      static_cast<Cairo::Surface *>(static_cast<const std::__shared_ptr_access<Cairo::ImageSurface, 2, false, false>&>(this->surface).operator->())->write_to_png(static_cast<const std::basic_string<char, std::char_traits<char>, std::allocator<char> >>(static_cast<const std::filesystem::path>(this->path).string()));
    }
    
    std::filesystem::path path;
    unsigned int frame_width;
    unsigned int frame_height;
    unsigned int viewport_width;
    unsigned int viewport_height;
    std::shared_ptr<Cairo::ImageSurface> surface;
    std::array<std::array<std::shared_ptr<Cairo::Context>, 2>, 3> crs;
  };
  
  #endif
  static void DOCTEST_ANON_FUNC_2();
  static const int DOCTEST_ANON_VAR_3 = doctest::detail::consume(&DOCTEST_ANON_VAR_3, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_2, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(260), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - grid")))));
  static void DOCTEST_ANON_FUNC_2()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-grid.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(Sudoku<AnnotatedCell<4>, 4>()), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(Sudoku<AnnotatedCell<9>, 9>()), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  static void DOCTEST_ANON_FUNC_4();
  static const int DOCTEST_ANON_VAR_5 = doctest::detail::consume(&DOCTEST_ANON_VAR_5, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_4, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(274), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - grid - multiple sizes")))));
  static void DOCTEST_ANON_FUNC_4()
  {
    std::array<std::array<unsigned int, 3>, 2> frame_sizes = {{{{static_cast<unsigned int>(100), static_cast<unsigned int>(140), static_cast<unsigned int>(200)}}, {{static_cast<unsigned int>(280), static_cast<unsigned int>(400), static_cast<unsigned int>(560)}}}};
    TestImage<3, 2> image = TestImage<3, 2>(std::filesystem::path("tests/unit/explanation/art/draw-grid-multiple-sizes.png", std::filesystem::path::auto_format), static_cast<unsigned int>(580), static_cast<unsigned int>(580));
    for(unsigned int col = static_cast<unsigned int>(0); col != static_cast<unsigned int>(3); ++col) {
      for(unsigned int row = static_cast<unsigned int>(0); row != static_cast<unsigned int>(2); ++row) {
        const unsigned int frame_size = frame_sizes.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col));
        const double grid_size = round_grid_size<9>(frame_size);
        static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
        draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(row)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(Sudoku<AnnotatedCell<9>, 9>()), {grid_size, {false}, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
      }
      
    }
    
  }
  static void DOCTEST_ANON_FUNC_6();
  static const int DOCTEST_ANON_VAR_7 = doctest::detail::consume(&DOCTEST_ANON_VAR_7, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_6, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(293), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - known-values circled")))));
  static void DOCTEST_ANON_FUNC_6()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-known-values-circled.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<4>, 4> sudoku = Sudoku<AnnotatedCell<4>, 4>();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin2).operator++()) {
          SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin2).operator*();
          const std::pair<unsigned int, unsigned int> __cell300 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<4>, 4>::Cell>(cell).coordinates());
          const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell300));
          const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell300));
          static_cast<AnnotatedCell<4>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(4));
        }
        
      }
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{SudokuConstants<4>::cells.begin(), SudokuConstants<4>::cells.end(), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator++()) {
          SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator*();
          const std::pair<unsigned int, unsigned int> __cell317 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
          const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell317));
          const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell317));
          static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
        }
        
      }
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end(), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  static void DOCTEST_ANON_FUNC_8();
  static const int DOCTEST_ANON_VAR_9 = doctest::detail::consume(&DOCTEST_ANON_VAR_9, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_8, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(331), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all inputs")))));
  static void DOCTEST_ANON_FUNC_8()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-inputs.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell337 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell337));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell337));
        static_cast<AnnotatedCell<9>&>(cell).set_input((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_10();
  static const int DOCTEST_ANON_VAR_11 = doctest::detail::consume(&DOCTEST_ANON_VAR_11, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_10, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(349), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all todo")))));
  static void DOCTEST_ANON_FUNC_10()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-todo.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell355 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell355));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell355));
        static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_12();
  static const int DOCTEST_ANON_VAR_13 = doctest::detail::consume(&DOCTEST_ANON_VAR_13, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_12, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(368), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all processed")))));
  static void DOCTEST_ANON_FUNC_12()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-processed.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell374 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell374));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell374));
        static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
        static_cast<AnnotatedCell<9>&>(cell).set_propagated();
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, true, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_14();
  static const int DOCTEST_ANON_VAR_15 = doctest::detail::consume(&DOCTEST_ANON_VAR_15, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_14, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(388), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - known-values boxed")))));
  static void DOCTEST_ANON_FUNC_14()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-known-values-boxed.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell394 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell394));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell394));
        static_cast<AnnotatedCell<9>&>(cell).set_deduced((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9));
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{SudokuConstants<9>::cells.begin(), SudokuConstants<9>::cells.end(), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, std::tuple<double, double, double>{0, 1, 0}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_16();
  static const int DOCTEST_ANON_VAR_17 = doctest::detail::consume(&DOCTEST_ANON_VAR_17, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_16, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(408), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - all forbidden")))));
  static void DOCTEST_ANON_FUNC_16()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-all-forbidden.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    const double grid_size = round_grid_size<9>(image.viewport_height);
    static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
    Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end1 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin1)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end1))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator++()) {
        SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin1).operator*();
        const std::pair<unsigned int, unsigned int> __cell414 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell414));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell414));
        {
          const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
          const unsigned int * __begin2 = __range2.begin();
          const unsigned int * __end2 = __range2.end();
          for(; __begin2 != __end2; ++__begin2) {
            const unsigned int value = *__begin2;
            if(value != ((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9))) {
              static_cast<AnnotatedCell<9>&>(cell).forbid(value);
            } 
            
          }
          
        }
      }
      
    }
    draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
  }
  static void DOCTEST_ANON_FUNC_18();
  static const int DOCTEST_ANON_VAR_19 = doctest::detail::consume(&DOCTEST_ANON_VAR_19, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_18, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(430), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - possible-values circled")))));
  static void DOCTEST_ANON_FUNC_18()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-possible-values-circled.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<4>, 4> sudoku = Sudoku<AnnotatedCell<4>, 4>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      {
        const std::array<std::pair<unsigned int, unsigned int>, 16> & __range2 = SudokuConstants<4>::cells;
        const std::pair<unsigned int, unsigned int> * __begin2 = __range2.begin();
        const std::pair<unsigned int, unsigned int> * __end2 = __range2.end();
        for(; __begin2 != __end2; ++__begin2) {
          const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(*__begin2);
          {
            const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
            const unsigned int * __begin3 = __range3.begin();
            const unsigned int * __end3 = __range3.end();
            for(; __begin3 != __end3; ++__begin3) {
              const unsigned int value = *__begin3;
              circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{cell, value});
            }
            
          }
        }
        
      }
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator++()) {
          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator*());
          {
            const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
            const unsigned int * __begin3 = __range3.begin();
            const unsigned int * __end3 = __range3.end();
            for(; __begin3 != __end3; ++__begin3) {
              const unsigned int value = *__begin3;
              circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{cell.coordinates(), value});
            }
            
          }
        }
        
      }
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  static void DOCTEST_ANON_FUNC_20();
  static const int DOCTEST_ANON_VAR_21 = doctest::detail::consume(&DOCTEST_ANON_VAR_21, doctest::detail::regTest(static_cast<const doctest::detail::TestCase>(doctest::detail::TestCase(DOCTEST_ANON_FUNC_20, static_cast<const char *>("/wd/src/explanation/art.cpp"), static_cast<unsigned int>(472), static_cast<const doctest::detail::TestSuite>(doctest_detail_test_suite_ns::getCurrentTestSuite()), static_cast<const doctest::String>(doctest::String()), -1).operator*(static_cast<const char *>("draw - possible-values linked")))));
  static void DOCTEST_ANON_FUNC_20()
  {
    TestImage<2, 1> image = TestImage<2, 1>(std::filesystem::path("tests/unit/explanation/art/draw-possible-values-linked.png", std::filesystem::path::auto_format), static_cast<unsigned int>(300), static_cast<unsigned int>(300));
    {
      const double grid_size = round_grid_size<4>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<4>, 4> sudoku = Sudoku<AnnotatedCell<4>, 4>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>{2, 3};
      {
        const std::array<std::pair<unsigned int, unsigned int>, 16> & __range2 = SudokuConstants<4>::cells;
        const std::pair<unsigned int, unsigned int> * __begin2 = __range2.begin();
        const std::pair<unsigned int, unsigned int> * __end2 = __range2.end();
        for(; __begin2 != __end2; ++__begin2) {
          const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(*__begin2);
          if(!std::operator==(cell, static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))) {
            const std::pair<unsigned int, unsigned int> __cell484 = std::pair<unsigned int, unsigned int>(cell);
            const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell484));
            const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell484));
            {
              const std::array<unsigned int, 4> & __range4 = SudokuConstants<4>::values;
              const unsigned int * __begin4 = __range4.begin();
              const unsigned int * __end4 = __range4.end();
              for(; __begin4 != __end4; ++__begin4) {
                const unsigned int value = *__begin4;
                if(value == ((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(4))) {
                  links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{source_cell, cell, value});
                  circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{cell, value});
                } 
                
              }
              
            }
          } 
          
        }
        
      }
      draw<4>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(0)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<4>, 4>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
    {
      const double grid_size = round_grid_size<9>(image.viewport_height);
      static_cast<const std::__shared_ptr_access<Cairo::Context, 2, false, false>&>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0))).operator->()->translate((static_cast<double>(image.viewport_width) - grid_size) / static_cast<double>(2), (static_cast<double>(image.viewport_height) - grid_size) / static_cast<double>(2));
      Sudoku<AnnotatedCell<9>, 9> sudoku = Sudoku<AnnotatedCell<9>, 9>();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > > links_from_cell_to_value = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > > circled_values = std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >();
      std::pair<unsigned int, unsigned int> source_cell = std::pair<unsigned int, unsigned int>{2, 3};
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end2 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin2)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end2))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator++()) {
          SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin2).operator*();
          const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(cell).coordinates());
          if(!std::operator==(coords, static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))) {
            const std::pair<unsigned int, unsigned int> __coords515 = std::pair<unsigned int, unsigned int>(coords);
            const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords515));
            const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__coords515));
            {
              const std::array<unsigned int, 9> & __range4 = SudokuConstants<9>::values;
              const unsigned int * __begin4 = __range4.begin();
              const unsigned int * __end4 = __range4.end();
              for(; __begin4 != __end4; ++__begin4) {
                const unsigned int value = *__begin4;
                if(value == ((row + (static_cast<unsigned int>(2) * col)) % static_cast<unsigned int>(9))) {
                  links_from_cell_to_value.push_back(std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>{source_cell, coords, value});
                  circled_values.push_back(std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>{coords, value});
                } 
                
              }
              
            }
          } 
          
        }
        
      }
      draw<9>(std::shared_ptr<Cairo::Context>(static_cast<const std::shared_ptr<Cairo::Context>>(image.crs.operator[](static_cast<unsigned long>(1)).operator[](static_cast<unsigned long>(0)))), static_cast<const Sudoku<AnnotatedCell<9>, 9>>(sudoku), {grid_size, true, {false}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(source_cell))}, static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > >{}, {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, unsigned int> > >>(circled_values)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}, std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >(static_cast<const std::vector<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int>, std::allocator<std::tuple<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>, unsigned int> > >>(links_from_cell_to_value)), {static_cast<double>(2)}, {std::tuple<double, double, double>{1, 0, 0}}});
    };
  }
  
}  // namespace art
