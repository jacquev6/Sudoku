// Copyright 2023 Vincent Jacques

#ifndef EXPLORATION_EVENTS_HPP_
#define EXPLORATION_EVENTS_HPP_

#include <vector>

#include "sudoku.hpp"


namespace exploration {

struct EventVisitor;

struct Event {
  virtual ~Event() = default;
  virtual void accept(EventVisitor&) const = 0;
};

// Name events like affirmative sentences in present tense
struct CellIsSetInInput;
struct InputsAreDone;

struct PropagationStartsForSudoku;
struct PropagationStartsForCell;
struct CellPropagates;
struct CellIsDeducedFromSingleAllowedValue;
struct CellIsDeducedAsSinglePlaceForValueInRegion;
struct PropagationIsDoneForCell;
struct PropagationIsDoneForSudoku;

struct ExplorationStarts;
struct HypothesisIsMade;
struct HypothesisIsRejected;
struct SudokuIsSolved;
struct HypothesisIsAccepted;
struct ExplorationIsDone;

struct EventVisitor {
  virtual ~EventVisitor() = default;

  virtual void visit(const CellIsSetInInput&) = 0;
  virtual void visit(const InputsAreDone&) = 0;

  virtual void visit(const PropagationStartsForSudoku&) = 0;
  virtual void visit(const PropagationStartsForCell&) = 0;
  virtual void visit(const CellPropagates&) = 0;
  virtual void visit(const CellIsDeducedFromSingleAllowedValue&) = 0;
  virtual void visit(const CellIsDeducedAsSinglePlaceForValueInRegion&) = 0;
  virtual void visit(const PropagationIsDoneForCell&) = 0;
  virtual void visit(const PropagationIsDoneForSudoku&) = 0;

  virtual void visit(const ExplorationStarts&) = 0;
  virtual void visit(const HypothesisIsMade&) = 0;
  virtual void visit(const HypothesisIsRejected&) = 0;
  virtual void visit(const SudokuIsSolved&) = 0;
  virtual void visit(const HypothesisIsAccepted&) = 0;
  virtual void visit(const ExplorationIsDone&) = 0;
};

struct CellIsSetInInput : Event {
  CellIsSetInInput(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
};

struct InputsAreDone : Event {
  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }
};

struct PropagationStartsForSudoku : Event {
  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }
};

struct PropagationStartsForCell : Event {
  PropagationStartsForCell(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
};

struct CellPropagates : Event {
  CellPropagates(
    const AnnotatedSudoku::Coordinates& source_cell_, const AnnotatedSudoku::Coordinates& target_cell_, unsigned value_
  ) :  // NOLINT(whitespace/parens)
    source_cell(source_cell_), target_cell(target_cell_), value(value_)
  {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates source_cell;
  const AnnotatedSudoku::Coordinates target_cell;
  const unsigned value;
};

struct CellIsDeducedFromSingleAllowedValue : Event {
  CellIsDeducedFromSingleAllowedValue(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) :
    cell(cell_), value(value_)
  {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
};

struct CellIsDeducedAsSinglePlaceForValueInRegion : Event {
  CellIsDeducedAsSinglePlaceForValueInRegion(
    const AnnotatedSudoku::Coordinates& cell_, unsigned value_, unsigned region_
  ) :  // NOLINT(whitespace/parens)
    cell(cell_), value(value_), region(region_)
  {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
  const unsigned region;
};

struct PropagationIsDoneForCell : Event {
  PropagationIsDoneForCell(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
};

struct PropagationIsDoneForSudoku : Event {
  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }
};

struct ExplorationStarts : Event {
  ExplorationStarts(const AnnotatedSudoku::Coordinates& cell_, const std::vector<unsigned>& allowed_values_) :
    cell(cell_), allowed_values(allowed_values_)
  {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const std::vector<unsigned> allowed_values;
};

struct HypothesisIsMade : Event {
  HypothesisIsMade(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) :
    cell(cell_), value(value_), spoiler(std::nullopt)
  {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
  std::optional<bool> spoiler;
};

struct HypothesisIsRejected : Event {
  HypothesisIsRejected(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
};

struct SudokuIsSolved : Event {
  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }
};

struct HypothesisIsAccepted : Event {
  HypothesisIsAccepted(const AnnotatedSudoku::Coordinates& cell_, unsigned value_) : cell(cell_), value(value_) {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
  const unsigned value;
};

struct ExplorationIsDone : Event {
  explicit ExplorationIsDone(const AnnotatedSudoku::Coordinates& cell_) : cell(cell_) {}

  void accept(EventVisitor& visitor) const override { visitor.visit(*this); }

  const AnnotatedSudoku::Coordinates cell;
};

}  // namespace exploration

#endif  // EXPLORATION_EVENTS_HPP_
