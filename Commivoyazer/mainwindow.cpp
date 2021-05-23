#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
extern int s;
extern QVector <QVector<int>> matrix;
extern int len;
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClearAll()
{
    s = 3;
    ui->BtnAdd->setChecked(false);
    ui->BtnDel->setChecked(false);
    ui->BtnAddPath->setChecked(false);
    ui->BtnAddPath2->setChecked(false);
}


void MainWindow::on_BtnAdd_clicked()
{
    if (ui->BtnAdd->isChecked())
    {
        ClearAll();
        s = 0;
        ui->BtnAdd->setChecked(true);
    }
    else
    {
        s = 3;
        ui->BtnAdd->setChecked(false);
    }

}


void MainWindow::on_BtnDel_clicked()
{
    if (ui->BtnDel->isChecked())
    {
        ClearAll();
        s = 4;
        ui->BtnDel->setChecked(true);   
    }
    else
    {
        s = 3;
        ui->BtnDel->setChecked(false);
    }
}


void MainWindow::on_BtnAddPath_clicked()
{
    if (ui->BtnAddPath->isChecked())
    {
        ClearAll();
        s = 1;
        ui->BtnAddPath->setChecked(true);
    }
    else
    {
        s = 3;
        ui->BtnAddPath->setChecked(false);
    }
}


void MainWindow::on_BtnAddPath2_clicked()
{

    if (ui->BtnAddPath2->isChecked())
    {
        ClearAll();
        s = 2;
        ui->BtnAddPath2->setChecked(true);
    }
    else
    {
        s = 3;
        ui->BtnAddPath2->setChecked(false);
    }
}


void MainWindow::on_BtnDo_clicked()
{
    int max = 1000;
    ClearAll();
    QVector <int> result_arr_1;
    QVector <int> result_arr_2;
    int minG=0;
    bool flag=true;
    QVector <QVector<int>> data=matrix;
    for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (i==k || data[i][k]==0) data[i][k]=max;
    while (flag)
    {
        QVector <int> row(len);
        row.fill(max);
        QVector <int> column(len);
        column.fill(max);
        for (int i=0;i<len;i++)
            for (int k=0;k<len;k++)
                row[i]=qMin(row[i],data[i][k]);
        for (int i=0;i<len;i++)
            for (int k=0;k<len;k++)
                if (row[i]!=max && data[i][k]!=max)
                    data[i][k]-=row[i];
        for (int i=0;i<len;i++)
            for (int k=0;k<len;k++)
                column[k]=qMin(column[k],data[i][k]);
        for (int i=0;i<len;i++)
            for (int k=0;k<len;k++)
                if (column[k]!=max && data[i][k]!=max)
                    data[i][k]-=column[k];
        int max_mark_x;
        int max_mark_y;
        int max_mark=-1;
        for (int i=0;i<len;i++)
            for (int k=0;k<len;k++)
                if (data[i][k]==0)
        {
            int min1=max;
            int min2=max;
            for (int j=0;j<len;j++)
                if (j!=k)
                    min1=qMin(min1,data[i][j]);
            for (int j=0;j<len;j++)
                if (j!=i)
                    min2=qMin(min2,data[j][k]);
            if (min1==max || min2==max || min1+min2>max_mark)
            {
                max_mark=min1+min2;
                max_mark_x=i;
                max_mark_y=k;
            }
        }
        minG+=matrix[max_mark_x][max_mark_y];
        data[max_mark_y][max_mark_x]=max;
        for (int i=0;i<len;i++)
        {
            data[max_mark_x][i]=max;
            data[i][max_mark_y]=max;
        }
        result_arr_1.push_back(max_mark_x+1);
        result_arr_2.push_back(max_mark_y+1);
        flag=false;
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]!=max) flag=true;
    }
    QString result=">"+QString::number(result_arr_1[0]-1)+">"+QString::number(result_arr_2[0]-1);
    int x=result_arr_2[0];
    result_arr_1.erase(result_arr_1.begin());
    result_arr_2.erase(result_arr_2.begin());
    while (result_arr_1.size()!=0)
    {
        for (int i=0;i<result_arr_1.size();i++) if (result_arr_1[i]==x)
        {
            result+=">"+QString::number(result_arr_2[i]-1);
            x=result_arr_2[i];
            result_arr_1.erase(result_arr_1.begin()+i);
            result_arr_2.erase(result_arr_2.begin()+i);
            break;
        }
    }
    result[0]=' ';

    result+=" Длинна пути: "+QString::number(minG);
    QMessageBox::about(this, "Решение",result);
}
