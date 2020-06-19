#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumWidth(400);
    currentHeading = 0;
    currentQuestion = 0;
    centralWidget = new QWidget;
    centralLayout = new QVBoxLayout;
    buttonsLayout = new QHBoxLayout;
    headingLabel = new QLabel;
    initForm = new InitForm;
    questionForm = new QuestionForm;
    dialog = new QInputDialog;

    headings.resize(5);
    questions.resize(25);
    answers.resize(25);

    setCentralWidget(centralWidget);
    centralWidget->setLayout(centralLayout);
    headingLabel->setAlignment(Qt::AlignCenter);
    headingLabel->setText("Set price for difficulty of questions");
    centralLayout->setAlignment(Qt::AlignHCenter);
    centralLayout->addWidget(headingLabel);
    centralLayout->addWidget(initForm);
    centralLayout->addLayout(buttonsLayout);

    dialog->setWindowTitle("Heading name");
    dialog->setLabelText("Set heading " + QString::number(currentHeading+1) + " name");
    dialog->setModal(true);

    connect(initForm, SIGNAL(setPrices(QVector<int>)), this, SLOT(onSetPrices(QVector<int>)));
    connect(dialog, SIGNAL(rejected()), this, SLOT(close()));
    connect(dialog, SIGNAL(textValueChanged(const QString&)), this, SLOT(onTextValueChanged(QString)));
    connect(dialog, SIGNAL(accepted()), this, SLOT(checkValue()));
    connect(questionForm, SIGNAL(nextQuestion()), this, SLOT(onNextQuestion()));
    connect(questionForm, SIGNAL(previousQuestion()), this, SLOT(onPreviousQuestion()));
    connect(questionForm, SIGNAL(saveQuestion(QString, QString)), this, SLOT(onSaveQuestion(QString, QString)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onSetPrices(QVector<int> prices){
    for(auto p : prices){
        if(p == 0){
            return;
        }
    }
    this->prices = prices;
    headingPhase();
}

void MainWindow::headingPhase(){
    dialog->show();
}


void MainWindow::onTextValueChanged(QString heading){
    headings[currentHeading] = heading;
}

void MainWindow::checkValue(){
    if(headings[currentHeading] == ""){
        headingPhase();
    }else{
        questionPhase();
    }
}

void MainWindow::questionPhase(){
    if(initForm != nullptr){
        delete initForm;
        initForm = nullptr;
    }
    centralLayout->addWidget(questionForm, 1);
    headingLabel->setText("Add question");
    questionForm->setHeading(headings[currentHeading]);
    questionForm->setPrice(QString::number(prices[currentQuestion]));
    questionForm->setQuestion(questions[currentQuestion]);
    questionForm->setAnswer(answers[currentQuestion]);
}

void MainWindow::onSaveQuestion(QString question, QString answer){
    questions[currentQuestion] = question;
    answers[currentQuestion] = answer;
}

void MainWindow::onNextQuestion(){
    if(currentQuestion+1 < 5){
        currentQuestion++;
        questionForm->setHeading(headings[currentHeading]);
        questionForm->setPrice(QString::number(prices[currentQuestion]));
        questionForm->setQuestion(questions[currentQuestion]);
        questionForm->setAnswer(answers[currentQuestion]);
    }else{
        if(currentHeading+1 < 5){
            currentHeading++;
            currentQuestion = 0;
            if(headings[currentHeading] == ""){
                headingPhase();
            }
        }else{
            saveGame();
        }
    }
}

void MainWindow::onPreviousQuestion(){
    if(currentQuestion+1 > 1){
        currentQuestion--;    }else{
        if(currentHeading+1 > 1){
            currentHeading--;
            currentQuestion = 4;
        }
    }
    questionForm->setHeading(headings[currentHeading]);
    questionForm->setPrice(QString::number(prices[currentQuestion]));
    questionForm->setQuestion(questions[currentQuestion]);
    questionForm->setAnswer(answers[currentQuestion]);
}

void MainWindow::saveGame(){
    QJsonDocument doc;
    QJsonArray contents;
    QJsonObject game;
    game.insert("identificator", "ownGame");
    for(auto p : prices){
        game.insert("dif"+QString::number(prices.indexOf(p)+1), p);
    }
    for(int i = 1; i < 6; i++){

        QJsonObject heading;
        heading.insert("heading", headings[i-1]);
        QJsonArray questionsArr;
        for(int j = 1; j < 6; j++){
            QJsonObject question;
            question.insert("difficulty", j);
            question.insert("type", "normal");
            question.insert("text", questions[j*i-1]);
            question.insert("answer", answers[j*i-1]);
            questionsArr.push_back(question);
        }
        heading.insert("questions", questionsArr);
        contents.push_back(heading);
    }
    game.insert("contents", contents);
    QString filePath = QFileDialog::getSaveFileUrl().toString().remove(0, 8);
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    doc.setObject(game);
    file.write(doc.toJson());
    file.close();
    QMessageBox::information(this, "Save", "Game saved successful");
    close();
}

