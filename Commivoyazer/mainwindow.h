#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "myglwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QButtonGroup>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ClearAll();
private slots:
    void on_BtnAdd_clicked();
    void on_BtnDel_clicked();
    void on_BtnAddPath_clicked();
    void on_BtnAddPath2_clicked();
    void on_BtnDo_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
