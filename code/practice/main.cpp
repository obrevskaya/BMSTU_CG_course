#include "drawer.h"
#include "lightsource.h"
#include "mainwindow.h"
#include "model.h"
#include "polygon.h"
#include "ui_mainwindow.h"
#include "zbuffer.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  if (argc == 2 && strcmp(argv[1], "-im") == 0) {
    w.show();
    w.set_flag();
    w.on_drawButton_clicked();
    return EXIT_SUCCESS;
  }

  w.show();
  return a.exec();
}
