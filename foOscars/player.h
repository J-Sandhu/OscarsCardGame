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

    QVector<QVector<int>> peoplePile;
    QVector<int> scoreManipulators;
    int score;
    long long id;


    void recalculateScore();
    QVector<int> calulatePeopleSums();

};

#endif // PLAYER_H
