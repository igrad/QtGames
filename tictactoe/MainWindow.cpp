#include "MainWindow.h"
#include "GridButton.h"

using namespace ttt;

MainWindow::MainWindow() {
  setCentralWidget(&CentralWidget);
  CentralWidget.setLayout(&MainLayout);

  GridWidget.setLayout(&GridLayout);
  MainLayout.addWidget(&GridWidget);

  MainLayout.addWidget(&GameOverButton);

  connect(&GameOverButton, &QPushButton::clicked, this,
          &MainWindow::HandleGameOverClicked);

  BuildGrid();
}

MainWindow::~MainWindow() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      delete GridButtons[row][col];
    }
  }
}

void MainWindow::HandleCellAssigned(const int row, const int col,
                                    const Owner owner) {
  GridButtons[row][col]->HandleCellAssigned(owner);
}

void MainWindow::HandleGameOver(const Owner winner) {
  if (winner == Owner::None) {
    GameOverButton.setText("Stalemate!");
  } else {
    GameOverButton.setText(ToString(winner) + " has won!");
  }

  MainLayout.setCurrentWidget(&GameOverButton);
}

void MainWindow::HandleGameOverClicked() {
  ResetGrid();

  MainLayout.setCurrentWidget(&GridWidget);

  emit GameOverClicked();
}

void MainWindow::BuildGrid() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      GridButton *newBtn = new GridButton(row, col);
      GridButtons[row][col] = newBtn;
      GridLayout.addWidget(newBtn, row, col);
      connect(newBtn, &GridButton::CellClicked, this, &MainWindow::CellClicked);
    }
  }
}

void MainWindow::ResetGrid() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      GridButtons[row][col]->Reset();
    }
  }
}
