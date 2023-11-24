// Copyright 2023 Vincent Jacques

#include "events.hpp"

namespace exploration
{
  void CellIsSetInInput::apply(Stack<size> * stack) const
  {
    stack->current().cell(this->cell).set_input(this->value);
  }
  
  void InputsAreDone::apply(Stack<size> * stack) const
  {
  }
  
  void PropagationStartsForSudoku::apply(Stack<size> * stack) const
  {
  }
  
  void PropagationStartsForCell::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 22, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->cell).get() == this->value) ? void(0) : __assert_fail("stack->current().cell(cell).get() == value", "/wd/src/exploration/events.cpp", 23, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 24, __extension____PRETTY_FUNCTION__));
  }
  
  void CellPropagates::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().cell(this->source_cell).is_set()) ? void(0) : __assert_fail("stack->current().cell(source_cell).is_set()", "/wd/src/exploration/events.cpp", 29, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->source_cell).get() == this->value) ? void(0) : __assert_fail("stack->current().cell(source_cell).get() == value", "/wd/src/exploration/events.cpp", 30, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->target_cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(target_cell).is_set()", "/wd/src/exploration/events.cpp", 31, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->target_cell).is_allowed(this->value)) ? void(0) : __assert_fail("stack->current().cell(target_cell).is_allowed(value)", "/wd/src/exploration/events.cpp", 32, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->source_cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(source_cell).is_propagated()", "/wd/src/exploration/events.cpp", 33, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->target_cell).forbid(this->value);
  }
  
  void CellIsDeducedFromSingleAllowedValue::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(!stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 40, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 41, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->cell).set_deduced(this->value);
  }
  
  void CellIsDeducedAsSinglePlaceForValueInRegion::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(!stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 48, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 49, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->cell).set_deduced(this->value);
  }
  
  void PropagationIsDoneForCell::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 56, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->cell).get() == this->value) ? void(0) : __assert_fail("stack->current().cell(cell).get() == value", "/wd/src/exploration/events.cpp", 57, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 58, __extension____PRETTY_FUNCTION__));
    stack->current().cell(this->cell).set_propagated();
  }
  
  void PropagationIsDoneForSudoku::apply(Stack<size> * stack) const
  {
  }
  
  void ExplorationStarts::apply(Stack<size> * stack) const
  {
  }
  
  void HypothesisIsMade::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(!stack->current().cell(this->cell).is_set()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_set()", "/wd/src/exploration/events.cpp", 73, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(stack->current().cell(this->cell).is_allowed(this->value)) ? void(0) : __assert_fail("stack->current().cell(cell).is_allowed(value)", "/wd/src/exploration/events.cpp", 74, __extension____PRETTY_FUNCTION__));
    (static_cast<bool>(!stack->current().cell(this->cell).is_propagated()) ? void(0) : __assert_fail("!stack->current().cell(cell).is_propagated()", "/wd/src/exploration/events.cpp", 75, __extension____PRETTY_FUNCTION__));
    stack->push();
    stack->current().cell(this->cell).set_deduced(this->value);
  }
  
  void HypothesisIsRejected::apply(Stack<size> * stack) const
  {
    stack->pop();
  }
  
  void SudokuIsSolved::apply(Stack<size> * stack) const
  {
    (static_cast<bool>(stack->current().is_solved()) ? void(0) : __assert_fail("stack->current().is_solved()", "/wd/src/exploration/events.cpp", 88, __extension____PRETTY_FUNCTION__));
  }
  
  void HypothesisIsAccepted::apply(Stack<size> * stack) const
  {
  }
  
  void ExplorationIsDone::apply(Stack<size> * stack) const
  {
  }
  
  template<>
  struct CellIsSetInInput<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_input(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsSetInInput<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_input(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct InputsAreDone<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
  };
  
  template<>
  struct InputsAreDone<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationStartsForSudoku<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationStartsForSudoku<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationStartsForCell<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(22), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(23), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(24), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<4>::apply(Stack<size> *) const [size = 4]")));
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct PropagationStartsForCell<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(22), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(23), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(24), static_cast<const char *>(__extension__"void exploration::PropagationStartsForCell<9>::apply(Stack<size> *) const [size = 9]")));
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellPropagates<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->source_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(29), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->source_cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(30), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->target_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(target_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(31), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->target_cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(target_cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(32), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->source_cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(source_cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(33), static_cast<const char *>(__extension__"void exploration::CellPropagates<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->target_cell)).forbid(this->value);
    }
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  template<>
  struct CellPropagates<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->source_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(29), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->source_cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(source_cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(30), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->target_cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(target_cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(31), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->target_cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(target_cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(32), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->source_cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(source_cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(33), static_cast<const char *>(__extension__"void exploration::CellPropagates<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->target_cell)).forbid(this->value);
    }
    
    std::pair<unsigned int, unsigned int> source_cell;
    std::pair<unsigned int, unsigned int> target_cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsDeducedFromSingleAllowedValue<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(40), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(41), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsDeducedFromSingleAllowedValue<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(40), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(41), static_cast<const char *>(__extension__"void exploration::CellIsDeducedFromSingleAllowedValue<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(48), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(49), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  template<>
  struct CellIsDeducedAsSinglePlaceForValueInRegion<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(48), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(49), static_cast<const char *>(__extension__"void exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
    unsigned int region;
  };
  
  template<>
  struct PropagationIsDoneForCell<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(56), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(57), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(58), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<4>::apply(Stack<size> *) const [size = 4]")));
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_propagated();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct PropagationIsDoneForCell<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(56), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).get() == this->value) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).get() == value"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(57), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(58), static_cast<const char *>(__extension__"void exploration::PropagationIsDoneForCell<9>::apply(Stack<size> *) const [size = 9]")));
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_propagated();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct PropagationIsDoneForSudoku<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
  };
  
  template<>
  struct PropagationIsDoneForSudoku<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
  };
  
  template<>
  struct ExplorationStarts<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  template<>
  struct ExplorationStarts<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    std::vector<unsigned int, std::allocator<unsigned int> > allowed_values;
  };
  
  template<>
  struct HypothesisIsMade<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(73), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(74), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<4>::apply(Stack<size> *) const [size = 4]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(75), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<4>::apply(Stack<size> *) const [size = 4]")));
      stack->push();
      static_cast<AnnotatedCell<4>&>(static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsMade<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_set()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(73), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_allowed(this->value)) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().cell(cell).is_allowed(value)"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(74), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<9>::apply(Stack<size> *) const [size = 9]")));
      (static_cast<bool>(!static_cast<const AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).is_propagated()) ? void(0) : __assert_fail(static_cast<const char *>("!stack->current().cell(cell).is_propagated()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(75), static_cast<const char *>(__extension__"void exploration::HypothesisIsMade<9>::apply(Stack<size> *) const [size = 9]")));
      stack->push();
      static_cast<AnnotatedCell<9>&>(static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack->current()).cell(this->cell)).set_deduced(this->value);
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsRejected<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      stack->pop();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsRejected<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      stack->pop();
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct SudokuIsSolved<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
      (static_cast<bool>(static_cast<const Sudoku<AnnotatedCell<4>, 4>>(stack->current()).is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().is_solved()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(88), static_cast<const char *>(__extension__"void exploration::SudokuIsSolved<4>::apply(Stack<size> *) const [size = 4]")));
    }
    
  };
  
  template<>
  struct SudokuIsSolved<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
      (static_cast<bool>(static_cast<const Sudoku<AnnotatedCell<9>, 9>>(stack->current()).is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("stack->current().is_solved()"), static_cast<const char *>("/wd/src/exploration/events.cpp"), static_cast<unsigned int>(88), static_cast<const char *>(__extension__"void exploration::SudokuIsSolved<9>::apply(Stack<size> *) const [size = 9]")));
    }
    
  };
  
  template<>
  struct HypothesisIsAccepted<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct HypothesisIsAccepted<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
    unsigned int value;
  };
  
  template<>
  struct ExplorationIsDone<static_cast<unsigned int>(4)>
  {
    void apply(Stack<4> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  template<>
  struct ExplorationIsDone<static_cast<unsigned int>(9)>
  {
    void apply(Stack<9> * stack) const
    {
    }
    
    std::pair<unsigned int, unsigned int> cell;
  };
  
  
}  // namespace exploration
