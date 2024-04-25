#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QString>

class Player
{
public:
    Player();

    /// players name
    QString name;

    /// the action cards in this players hand
    QVector<int> actionPile;

    /// the index of the action card that was selected
    int selectedActionIndex;

    /// this player's index in the player array
    int indexInPlayerArray;

    // THIS CORRESPONDS TO COLOR INDECES
    /// vector of all blue people this player has
    QVector<int> bluePeoplePile; //color index = 0

    /// vector of all green people this player has
    QVector<int> greenPeoplePile; // color index = 1

    /// vector of all purple people this player has
    QVector<int> purplePeoplePile; // color index = 2

    /// vector of all red people this player has
    QVector<int> redPeoplePile; // color index = 3

    /// booleans that alert score calcualor what is in play
    QVector<bool> scoreManipulators{false,false,false,false};

    /// other point modifiers
    int miscPoint=0;

    /// this player's score
    int score;

    /// the socketDescriptor of this players socket
    long long id;


};

#endif // PLAYER_H
