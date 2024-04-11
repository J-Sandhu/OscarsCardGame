#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QString>

class Player
{
public:
    Player();
    QString name;

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
