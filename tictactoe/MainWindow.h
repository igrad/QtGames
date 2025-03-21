#pragma once

#include "GridButton.h"
#include <QMainWindow>

#include "common.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedLayout>

namespace ttt {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

signals:
  void CellClicked(const int row, const int col);
  void GameOverClicked();

public slots:
  void HandleCellAssigned(const int row, const int col, const Owner owner);
  void HandleGameOver(const Owner winner);

private slots:
  void HandleGameOverClicked();

private:
  void BuildGrid();
  void ResetGrid();

  QWidget CentralWidget;
  QStackedLayout MainLayout;
  QPushButton GameOverButton;
  QWidget GridWidget;
  QGridLayout GridLayout;
  GridButton *GridButtons[3][3];
  QLabel VictoryLabel;
  QVBoxLayout VictoryLayout;
};
} // namespace ttt
