#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QVector>
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
#include <iterator>

#include <iostream>
using namespace std;
class GameState
{
public:
    GameState();
    vector<Player> players;
    int currentPlayerIndex=0;
    
    QVector<int> actionCardStack;


    QVector<int> personCardStack;
    QVector<int> tableau;

    //yes yes in know we can make this better later -chase
    QVector<bool> tableauEnableds;

    QByteArray serialize();
    void deserialize(QByteArray serializedGameState);
    void resetGameState();

};

#endif // GAMESTATE_H
