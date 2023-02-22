#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "lightsource.h"
#include "model.h"
#include <QColor>
#include <vector>
struct Cell {
  double z;
  QColor c;
};

class ZBuffer {
public:
  ZBuffer(size_t x, size_t y);
  ZBuffer();
  ~ZBuffer();

  size_t sX();
  size_t sY();
  QColor getColorCell(int x, int y);
  void setSize(size_t x, size_t y);

  void putModels(std::vector<Model> &models, std::vector<LightSource> &ls);
  void putPolygon(std::vector<QVector3D> &points, std::vector<LightSource> &ls,
                  QColor c, std::vector<std::vector<std::vector<double>>> &shadows);

  void show(QPainter &painter);


private:
  size_t _sX, _sY;
  std::vector<std::vector<Cell>> _buf;
};



#endif // ZBUFFER_H
