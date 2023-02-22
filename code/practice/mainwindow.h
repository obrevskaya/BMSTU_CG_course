#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawer.h"
#include "rain.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void set_flag();

public slots:
  void on_drawButton_clicked();

private slots:
  void on_loadButton_clicked();

  void on_lightningButton_clicked();

  void on_stopLightningButton_clicked();

  void on_stopRainButton_clicked();

  void on_rainButton_clicked();

  void on_clearButton_clicked();

  void on_doubleSpinBox_editingFinished();

  void on_addLightButton_clicked();

private:
  Ui::MainWindow *ui;
  Drawer s;
  bool flag = false;
  bool lightningFlag = false;
  bool rainFlag = false;
  bool clearFlag = false;
  Rain rn;
  std::shared_ptr<QImage> _image;

};
#endif // MAINWINDOW_H
