#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <QMessageBox>
#include <QtGui>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    void pic_upd();

private slots:
    void num_Operations();
    void digits();
    void on_BtnDelOne_clicked();
    void on_BtnClearAll_clicked();
    void on_BtnDot_clicked();
    void on_BtnPM_clicked();
    void on_BtnDo_clicked();
    void on_BtnPP_clicked();
    bool checkOP();
    void update1();
    void on_BtnMode_clicked();
    void on_BtnCtg_clicked();
    void on_BtnTg_clicked();
    void on_BtnCos_clicked();
    void on_BtnSin_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
