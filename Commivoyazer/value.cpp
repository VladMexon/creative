#include "value.h"
#include "ui_value.h"

Value::Value(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Value)
{
    ui->setupUi(this);
    ui->Val->setFocus();
}

Value::~Value()
{
    delete ui;
}

void Value::on_BtnOk_clicked()
{
    extern QString text_for_arrows;
    text_for_arrows = ui->Val->text();
    this->close();
}
