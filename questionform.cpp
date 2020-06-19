#include "questionform.h"
#include "ui_questionform.h"

QuestionForm::QuestionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionForm)
{
    ui->setupUi(this);
}

QuestionForm::~QuestionForm()
{
    delete ui;
}

void QuestionForm::setHeading(QString heading){
    ui->headingLabel->setText("Heading: " + heading);
}

void QuestionForm::setPrice(QString price){
    ui->priceLabel->setText("Price: " + price);
}

void QuestionForm::on_pushButton_2_clicked()
{
    emit saveQuestion(ui->questonEdit->toPlainText(), ui->answerEdit->toPlainText());
    emit nextQuestion();
}

void QuestionForm::on_pushButton_clicked()
{
    emit saveQuestion(ui->questonEdit->toPlainText(), ui->answerEdit->toPlainText());
    emit previousQuestion();
}

void QuestionForm::setQuestion(QString question){
    ui->questonEdit->setText(question);
}

void QuestionForm::setAnswer(QString answer){
    ui->answerEdit->setText(answer);
}
