#ifndef MODEL_H
#define MODEL_H

#include "polygon.h"
#include <QColor>
#include <QPoint>
#include <QVector3D>

class Model {
public:
  Model();
  Model(std::vector<Polygon> polygons);

  std::vector<Polygon> getPolygons();
  void initPyramid();
  void initGround(int width, int height);

private:
  std::vector<Polygon> _polygons;
};

#endif // MODEL_H
