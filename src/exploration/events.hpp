// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <vector>

#include "annotations.hpp"


namespace exploration {

template<unsigned size>
struct EventVisitor;

template<unsigned size>
struct Event {
  virtual ~Event() = default;
  virtual void accept(EventVisitor<size>&) const = 0;
  virtual void apply(Stack<size>*) const = 0;
};

// Name events like affirmative sentences in present tense
template<unsigned size>
struct CellIsSetInInput;
template<unsigned size>
struct InputsAreDone;

template<unsigned size>
struct PropagationStartsForSudoku;
template<unsigned size>
struct PropagationStartsForCell;
template<unsigned size>
struct CellPropagates;
template<unsigned size>
struct CellIsDeducedFromSingleAllowedValue;
template<unsigned size>
struct CellIsDeducedAsSinglePlaceForValueInRegion;
template<unsigned size>
struct PropagationIsDoneForCell;
template<unsigned size>
struct PropagationIsDoneForSudoku;

template<unsigned size>
struct ExplorationStarts;
template<unsigned size>
struct HypothesisIsMade;
template<unsigned size>
struct HypothesisIsRejected;
template<unsigned size>
struct SudokuIsSolved;
template<unsigned size>
struct HypothesisIsAccepted;
template<unsigned size>
struct ExplorationIsDone;

template<unsigned size>
struct EventVisitor {
  virtual ~EventVisitor() = default;

  virtual void visit(const CellIsSetInInput<size>&) = 0;
  virtual void visit(const InputsAreDone<size>&) = 0;

  virtual void visit(const PropagationStartsForSudoku<size>&) = 0;
  virtual void visit(const PropagationStartsForCell<size>&) = 0;
  virtual void visit(const CellPropagates<size>&) = 0;
  virtual void visit(const CellIsDeducedFromSingleAllowedValue<size>&) = 0;
  virtual void visit(const CellIsDeducedAsSinglePlaceForValueInRegion<size>&) = 0;
  virtual void visit(const PropagationIsDoneForCell<size>&) = 0;
  virtual void visit(const PropagationIsDoneForSudoku<size>&) = 0;

  virtual void visit(const ExplorationStarts<size>&) = 0;
  virtual void visit(const HypothesisIsMade<size>&) = 0;
  virtual void visit(const HypothesisIsRejected<size>&) = 0;
  virtual void visit(const SudokuIsSolved<size>&) = 0;
  virtual void visit(const HypothesisIsAccepted<size>&) = 0;
  virtual void visit(const ExplorationIsDone<size>&) = 0;
};

template<unsigned size>
struct CellIsSetInInput : Event<size> {
  CellIsSetInInput(const Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
};

template<unsigned size>
struct InputsAreDone : Event<size> {
  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;
};

template<unsigned size>
struct PropagationStartsForSudoku : Event<size> {
  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;
};

template<unsigned size>
struct PropagationStartsForCell : Event<size> {
  PropagationStartsForCell(const Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
};

template<unsigned size>
struct CellPropagates : Event<size> {
  CellPropagates(
    const Coordinates& source_cell_, const Coordinates& target_cell_, unsigned value_
  ) :  // NOLINT(whitespace/parens)
    source_cell(source_cell_), target_cell(target_cell_), value(value_)
  {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates source_cell;
  const Coordinates target_cell;
  const unsigned value;
};

template<unsigned size>
struct CellIsDeducedFromSingleAllowedValue : Event<size> {
  CellIsDeducedFromSingleAllowedValue(const Coordinates& cell_, unsigned value_) :
    cell(cell_), value(value_)
  {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
};

template<unsigned size>
struct CellIsDeducedAsSinglePlaceForValueInRegion : Event<size> {
  CellIsDeducedAsSinglePlaceForValueInRegion(
    const Coordinates& cell_, unsigned value_, unsigned region_
  ) :  // NOLINT(whitespace/parens)
    cell(cell_), value(value_), region(region_)
  {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
  const unsigned region;
};

template<unsigned size>
struct PropagationIsDoneForCell : Event<size> {
  PropagationIsDoneForCell(const Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
};

template<unsigned size>
struct PropagationIsDoneForSudoku : Event<size> {
  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;
};

template<unsigned size>
struct ExplorationStarts : Event<size> {
  ExplorationStarts(const Coordinates& cell_, const std::vector<unsigned>& allowed_values_) :
    cell(cell_), allowed_values(allowed_values_)
  {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const std::vector<unsigned> allowed_values;
};

template<unsigned size>
struct HypothesisIsMade : Event<size> {
  HypothesisIsMade(const Coordinates& cell_, unsigned value_) :
    cell(cell_), value(value_), spoiler(std::nullopt)
  {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
  std::optional<bool> spoiler;
};

template<unsigned size>
struct HypothesisIsRejected : Event<size> {
  HypothesisIsRejected(const Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
};

template<unsigned size>
struct SudokuIsSolved : Event<size> {
  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;
};

template<unsigned size>
struct HypothesisIsAccepted : Event<size> {
  HypothesisIsAccepted(const Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
  const unsigned value;
};

template<unsigned size>
struct ExplorationIsDone : Event<size> {
  explicit ExplorationIsDone(const Coordinates& cell_) : cell(cell_) {}

  void accept(EventVisitor<size>& visitor) const override { visitor.visit(*this); }
  void apply(Stack<size>*) const override;

  const Coordinates cell;
};

}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
