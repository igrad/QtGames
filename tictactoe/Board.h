#pragma once

#include "common.h"

#include <QMap>
#include <QObject>

namespace ttt {

class Board : public QObject {
  Q_OBJECT
public:
  explicit Board(QObject *parent = nullptr);
  ~Board();

  void ResetBoard();

  const Owner GetGridOwner(const int row, int col) const;
  bool SetGridOwner(const int row, const int col, const Owner owner);
  void CheckForGameCompletion(const int lastMoveRow, const int lastMoveCol,
                              const Team lastMoveTeam);

public slots:
  void HandleTurnChanged(const Team team);
  void HandleCellClicked(const int row, const int col);
  void HandleGameOverClicked();

signals:
  void GameOver(const Owner winner);
  void CellAssigned(const int row, const int col, const Owner owner);

private:
  bool CheckForRowCompletion(const int row, const Team team) const;
  bool CheckForColCompletion(const int col, const Team team) const;
  bool CheckForDiagCompletion(const Team team) const;
  bool CheckForStalemate() const;

  Team CurrentTeam;
  Owner Grid[3][3];
};
} // namespace ttt
