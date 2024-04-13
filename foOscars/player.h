#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QString>

class Player
{
public:
    Player();

    //right now hard coded as player, but we can change it later
    QString name = "player";

    QVector<int> actionPile;
    int selectedActionIndex;

    QVector<int> bluePeoplePile;
    QVector<int> redPeoplePile;
    QVector<int> purplePeoplePile;
    QVector<int> greenPeoplePile;

    QVector<int> scoreManipulators;
    int score;
    long long id;

    void recalculateScore();
    QVector<int> calulatePeopleSums();

};

#endif // PLAYER_H
