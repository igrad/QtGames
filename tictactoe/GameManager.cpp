#include "GameManager.h"

using namespace ttt;

GameManager::GameManager(MainWindow *mainWindow, QObject *parent)
    : CurrentTurn(Team::O), TheBoard(this) {
  connect(mainWindow, &MainWindow::CellClicked, &TheBoard,
          &Board::HandleCellClicked);
  connect(&TheBoard, &Board::CellAssigned, this,
          &GameManager::HandleCellAssigned);
  connect(this, &GameManager::CellAssigned, mainWindow,
          &MainWindow::HandleCellAssigned);
  connect(this, &GameManager::TurnChanged, &TheBoard,
          &Board::HandleTurnChanged);
  connect(&TheBoard, &Board::GameOver, mainWindow, &MainWindow::HandleGameOver);
  connect(mainWindow, &MainWindow::GameOverClicked, &TheBoard,
          &Board::HandleGameOverClicked);
}

GameManager::~GameManager() {}

void GameManager::HandleCellAssigned(const int row, const int col,
                                     const Owner owner) {
  CurrentTurn = (owner == Owner::O) ? Team::X : Team::O;
  emit TurnChanged(CurrentTurn);
  emit CellAssigned(row, col, owner);

  TheBoard.CheckForGameCompletion(row, col, ToTeam(owner));
}
