#include "myglwidget.h"
#include "painter.h"
#include <QPainter>
#include <top.h>
#include <line.h>
#include <QMouseEvent>
#include "value.h"
extern QVector<TOP> graph1;
extern QVector<Line> graph2;
extern QVector <QVector<int>> matrix;
extern int len;
extern int mem_x;
extern int mem_y;
extern int mem_num;
extern int s;
extern QString text_for_arrows;

myGLWidget::myGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    mypainter=new Painter;
}

void myGLWidget::mousePressEvent(QMouseEvent *event)
{

    int m;
    if (s==0)
    {
        TOP a(event->x(),event->y());
        graph1.push_back(a);
        len++;
        QVector <int> row(len);
        row.fill(0);
        matrix.append(row);
        for (int i=0;i<len-1;i++) matrix[i].append(0);
    }
    else if (s==1 || s==2)
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                mem_x=x2;
                mem_y=y2;
                mem_num=i;
                s=(s==1)? 6:7;
                break;
            }
        }
    }
    else if (s==6 || s==7)
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                if (s==6)
                {
                    Value wind;
                    wind.setModal(true);
                    wind.exec();
                    m=text_for_arrows.toInt();
                    Line a(mem_x,mem_y,x2,y2,1,m);
                    graph2.push_back(a);
                    matrix[mem_num][i]=m;
                    matrix[i][mem_num]=m;
                }
                else
                {
                    Value wind;
                    wind.setModal(true);
                    wind.exec();
                    m=text_for_arrows.toInt();
                    Line a(mem_x,mem_y,x2,y2,2,m);
                    graph2.push_back(a);
                    //matrix
                    matrix[mem_num][i]=m;
                }
                s=(s==6)? 1:2;
                break;
            }
        }
    }
    else if (s==3)
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                graph1[i].flagg=true;
                break;
            }
        }
    }
    else if (s==4)
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=graph1[i].x;
            int y2=graph1[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1600)
            {
                QVector<Line> graph2_new;
                for (int j=0;j<graph2.size();j++)
                {
                    if (!(graph2[j].x1==graph1[i].x && graph2[j].y1==graph1[i].y)
                       && !(graph2[j].x2==graph1[i].x && graph2[j].y2==graph1[i].y))
                    {
                        graph2_new.push_back(graph2[j]);
                    }
                }
                graph2=graph2_new;
                graph1.erase(graph1.begin()+i);
                len--;
                for (int j=0;j<len;j++) matrix[j].erase(matrix[j].begin()+i);
                matrix.erase(matrix.begin()+i);
                break;
            }
        }
    }
    redraw();
}
void myGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (s==3)
        for (int i=0;i<len;i++)
            graph1[i].flagg=false;
    redraw();
}
void myGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (s==3)
    {
        for (int i=0;i<len;i++)
        {
            if (graph1[i].flagg)
            {
                for (int j=0;j<graph2.size();j++)
                {
                    if (graph2[j].x1==graph1[i].x && graph2[j].y1==graph1[i].y)
                    {
                        graph2[j].x1=event->x();
                        graph2[j].y1=event->y();
                    }
                    if (graph2[j].x2==graph1[i].x && graph2[j].y2==graph1[i].y)
                    {
                        graph2[j].x2=event->x();
                        graph2[j].y2=event->y();
                    }
                }
                graph1[i].x=event->x();
                graph1[i].y=event->y();
                break;
            }
        }
    }
    redraw();
}

void myGLWidget::redraw()
{
    this->update();
}
void myGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    mypainter->Draw(&painter,event);
    painter.end();
}
