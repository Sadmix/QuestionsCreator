#ifndef INITFORM_H
#define INITFORM_H

#include <QWidget>
#include <QIntValidator>

namespace Ui {
class InitForm;
}

class InitForm : public QWidget
{
    Q_OBJECT

public:
    explicit InitForm(QWidget *parent = nullptr);
    ~InitForm();

private slots:
    void on_price1Edit_textChanged(const QString &arg1);

    void on_price2Edit_textChanged(const QString &arg1);

    void on_price3Edit_textChanged(const QString &arg1);

    void on_price4Edit_textChanged(const QString &arg1);

    void on_price5Edit_textChanged(const QString &arg1);

    void on_cancelBtn_clicked();

    void on_nextBtn_clicked();

signals:

    void setPrices(QVector<int> prices);

private:
    Ui::InitForm *ui;
    QVector<int> price;
};

#endif // INITFORM_H
