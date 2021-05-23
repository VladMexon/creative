#ifndef VALUE_H
#define VALUE_H

#include <QDialog>

namespace Ui {
class Value;
}

class Value : public QDialog
{
    Q_OBJECT

public:
    explicit Value(QWidget *parent = nullptr);
    ~Value();

private slots:
    void on_BtnOk_clicked();

private:
    Ui::Value *ui;
};

#endif // VALUE_H
