#ifndef QUESTIONFORM_H
#define QUESTIONFORM_H

#include <QWidget>

namespace Ui {
class QuestionForm;
}

class QuestionForm : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionForm(QWidget *parent = nullptr);
    ~QuestionForm();
    void setHeading(QString heading);
    void setPrice(QString price);
    void setQuestion(QString question);
    void setAnswer(QString answer);

signals:
    void nextQuestion();
    void previousQuestion();
    void saveQuestion(QString question, QString answer);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::QuestionForm *ui;
};

#endif // QUESTIONFORM_H
