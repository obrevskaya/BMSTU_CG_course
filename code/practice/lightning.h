#ifndef LIGHTNING_H
#define LIGHTNING_H
#include <QPoint>
#include <QPainter>

typedef struct
{
    QPoint p1;
    QPoint p2;
} line_t;

class Lightning
{
public:
    Lightning();
    void generateLightning(QPoint &p1, QPoint &p2);
    void drawLightning(QPainter &painter);
private:
    std::vector<line_t> _branches;
};

#endif // LIGHTNING_H
