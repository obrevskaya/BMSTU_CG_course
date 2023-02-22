#include "lightsource.h"

LightSource::LightSource() {}

LightSource::LightSource(QVector3D pos, double intensity)
    : _pos(pos), _intens(intensity) {}

QVector3D LightSource::getPos() { return _pos; }

double LightSource::getIntensity() { return _intens; }
