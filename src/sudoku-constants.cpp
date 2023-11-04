// Copyright 2023 Vincent Jacques

#include "sudoku-constants.hpp"


static_assert(SudokuConstantsT<4>::values == decltype(SudokuConstantsT<4>::values){
  0, 1, 2, 3
});

static_assert(SudokuConstantsT<4>::cells == decltype(SudokuConstantsT<4>::cells){{
  {0, 0}, {0, 1}, {0, 2}, {0, 3},
  {1, 0}, {1, 1}, {1, 2}, {1, 3},
  {2, 0}, {2, 1}, {2, 2}, {2, 3},
  {3, 0}, {3, 1}, {3, 2}, {3, 3},
}});

static_assert(SudokuConstantsT<4>::regions == decltype(SudokuConstantsT<4>::regions){{
  // Rows
  {{{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
  {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}},
  {{{2, 0}, {2, 1}, {2, 2}, {2, 3}}},
  {{{3, 0}, {3, 1}, {3, 2}, {3, 3}}},
  // Columns
  {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
  {{{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
  {{{0, 2}, {1, 2}, {2, 2}, {3, 2}}},
  {{{0, 3}, {1, 3}, {2, 3}, {3, 3}}},
  // Squares
  {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},
  {{{0, 2}, {0, 3}, {1, 2}, {1, 3}}},
  {{{2, 0}, {2, 1}, {3, 0}, {3, 1}}},
  {{{2, 2}, {2, 3}, {3, 2}, {3, 3}}},
}});

static_assert(SudokuConstantsT<9>::regions == decltype(SudokuConstantsT<9>::regions){{
  // Rows
  {{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}}},
  {{{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}}},
  {{{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}}},
  {{{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}}},
  {{{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8}}},
  {{{5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}}},
  {{{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}}},
  {{{7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7}, {7, 8}}},
  {{{8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {8, 6}, {8, 7}, {8, 8}}},
  // Columns
  {{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}}},
  {{{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}}},
  {{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}}},
  {{{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}}},
  {{{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}}},
  {{{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}, {8, 5}}},
  {{{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}, {8, 6}}},
  {{{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}, {8, 7}}},
  {{{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}}},
  // Squares
  {{{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}}},
  {{{0, 3}, {0, 4}, {0, 5}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5}}},
  {{{0, 6}, {0, 7}, {0, 8}, {1, 6}, {1, 7}, {1, 8}, {2, 6}, {2, 7}, {2, 8}}},
  {{{3, 0}, {3, 1}, {3, 2}, {4, 0}, {4, 1}, {4, 2}, {5, 0}, {5, 1}, {5, 2}}},
  {{{3, 3}, {3, 4}, {3, 5}, {4, 3}, {4, 4}, {4, 5}, {5, 3}, {5, 4}, {5, 5}}},
  {{{3, 6}, {3, 7}, {3, 8}, {4, 6}, {4, 7}, {4, 8}, {5, 6}, {5, 7}, {5, 8}}},
  {{{6, 0}, {6, 1}, {6, 2}, {7, 0}, {7, 1}, {7, 2}, {8, 0}, {8, 1}, {8, 2}}},
  {{{6, 3}, {6, 4}, {6, 5}, {7, 3}, {7, 4}, {7, 5}, {8, 3}, {8, 4}, {8, 5}}},
  {{{6, 6}, {6, 7}, {6, 8}, {7, 6}, {7, 7}, {7, 8}, {8, 6}, {8, 7}, {8, 8}}},
}});

static_assert(SudokuConstantsT<4>::regions_of == decltype(SudokuConstantsT<4>::regions_of){{
  {{{0, 4, 8}, {0, 5, 8}, {0, 6, 9}, {0, 7, 9}}},
  {{{1, 4, 8}, {1, 5, 8}, {1, 6, 9}, {1, 7, 9}}},
  {{{2, 4, 10}, {2, 5, 10}, {2, 6, 11}, {2, 7, 11}}},
  {{{3, 4, 10}, {3, 5, 10}, {3, 6, 11}, {3, 7, 11}}},
}});

static_assert(SudokuConstantsT<9>::regions_of == decltype(SudokuConstantsT<9>::regions_of){{
  {{
    {0, 9, 18}, {0, 10, 18}, {0, 11, 18}, {0, 12, 19}, {0, 13, 19}, {0, 14, 19}, {0, 15, 20}, {0, 16, 20}, {0, 17, 20}
  }},
  {{
    {1, 9, 18}, {1, 10, 18}, {1, 11, 18}, {1, 12, 19}, {1, 13, 19}, {1, 14, 19}, {1, 15, 20}, {1, 16, 20}, {1, 17, 20}
  }},
  {{
    {2, 9, 18}, {2, 10, 18}, {2, 11, 18}, {2, 12, 19}, {2, 13, 19}, {2, 14, 19}, {2, 15, 20}, {2, 16, 20}, {2, 17, 20}
  }},
  {{
    {3, 9, 21}, {3, 10, 21}, {3, 11, 21}, {3, 12, 22}, {3, 13, 22}, {3, 14, 22}, {3, 15, 23}, {3, 16, 23}, {3, 17, 23}
  }},
  {{
    {4, 9, 21}, {4, 10, 21}, {4, 11, 21}, {4, 12, 22}, {4, 13, 22}, {4, 14, 22}, {4, 15, 23}, {4, 16, 23}, {4, 17, 23}
  }},
  {{
    {5, 9, 21}, {5, 10, 21}, {5, 11, 21}, {5, 12, 22}, {5, 13, 22}, {5, 14, 22}, {5, 15, 23}, {5, 16, 23}, {5, 17, 23}
  }},
  {{
    {6, 9, 24}, {6, 10, 24}, {6, 11, 24}, {6, 12, 25}, {6, 13, 25}, {6, 14, 25}, {6, 15, 26}, {6, 16, 26}, {6, 17, 26}
  }},
  {{
    {7, 9, 24}, {7, 10, 24}, {7, 11, 24}, {7, 12, 25}, {7, 13, 25}, {7, 14, 25}, {7, 15, 26}, {7, 16, 26}, {7, 17, 26}
  }},
  {{
    {8, 9, 24}, {8, 10, 24}, {8, 11, 24}, {8, 12, 25}, {8, 13, 25}, {8, 14, 25}, {8, 15, 26}, {8, 16, 26}, {8, 17, 26}
  }},
}});
