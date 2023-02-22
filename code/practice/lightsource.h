#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QColor>
#include <QVector3D>

class LightSource {
public:
  LightSource();
  LightSource(QVector3D pos, double intensity);

  QVector3D getPos();
  double getIntensity();

private:
  QVector3D _pos;
  double _intens;
};

#endif // LIGHTSOURCE_H
