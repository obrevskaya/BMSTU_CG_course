#ifndef DRAWER_H
#define DRAWER_H

#include "lightsource.h"
#include "model.h"
#include "zbuffer.h"
#include <QImage>

#define HEIGHT_SCREEN 820
#define WIDTH_SCREEN 1296

class Drawer {
public:
  Drawer();
  Drawer(std::vector<LightSource> lightSources,
         std::vector<Model> models, int canvasHeight, int canvasWidth);

  std::vector<LightSource> getLight();
  void deleteModels();
  void deleteLights();
  void addModel(Model &m);
  void addLight(LightSource &l);
  void setSize(size_t width, size_t height);

  bool loadFile(const char* filename);

  std::shared_ptr<QImage> draw();

private:
  std::vector<LightSource> _lightSources;
  std::vector<Model> _models;
  int _canvasHeight;
  int _canvasWidth;
  ZBuffer zb;
};

#endif // DRAWER_H
