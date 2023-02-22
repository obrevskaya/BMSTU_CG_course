#include "lightning.h"
#include <QVector2D>

#define MIN_DIST 15

Lightning::Lightning()
{

}

void Lightning::generateLightning(QPoint &point1, QPoint &point2)
{
    srand(time (NULL));
    _branches.clear();
    int mx_var = sqrt((point1.x() - point2.x()) * (point1.x() - point2.x())
                      + (point1.y() - point2.y()) * (point1.y() - point2.y())) / 2;
    if (mx_var < MIN_DIST) mx_var = 15;

    _branches.push_back(line_t{point1, point2});


    int k = 3 + rand() % 8;
    for(int i = 0; i < k && i < _branches.size(); i++)
    {
        QVector2D p1 = QVector2D(_branches[i].p1.x(), _branches[i].p1.y());
        QVector2D p2 = QVector2D(_branches[i].p2.x(), _branches[i].p2.y());

        _branches.erase(_branches.begin() + i);

        QVector2D mid = (p1 + p2) / 2;
        if ((mid - p1).length() < MIN_DIST)
        {
            _branches.push_back({QPoint(p1.x(), p1.y()), QPoint(p2.x(), p2.y())});
            break;
        }


        QVector2D N(p2.y() - p1.y(), -(p2.x() - p1.x()));
        N.normalize();

        bool flag = rand()%2;
        if (flag)
        {
            mid += N * (7 + rand()%5);
            QVector2D newPoint(mid.x() + 2 + rand()%80, mid.y() + 2 + rand()%80);
            _branches.push_back({QPoint(newPoint.x(), newPoint.y()), QPoint(mid.x(), mid.y())});
        }
        else mid -= N * (7 + rand()%5);


        _branches.push_back({QPoint(p1.x(), p1.y()), QPoint(mid.x(), mid.y())});
        _branches.push_back({QPoint(mid.x(), mid.y()), QPoint(p2.x(), p2.y())});

        if ((mid - p1).length() < 3 * MIN_DIST) continue;

        i--;
    }
}

void Lightning::drawLightning(QPainter &painter)
{
    for(auto iter = _branches.begin(); iter != _branches.end(); iter++)
        painter.drawLine((*iter).p1, (*iter).p2);
}
