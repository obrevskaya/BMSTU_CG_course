#include "mainwindow.h"
#include "drawer.h"
#include "lightsource.h"
#include "lightning.h"
#include "model.h"
#include "rain.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QPainter>
#include <unistd.h>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QGraphicsScene *scene = new QGraphicsScene();
  ui->graphicsView->setScene(scene);
  ui->graphicsView->scene()->clear();

}

MainWindow::~MainWindow() {
  delete ui->graphicsView->scene();
  delete ui;
}

void MainWindow::set_flag() { flag = true; }

void MainWindow::on_drawButton_clicked() {
  s.setSize(ui->graphicsView->width(), ui->graphicsView->height());

  if(s.getLight().size() == 0)
  {
      LightSource ls = LightSource({600, 1000, 2000}, 0.9);
      s.addLight(ls);
  }

  _image = s.draw();
  QPixmap pixmap = QPixmap::fromImage(*_image);
  ui->graphicsView->scene()->addPixmap(pixmap);
  if (flag)
    _image->save("img.png", "PNG");
}

void MainWindow::on_loadButton_clicked()
{
    auto filename = QFileDialog::getOpenFileName();
    if (filename.isEmpty())
        return;

    QByteArray ba = filename.toLocal8Bit();
    const char *c_str = ba.data();
    if(!s.loadFile(c_str))
        return;
}

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_lightningButton_clicked()
{
    srand(time (NULL));
    int min = 10;
    int max = 250;

    lightningFlag = true;
    if (rainFlag) return;

    s.setSize(ui->graphicsView->width(), ui->graphicsView->height());

    if(s.getLight().size() == 0)
    {
        LightSource ls = LightSource({600, 1000, 2000}, 0.9);
        s.addLight(ls);
    }
    _image = s.draw();
    QPixmap pixmap1 = QPixmap::fromImage(*_image);
    ui->graphicsView->scene()->addPixmap(pixmap1);

    Lightning lightning;

    while(lightningFlag)
    {
        if (rainFlag) break;
        QPainter painter(_image.get());
        painter.setPen(QPen(QColor(247, 255, 165), 2));

        int x = min + rand() % (ui->graphicsView->width() - min + 1);
        int y = min + rand() % (max - min + 1);
        QPoint p1(x, y);
        QPoint p2(min + rand() % (ui->graphicsView->width() - min + 1), min + rand() % (max - min + 1));

        lightning.generateLightning(p1, p2);
        lightning.drawLightning(painter);
        painter.end();

        QPixmap pixmap = QPixmap::fromImage(*_image);
        ui->graphicsView->scene()->addPixmap(pixmap);

        delay(1);
        _image = s.draw();
        QPixmap pixmap1 = QPixmap::fromImage(*_image);
        ui->graphicsView->scene()->addPixmap(pixmap1);
    }
}

void MainWindow::on_stopLightningButton_clicked()
{
    lightningFlag = false;
}

void MainWindow::on_rainButton_clicked()
{
    rainFlag = true;

    rn.setA(ui->doubleSpinBoxA->value());

    int min = 10;
    int max = 250;
    srand(time (NULL));

    s.setSize(ui->graphicsView->width(), ui->graphicsView->height());
    if(s.getLight().size() == 0)
    {
        LightSource ls = LightSource({600, 1000, 2000}, 0.9);
        s.addLight(ls);
    }
    _image = s.draw();
    QPixmap pixmap1 = QPixmap::fromImage(*_image);
    ui->graphicsView->scene()->addPixmap(pixmap1);




    while(1)
    {


        if (lightningFlag)
        {
            int x = min + rand() % (ui->graphicsView->width() - min + 1);
            int y = min + rand() % (max - min + 1);
            QPoint p1(x, y);
            QPoint p2(min + rand() % (ui->graphicsView->width() - min + 1), min + rand() % (max - min + 1));


            QPainter painter1(_image.get());
            painter1.setPen(QPen(QColor(247, 255, 165), 2));
            Lightning lightning;
            lightning.generateLightning(p1, p2);
            lightning.drawLightning(painter1);
            painter1.end();

            QPixmap pixmap2 = QPixmap::fromImage(*_image);
            ui->graphicsView->scene()->addPixmap(pixmap2);
        }



        QPainter painter(_image.get());
        painter.setPen(QPen(QColor(204, 255, 255), 2));



        rn.generateRain(ui->graphicsView->width(), rainFlag);
        if(clearFlag)
        {
            clearFlag = false;
            painter.end();
            break;
        }
        rn.drawRain(painter, ui->graphicsView->height());

        QPixmap pixmap = QPixmap::fromImage(*_image);
        ui->graphicsView->scene()->addPixmap(pixmap);

        delay(1);



        _image = s.draw();
        QPixmap pixmap1 = QPixmap::fromImage(*_image);
        ui->graphicsView->scene()->addPixmap(pixmap1);
    }


}

void MainWindow::on_stopRainButton_clicked()
{
    rainFlag = false;
}

void MainWindow::on_clearButton_clicked()
{
    lightningFlag = false;
    rainFlag = false;
    clearFlag = true;
    s.deleteModels();
    s.deleteLights();
    s.draw();
}




void MainWindow::on_addLightButton_clicked()
{
    LightSource l = LightSource(QVector3D(ui->doubleSpinBoxX->value(),
                                          ui->doubleSpinBoxY->value(), ui->doubleSpinBoxZ->value()), 0.9);
    s.addLight(l);
}

