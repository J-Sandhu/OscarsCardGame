#include "otherplayerhands.h"
#include "ui_otherplayerhands.h"
#include <QLabel>

otherPlayerHands::otherPlayerHands(QWidget *parent, Player* player, QVector<QPixmap>* peopleImages)
    : QDialog(parent)
    , ui(new Ui::otherPlayerHands)
    , player(player)
    , peopleImages(peopleImages)
{
    ui->setupUi(this);

<<<<<<< HEAD
    //display action cards
    for (int i = 0; i < player->actionPile.size(); i++){
        //create QLabels
        QLabel* label = new QLabel(this);
        //can adjust height later
        label->setGeometry(0, 0, 100, 80);
        std::string fileName = ":/people/" + std::to_string(player->actionPile.at(i)) + "p.png";
        QPixmap pixmap(QString::fromStdString(fileName));
        label->setPixmap(pixmap.scaledToHeight(label->geometry().height(), Qt::FastTransformation));
=======
    // add blue people to scroll view
    for(int i = 0; i < player->bluePeoplePile.size(); i++){
        int personCardID = player->bluePeoplePile.at(i);
>>>>>>> ee107636488a5ce8a161deaf05b2f9c399e64477

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,300,420);
        button->setBaseSize(300,420);
        button->setFixedSize(300,420);

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 300, 420);
        label->setPixmap(peopleImages->at(personCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));
        //connect(button, &QPushButton::clicked, this, &MainWindow::anotherPlayerPersonCardClicked);
        personLayout->addWidget(button);
    }

    for(int i = 0; i < player->greenPeoplePile.size(); i++){
        int personCardID = player->greenPeoplePile.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,300,420);
        button->setBaseSize(300,420);
        button->setFixedSize(300,420);

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 300, 420);
        label->setPixmap(peopleImages->at(personCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));
        //connect(button, &QPushButton::clicked, this, &MainWindow::anotherPlayerPersonCardClicked);
        personLayout->addWidget(button);
    }

    for(int i = 0; i < player->purplePeoplePile.size(); i++){
        int personCardID = player->purplePeoplePile.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,300,420);
        button->setBaseSize(300,420);
        button->setFixedSize(300,420);

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 300, 420);
        label->setPixmap(peopleImages->at(personCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));
        //connect(button, &QPushButton::clicked, this, &MainWindow::anotherPlayerPersonCardClicked);
        personLayout->addWidget(button);
    }

    for(int i = 0; i < player->redPeoplePile.size(); i++){
        int personCardID = player->redPeoplePile.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,300,420);
        button->setBaseSize(300,420);
        button->setFixedSize(300,420);

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 300, 420);
        label->setPixmap(peopleImages->at(personCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));
        //connect(button, &QPushButton::clicked, this, &MainWindow::anotherPlayerPersonCardClicked);
        personLayout->addWidget(button);
    }

    personScrollWidget->setLayout(personLayout);
    ui->scrollArea->setWidget(personScrollWidget);
}

otherPlayerHands::~otherPlayerHands()
{
    delete ui;
}

