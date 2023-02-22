#include "model.h"
#include <QVector3D>

Model::Model() {}

Model::Model(std::vector<Polygon> polygons)
    : _polygons(polygons) {}

std::vector<Polygon> Model::getPolygons() { return _polygons; }

void Model::initPyramid() {
  _polygons =  {Polygon(QVector3D(300, 200, 20), QVector3D(400, 200, 400), QVector3D(470, 100, 40)),
                Polygon(QVector3D(400, 200, 400),QVector3D(470, 100, 40), QVector3D(400, 500, 400)),
                Polygon(QVector3D(300, 200, 20), QVector3D(470, 100, 40), QVector3D(400, 500, 400)),
                Polygon(QVector3D(300, 200, 20), QVector3D(400, 200, 400), QVector3D(400, 500, 400))};
}

void Model::initGround(int width, int height)
{
    _polygons =  {
                  Polygon(QVector3D(-width, height - 400, -1000), QVector3D(2*width, height - 400,  -1000), QVector3D(-width, height + 400, 1000)),
                  Polygon(QVector3D(2*width, height - 400,  -1000), QVector3D(-width, height + 400, 1000), QVector3D(2*width, height + 400, 1000))};

}
