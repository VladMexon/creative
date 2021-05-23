#include "mainwindow.h"
#include "top.h"
#include "line.h"
#include <QApplication>
#include <QLineEdit>
int s = 3;
int len=0;
int mem_x;
int mem_y;
int mem_num;
QVector <TOP> graph1;
QVector <Line> graph2;
QVector <QVector<int>> matrix;
QString text_for_arrows;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
