// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <minisat/simp/SimpSolver.h>

#include "../puzzle/sudoku-constants.hpp"


template<unsigned int size>
Sudoku<ValueCell, size> solve_using_sat(Sudoku<ValueCell, size> sudoku)
{
  Minisat::SimpSolver solver = Minisat::SimpSolver();
  std::array<std::array<std::array<Minisat::Var, size>, size>, size> has_value;
  {
    auto && __range1 = SudokuConstants<size>::values;
    for(; ; ) {
      const unsigned int row;
      {
        auto && __range2 = SudokuConstants<size>::values;
        for(; ; ) {
          const unsigned int col;
          {
            auto && __range3 = SudokuConstants<size>::values;
            for(; ; ) {
              const unsigned int val;
              has_value[row][col][val] = solver.newVar(Minisat::lbool(Minisat::l_Undef), true);
            }
            
          }
        }
        
      }
    }
    
  }
  {
    auto && __range1 = SudokuConstants<size>::cells;
    for(; ; ) {
      const auto & cell;
      const auto __cell25 = cell;
      {
        Minisat::vec<Minisat::Lit, int> clause = Minisat::vec<Minisat::Lit, int>();
        {
          auto && __range3 = SudokuConstants<size>::values;
          for(; ; ) {
            const unsigned int val;
            push(Minisat::mkLit(has_value[row][col][val]));
          }
          
        }
        solver.addClause(static_cast<const Minisat::vec<Minisat::Lit, int>>(clause));
      };
      {
        auto && __range2 = SudokuConstants<size>::values;
        for(; ; ) {
          const unsigned int val1;
          {
            auto && __range3 = SudokuConstants<size>::values;
            for(; ; ) {
              const unsigned int val2;
              if(val1 < val2) {
                addClause(~Minisat::mkLit(has_value[row][col][val1]), ~Minisat::mkLit(has_value[row][col][val2]));
              } 
              
            }
            
          }
        }
        
      }
    }
    
  }
  {
    auto && __range1 = SudokuConstants<size>::regions;
    for(; ; ) {
      const auto & region;
      {
        auto && __range2 = SudokuConstants<size>::values;
        for(; ; ) {
          const unsigned int val;
          {
            auto && __range3 = region;
            for(; ; ) {
              const auto cell1;
              {
                auto && __range4 = region;
                for(; ; ) {
                  const auto cell2;
                  if(cell1 < cell2) {
                    addClause(~Minisat::mkLit(has_value[cell1.first][cell1.second][val]), ~Minisat::mkLit(has_value[cell2.first][cell2.second][val]));
                  } 
                  
                }
                
              }
            }
            
          }
        }
        
      }
    }
    
  }
  {
    auto && __range1 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      const auto __cell67 = cell.coordinates();
      const auto value = cell.get();
      if(value) {
        addClause(Minisat::mkLit(has_value[row][col][*value]));
      } 
      
    }
    
  }
  Minisat::vec<Minisat::Lit, int> dummy = Minisat::vec<Minisat::Lit, int>();
  if(static_cast<const Minisat::lbool>(solver.solveLimited(static_cast<const Minisat::vec<Minisat::Lit, int>>(dummy), true, false)).operator==(Minisat::lbool(Minisat::l_True))) {
    {
      auto && __range2 = sudoku.cells();
      for(; ; ) {
        auto & cell;
        const auto __cell77 = cell.coordinates();
        {
          auto && __range3 = SudokuConstants<size>::values;
          for(; ; ) {
            const unsigned int val;
            if(static_cast<Minisat::Solver&>(solver).model[has_value[row][col][val]] == Minisat::l_True) {
              cell.set(val);
            } 
            
          }
          
        }
      }
      
    }
  } 
  
  return sudoku;
}


/* First instantiated from: sudoku-solver.cpp:89 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_sat<4>(Sudoku<ValueCell, 4> sudoku)
{
  Minisat::SimpSolver solver = Minisat::SimpSolver();
  std::array<std::array<std::array<int, 4>, 4>, 4> has_value;
  {
    const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
    const unsigned int * __begin0 = __range1.begin();
    const unsigned int * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      const unsigned int row = *__begin0;
      {
        const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
        const unsigned int * __begin0 = __range2.begin();
        const unsigned int * __end0 = __range2.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int col = *__begin0;
          {
            const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
            const unsigned int * __begin0 = __range3.begin();
            const unsigned int * __end0 = __range3.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val = *__begin0;
              has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)) = solver.newVar(Minisat::lbool(Minisat::l_Undef), true);
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::pair<unsigned int, unsigned int>, 16> & __range1 = SudokuConstants<4>::cells;
    const std::pair<unsigned int, unsigned int> * __begin0 = __range1.begin();
    const std::pair<unsigned int, unsigned int> * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::pair<unsigned int, unsigned int> & cell = *__begin0;
      const std::pair<unsigned int, unsigned int> __cell25 = std::pair<unsigned int, unsigned int>(cell);
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell25));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell25));
      {
        Minisat::vec<Minisat::Lit, int> clause = Minisat::vec<Minisat::Lit, int>();
        {
          const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
          const unsigned int * __begin0 = __range3.begin();
          const unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            clause.push(static_cast<const Minisat::Lit>(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)), false)));
          }
          
        }
        solver.addClause(static_cast<const Minisat::vec<Minisat::Lit, int>>(clause));
      };
      {
        const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
        const unsigned int * __begin0 = __range2.begin();
        const unsigned int * __end0 = __range2.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val1 = *__begin0;
          {
            const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
            const unsigned int * __begin0 = __range3.begin();
            const unsigned int * __end0 = __range3.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val2 = *__begin0;
              if(val1 < val2) {
                solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val1)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val2)), false)));
              } 
              
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::array<std::pair<unsigned int, unsigned int>, 4>, 12> & __range1 = SudokuConstants<4>::regions;
    const std::array<std::pair<unsigned int, unsigned int>, 4> * __begin0 = __range1.begin();
    const std::array<std::pair<unsigned int, unsigned int>, 4> * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::array<std::pair<unsigned int, unsigned int>, 4> & region = *__begin0;
      {
        const std::array<unsigned int, 4> & __range2 = SudokuConstants<4>::values;
        const unsigned int * __begin0 = __range2.begin();
        const unsigned int * __end0 = __range2.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val = *__begin0;
          {
            const std::array<std::pair<unsigned int, unsigned int>, 4> & __range3 = region;
            const std::pair<unsigned int, unsigned int> * __begin0 = __range3.begin();
            const std::pair<unsigned int, unsigned int> * __end0 = __range3.end();
            for(; __begin0 != __end0; ++__begin0) {
              const std::pair<unsigned int, unsigned int> cell1 = std::pair<unsigned int, unsigned int>(*__begin0);
              {
                const std::array<std::pair<unsigned int, unsigned int>, 4> & __range4 = region;
                const std::pair<unsigned int, unsigned int> * __begin0 = __range4.begin();
                const std::pair<unsigned int, unsigned int> * __end0 = __range4.end();
                for(; __begin0 != __end0; ++__begin0) {
                  const std::pair<unsigned int, unsigned int> cell2 = std::pair<unsigned int, unsigned int>(*__begin0);
                  if(operator<(std::operator<=>(cell1, cell2), __cmp_cat::__unspec(static_cast<std::__cmp_cat::__unspec *>(0)))) {
                    solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell1.first)).operator[](static_cast<unsigned long>(cell1.second)).operator[](static_cast<unsigned long>(val)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell2.first)).operator[](static_cast<unsigned long>(cell2.second)).operator[](static_cast<unsigned long>(val)), false)));
                  } 
                  
                }
                
              }
            }
            
          }
        }
        
      }
    }
    
  }
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const SudokuBase<ValueCell, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::pair<unsigned int, unsigned int> __cell67 = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell67));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell67));
      const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(value.operator bool())) {
        solver.addClause(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(value.operator*())), false));
      } 
      
    }
    
  }
  Minisat::vec<Minisat::Lit, int> dummy = Minisat::vec<Minisat::Lit, int>();
  if(static_cast<const Minisat::lbool>(solver.solveLimited(static_cast<const Minisat::vec<Minisat::Lit, int>>(dummy), true, false)).operator==(Minisat::lbool(Minisat::l_True))) {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
        SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*();
        const std::pair<unsigned int, unsigned int> __cell77 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<ValueCell, 4>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell77));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell77));
        {
          const std::array<unsigned int, 4> & __range3 = SudokuConstants<4>::values;
          const unsigned int * __begin0 = __range3.begin();
          const unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            if(static_cast<const Minisat::lbool>(static_cast<Minisat::Solver&>(solver).model.operator[](has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)))).operator==(Minisat::lbool(Minisat::l_True))) {
              static_cast<ValueCell&>(cell).set(val);
            } 
            
          }
          
        }
      }
      
    }
  } 
  
  return Sudoku<ValueCell, 4>(static_cast<const Sudoku<ValueCell, 4> &&>(sudoku));
}
#endif


/* First instantiated from: sudoku-solver.cpp:90 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_sat<9>(Sudoku<ValueCell, 9> sudoku)
{
  Minisat::SimpSolver solver = Minisat::SimpSolver();
  std::array<std::array<std::array<int, 9>, 9>, 9> has_value;
  {
    const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
    const unsigned int * __begin0 = __range1.begin();
    const unsigned int * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      const unsigned int row = *__begin0;
      {
        const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
        const unsigned int * __begin0 = __range2.begin();
        const unsigned int * __end0 = __range2.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int col = *__begin0;
          {
            const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
            const unsigned int * __begin0 = __range3.begin();
            const unsigned int * __end0 = __range3.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val = *__begin0;
              has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)) = solver.newVar(Minisat::lbool(Minisat::l_Undef), true);
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::pair<unsigned int, unsigned int>, 81> & __range1 = SudokuConstants<9>::cells;
    const std::pair<unsigned int, unsigned int> * __begin0 = __range1.begin();
    const std::pair<unsigned int, unsigned int> * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::pair<unsigned int, unsigned int> & cell = *__begin0;
      const std::pair<unsigned int, unsigned int> __cell25 = std::pair<unsigned int, unsigned int>(cell);
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell25));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell25));
      {
        Minisat::vec<Minisat::Lit, int> clause = Minisat::vec<Minisat::Lit, int>();
        {
          const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
          const unsigned int * __begin0 = __range3.begin();
          const unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            clause.push(static_cast<const Minisat::Lit>(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)), false)));
          }
          
        }
        solver.addClause(static_cast<const Minisat::vec<Minisat::Lit, int>>(clause));
      };
      {
        const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
        const unsigned int * __begin0 = __range2.begin();
        const unsigned int * __end0 = __range2.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val1 = *__begin0;
          {
            const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
            const unsigned int * __begin0 = __range3.begin();
            const unsigned int * __end0 = __range3.end();
            for(; __begin0 != __end0; ++__begin0) {
              const unsigned int val2 = *__begin0;
              if(val1 < val2) {
                solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val1)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val2)), false)));
              } 
              
            }
            
          }
        }
        
      }
    }
    
  }
  {
    const std::array<std::array<std::pair<unsigned int, unsigned int>, 9>, 27> & __range1 = SudokuConstants<9>::regions;
    const std::array<std::pair<unsigned int, unsigned int>, 9> * __begin0 = __range1.begin();
    const std::array<std::pair<unsigned int, unsigned int>, 9> * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      const std::array<std::pair<unsigned int, unsigned int>, 9> & region = *__begin0;
      {
        const std::array<unsigned int, 9> & __range2 = SudokuConstants<9>::values;
        const unsigned int * __begin0 = __range2.begin();
        const unsigned int * __end0 = __range2.end();
        for(; __begin0 != __end0; ++__begin0) {
          const unsigned int val = *__begin0;
          {
            const std::array<std::pair<unsigned int, unsigned int>, 9> & __range3 = region;
            const std::pair<unsigned int, unsigned int> * __begin0 = __range3.begin();
            const std::pair<unsigned int, unsigned int> * __end0 = __range3.end();
            for(; __begin0 != __end0; ++__begin0) {
              const std::pair<unsigned int, unsigned int> cell1 = std::pair<unsigned int, unsigned int>(*__begin0);
              {
                const std::array<std::pair<unsigned int, unsigned int>, 9> & __range4 = region;
                const std::pair<unsigned int, unsigned int> * __begin0 = __range4.begin();
                const std::pair<unsigned int, unsigned int> * __end0 = __range4.end();
                for(; __begin0 != __end0; ++__begin0) {
                  const std::pair<unsigned int, unsigned int> cell2 = std::pair<unsigned int, unsigned int>(*__begin0);
                  if(operator<(std::operator<=>(cell1, cell2), __cmp_cat::__unspec(static_cast<std::__cmp_cat::__unspec *>(0)))) {
                    solver.addClause(Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell1.first)).operator[](static_cast<unsigned long>(cell1.second)).operator[](static_cast<unsigned long>(val)), false)), Minisat::operator~(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(cell2.first)).operator[](static_cast<unsigned long>(cell2.second)).operator[](static_cast<unsigned long>(val)), false)));
                  } 
                  
                }
                
              }
            }
            
          }
        }
        
      }
    }
    
  }
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const SudokuBase<ValueCell, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::pair<unsigned int, unsigned int> __cell67 = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
      const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell67));
      const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell67));
      const std::optional<unsigned int> value = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(value.operator bool())) {
        solver.addClause(Minisat::mkLit(has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(value.operator*())), false));
      } 
      
    }
    
  }
  Minisat::vec<Minisat::Lit, int> dummy = Minisat::vec<Minisat::Lit, int>();
  if(static_cast<const Minisat::lbool>(solver.solveLimited(static_cast<const Minisat::vec<Minisat::Lit, int>>(dummy), true, false)).operator==(Minisat::lbool(Minisat::l_True))) {
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
        SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*();
        const std::pair<unsigned int, unsigned int> __cell77 = static_cast<const std::pair<unsigned int, unsigned int>>(static_cast<const SudokuBase<ValueCell, 9>::Cell>(cell).coordinates());
        const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell77));
        const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__cell77));
        {
          const std::array<unsigned int, 9> & __range3 = SudokuConstants<9>::values;
          const unsigned int * __begin0 = __range3.begin();
          const unsigned int * __end0 = __range3.end();
          for(; __begin0 != __end0; ++__begin0) {
            const unsigned int val = *__begin0;
            if(static_cast<const Minisat::lbool>(static_cast<Minisat::Solver&>(solver).model.operator[](has_value.operator[](static_cast<unsigned long>(row)).operator[](static_cast<unsigned long>(col)).operator[](static_cast<unsigned long>(val)))).operator==(Minisat::lbool(Minisat::l_True))) {
              static_cast<ValueCell&>(cell).set(val);
            } 
            
          }
          
        }
      }
      
    }
  } 
  
  return Sudoku<ValueCell, 9>(static_cast<const Sudoku<ValueCell, 9> &&>(sudoku));
}
#endif


template Sudoku<ValueCell, 4> solve_using_sat(Sudoku<ValueCell, 4>);
template Sudoku<ValueCell, 9> solve_using_sat(Sudoku<ValueCell, 9>);
