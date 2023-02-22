#include "rain.h"
#include <QTimer>

Rain::Rain()
{

}

void Rain::setA(double a){ _a = a;}

void Rain::drawRain(QPainter &painter, int height)
{
    for(auto iter = _bufRain.begin(); iter != _bufRain.end(); iter++)
    {
        painter.drawLine((*iter).x(), (*iter).y(), (*iter).x() + 15 * (_a), (*iter).y() + 15 );
        if ((*iter).y() + 15 >= height - 100)
            _bufRain.erase(iter);
    }
    painter.end();
}

void Rain::generateRain(int width, bool flag)
{
    int size = _bufRain.size();
    for(int i = 0; i < size; i++)
        _bufRain[i] += 15 * QVector2D(_a, 1);

    if (flag)
        for (int i = 0; i < width / 50; i++)
        {
            _bufRain.push_back(QVector2D(rand()%width, 0));
            if (_a > 0 && rand()%10 == 0)
                _bufRain.push_back(QVector2D(0, rand()%(1 + (int)_bufRain[0].y())));
            if (_a < 0 && rand()%10 == 0)
                _bufRain.push_back(QVector2D(width, rand()%(1 + (int)_bufRain[0].y())));
        }
}
