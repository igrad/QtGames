#pragma once

#include "Board.h"
#include "MainWindow.h"
#include "common.h"

#include <QObject>

namespace ttt {
class GameManager : public QObject {
  Q_OBJECT

public:
  GameManager(MainWindow *mainWindow, QObject *parent = nullptr);
  ~GameManager();

signals:
  void TurnChanged(const Team team);
  void CellAssigned(const int row, const int col, const Owner owner);

private slots:
  void HandleCellAssigned(const int row, const int col, const Owner owner);

private:
  Team CurrentTurn;
  Board TheBoard;
};
} // namespace ttt
