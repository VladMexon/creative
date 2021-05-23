#ifndef PAINTER_H
#define PAINTER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class Painter
{
public:
    Painter();
public:
    void Draw(QPainter *painter, QPaintEvent *event);
    void DrawLine(int x1,int y1,int x2,int y2, int type,QPainter *painter,QString text);
    void DrawTop(int x,int y,QString text,QPainter *painter );
    QBrush front;
private:
    QBrush back;
    QFont glFont;
    QPen textPen;
};

#endif //PAINTER_H
