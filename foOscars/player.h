#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QString>

class Player
{
public:
    Player();

    //right now hard coded as player, but we can change it later
    QString name;

    QVector<int> actionPile;
    int selectedActionIndex;
    int indexInPlayerArray;


    // THIS CORRESPONDS TO COLOR INDECES

    QVector<int> bluePeoplePile; //color index = 0
    QVector<int> greenPeoplePile; // color index = 1
    QVector<int> purplePeoplePile; // color index = 2
    QVector<int> redPeoplePile; // color index = 3

    QVector<bool> scoreManipulators;


    int score;
    long long id;


};

#endif // PLAYER_H
