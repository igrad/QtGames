#include "Board.h"

using namespace ttt;

Board::Board(QObject *parent) : Grid() { ResetBoard(); }

Board::~Board() {}

void Board::ResetBoard() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; row < 3; ++row) {
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

void Board::CheckForGameCompletion(const int lastMoveRow, const int lastMoveCol,
                                   const Team lastMoveTeam) {
  if (CheckForRowCompletion(lastMoveRow, lastMoveTeam) ||
      CheckForColCompletion(lastMoveCol, lastMoveTeam) ||
      CheckForDiagCompletion(lastMoveTeam)) {
    emit GameOver(lastMoveTeam);
  }
}
