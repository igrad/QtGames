#include "GameManager.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  ttt::MainWindow mainWindow;
  ttt::GameManager game(&mainWindow, &app);

  mainWindow.show();
  return app.exec();
}
