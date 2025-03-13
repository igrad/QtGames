#include "GameManager.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  ttt::GameManager game(&app);
  std::cout << "Hello world!" << std::endl;
  return 0;
}
