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


    typedef std::pair<int,int> person;


    // THIS CORRESPONDS TO COLOR INDECES
    int numberOfColors= 4;
    // QVector<person> bluePeoplePile; //color index = 0
    // QVector<person> greenPeoplePile; // color index = 1
    // QVector<person> purplePeoplePile; // color index = 2
    // QVector<person> redPeoplePile; // color index = 3
    // QVector<person> crewPile;
    QVector<bool> scoreManipulators;

    QVector<int> bluePeoplePile; //color index = 0
    QVector<int> greenPeoplePile; // color index = 1
    QVector<int> purplePeoplePile; // color index = 2
    QVector<int> redPeoplePile; // color index = 3
    QVector<int> crewPile;



    int score;
    long long id;

    void recalculateScore();
    int calulateColorSum(int color,bool manipultorEnabled);

};

#endif // PLAYER_H
