// Copyright 2023 Vincent Jacques

#include "sudoku-solver.hpp"

#include <cassert>
#include <functional>
#include <list>
#include <set>
#include <utility>
#include <vector>


// FIFO with unique elements
template<typename T>
class UniqueQueue
{
  
  public: 
  inline void add(const T & t)
  {
    if(this->set.insert(t).second) {
      this->list.push_back(t);
    } 
    
  }
  
  inline bool empty() const
  {
    (static_cast<bool>(this->list.empty() == this->set.empty()) ? void(0) : __assert_fail("list.empty() == set.empty()", "/wd/src/exploration/sudoku-solver.cpp", 24, __extension____PRETTY_FUNCTION__));
    return this->list.empty();
  }
  
  inline bool has(const T & t) const
  {
    return this->set.count(t);
  }
  
  inline T get()
  {
    (static_cast<bool>(!this->empty()) ? void(0) : __assert_fail("!empty()", "/wd/src/exploration/sudoku-solver.cpp", 33, __extension____PRETTY_FUNCTION__));
    const T t = this->list.front() /* NRVO variable */;
    this->list.pop_front();
    this->set.erase(t);
    return t;
  }
  
  
  private: 
  std::list<T> list;
  std::set<T> set;
};

/* First instantiated from: sudoku-solver.cpp:95 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class UniqueQueue<std::pair<unsigned int, unsigned int> >
{
  
  public: 
  inline void add(const std::pair<unsigned int, unsigned int> & t)
  {
    if(this->set.insert(t).second) {
      this->list.push_back(t);
    } 
    
  }
  
  inline bool empty() const
  {
    (static_cast<bool>(static_cast<int>(this->list.empty()) == static_cast<int>(this->set.empty())) ? void(0) : __assert_fail(static_cast<const char *>("list.empty() == set.empty()"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(24), static_cast<const char *>(__extension__"bool UniqueQueue<std::pair<unsigned int, unsigned int>>::empty() const [T = std::pair<unsigned int, unsigned int>]")));
    return this->list.empty();
  }
  
  inline bool has(const std::pair<unsigned int, unsigned int> & t) const;
  
  inline std::pair<unsigned int, unsigned int> get()
  {
    (static_cast<bool>(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> > *>(this)->empty()) ? void(0) : __assert_fail(static_cast<const char *>("!empty()"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(33), static_cast<const char *>(__extension__"T UniqueQueue<std::pair<unsigned int, unsigned int>>::get() [T = std::pair<unsigned int, unsigned int>]")));
    const std::pair<unsigned int, unsigned int> t = std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int>>(this->list.front())) /* NRVO variable */;
    this->list.pop_front();
    this->set.erase(t);
    return std::pair<unsigned int, unsigned int>(static_cast<const std::pair<unsigned int, unsigned int> &&>(t));
  }
  
  
  private: 
  std::list<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int, unsigned int> > > list;
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > set;
  public: 
  // inline ~UniqueQueue() noexcept = default;
  // inline UniqueQueue() noexcept = default;
};

#endif



// This is the only way to modify the Stack (everywhere else, it's manipulated through const references).
// This design ensures that the events returned to the client can replicate exactly the evolution of the
// stack that happened during the exploration, because the stack actually evolved only through said events.
// (I think this is brilliant, but I *may* biased as I'm the author of this code).
template<unsigned int size>
struct EventAdder
{
  inline EventAdder(Stack<size> * stack_, const std::function<void (exploration::Event<size> &&)> & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  inline void operator()(exploration::Event<size> && event) const
  {
        
    class __lambda_56_16
    {
      public: 
      template<class type_parameter_1_0>
      inline auto operator()(const type_parameter_1_0 & e) const
      {
        e.apply(__this->stack);
      }
      private: 
      const EventAdder<size> * __this;
      
      public:
      __lambda_56_16(const EventAdder<size> * _this)
      : __this{_this}
      {}
      
    };
    
    std::visit(__lambda_56_16{this}, event);
    this->add_event(std::move(event));
  }
  
  
  private: 
  Stack<size> * stack;
  const std::function<void (exploration::Event<size> &&)> & add_event;
};

/* First instantiated from: sudoku-solver.cpp:266 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<4>
{
  inline EventAdder(Stack<4> * stack_, const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)> & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  inline void operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && event) const
  {
        
    class __lambda_56_16
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
      {
        e.apply(__this->stack);
      }
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsSetInInput<4> >(const exploration::CellIsSetInInput<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::InputsAreDone<4> >(const exploration::InputsAreDone<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<4> >(const exploration::PropagationStartsForSudoku<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<4> >(const exploration::PropagationStartsForCell<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellPropagates<4> >(const exploration::CellPropagates<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<4> >(const exploration::CellIsDeducedFromSingleAllowedValue<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<4> >(const exploration::PropagationIsDoneForCell<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<4> >(const exploration::PropagationIsDoneForSudoku<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationStarts<4> >(const exploration::ExplorationStarts<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsMade<4> >(const exploration::HypothesisIsMade<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<4> >(const exploration::HypothesisIsRejected<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::SudokuIsSolved<4> >(const exploration::SudokuIsSolved<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<4> >(const exploration::HypothesisIsAccepted<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationIsDone<4> >(const exploration::ExplorationIsDone<4> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      private: 
      const EventAdder<4> * __this;
      
      public:
      __lambda_56_16(const EventAdder<4> * _this)
      : __this{_this}
      {}
      
    };
    
    std::visit<__lambda_56_16, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(__lambda_56_16{this}, event);
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(event));
  }
  
  
  private: 
  Stack<4> * stack;
  const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)> & add_event;
  public: 
};

#endif
/* First instantiated from: sudoku-solver.cpp:266 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventAdder<9>
{
  inline EventAdder(Stack<9> * stack_, const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)> & add_event_)
  : stack{stack_}
  , add_event{add_event_}
  {
  }
  
  inline void operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && event) const
  {
        
    class __lambda_56_16
    {
      public: 
      template<class type_parameter_0_0>
      inline /*constexpr */ auto operator()(const type_parameter_0_0 & e) const
      {
        e.apply(__this->stack);
      }
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsSetInInput<9> >(const exploration::CellIsSetInInput<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::InputsAreDone<9> >(const exploration::InputsAreDone<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForSudoku<9> >(const exploration::PropagationStartsForSudoku<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationStartsForCell<9> >(const exploration::PropagationStartsForCell<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellPropagates<9> >(const exploration::CellPropagates<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedFromSingleAllowedValue<9> >(const exploration::CellIsDeducedFromSingleAllowedValue<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> >(const exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForCell<9> >(const exploration::PropagationIsDoneForCell<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::PropagationIsDoneForSudoku<9> >(const exploration::PropagationIsDoneForSudoku<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationStarts<9> >(const exploration::ExplorationStarts<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsMade<9> >(const exploration::HypothesisIsMade<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsRejected<9> >(const exploration::HypothesisIsRejected<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::SudokuIsSolved<9> >(const exploration::SudokuIsSolved<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::HypothesisIsAccepted<9> >(const exploration::HypothesisIsAccepted<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      
      #ifdef INSIGHTS_USE_TEMPLATE
      template<>
      inline /*constexpr */ void operator()<exploration::ExplorationIsDone<9> >(const exploration::ExplorationIsDone<9> & e) const
      {
        e.apply(__this->stack);
      }
      #endif
      
      private: 
      const EventAdder<9> * __this;
      
      public:
      __lambda_56_16(const EventAdder<9> * _this)
      : __this{_this}
      {}
      
    };
    
    std::visit<__lambda_56_16, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(__lambda_56_16{this}, event);
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(event));
  }
  
  
  private: 
  Stack<9> * stack;
  const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)> & add_event;
  public: 
};

#endif



// Make sure a closing event is added, however the scope is exited
template<unsigned int size>
struct EventsPairGuard
{
  inline EventsPairGuard(const EventAdder<size> & add_event_, exploration::Event<size> && in, exploration::Event<size> && out_)
  : add_event{add_event_}
  , out{std::move(out_)}
  {
    this->add_event(std::move(in));
  }
  
  inline ~EventsPairGuard()
  {
    this->add_event(std::move(this->out));
  }
  
  const EventAdder<size> & add_event;
  exploration::Event<size> out;
};

/* First instantiated from: sudoku-solver.cpp:100 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<4>
{
  inline EventsPairGuard(const EventAdder<4> & add_event_, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && in, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > && out_)
  : add_event{add_event_}
  , out{std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(out_))}
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(in));
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &>(this->out));
  }
  
  const EventAdder<4> & add_event;
  std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > out;
  // inline EventsPairGuard<4> & operator=(const EventsPairGuard<4> &) /* noexcept */ = delete;
};

#endif
/* First instantiated from: sudoku-solver.cpp:100 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct EventsPairGuard<9>
{
  inline EventsPairGuard(const EventAdder<9> & add_event_, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && in, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > && out_)
  : add_event{add_event_}
  , out{std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(out_))}
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(in));
  }
  
  inline ~EventsPairGuard() noexcept
  {
    this->add_event.operator()(std::move<std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &>(this->out));
  }
  
  const EventAdder<9> & add_event;
  std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > out;
  // inline EventsPairGuard<9> & operator=(const EventsPairGuard<9> &) /* noexcept */ = delete;
};

#endif



template<unsigned int size>
bool propagate(const Stack<size> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo_, const EventAdder<size> & add_event)
{
  UniqueQueue<std::pair<unsigned int, unsigned int> > todo = UniqueQueue<std::pair<unsigned int, unsigned int> >();
  {
    const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & __range1 = todo_;
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __begin1 = __range1.begin();
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __end1 = __range1.end();
    for(; !operator==(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1), static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__end1)); __begin1.operator++()) {
      const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1).operator*());
      todo.add(cell);
    }
    
  }
  EventsPairGuard<size> guard = add_event, exploration::PropagationStartsForSudoku<size>(), exploration::PropagationIsDoneForSudoku<size>();
  while(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = static_cast<const std::pair<unsigned int, unsigned int>>(todo.get());
    const auto & source_cell = stack.current().cell(source_coords);
    (static_cast<bool>(source_cell.is_set()) ? void(0) : __assert_fail("source_cell.is_set()", "/wd/src/exploration/sudoku-solver.cpp", 108, __extension____PRETTY_FUNCTION__));
    const unsigned int value = source_cell.get();
    EventsPairGuard<size> guard = add_event, exploration::PropagationStartsForCell<size>(source_coords, value), exploration::PropagationIsDoneForCell<size>(source_coords, value);
    const std::pair<unsigned int, unsigned int> __source_coords116 = std::pair<unsigned int, unsigned int>(source_coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords116));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords116));
    {
      auto && __range2 = source_cell.regions();
      for(; ; ) {
        const auto & source_region;
        {
          auto && __range3 = source_region.cells();
          for(; ; ) {
            const auto & target_cell;
            const auto target_coords = target_cell.coordinates();
            if(target_cell != source_cell) {
              if(target_cell.is_set()) {
                if(target_cell.get() == value) {
                  return false;
                } 
                
              } else {
                (static_cast<bool>(target_cell.allowed_count() > 1) ? void(0) : __assert_fail("target_cell.allowed_count() > 1", "/wd/src/exploration/sudoku-solver.cpp", 126, __extension____PRETTY_FUNCTION__));
                if(target_cell.is_allowed(value)) {
                  add_event(exploration::CellPropagates<size>(source_coords, target_coords, value));
                  if(target_cell.allowed_count() == 1) {
                    {
                      auto && __range8 = SudokuConstants<size>::values;
                      for(; ; ) {
                        unsigned int value;
                        if(target_cell.is_allowed(value)) {
                          add_event(exploration::CellIsDeducedFromSingleAllowedValue<size>(target_coords, value));
                          todo.add(target_coords);
                          break;
                        } 
                        
                      }
                      
                    }
                  } 
                  
                  {
                    auto && __range7 = target_cell.regions();
                    for(; ; ) {
                      const auto & target_region;
                      unsigned int count = static_cast<unsigned int>(0);
                      const typename AnnotatedSudoku<size>::Cell * single_cell;
                      {
                        auto && __range8 = target_region.cells();
                        for(; ; ) {
                          const auto & cell;
                          if(cell.is_allowed(value)) {
                            ++count;
                            single_cell = &cell;
                          } 
                          
                        }
                        
                      }
                      if((count == static_cast<unsigned int>(1)) && !single_cell->is_set()) {
                        const std::pair<unsigned int, unsigned int> single_coords = single_cell->coordinates();
                        add_event(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<size>(single_coords, value, target_region.index()));
                        todo.add(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event(exploration::SudokuIsSolved<size>());
                  } 
                  
                } else {
                } 
                
              } 
              
            } 
            
          }
          
        }
      }
      
    }
  }
  
  return true;
}


/* First instantiated from: sudoku-solver.cpp:248 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<4>(const Stack<4> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo_, const EventAdder<4> & add_event)
{
  UniqueQueue<std::pair<unsigned int, unsigned int> > todo = UniqueQueue<std::pair<unsigned int, unsigned int> >();
  {
    const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & __range1 = todo_;
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __begin1 = __range1.begin();
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __end1 = __range1.end();
    for(; !operator==(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1), static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__end1)); __begin1.operator++()) {
      const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1).operator*());
      todo.add(cell);
    }
    
  }
  EventsPairGuard<4> guard = EventsPairGuard<4>(add_event, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationStartsForSudoku<4>()), std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationIsDoneForSudoku<4>()));
  while(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = static_cast<const std::pair<unsigned int, unsigned int>>(todo.get());
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(108), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 4U]")));
    const unsigned int value = static_cast<const AnnotatedCell<4>&>(source_cell).get();
    EventsPairGuard<4> guard = EventsPairGuard<4>(add_event, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationStartsForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::PropagationIsDoneForCell<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
    const std::pair<unsigned int, unsigned int> __source_coords116 = std::pair<unsigned int, unsigned int>(source_coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords116));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords116));
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> > && __range2 = source_cell.regions();
      boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<4>, 4>::Region & source_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator*();
        {
          boost::iterator_range<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = source_region.cells();
          boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
          boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
          for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
            const SudokuBase<AnnotatedCell<4>, 4>::Cell & target_cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
            const std::pair<unsigned int, unsigned int> target_coords = static_cast<const std::pair<unsigned int, unsigned int>>(target_cell.coordinates());
            if(!target_cell.operator==(source_cell)) {
              if(static_cast<const AnnotatedCell<4>&>(target_cell).is_set()) {
                if(static_cast<const AnnotatedCell<4>&>(target_cell).get() == value) {
                  return false;
                } 
                
              } else {
                (static_cast<bool>(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 4U]")));
                if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellPropagates<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<4>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 4> & __range8 = SudokuConstants<4>::values;
                      const unsigned int * __begin0 = __range8.begin();
                      const unsigned int * __end0 = __range8.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<4>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellIsDeducedFromSingleAllowedValue<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          todo.add(target_coords);
                          break;
                        } 
                        
                      }
                      
                    }
                  } 
                  
                  {
                    boost::iterator_range<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> > && __range7 = target_cell.regions();
                    boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range7).begin();
                    boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range7).end();
                    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator++()) {
                      const SudokuBase<AnnotatedCell<4>, 4>::Region & target_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Region, long, false, false>&>(__begin0).operator*();
                      unsigned int count = static_cast<unsigned int>(0);
                      const typename AnnotatedSudoku<4U>::Cell * single_cell;
                      {
                        boost::iterator_range<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range8 = target_region.cells();
                        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range8).begin();
                        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range8).end();
                        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
                          const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
                          if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(value)) {
                            ++count;
                            single_cell = &cell;
                          } 
                          
                        }
                        
                      }
                      if((count == static_cast<unsigned int>(1)) && !static_cast<const AnnotatedCell<4> *>(single_cell)->is_set()) {
                        const std::pair<unsigned int, unsigned int> single_coords = static_cast<const std::pair<unsigned int, unsigned int>>(single_cell->coordinates());
                        add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        todo.add(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::SudokuIsSolved<4>()));
                  } 
                  
                } else {
                } 
                
              } 
              
            } 
            
          }
          
        }
      }
      
    }
  }
  
  return true;
}
#endif


/* First instantiated from: sudoku-solver.cpp:248 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate<9>(const Stack<9> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo_, const EventAdder<9> & add_event)
{
  UniqueQueue<std::pair<unsigned int, unsigned int> > todo = UniqueQueue<std::pair<unsigned int, unsigned int> >();
  {
    const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & __range1 = todo_;
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __begin1 = __range1.begin();
    std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> > __end1 = __range1.end();
    for(; !operator==(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1), static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__end1)); __begin1.operator++()) {
      const std::pair<unsigned int, unsigned int> cell = std::pair<unsigned int, unsigned int>(static_cast<const std::_Rb_tree_const_iterator<std::pair<unsigned int, unsigned int> >>(__begin1).operator*());
      todo.add(cell);
    }
    
  }
  EventsPairGuard<9> guard = EventsPairGuard<9>(add_event, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationStartsForSudoku<9>()), std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationIsDoneForSudoku<9>()));
  while(!static_cast<const UniqueQueue<std::pair<unsigned int, unsigned int> >>(todo).empty()) {
    const std::pair<unsigned int, unsigned int> source_coords = static_cast<const std::pair<unsigned int, unsigned int>>(todo.get());
    const Cell & source_cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cell(source_coords);
    (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(source_cell).is_set()) ? void(0) : __assert_fail(static_cast<const char *>("source_cell.is_set()"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(108), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 9U]")));
    const unsigned int value = static_cast<const AnnotatedCell<9>&>(source_cell).get();
    EventsPairGuard<9> guard = EventsPairGuard<9>(add_event, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationStartsForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::PropagationIsDoneForCell<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
    const std::pair<unsigned int, unsigned int> __source_coords116 = std::pair<unsigned int, unsigned int>(source_coords);
    const unsigned int && row = std::get<0UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords116));
    const unsigned int && col = std::get<1UL>(static_cast<const std::pair<unsigned int, unsigned int> &&>(__source_coords116));
    {
      boost::iterator_range<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> > && __range2 = source_cell.regions();
      boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).begin();
      boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range2).end();
      for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator++()) {
        const SudokuBase<AnnotatedCell<9>, 9>::Region & source_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator*();
        {
          boost::iterator_range<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range3 = source_region.cells();
          boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).begin();
          boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range3).end();
          for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
            const SudokuBase<AnnotatedCell<9>, 9>::Cell & target_cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
            const std::pair<unsigned int, unsigned int> target_coords = static_cast<const std::pair<unsigned int, unsigned int>>(target_cell.coordinates());
            if(!target_cell.operator==(source_cell)) {
              if(static_cast<const AnnotatedCell<9>&>(target_cell).is_set()) {
                if(static_cast<const AnnotatedCell<9>&>(target_cell).get() == value) {
                  return false;
                } 
                
              } else {
                (static_cast<bool>(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() > static_cast<unsigned int>(1)) ? void(0) : __assert_fail(static_cast<const char *>("target_cell.allowed_count() > 1"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(126), static_cast<const char *>(__extension__"bool propagate(const Stack<size> &, const std::set<Coordinates> &, const EventAdder<size> &) [size = 9U]")));
                if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                  add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellPropagates<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                  if(static_cast<const AnnotatedCell<9>&>(target_cell).allowed_count() == static_cast<unsigned int>(1)) {
                    {
                      const std::array<unsigned int, 9> & __range8 = SudokuConstants<9>::values;
                      const unsigned int * __begin0 = __range8.begin();
                      const unsigned int * __end0 = __range8.end();
                      for(; __begin0 != __end0; ++__begin0) {
                        unsigned int value = *__begin0;
                        if(static_cast<const AnnotatedCell<9>&>(target_cell).is_allowed(value)) {
                          add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellIsDeducedFromSingleAllowedValue<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                          todo.add(target_coords);
                          break;
                        } 
                        
                      }
                      
                    }
                  } 
                  
                  {
                    boost::iterator_range<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> > && __range7 = target_cell.regions();
                    boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range7).begin();
                    boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range7).end();
                    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator++()) {
                      const SudokuBase<AnnotatedCell<9>, 9>::Region & target_region = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_199_24, const unsigned int *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Region, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Region, long, false, false>&>(__begin0).operator*();
                      unsigned int count = static_cast<unsigned int>(0);
                      const typename AnnotatedSudoku<9U>::Cell * single_cell;
                      {
                        boost::iterator_range<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range8 = target_region.cells();
                        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range8).begin();
                        boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range8).end();
                        for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
                          const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_74_28, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
                          if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(value)) {
                            ++count;
                            single_cell = &cell;
                          } 
                          
                        }
                        
                      }
                      if((count == static_cast<unsigned int>(1)) && !static_cast<const AnnotatedCell<9> *>(single_cell)->is_set()) {
                        const std::pair<unsigned int, unsigned int> single_coords = static_cast<const std::pair<unsigned int, unsigned int>>(single_cell->coordinates());
                        add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
                        todo.add(single_coords);
                      } 
                      
                    }
                    
                  }
                  if(stack.current().is_solved()) {
                    add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::SudokuIsSolved<9>()));
                  } 
                  
                } else {
                } 
                
              } 
              
            } 
            
          }
          
        }
      }
      
    }
  }
  
  return true;
}
#endif



template<unsigned int size>
std::pair<unsigned int, unsigned int> get_most_constrained_cell(const AnnotatedSudoku<size> & sudoku)
{
  std::pair<unsigned int, unsigned int> best_coords = std::pair<unsigned int, unsigned int>() /* NRVO variable */;
  unsigned int best_count = size + static_cast<unsigned int>(1);
  {
    auto && __range1 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      if(cell.is_set()) {
        continue;
      } 
      
      unsigned int count = cell.allowed_count();
      if(count < best_count) {
        best_coords = cell.coordinates();
        best_count = count;
      } 
      
      if(best_count == static_cast<unsigned int>(2)) {
        break;
      } 
      
    }
    
  }
  return std::pair<unsigned int, unsigned int>(static_cast<std::pair<unsigned int, unsigned int> &&>(best_coords));
}


/* First instantiated from: sudoku-solver.cpp:213 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::pair<unsigned int, unsigned int> get_most_constrained_cell<4>(const Sudoku<AnnotatedCell<4>, 4> & sudoku)
{
  std::pair<unsigned int, unsigned int> best_coords = std::pair<unsigned int, unsigned int>() /* NRVO variable */;
  unsigned int best_count = 4U + static_cast<unsigned int>(1);
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*();
      if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
        continue;
      } 
      
      unsigned int count = static_cast<const AnnotatedCell<4>&>(cell).allowed_count();
      if(count < best_count) {
        best_coords.operator=(cell.coordinates());
        best_count = count;
      } 
      
      if(best_count == static_cast<unsigned int>(2)) {
        break;
      } 
      
    }
    
  }
  return std::pair<unsigned int, unsigned int>(static_cast<std::pair<unsigned int, unsigned int> &&>(best_coords));
}
#endif


/* First instantiated from: sudoku-solver.cpp:213 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::pair<unsigned int, unsigned int> get_most_constrained_cell<9>(const Sudoku<AnnotatedCell<9>, 9> & sudoku)
{
  std::pair<unsigned int, unsigned int> best_coords = std::pair<unsigned int, unsigned int>() /* NRVO variable */;
  unsigned int best_count = 9U + static_cast<unsigned int>(1);
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_162_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, const SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, const SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*();
      if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
        continue;
      } 
      
      unsigned int count = static_cast<const AnnotatedCell<9>&>(cell).allowed_count();
      if(count < best_count) {
        best_coords.operator=(cell.coordinates());
        best_count = count;
      } 
      
      if(best_count == static_cast<unsigned int>(2)) {
        break;
      } 
      
    }
    
  }
  return std::pair<unsigned int, unsigned int>(static_cast<std::pair<unsigned int, unsigned int> &&>(best_coords));
}
#endif



template<unsigned int size>
bool propagate_and_explore(const Stack<size> &, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size> &);
;


template<unsigned int size>
bool explore(const Stack<size> & stack, const EventAdder<size> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail("!stack.current().is_solved()", "/wd/src/exploration/sudoku-solver.cpp", 211, __extension____PRETTY_FUNCTION__));
  const auto & cell = stack.current().cell(get_most_constrained_cell(stack.current()));
  const std::pair<unsigned int, unsigned int> coords = cell.coordinates();
  std::vector<unsigned int, std::allocator<unsigned int> > allowed_values = std::vector<unsigned int, std::allocator<unsigned int> >();
  {
    auto && __range1 = SudokuConstants<size>::values;
    for(; ; ) {
      unsigned int val;
      if(cell.is_allowed(val)) {
        allowed_values.push_back(static_cast<const unsigned int>(val));
      } 
      
    }
    
  }
  EventsPairGuard<size> guard = add_event, exploration::ExplorationStarts<size>(coords, allowed_values), exploration::ExplorationIsDone<size>(coords);
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range1 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin1 = __range1.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end1 = __range1.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end1)); __begin1.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1).operator*();
      add_event(exploration::HypothesisIsMade<size>(coords, val));
      if(propagate_and_explore(stack, {coords}, add_event)) {
        add_event(exploration::HypothesisIsAccepted<size>(coords, val));
        return true;
      } else {
        add_event(exploration::HypothesisIsRejected<size>(coords, val));
      } 
      
    }
    
  }
  return false;
}


/* First instantiated from: sudoku-solver.cpp:252 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<4>(const Stack<4> & stack, const EventAdder<4> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(211), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size> &) [size = 4U]")));
  const Cell & cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cell(static_cast<const std::pair<unsigned int, unsigned int>>(get_most_constrained_cell<4>(stack.current())));
  const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
  std::vector<unsigned int, std::allocator<unsigned int> > allowed_values = std::vector<unsigned int, std::allocator<unsigned int> >();
  {
    const std::array<unsigned int, 4> & __range1 = SudokuConstants<4>::values;
    const unsigned int * __begin0 = __range1.begin();
    const unsigned int * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      unsigned int val = *__begin0;
      if(static_cast<const AnnotatedCell<4>&>(cell).is_allowed(val)) {
        allowed_values.push_back(static_cast<const unsigned int>(val));
      } 
      
    }
    
  }
  EventsPairGuard<4> guard = EventsPairGuard<4>(add_event, std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::ExplorationStarts<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::ExplorationIsDone<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range1 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin1 = __range1.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end1 = __range1.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end1)); __begin1.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1).operator*();
      add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::HypothesisIsMade<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<4>(stack, std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::less<std::pair<unsigned int, unsigned int> >>(std::less<std::pair<unsigned int, unsigned int> >()), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::HypothesisIsAccepted<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::HypothesisIsRejected<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif


/* First instantiated from: sudoku-solver.cpp:252 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool explore<9>(const Stack<9> & stack, const EventAdder<9> & add_event)
{
  (static_cast<bool>(!stack.current().is_solved()) ? void(0) : __assert_fail(static_cast<const char *>("!stack.current().is_solved()"), static_cast<const char *>("/wd/src/exploration/sudoku-solver.cpp"), static_cast<unsigned int>(211), static_cast<const char *>(__extension__"bool explore(const Stack<size> &, const EventAdder<size> &) [size = 9U]")));
  const Cell & cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cell(static_cast<const std::pair<unsigned int, unsigned int>>(get_most_constrained_cell<9>(stack.current())));
  const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
  std::vector<unsigned int, std::allocator<unsigned int> > allowed_values = std::vector<unsigned int, std::allocator<unsigned int> >();
  {
    const std::array<unsigned int, 9> & __range1 = SudokuConstants<9>::values;
    const unsigned int * __begin0 = __range1.begin();
    const unsigned int * __end0 = __range1.end();
    for(; __begin0 != __end0; ++__begin0) {
      unsigned int val = *__begin0;
      if(static_cast<const AnnotatedCell<9>&>(cell).is_allowed(val)) {
        allowed_values.push_back(static_cast<const unsigned int>(val));
      } 
      
    }
    
  }
  EventsPairGuard<9> guard = EventsPairGuard<9>(add_event, std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::ExplorationStarts<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)), std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::ExplorationIsDone<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
  {
    std::vector<unsigned int, std::allocator<unsigned int> > & __range1 = allowed_values;
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __begin1 = __range1.begin();
    __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > > __end1 = __range1.end();
    for(; !__gnu_cxx::operator==(static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1), static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__end1)); __begin1.operator++()) {
      unsigned int val = static_cast<const __gnu_cxx::__normal_iterator<unsigned int *, std::vector<unsigned int, std::allocator<unsigned int> > >>(__begin1).operator*();
      add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::HypothesisIsMade<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      if(propagate_and_explore<9>(stack, std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >{std::initializer_list<std::pair<unsigned int, unsigned int> >{std::pair<unsigned int, unsigned int>(coords)}, static_cast<const std::less<std::pair<unsigned int, unsigned int> >>(std::less<std::pair<unsigned int, unsigned int> >()), static_cast<const std::allocator<std::pair<unsigned int, unsigned int> >>(std::allocator<std::pair<unsigned int, unsigned int> >())}, add_event)) {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::HypothesisIsAccepted<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        return true;
      } else {
        add_event.operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::HypothesisIsRejected<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
      } 
      
    }
    
  }
  return false;
}
#endif



template<unsigned int size>
bool propagate_and_explore(const Stack<size> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<size> & add_event)
{
  if(propagate(stack, todo, add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}


/* First instantiated from: sudoku-solver.cpp:279 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<4>(const Stack<4> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<4> & add_event)
{
  if(propagate<4>(stack, todo, add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<4>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif


/* First instantiated from: sudoku-solver.cpp:279 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
bool propagate_and_explore<9>(const Stack<9> & stack, const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > & todo, const EventAdder<9> & add_event)
{
  if(propagate<9>(stack, todo, add_event)) {
    if(stack.current().is_solved()) {
      return true;
    } else {
      return explore<9>(stack, add_event);
    } 
    
  } else {
    return false;
  } 
  
}
#endif



template<unsigned int size>
Sudoku<ValueCell, size> solve_using_exploration(Sudoku<ValueCell, size> sudoku, const std::function<void (exploration::Event<size> &&)> & add_event_)
{
  Stack<size> stack;
  EventAdder<size> add_event = &stack, add_event_;
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    auto && __range1 = sudoku.cells();
    for(; ; ) {
      const auto & cell;
      const auto val = cell.get();
      if(val) {
        const std::pair<unsigned int, unsigned int> coords = cell.coordinates();
        add_event(exploration::CellIsSetInInput<size>(coords, *val));
        todo.insert(coords);
      } 
      
    }
    
  }
  add_event(exploration::InputsAreDone<size>());
  propagate_and_explore(stack, std::move<std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo), add_event);
  {
    auto && __range1 = stack.current().cells();
    for(; ; ) {
      const auto & cell;
      if(cell.is_set()) {
        sudoku.cell(cell.coordinates()).set(cell.get());
      } 
      
    }
    
  }
  return sudoku;
}


/* First instantiated from: sudoku-solver.cpp:289 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 4> solve_using_exploration<4>(Sudoku<ValueCell, 4> sudoku, const std::function<void (std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> > &&)> & add_event_)
{
  Stack<4> stack = Stack<4>();
  EventAdder<4> add_event = EventAdder<4>(&stack, add_event_);
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 4>::Cell & cell = static_cast<const SudokuBase<ValueCell, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<4>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::CellIsSetInInput<4>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.insert(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<4>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<4>, exploration::InputsAreDone<4>, exploration::PropagationStartsForSudoku<4>, exploration::PropagationStartsForCell<4>, exploration::CellPropagates<4>, exploration::CellIsDeducedFromSingleAllowedValue<4>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<4>, exploration::PropagationIsDoneForCell<4>, exploration::PropagationIsDoneForSudoku<4>, exploration::ExplorationStarts<4>, exploration::HypothesisIsMade<4>, exploration::HypothesisIsRejected<4>, exploration::SudokuIsSolved<4>, exploration::HypothesisIsAccepted<4>, exploration::ExplorationIsDone<4> >(exploration::InputsAreDone<4>()));
  propagate_and_explore<4>(static_cast<const Stack<4>>(stack), static_cast<const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<4>>(add_event));
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<4>, 4>&>(stack.current()).cells();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<4>, 4>::Cell & cell = static_cast<const SudokuBase<AnnotatedCell<4>, 4>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<4>, 4>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<4>, 4>::Cell &, long, false, false>&>(__begin0).operator*());
      if(static_cast<const AnnotatedCell<4>&>(cell).is_set()) {
        static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 4>&>(sudoku).cell(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()))).set(static_cast<const AnnotatedCell<4>&>(cell).get());
      } 
      
    }
    
  }
  return Sudoku<ValueCell, 4>(static_cast<const Sudoku<ValueCell, 4> &&>(sudoku));
}
#endif


/* First instantiated from: sudoku-solver.cpp:294 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
Sudoku<ValueCell, 9> solve_using_exploration<9>(Sudoku<ValueCell, 9> sudoku, const std::function<void (std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> > &&)> & add_event_)
{
  Stack<9> stack = Stack<9>();
  EventAdder<9> add_event = EventAdder<9>(&stack, add_event_);
  std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > todo = std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > >();
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cells();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<ValueCell, 9>::Cell & cell = static_cast<const SudokuBase<ValueCell, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<ValueCell, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<ValueCell, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      const std::optional<unsigned int> val = static_cast<const std::optional<unsigned int>>(static_cast<const ValueCell&>(cell).get());
      if(static_cast<bool>(val.operator bool())) {
        const std::pair<unsigned int, unsigned int> coords = static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates());
        static_cast<const EventAdder<9>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::CellIsSetInInput<9>(/* INSIGHTS-TODO: CodeGenerator.cpp:3850 stmt: CXXParenListInitExpr */)));
        todo.insert(coords);
      } 
      
    }
    
  }
  static_cast<const EventAdder<9>>(add_event).operator()(std::variant<exploration::CellIsSetInInput<9>, exploration::InputsAreDone<9>, exploration::PropagationStartsForSudoku<9>, exploration::PropagationStartsForCell<9>, exploration::CellPropagates<9>, exploration::CellIsDeducedFromSingleAllowedValue<9>, exploration::CellIsDeducedAsSinglePlaceForValueInRegion<9>, exploration::PropagationIsDoneForCell<9>, exploration::PropagationIsDoneForSudoku<9>, exploration::ExplorationStarts<9>, exploration::HypothesisIsMade<9>, exploration::HypothesisIsRejected<9>, exploration::SudokuIsSolved<9>, exploration::HypothesisIsAccepted<9>, exploration::ExplorationIsDone<9> >(exploration::InputsAreDone<9>()));
  propagate_and_explore<9>(static_cast<const Stack<9>>(stack), static_cast<const std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &&>(std::move<std::set<std::pair<unsigned int, unsigned int>, std::less<std::pair<unsigned int, unsigned int> >, std::allocator<std::pair<unsigned int, unsigned int> > > &>(todo)), static_cast<const EventAdder<9>>(add_event));
  {
    boost::iterator_range<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> > && __range1 = static_cast<SudokuBase<AnnotatedCell<9>, 9>&>(stack.current()).cells();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __begin0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).begin();
    boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default> __end0 = static_cast<const boost::iterator_range_detail::iterator_range_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, boost::iterators::incrementable_traversal_tag>&>(__range1).end();
    for(; boost::iterators::operator!=(static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__begin0)), static_cast<const boost::iterators::iterator_facade<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long>&>(static_cast<const boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>>(__end0))); static_cast<boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator++()) {
      const SudokuBase<AnnotatedCell<9>, 9>::Cell & cell = static_cast<const SudokuBase<AnnotatedCell<9>, 9>::Cell>(static_cast<const boost::iterators::detail::iterator_facade_base<boost::iterators::transform_iterator<__lambda_173_26, const std::pair<unsigned int, unsigned int> *, boost::use_default, boost::use_default>, SudokuBase<AnnotatedCell<9>, 9>::Cell, boost::iterators::random_access_traversal_tag, SudokuBase<AnnotatedCell<9>, 9>::Cell &, long, false, false>&>(__begin0).operator*());
      if(static_cast<const AnnotatedCell<9>&>(cell).is_set()) {
        static_cast<ValueCell&>(static_cast<SudokuBase<ValueCell, 9>&>(sudoku).cell(static_cast<const std::pair<unsigned int, unsigned int>>(cell.coordinates()))).set(static_cast<const AnnotatedCell<9>&>(cell).get());
      } 
      
    }
    
  }
  return Sudoku<ValueCell, 9>(static_cast<const Sudoku<ValueCell, 9> &&>(sudoku));
}
#endif


template Sudoku<ValueCell, 4> solve_using_exploration(
  Sudoku<ValueCell, 4>,
  const std::function<void(exploration::Event<4>&&)>&
);

template Sudoku<ValueCell, 9> solve_using_exploration(
  Sudoku<ValueCell, 9>,
  const std::function<void(exploration::Event<9>&&)>&
);
