#include "GameManager.h"

using namespace ttt;

GameManager::GameManager(QObject *parent)
    : CurrentTurn(Team::O), TheBoard(this) {}

GameManager::~GameManager() {}

void GameManager::SetTurn(const Team team) { CurrentTurn = team; }
