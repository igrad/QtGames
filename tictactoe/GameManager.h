#pragma once

#include "Board.h"
#include "common.h"

#include <QObject>

namespace ttt {
class GameManager : public QObject {
  Q_OBJECT
public:
  GameManager(QObject *parent = nullptr);
  ~GameManager();

  void SetTurn(const Team team);

private:
  Team CurrentTurn;
  Board TheBoard;
};
} // namespace ttt
