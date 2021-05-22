#include "mainwindow.h"
#include "ui_mainwindow.h"

QString deist;

QString FirstNumber = "";
QString SecondNumber = "";
QString ThridNumber = "";

QString FirstN = "";
QString SecondN = "";
QString ThridN = "";

QString tmp_des;

const float pi = 3.14159265359;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QWidget::setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    connect(ui->Btn0, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn1, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn2, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn3, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn4, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn5, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn6, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn7, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn8, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->Btn9, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->BtnPlus, SIGNAL(clicked()), this, SLOT(num_Operations()));
    connect(ui->BtnMinus, SIGNAL(clicked()), this, SLOT(num_Operations()));
    connect(ui->BtnDevide, SIGNAL(clicked()), this, SLOT(num_Operations()));
    connect(ui->BtnMult, SIGNAL(clicked()), this, SLOT(num_Operations()));

    ui->BtnPlus->setCheckable(true);
    ui->BtnMinus->setCheckable(true);
    ui->BtnMult->setCheckable(true);
    ui->BtnDevide->setCheckable(true);
    ui->BtnDot->setCheckable(true);
    ui->BtnPP->setCheckable(true);
    update1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkOP(){
    if(ui->BtnMinus->isChecked() || ui->BtnPlus->isChecked() || ui->BtnDevide->isChecked() || ui->BtnMult->isChecked())
    {
        return true;
    }
    return false;
}

void MainWindow::pic_upd()
{
    float degrees;
    if(::FirstNumber.toFloat() >= 0)
        degrees = ::FirstNumber.toFloat() + ::SecondNumber.toFloat() / 60 + ::ThridNumber.toFloat() / 3600;
    else
        degrees = ::FirstNumber.toFloat() - ::SecondNumber.toFloat() / 60 - ::ThridNumber.toFloat() / 3600;
    QLineF angleline;
    angleline.setP1(QPointF(1, 0));
    angleline.setAngle(degrees);
    angleline.setLength(130);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(10, 0, -4, -2);
    ui->graphicsView->setScene(scene);

    scene->addLine(angleline, QPen(Qt::red, 2));
}

void sixty(){
    int first = ::FirstNumber.toInt();
    int second = ::SecondNumber.toInt();
    int thrid = ::ThridNumber.toInt();
    while(thrid >= 60){
        thrid -= 60;
        second++;
    }
    while(second >= 60){
        second -= 60;
        first++;
    }
    while(thrid <= -60){
        thrid += 60;
        second--;
    }
    while(second <= -60){
        second += 60;
        first--;
    }
    for(int i = 0; i < 2; i++)
    {
        if(second <= 0 && thrid > 0)
        {
            second++;
            thrid = thrid - 60;
        }
        if(first < 0 && second > 0)
        {
            first++;
            second = second - 60;
        }
        if(second >= 0 && thrid < 0)
        {
            second--;
            thrid = 60 + thrid;
        }
        if(first > 0 && second < 0)
        {
            first--;
            second = 60 + second;
        }
    }
    ::FirstNumber = QString::number(first);
    ::SecondNumber = QString::number(second);
    ::ThridNumber = QString::number(thrid);
}

void MainWindow::update1(){
    QString tmpf;
    QString tmps;
    QString tmpt;
    if(!checkOP()){
        if(FirstNumber == "") tmpf = "0";
        else tmpf = ::FirstNumber;
        if(SecondNumber == "") tmps = "0";
        else tmps = ::SecondNumber;
        if(ThridNumber == "") tmpt = "0";
        else tmpt = ::ThridNumber;
    }
    else{
        if(FirstN == "") tmpf = "0";
        else tmpf = ::FirstN;
        if(SecondN == "") tmps = "0";
        else tmps = ::SecondN;
        if(ThridN == "") tmpt = "0";
        else tmpt = ::ThridN;
    }
    QString res = tmpf + "°" + tmps + "'" + tmpt + "''";
    ui->res_label->setText(res);
}

void MainWindow::digits()
{
    if(!ui->BtnMode->isChecked())
    {
        if (!checkOP()){
            if(!(::FirstNumber[0] == "-" || ::SecondNumber[0] == "-" || ::ThridNumber[0] == "-"))
            {
                if(ui->BtnPP->isChecked())
                    ::ThridNumber += ((QPushButton*)sender())->text();
                else if(ui->BtnDot->isChecked())
                    ::SecondNumber += ((QPushButton*)sender())->text();
                else
                    ::FirstNumber += ((QPushButton*)sender())->text();
            }
            else
            {
                if(ui->BtnPP->isChecked())
                    ::ThridNumber += ((QPushButton*)sender())->text();
                else if(ui->BtnDot->isChecked())
                    ::SecondNumber += ((QPushButton*)sender())->text();
                else
                    ::FirstNumber += ((QPushButton*)sender())->text();
                if(::FirstNumber.toInt() > 0)
                    ::FirstNumber = QString::number(-::FirstNumber.toInt());
                if(::SecondNumber.toInt() > 0)
                    ::SecondNumber = QString::number(-::SecondNumber.toInt());
                if(::ThridNumber.toInt() > 0)
                    ::ThridNumber = QString::number(-::ThridNumber.toInt());
            }
            update1();
        }
        else{
            if(::FirstN[0] != "-" && ::SecondN[0] != "-" && ::ThridN[0] != "-")
            {
                if(ui->BtnPP->isChecked())
                    ::ThridN += ((QPushButton*)sender())->text();
                else if(ui->BtnDot->isChecked())
                    ::SecondN += ((QPushButton*)sender())->text();
                else
                    ::FirstN += ((QPushButton*)sender())->text();
            }
            else
            {
                if(ui->BtnPP->isChecked())
                {
                    ::ThridN += ((QPushButton*)sender())->text();
                    ::ThridN = QString::number(-::ThridN.toInt());
                }
                else if(ui->BtnDot->isChecked())
                {
                    ::SecondN += ((QPushButton*)sender())->text();
                    ::SecondN = QString::number(-::SecondN.toInt());
                }
                else
                {
                    ::FirstN += ((QPushButton*)sender())->text();
                    ::FirstN = QString::number(-::FirstN.toInt());
                }

        }
            update1();
        }
    }
    else
    {
        QString tmp = ui->label_des->text() + ((QPushButton*)sender())->text();
        ui->label_des->setText(tmp);
    }

}

void MainWindow::on_BtnDelOne_clicked() //Перепиши!!!
{
    if(!ui->BtnMode->isChecked())
    {
        if(!checkOP())
        {
            if(ui->BtnDot->isChecked())
                ::SecondNumber = ::SecondNumber.mid(0, ::SecondNumber.length() - 1);
            else if(ui->BtnPP->isChecked())
                ::ThridNumber = ::ThridNumber.mid(0, ::ThridNumber.length() - 1);
            else
                ::FirstNumber = ::FirstNumber.mid(0, ::FirstNumber.length() - 1);
        }
        else
        {
            if(ui->BtnDot->isChecked())
                ::SecondN = ::SecondN.mid(0, ::SecondN.length() - 1);
            else if(ui->BtnPP->isChecked())
                ::ThridN = ::ThridN.mid(0, ::ThridN.length() - 1);
            else
                ::FirstN = ::FirstN.mid(0, ::FirstN.length() - 1);
        }
        update1();
    }
    else
        ui->label_des->setText(ui->label_des->text().mid(0, ui->label_des->text().length() - 1));
}

void MainWindow::on_BtnClearAll_clicked()
{
    ::FirstNumber = "";
    ::SecondNumber = "";
    ::ThridNumber = "";

    ::FirstN = "";
    ::SecondN = "";
    ::ThridN = "";

    ::tmp_des = "";

    ui->label->setText("");
    ui->res_label->setText("");
    ui->label_des->setText("");

    ui->BtnMinus->setChecked(false);
    ui->BtnPlus->setChecked(false);
    ui->BtnMult->setChecked(false);
    ui->BtnDevide->setChecked(false);
    ui->BtnDot->setChecked(false);
    ui->BtnPP->setChecked(false);
}

void MainWindow::on_BtnDot_clicked()
{
    if(!ui->BtnMode->isChecked())
    {
        if(ui->BtnDot->isChecked())
        {
            ui->BtnDot->setChecked(true);
            ui->BtnPP->setChecked(false);
        }
        else
           ui->BtnDot->setChecked(false);
    }
    else
    {
        if(ui->label_des->text() != "" && !ui->label_des->text().contains("."))
        {
          ui->label_des->setText(ui->label_des->text() + ".");
        }

    }

}

void MainWindow::on_BtnPP_clicked()
{
    if(!ui->BtnMode->isChecked())
    {
        if(ui->BtnPP->isChecked())
        {
            ui->BtnPP->setChecked(true);
            ui->BtnDot->setChecked(false);
        }
        else
           ui->BtnPP->setChecked(false);
    }
    else
    {
        QString result = "";
        if(checkOP())
            on_BtnDo_clicked();
        ui->BtnPP->setChecked(false);
        if(ui->label_des->text().toFloat() >= 0)
        {
            result += "√" + QString::number(ui->label_des->text().toFloat()) + "=";
            ui->label_des->setText(QString::number(sqrt(ui->label_des->text().toFloat())));
            result += ui->label_des->text();
            ui->results->addItem(result);
        }
        else
        {
          QMessageBox::critical(this, "Ошибка!", "Корень из отрицательного числа!");
          on_BtnClearAll_clicked();
        }
    }
}

void MainWindow::on_BtnPM_clicked()
{
    int tmp;
    if(!ui->BtnMode->isChecked())
    {
        if(!checkOP()){
           tmp = -::ThridNumber.toInt();
           ::ThridNumber = QString::number(tmp);
           tmp = -::SecondNumber.toInt();
           ::SecondNumber = QString::number(tmp);
           tmp = -::FirstNumber.toInt();
           ::FirstNumber = QString::number(tmp);
        }
        else{
            tmp = -::ThridN.toInt();
            ::ThridN = QString::number(tmp);
            tmp = -::SecondN.toInt();
            ::SecondN = QString::number(tmp);
            tmp = -::FirstN.toInt();
            ::FirstN = QString::number(tmp);
        }
        update1();
    }
    else
    {
        float tmp = -ui->label_des->text().toFloat();
        ui->label_des->setText(QString::number(tmp));
    }
}

void MainWindow::num_Operations()
{
    QPushButton* snd = ((QPushButton*)sender());
    if(ui->BtnMinus->isChecked())
        ui->BtnMinus->setChecked(false);
    if(ui->BtnPlus->isChecked())
        ui->BtnPlus->setChecked(false);
    if(ui->BtnDevide->isChecked())
        ui->BtnDevide->setChecked(false);
    if(ui->BtnMult->isChecked())
        ui->BtnMult->setChecked(false);
    snd->setChecked(true);
    if(!ui->BtnMode->isChecked())
    {
        QString tmpf;
        QString tmps;
        QString tmpt;

        if(::FirstNumber == "") tmpf = "0";
        else tmpf = ::FirstNumber;
        if(SecondNumber  == "") tmps = "0";
        else tmps = ::SecondNumber;
        if(ThridNumber  == "") tmpt = "0";
        else tmpt = ::ThridNumber;
        ::deist = tmpf + "°" + tmps + "'" + tmpt + "''" + snd->text();
        ui->label->setText(::deist);

        update1();
        ui->BtnDot->setChecked(false);
        ui->BtnPP->setChecked(false);
    }
    else
    {
        if(ui->label_des->text() == "")
            ::deist = "0";
        else
            ::deist = ui->label_des->text();
        if(ui->label->text() == "")
        {
            ::tmp_des = ::deist;

            ui->label_des->setText("");
        }
        ::deist += snd->text();
        ui->label->setText(::deist);
    }
}

void MainWindow::on_BtnDo_clicked()
{
    QString result = "";
    sixty();
    update1();
    if(!ui->BtnMode->isChecked()){
        int tmpf = 0;
        int tmps = 0;
        int tmpt = 0;
        if(checkOP())
        {
            result += ::deist;
            if(ui->BtnMinus->isChecked())
            {
                tmpf = ::FirstNumber.toInt() - ::FirstN.toInt();
                tmps = ::SecondNumber.toInt() - ::SecondN.toInt();
                tmpt = ::ThridNumber.toInt() - ::ThridN.toInt();
            }
            else if(ui->BtnPlus->isChecked())
            {
                tmpf = ::FirstNumber.toInt() + ::FirstN.toInt();
                tmps = ::SecondNumber.toInt() + ::SecondN.toInt();
                tmpt = ::ThridNumber.toInt() + ::ThridN.toInt();
            }
            else if(ui->BtnDevide->isChecked())
            {
                ::ThridNumber = QString::number(::FirstNumber.toInt() * 60 * 60 + ::SecondNumber.toInt() * 60 + ::ThridNumber.toInt());
                ::ThridN = QString::number(::FirstN.toInt() * 60 * 60 + ::SecondN.toInt() * 60 + ::ThridN.toInt());
                if(::ThridN != "0" && ::ThridN != "" )
                {
                    ::ThridNumber = QString::number(::ThridNumber.toInt() / ::ThridN.toInt());
                    tmpf = ::ThridNumber.toInt();
                }
                else
                {
                    QMessageBox::critical(this, "Ошибка!", "На ноль делить нельзя!");
                    on_BtnClearAll_clicked();
                }

            }
            else if(ui->BtnMult->isChecked())
            {
                tmpf = ::FirstNumber.toInt() * ::FirstN.toInt();
                tmps = ::SecondNumber.toInt() * ::SecondN.toInt();
                tmpt = ::ThridNumber.toInt() * ::ThridN.toInt();
            }
            result += ui->res_label->text();

            ::FirstNumber = QString::number(tmpf);
            ::SecondNumber = QString::number(tmps);
            ::ThridNumber = QString::number(tmpt);

            sixty();

            ui->BtnMinus->setChecked(false);
            ui->BtnPlus->setChecked(false);
            ui->BtnMult->setChecked(false);
            ui->BtnDevide->setChecked(false);
            ui->BtnDot->setChecked(false);
            ui->BtnPP->setChecked(false);

            update1();
            result += "=" +  ui->res_label->text();

            ::FirstN = "";
            ::SecondN = "";
            ::ThridN = "";

            ui->label->setText("");


        }
        else result += ui->res_label->text() + "=" + ui->res_label->text();


    }
    else
    {
        if(checkOP())
        {
            result += ::deist;
            result += ui->label_des->text();
            if(ui->BtnMinus->isChecked())
            {
                ui->label_des->setText(QString::number(::tmp_des.toFloat() - ui->label_des->text().toFloat()));
            }
            else if(ui->BtnPlus->isChecked())
            {
                ui->label_des->setText(QString::number(::tmp_des.toFloat() + ui->label_des->text().toFloat()));
            }
            else if(ui->BtnDevide->isChecked())
            {
                if(ui->label_des->text().toFloat() != 0)
                    ui->label_des->setText(QString::number(::tmp_des.toFloat() / ui->label_des->text().toFloat()));
                else
                {
                    QMessageBox::critical(this, "Ошибка!", "На ноль делить нельзя!");
                    on_BtnClearAll_clicked();
                }
            }
            else if(ui->BtnMult->isChecked())
            {
                ui->label_des->setText(QString::number(::tmp_des.toFloat() * ui->label_des->text().toFloat()));
            }
            result += "=" + ui->label_des->text();
            ui->label->setText("");
            ui->BtnMinus->setChecked(false);
            ui->BtnPlus->setChecked(false);
            ui->BtnMult->setChecked(false);
            ui->BtnDevide->setChecked(false);
        }
        else result += QString::number(ui->label_des->text().toFloat()) + "=" + QString::number(ui->label_des->text().toFloat());
    }

    pic_upd();


    ui->results->addItem(result);
}

void MainWindow::on_BtnMode_clicked()
{
    QPushButton* tmp = ui->BtnMode;
    if(!tmp->isChecked())
    {
        tmp->setChecked(false);
        ui->BtnDot->setCheckable(true);
        ui->BtnPP->setChecked(false);
        ui->res_label->setStyleSheet("QLabel { border: 1px solid gray; border-style: outset; border-width: 2px; border-radius: 10px; border-color: rgb(255, 0, 4); }");
        ui->label_des->setStyleSheet("QLabel { border: 1px solid gray; border-style: outset; border-width: 2px; border-radius: 10px; border-color: gray; }");
        ui->BtnPP->setStyleSheet("QPushButton{ background-color: rgb(48, 145, 145); border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 16px; } QPushButton:hover { background-color: rgb(41, 125, 125); border-style: inset; } QPushButton:pressed { background-color: rgb(31, 95, 95); border-style: inset; } QPushButton:checked { background-color:rgb(31, 95, 95); border-style: inset; }");
        ui->BtnPP->setText("\"");
        ui->BtnDot->setText("'");
        ui->BtnSin->setText("Sin");
        ui->BtnCos->setText("Cos");
        ui->BtnTg->setText("Tg");
        ui->BtnCtg->setText("Ctg");
    }
    else
    {
        tmp->setChecked(true);
        ui->BtnDot->setCheckable(false);
        ui->BtnPP->setChecked(false);
        ui->label_des->setStyleSheet("QLabel { border: 1px solid gray; border-style: outset; border-width: 2px; border-radius: 10px; border-color: rgb(255, 0, 4); }");
        ui->res_label->setStyleSheet("QLabel { border: 1px solid gray; border-style: outset; border-width: 2px; border-radius: 10px; border-color: gray; }");
        ui->BtnPP->setStyleSheet("QPushButton{ background-color: rgb(255, 191, 0); border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 16px; } QPushButton:hover { background-color: rgb(229, 168, 0); border-style: inset; } QPushButton:pressed { background-color:rgb(188, 138, 0); border-style: inset; }");
        ui->BtnPP->setText("\"");
        ui->BtnPP->setText("√");
        ui->BtnDot->setText(".");
        ui->BtnSin->setText("ArcSin");
        ui->BtnCos->setText("ArcCos");
        ui->BtnTg->setText("ArcTg");
        ui->BtnCtg->setText("ArcCtg");
    }
}

void MainWindow::on_BtnCtg_clicked()
{
    QString result = "";
    if(checkOP()) on_BtnDo_clicked();
    if(!ui->BtnMode->isChecked())
    {
        float deg = (::FirstNumber.toFloat() + ::SecondNumber.toFloat() / 60 + ::ThridNumber.toFloat() / 3600) * pi / 180;
        ::tmp_des = QString::number(1/tan(deg));
        result += "Ctg(" + ui->res_label->text() + ")=" + ::tmp_des;
        ui->label_des->setText(::tmp_des);
        ui->results->addItem(result);
    }
    else
    {
        double decimal_degrees = (3.1415/2 - atan(ui->label_des->text().toFloat())) * 180 / pi;
        double minutes = (decimal_degrees - floor(decimal_degrees)) * 60.0;
        double seconds = (minutes - floor(minutes)) * 60.0;

        minutes = floor(minutes);
        seconds = floor(seconds);

        if(decimal_degrees > 0)
        {
            ::FirstNumber = QString::number((int)decimal_degrees);
            ::SecondNumber = QString::number(minutes);
            ::ThridNumber = QString::number(seconds);
        }
        else
        {
            ::FirstNumber = QString::number((int)decimal_degrees);
            ::SecondNumber = QString::number(-minutes);
            ::ThridNumber = QString::number(-seconds);
        }

        update1();
        result += "ArcCtg(" + ui->label_des->text() + ")=" + ui->res_label->text();
        ui->results->addItem(result);

    }
    pic_upd();

}

void MainWindow::on_BtnTg_clicked()
{
    QString result = "";
    if(checkOP()) on_BtnDo_clicked();
    if(!ui->BtnMode->isChecked())
    {
        float deg = (::FirstNumber.toFloat() + ::SecondNumber.toFloat() / 60 + ::ThridNumber.toFloat() / 3600) * pi / 180;
        ::tmp_des = QString::number(tan(deg));
        result += "Tg(" + ui->res_label->text() + ")=" + ::tmp_des;
        ui->label_des->setText(::tmp_des);
        ui->results->addItem(result);
    }
    else
    {
        double decimal_degrees = atan(ui->label_des->text().toFloat()) * 180 / pi;
        double minutes = (decimal_degrees - floor(decimal_degrees)) * 60.0;
        double seconds = (minutes - floor(minutes)) * 60.0;

        minutes = floor(minutes);
        seconds = floor(seconds);

        if(decimal_degrees > 0)
        {
            ::FirstNumber = QString::number((int)decimal_degrees);
            ::SecondNumber = QString::number(minutes);
            ::ThridNumber = QString::number(seconds);
        }
        else
        {
            ::FirstNumber = QString::number((int)decimal_degrees);
            ::SecondNumber = QString::number(-minutes);
            ::ThridNumber = QString::number(-seconds);
        }

        update1();
        result += "ArcTg(" + ui->label_des->text() + ")=" + ui->res_label->text();
        ui->results->addItem(result);
    }
    pic_upd();
}

void MainWindow::on_BtnCos_clicked()
{
    QString result = "";
    if(checkOP()) on_BtnDo_clicked();
    if(!ui->BtnMode->isChecked())
    {
        float deg = (::FirstNumber.toFloat() + ::SecondNumber.toFloat() / 60 + ::ThridNumber.toFloat() / 3600) * pi / 180;
        ::tmp_des = QString::number(cos(deg));
        result += "Cos(" + ui->res_label->text() + ")=" + ::tmp_des;
        ui->label_des->setText(::tmp_des);
        ui->results->addItem(result);
    }
    else
    {
        if(ui->label_des->text().toFloat() <= 1 && ui->label_des->text().toFloat() >= -1)
        {
            double decimal_degrees = acos(ui->label_des->text().toFloat()) * 180 / pi;
            double minutes = (decimal_degrees - floor(decimal_degrees)) * 60.0;
            double seconds = (minutes - floor(minutes)) * 60.0;

            minutes = floor(minutes);
            seconds = floor(seconds);

            if(decimal_degrees > 0)
            {
                ::FirstNumber = QString::number((int)decimal_degrees);
                ::SecondNumber = QString::number(minutes);
                ::ThridNumber = QString::number(seconds);
            }
            else
            {
                ::FirstNumber = QString::number((int)decimal_degrees);
                ::SecondNumber = QString::number(-minutes);
                ::ThridNumber = QString::number(-seconds);
            }
            update1();
            result += "ArcCos(" + ui->label_des->text() + ")=" + ui->res_label->text();
            ui->results->addItem(result);
        }
        else
        {
            QMessageBox::critical(this, "Ошибка!", "Выход за область определения функции!");
            on_BtnClearAll_clicked();
        }
    }
    pic_upd();
}

void MainWindow::on_BtnSin_clicked()
{
    QString result = "";
    if(checkOP()) on_BtnDo_clicked();
    if(!ui->BtnMode->isChecked())
    {
        float deg = (::FirstNumber.toFloat() + ::SecondNumber.toFloat() / 60 + ::ThridNumber.toFloat() / 3600) * pi/ 180;
        ::tmp_des = QString::number(sin(deg));
        result += "Sin(" + ui->res_label->text() + ")=" + ::tmp_des;
        ui->label_des->setText(::tmp_des);
        ui->results->addItem(result);
    }
    else
    {
        if(ui->label_des->text().toFloat() <= 1 && ui->label_des->text().toFloat() >= -1)
        {
            double decimal_degrees = asin(ui->label_des->text().toFloat()) * 180 / pi;
            double minutes = (decimal_degrees - floor(decimal_degrees)) * 60.0;
            double seconds = (minutes - floor(minutes)) * 60.0;

            minutes = floor(minutes);
            seconds = floor(seconds);

            if(decimal_degrees > 0)
            {
                ::FirstNumber = QString::number((int)decimal_degrees);
                ::SecondNumber = QString::number(minutes);
                ::ThridNumber = QString::number(seconds);
            }
            else
            {
                ::FirstNumber = QString::number((int)decimal_degrees);
                ::SecondNumber = QString::number(-minutes);
                ::ThridNumber = QString::number(-seconds);
            }

            update1();
            result += "ArcSin(" + ui->label_des->text() + ")=" + ui->res_label->text();
            ui->results->addItem(result);
        }
        else
        {
            QMessageBox::critical(this, "Ошибка!", "Выход за область определения функции!");
            on_BtnClearAll_clicked();
        }
    }
    pic_upd();
}

void MainWindow::on_pushButton_clicked()
{
    ui->results->clear();
}
