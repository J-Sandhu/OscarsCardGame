#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QString>

class Player
{
public:
    Player();
    std::vector<int>playerActionPile;
    std::vector<std::vector<int>>playerPeoplePile;
    long long id;
    int score;
    int selectedActionIndex;
    QString name;
    int scoreManipulators[5];
    int purpleCardSum;
    int redCardSum;
    int blueCardSum;
    int greenCardSum;


    void recalculateScore();
};

#endif // PLAYER_H
