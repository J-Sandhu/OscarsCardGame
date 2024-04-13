#ifndef OTHERPLAYERHANDS_H
#define OTHERPLAYERHANDS_H
#include <player.h>
#include <QDialog>

namespace Ui {
class otherPlayerHands;
}

class otherPlayerHands : public QDialog
{
    Q_OBJECT

public:
    explicit otherPlayerHands(QWidget *parent = nullptr, Player* player = nullptr);
    ~otherPlayerHands();

    Player* player;

private:
    Ui::otherPlayerHands *ui;
};

#endif // OTHERPLAYERHANDS_H
