#include "GridButton.h"

using namespace ttt;

namespace {
constexpr int GRID_BUTTON_SIZE = 90;
}

GridButton::GridButton(const int row, const int col, QWidget *parent)
    : QPushButton(parent), TheOwner(Owner::None), Row(row), Col(col) {
  setFixedSize(GRID_BUTTON_SIZE, GRID_BUTTON_SIZE);
  connect(this, &QPushButton::clicked, this, &GridButton::HandleClicked);
}

GridButton::~GridButton() {}

Owner GridButton::GetOwner() const { return TheOwner; }

void GridButton::Reset() { SetGridOwner(Owner::None); }

void GridButton::SetGridOwner(const Owner owner) {
  TheOwner = owner;
  switch (owner) {
  case Owner::None:
    setText("");
    break;
  case Owner::X:
    setText("X");
    break;
  case Owner::O:
    setText("O");
    break;
  }
}

void GridButton::HandleCellAssigned(const Owner owner) { SetGridOwner(owner); }

void GridButton::HandleClicked() { emit CellClicked(Row, Col); }
