#ifndef OTHERPLAYERHANDS_H
#define OTHERPLAYERHANDS_H
#include <player.h>
#include <QDialog>
#include <QHBoxLayout>
#include <QVector>
#include "mainwindow.h"

namespace Ui {
class otherPlayerHands;
}

class otherPlayerHands : public QDialog
{
    Q_OBJECT

public:
    explicit otherPlayerHands(QWidget *parent = nullptr, Player* player = nullptr, QVector<QPixmap>* personImages = nullptr);
    ~otherPlayerHands();

    Player* player;

    QHBoxLayout* personLayout = new QHBoxLayout;
    QWidget* personScrollWidget = new QWidget;

    QVector<QPixmap>* peopleImages;

private:
    Ui::otherPlayerHands *ui;
};

#endif // OTHERPLAYERHANDS_H
