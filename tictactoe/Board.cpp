#include "Board.h"

using namespace ttt;

Board::Board(QObject *parent) : QObject(parent), CurrentTeam(Team::O) {
  ResetBoard();
}

Board::~Board() {}

void Board::ResetBoard() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      Grid[row][col] = Owner::None;
    }
  }
}

const Owner Board::GetGridOwner(const int row, const int col) const {
  if (row < 3 && col < 3) {
    return Grid[row][col];
  } else {
    return Owner::None;
  }
}

bool Board::SetGridOwner(const int row, const int col, const Owner owner) {
  bool retVal = false;
  if (row < 3 && col < 3) {
    if (GetGridOwner(row, col) == Owner::None) {
      Grid[row][col] = owner;
      retVal = true;
    }
  }

  return retVal;
}

void Board::HandleTurnChanged(const Team team) { CurrentTeam = team; }

void Board::HandleCellClicked(const int row, const int col) {
  if (SetGridOwner(row, col, ToOwner(CurrentTeam))) {
    Grid[row][col] = ToOwner(CurrentTeam);
    emit CellAssigned(row, col, ToOwner(CurrentTeam));
  }
}

void Board::HandleGameOverClicked() { ResetBoard(); }

bool Board::CheckForRowCompletion(const int row, const Team team) const {
  bool complete = true;
  for (int col = 0; col < 3; ++col) {
    if (GetGridOwner(row, col) != team) {
      complete = false;
      break;
    }
  }

  return complete;
}

bool Board::CheckForColCompletion(const int col, const Team team) const {
  bool complete = true;
  for (int row = 0; row < 3; ++row) {
    if (GetGridOwner(row, col) != team) {
      complete = false;
      break;
    }
  }

  return complete;
}

bool Board::CheckForDiagCompletion(const Team team) const {
  if (GetGridOwner(1, 1) == team) {
    return (GetGridOwner(0, 0) == team && GetGridOwner(2, 2) == team) ||
           (GetGridOwner(0, 2) == team && GetGridOwner(2, 0) == team);
  } else
    return false;
}

bool Board::CheckForStalemate() const {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (GetGridOwner(row, col) == Owner::None)
        return false;
    }
  }

  return true;
}

void Board::CheckForGameCompletion(const int lastMoveRow, const int lastMoveCol,
                                   const Team lastMoveTeam) {
  if (CheckForRowCompletion(lastMoveRow, lastMoveTeam) ||
      CheckForColCompletion(lastMoveCol, lastMoveTeam) ||
      CheckForDiagCompletion(lastMoveTeam)) {
    emit GameOver(ToOwner(lastMoveTeam));
  } else if (CheckForStalemate()) {
    emit GameOver(Owner::None);
  }
}
