#ifndef RAIN_H
#define RAIN_H

#include <QTimer>
#include <QVector2D>
#include <QPainter>

class Rain
{
public:
    Rain();
    void generateRain(int width, bool flag);
    void drawRain(QPainter &painter, int height);
    void setA(double a);
private:
    std::vector<QVector2D> _bufRain;
    double _a = -0.6;

};

#endif // RAIN_H
