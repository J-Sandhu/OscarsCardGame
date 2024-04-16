#include "otherplayerhands.h"
#include "ui_otherplayerhands.h"
#include <QLabel>

otherPlayerHands::otherPlayerHands(QWidget *parent, Player* player)
    : QDialog(parent)
    , ui(new Ui::otherPlayerHands)
    , player(player)
{
    ui->setupUi(this);

    //display action cards
    for (int i = 0; i < player->actionPile.size(); i++){
        //create QLabels
        QLabel* label = new QLabel(this);
        //can adjust height later
        label->setGeometry(0, 0, 100, 80);
        std::string fileName = ":/people/" + std::to_string(player->actionPile.at(i)) + "p.png";
        QPixmap pixmap(QString::fromStdString(fileName));
        label->setPixmap(pixmap.scaledToHeight(label->geometry().height(), Qt::FastTransformation));

        //add to grid layout
        ui->gridLayout->addWidget(label, 0, i);
    }
}

otherPlayerHands::~otherPlayerHands()
{
    delete ui;
}

