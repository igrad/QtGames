#pragma once

#include "common.h"

#include <QMap>
#include <QObject>

namespace ttt {
enum class Owner : int { None, O, X };

constexpr bool operator==(Owner owner, Team team) {
  return (owner == Owner::O && team == Team::O) ||
         (owner == Owner::X && team == Team::X);
}

constexpr bool operator!=(const Owner owner, const Team team) {
  return !(owner == team);
}

class Board : public QObject {
  Q_OBJECT
public:
  explicit Board(QObject *parent = nullptr);
  ~Board();

  void ResetBoard();

  const Owner GetGridOwner(const int row, int col) const;
  bool SetGridOwner(const int row, const int col, const Owner owner);

signals:
  void GameOver(const Team winner);

private:
  bool CheckForRowCompletion(const int row, const Team team) const;
  bool CheckForColCompletion(const int col, const Team team) const;
  bool CheckForDiagCompletion(const Team team) const;
  void CheckForGameCompletion(const int lastMoveRow, const int lastMoveCol,
                              const Team lastMoveTeam);

  Owner Grid[3][3];
};
} // namespace ttt
