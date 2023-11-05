// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_ART_HPP_
#define EXPLANATION_ART_HPP_

#include <cairomm/cairomm.h>

#include <tuple>
#include <vector>

#include "../exploration/follower.hpp"


namespace Cairo {

class SaveGuard {
 public:
  explicit SaveGuard(const Cairo::RefPtr<Cairo::Context>& cr_) : cr(cr_) { cr->save(); }
  ~SaveGuard() { cr->restore(); }

 private:
  Cairo::RefPtr<Cairo::Context> cr;
};

}  // namespace Cairo


namespace art {

double round_grid_size(unsigned);

struct DrawOptions {
  double grid_size;
  bool possible = false;
  bool bold_todo = false;

  std::vector<AnnotatedSudoku::Coordinates> circled_cells;
  double circled_cells_line_width = 2;
  std::tuple<double, double, double> circled_cells_color = {1, 0, 0};

  std::vector<AnnotatedSudoku::Coordinates> boxed_cells;
  double boxed_cells_line_width = 2;
  std::tuple<double, double, double> boxed_cells_color = {1, 0, 0};

  std::vector<std::tuple<AnnotatedSudoku::Coordinates, unsigned>> circled_values;
  double circled_values_line_width = 2;
  std::tuple<double, double, double> circled_values_color = {1, 0, 0};

  std::vector<std::tuple<AnnotatedSudoku::Coordinates, AnnotatedSudoku::Coordinates, unsigned>>
    links_from_cell_to_value;
  double links_from_cell_to_value_line_width = 2;
  std::tuple<double, double, double> links_from_cell_to_value_color = {1, 0, 0};
};

void draw(Cairo::RefPtr<Cairo::Context>, const Follower::State&, const DrawOptions&);

}  // namespace art

#endif  // EXPLANATION_ART_HPP_
