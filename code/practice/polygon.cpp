#include "polygon.h"

Polygon::Polygon() {}

Polygon::Polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
}

Polygon::Polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c, QColor &col) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
    _c = col;
}

QVector3D* Polygon::points() { return _points; }

QColor Polygon::color() {return _c;}
