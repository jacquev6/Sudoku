// Copyright 2023 Vincent Jacques

#include "check.hpp"

#include <bitset>
#include <cassert>


template<unsigned int size>
bool is_solved(const Sudoku<ValueCell, size> & sudoku)
{
  {
    auto && __range1 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      if(!cell.get()) {
        return false;
      } 
      
    }
    
  }
  {
    auto && __range1 = sudoku.regions();
    for(; ; ) {
      const auto & region;
      std::bitset<size> seen;
      {
        auto && __range2 = region.cells();
        for(; ; ) {
          const auto & cell;
          const unsigned int val = *cell.get();
          (static_cast<bool>(val < size) ? void(0) : __assert_fail("val < size", "/wd/src/puzzle/check.cpp", 21, __extension____PRETTY_FUNCTION__));
          if(seen[val]) {
            return false;
          } 
          
          seen[val] = true;
        }
        
      }
    }
    
  }
  return true;
}


/* First instantiated from: check.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool is_solved<4>(const Sudoku<ValueCell, 4> & sudoku)
{
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<const SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*();
      if(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get()).operator bool())) {
        return false;
      } 
      
    }
    
  }
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default> > && __range1 = static_cast<const SudokuBase<ValueCell, 4>&>(sudoku).regions();
    boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Region, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Region & region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Region, long, false, false>&>(__begin0).operator*();
      std::bitset<4> seen = std::bitset<4>();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = region.cells();
        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*();
          const unsigned int val = static_cast<const ValueCell&>(cell).get().operator*();
          (static_cast<bool>(val < 4U) ? void(0) : __assert_fail(static_cast<const char *>("val < size"), static_cast<const char *>("/wd/src/puzzle/check.cpp"), static_cast<unsigned int>(21), static_cast<const char *>(__extension__"bool is_solved(const Sudoku<ValueCell, size> &) [size = 4U]")));
          if(static_cast<bool>(static_cast<const std::bitset<4>::reference>(seen.operator[](static_cast<unsigned long>(val))).operator bool())) {
            return false;
          } 
          
          seen.operator[](static_cast<unsigned long>(val)).operator=(true);
        }
        
      }
    }
    
  }
  return true;
}
#endif


/* First instantiated from: check.cpp:33 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool is_solved<9>(const Sudoku<ValueCell, 9> & sudoku)
{
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<const SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*();
      if(!static_cast<bool>(static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get()).operator bool())) {
        return false;
      } 
      
    }
    
  }
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default> > && __range1 = static_cast<const SudokuBase<ValueCell, 9>&>(sudoku).regions();
    boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Region, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Region & region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_184_26, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Region, long, false, false>&>(__begin0).operator*();
      std::bitset<9> seen = std::bitset<9>();
      {
        boost::iterator_range<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range2 = region.cells();
        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
          const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*();
          const unsigned int val = static_cast<const ValueCell&>(cell).get().operator*();
          (static_cast<bool>(val < 9U) ? void(0) : __assert_fail(static_cast<const char *>("val < size"), static_cast<const char *>("/wd/src/puzzle/check.cpp"), static_cast<unsigned int>(21), static_cast<const char *>(__extension__"bool is_solved(const Sudoku<ValueCell, size> &) [size = 9U]")));
          if(static_cast<bool>(static_cast<const std::bitset<9>::reference>(seen.operator[](static_cast<unsigned long>(val))).operator bool())) {
            return false;
          } 
          
          seen.operator[](static_cast<unsigned long>(val)).operator=(true);
        }
        
      }
    }
    
  }
  return true;
}
#endif


template bool is_solved(const Sudoku<ValueCell, 4>&);
template bool is_solved(const Sudoku<ValueCell, 9>&);
