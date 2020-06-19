#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

#include "initform.h"
#include "questionform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void headingPhase();
    void questionPhase();
    void saveGame();

private slots:
    void onSetPrices(QVector<int> prices);
    void onTextValueChanged(QString heading);
    void checkValue();
    void onNextQuestion();
    void onPreviousQuestion();
    void onSaveQuestion(QString question, QString answer);

private:
    QWidget *centralWidget;
    QVBoxLayout *centralLayout;
    QLabel *headingLabel;
    InitForm *initForm;
    QuestionForm *questionForm;
    QHBoxLayout *buttonsLayout;
    QInputDialog *dialog;
    QVector<int> prices;
    QVector<QString> headings;
    QVector<QString> questions;
    QVector<QString> answers;
    int currentHeading;
    int currentQuestion;
};
#endif // MAINWINDOW_H
