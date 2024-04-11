#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "player.h"
#include <QJsonObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QLatin1String>

#include <iostream>
using namespace std;
class GameState
{
public:
    GameState();
    vector<Player> players;
    int currentPlayerIndex=0;
    
    // 48+ 4
    // 2,3,4,8
    QVector<int> actionCardStack;

    //40 + 6
    // 2*2, 11*2, 12*4, 29*2
    QVector<int> personCardStack;
    QVector<int> tableau;

    void deserialize(QByteArray serializedGameState);
    
    QByteArray serialize();
    void resetGameState();

    /*NEEDS:
     * data to represent which player's turn

     * vector of action cards (deck and discard)
     * vector of people cards (deck and discard)
     * list of players
     *      players have
     *      vector of actions (hand)
     *      vector of people  (pile)
     *      index of currently selected action
     *      score
     */
};

#endif // GAMESTATE_H
