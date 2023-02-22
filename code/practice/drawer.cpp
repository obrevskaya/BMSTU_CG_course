#include "drawer.h"
#include "zbuffer.h"
#include <QPainter>
#include <QVector3D>
#include <iostream>
#include <fstream>
#include <sstream>

Drawer::Drawer() {}

Drawer::Drawer(std::vector<LightSource> lightSources, std::vector<Model> models,
               int canvasHeight, int canvasWidth)
    : _lightSources(lightSources), _models(models), _canvasHeight(canvasHeight), _canvasWidth(canvasWidth)
       {}

std::vector<LightSource> Drawer::getLight(){ return _lightSources;}

void Drawer::addModel(Model &m)
{
    _models.push_back(m);
}

void Drawer::deleteModels()
{
    _models.clear();
}

void Drawer::deleteLights()
{
    _lightSources.clear();
}

void Drawer::addLight(LightSource &l)
{
    _lightSources.push_back(l);
}

void Drawer::setSize(size_t width, size_t height)
{
    _canvasHeight = height;
    _canvasWidth = width;
}


void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    // строим поток из строки
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void add_polygons(std::vector<Polygon> &polygons, std::vector<QVector3D> &verticies,
                  const std::vector<std::string> &out, QColor color)
{
    int a[3];
    for (size_t i = 1; i < out.size(); i++)
    {
        std::vector<std::string> edg;
        tokenize(out[i], '/', edg);
        a[i - 1] = std::stoi(edg[0]) - 1;
    }
    polygons.push_back(Polygon(verticies[a[0]], verticies[a[1]], verticies[a[2]], color));
}

bool Drawer::loadFile(const char* filename)
{
    std::vector<Polygon> polygons;
    std::ifstream f ;
    f.open(filename);

    if (!f.is_open())
    {
        std::cout << "Ошибка открытия файла\n\n";
        return 0;
    }

    std::cout << "Файл успешно открыт\n\n";


    std::vector<QVector3D> verticies;
    std::string s;
    int flag = 0;
    QColor color;
    while(getline(f, s)){ // пока не достигнут конец файла класть очередную строку в переменную (s)
        std::vector<std::string> out;
        tokenize(s, ' ', out);
        if (out[0] == "o")
        {
            if (out[1] == "house" || out[1] == "small_house") color = QColor(124,95,27);
            if (out[1] == "trunk" || out[1] == "small_trunk") color = QColor(196,158,39);
            if (out[1] == "fir" || out[1] == "small_fir") color = QColor(13,125,39);
            if (out[1] == "leaf" || out[1] == "small_leaf" || out[1] == "extra_leaf") color = QColor(125,222,95);
            if(out[1] == "ground") color = QColor(68,129,50);
            if(out[1] == "dog") color = QColor(204,204,153);
            if(out[1] == "cow") color = QColor(219,131,29);
            if (flag)
                _models.push_back(Model(polygons));
            flag++;
        }

        if (out[0] == "v")
            verticies.push_back(QVector3D(stod(out[1]), stod(out[2]), stod(out[3])));
        if (out[0] == "f"){
            add_polygons(polygons, verticies, out, color);
        }
    }
    _models.push_back(Model(polygons));
    f.close();
    return 1;
}



std::shared_ptr<QImage> Drawer::draw() {
  std::shared_ptr<QImage> image = std::make_shared<QImage>(
      _canvasWidth, _canvasHeight, QImage::Format_RGB32);
  QPainter painter(image.get());
  image->fill(Qt::black);


  zb.setSize(_canvasWidth, _canvasHeight);



  zb.putModels(_models, _lightSources);
  zb.show(painter);

  painter.end();
  return image;
}
