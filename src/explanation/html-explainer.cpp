// Copyright 2023 Vincent Jacques

#include "html-explainer.hpp"

#include <cairomm/cairomm.h>

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include <boost/format.hpp>

#include "art.hpp"


template<unsigned size>
class HtmlExplainer {
 public:
  HtmlExplainer(
    const Explanation<size>& explanation_,
    const std::filesystem::path& directory_path_,
    unsigned frame_width_,
    unsigned frame_height_
  ) :  // NOLINT(whitespace/parens)
    explanation(explanation_),
    directory_path(directory_path_),
    frame_width(frame_width_),
    frame_height(frame_height_),
    index_file(),
    stack()
  {  // NOLINT(whitespace/braces)
    std::filesystem::create_directories(directory_path);
    index_file.open(directory_path / "index.html");
    index_file << "<html><head><title>jacquev6/Sudoku - Solving explanation</title></head><body>\n";
  }

  ~HtmlExplainer() {
    index_file << "</body></html>\n";
  }

 public:
  void explain() {
    for (const auto& cell : explanation.inputs.cells()) {
      const std::optional<unsigned> value = cell.get();
      if (value) {
        stack.current().cell(cell.coordinates()).set_input(*value);
      }
    }

    index_file << "<h1>Input grid</h1>\n";
    make_image("input.png", { .inputs = false });
    index_file << "<p><img src=\"input.png\"/></p>\n";

    index_file << "<h1>Possible values</h1>\n";
    make_image("initial-possible.png", { .possible = true });
    index_file << "<p><img src=\"initial-possible.png\"/></p>\n";

    explain(explanation.propagations);
    explain(explanation.exploration);
  }

 private:
  void explain(const std::vector<typename Explanation<size>::Propagation>& propagations) {
    index_file << "<h1>Propagation</h1>\n";
    for (const auto& propagation : propagations) {
      const auto [src_row, src_col] = propagation.source;
      index_file << "<h2>Propagation from (" << src_row + 1 << ", " << src_col + 1 << ")</h2>\n";
      const unsigned value = propagation.value;
      for (const auto& target : propagation.targets) {
        stack.current().cell(target.cell).forbid(value);

        const auto [tgt_row, tgt_col] = target.cell;
        const std::string image_name =
          str(boost::format("propagation-%1%-%2%--%3%-%4%.png")
          % (src_row + 1) % (src_col + 1) % (tgt_row + 1) % (tgt_col + 1));
        make_image(
          image_name,
          {
            .possible = true,
            .bold_todo = true,
            .circled_cells = {propagation.source},
            .circled_values = {{target.cell, value}},
            .links_from_cell_to_value = {{propagation.source, target.cell, value}},
          });
        index_file << "<p><img src=\"" << image_name << "\"/></p>\n";
        for (const auto& deduction : target.single_value_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          if (deduction.solved) {
            index_file << "<h1>Solved grid</h1>\n";
            make_image("solved.png", {}, { .draw_stack = false });
            index_file << "<p><img src=\"solved.png\"/></p>\n";
          }
        }
        for (const auto& deduction : target.single_place_deductions) {
          stack.current().cell(deduction.cell).set_deduced(deduction.value);
          if (deduction.solved) {
            index_file << "<h1>Solved grid</h1>\n";
            make_image("solved.png", {}, { .draw_stack = false });
            index_file << "<p><img src=\"solved.png\"/></p>\n";
          }
        }
      }
      stack.current().cell(propagation.source).set_propagated();
    }
  }

  void explain(const std::optional<typename Explanation<size>::Exploration>& exploration) {
    if (exploration.has_value()) {
      explain(*exploration);
    }
  }

  void explain(const typename Explanation<size>::Exploration& exploration) {
    const auto [row, col] = exploration.cell;
    index_file << "<h1>Exploration for (" << row + 1 << ", " << col + 1 << ")</h1>\n";
    for (const auto& hypothesis : exploration.explored_hypotheses) {
      stack.push();
      stack.current().cell(exploration.cell).set_hypothesis(hypothesis.value);

      index_file << "<h2>Trying " << hypothesis.value + 1 << " for (" << row + 1 << ", " << col + 1 << ")</h2>\n";
      const std::string image_name =
        str(boost::format("exploration-%1%-%2%--%3%.png") % (row + 1) % (col + 1) % (hypothesis.value + 1));
      make_image(
        image_name,
        {
          .possible = true,
          .bold_todo = true,
          .circled_cells = {exploration.cell},
        });
      index_file << "<p><img src=\"" << image_name << "\"/></p>\n";

      explain(hypothesis.propagations);
      explain(hypothesis.exploration);

      stack.pop();
    }
  }

 private:
  struct MakeImageOptions {
    bool draw_stack = true;
  };
  void make_image(const std::string& name, art::DrawOptions draw_options, const MakeImageOptions& options = {}) const {
    #ifndef NDEBUG
    assert(generated_image_names.count(name) == 0);
    generated_image_names.insert(name);
    #endif

    auto surface = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, frame_width, frame_height);
    auto cr = Cairo::Context::create(surface);
    const unsigned margin = 10;
    const unsigned viewport_width = frame_width - 2 * margin;
    const unsigned viewport_height = frame_height - 2 * margin;

    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr->save();
    cr->translate(margin, margin);

    const double grid_size = art::round_grid_size<size>(viewport_height);
    if (options.draw_stack && stack.height() > 1) {
      {
        Cairo::SaveGuard guard(cr);
        const double small_grid_size = art::round_grid_size<size>(viewport_width - grid_size - 3 * margin);
        for (const auto& saved : stack.saved()) {
          art::draw(cr, saved, {.grid_size = small_grid_size});
          cr->translate(0, small_grid_size + margin);
        }
      }
      cr->translate(
        (viewport_width - grid_size),
        (viewport_height - grid_size) / 2);
    } else {
      cr->translate(
        (viewport_width - grid_size) / 2,
        (viewport_height - grid_size) / 2);
    }
    draw_options.grid_size = grid_size;
    art::draw(cr, stack.current(), draw_options);

    cr->restore();
    // @todo Remove the margin visualisation
    cr->rectangle(0, 0, frame_width, frame_height);
    cr->rectangle(margin, margin, viewport_width, viewport_height);
    cr->set_fill_rule(Cairo::Context::FillRule::EVEN_ODD);
    cr->set_source_rgba(1, 0.5, 0.5, 0.5);
    cr->fill();

    surface->write_to_png((directory_path / name).string());
  }

 private:
  const Explanation<size>& explanation;
  std::filesystem::path directory_path;
  unsigned frame_width;
  unsigned frame_height;
  std::ofstream index_file;
  Stack<ExplainableSudoku<size>> stack;
  #ifndef NDEBUG
  mutable std::set<std::string> generated_image_names;
  #endif
};

template<unsigned size>
void explain_as_html(
  const Explanation<size>& explanation,
  const std::filesystem::path& directory_path,
  unsigned frame_width,
  unsigned frame_height
) {
  HtmlExplainer<size>(explanation, directory_path, frame_width, frame_height).explain();
}

template void explain_as_html<4>(const Explanation<4>&, const std::filesystem::path&, unsigned, unsigned);
template void explain_as_html<9>(const Explanation<9>&, const std::filesystem::path&, unsigned, unsigned);
