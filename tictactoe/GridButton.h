#pragma once

#include "common.h"
#include <QPushButton>

namespace ttt {
class GridButton : public QPushButton {
  Q_OBJECT

public:
  explicit GridButton(const int row, const int col, QWidget *parent = nullptr);
  ~GridButton();

  Owner GetOwner() const;
  void SetGridOwner(const Owner owner);

public slots:
  void Reset();
  void HandleCellAssigned(const Owner owner);

signals:
  void CellClicked(const int row, const int col);

private slots:
  void HandleClicked();

private:
  Owner TheOwner;
  int Row;
  int Col;
};
} // namespace ttt
