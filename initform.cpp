#include "initform.h"
#include "ui_initform.h"

InitForm::InitForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitForm)
{
    ui->setupUi(this);
    price.resize(5);
    ui->price1Edit->setValidator(new QIntValidator(0, 10000, this));
    ui->price2Edit->setValidator(new QIntValidator(0, 10000, this));
    ui->price3Edit->setValidator(new QIntValidator(0, 10000, this));
    ui->price4Edit->setValidator(new QIntValidator(0, 10000, this));
    ui->price5Edit->setValidator(new QIntValidator(0, 10000, this));
}

InitForm::~InitForm()
{
    delete ui;
}

void InitForm::on_price1Edit_textChanged(const QString &arg1)
{
    price[0] = arg1.toInt();
}

void InitForm::on_price2Edit_textChanged(const QString &arg1)
{
    price[1] = arg1.toInt();
}

void InitForm::on_price3Edit_textChanged(const QString &arg1)
{
    price[2] = arg1.toInt();
}

void InitForm::on_price4Edit_textChanged(const QString &arg1)
{
    price[3] = arg1.toInt();
}

void InitForm::on_price5Edit_textChanged(const QString &arg1)
{
    price[4] = arg1.toInt();
}

void InitForm::on_cancelBtn_clicked()
{

}

void InitForm::on_nextBtn_clicked()
{
    emit setPrices(price);
}
