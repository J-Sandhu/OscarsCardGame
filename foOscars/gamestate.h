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
    ///
    /// \brief GameState:
    ///  default constructor
    GameState();
    ///
    /// \brief players:
    ///  holds player objects representing all players of the game
    vector<Player> players;
    ///
    /// \brief indexOfWinner:
    ///  index of player with highest score at the end of the game
    int indexOfWinner;
    ///
    /// \brief currentPlayerIndex:
    ///  index of player whose turn it is
    int currentPlayerIndex=0;
    ///
    /// \brief round:
    ///  which round the game is in
    int round;
    ///
    /// \brief gameOver:
    ///  whether the game is over
    bool gameOver;
    // 48+ 4
    // 2,3,4,8
    ///
    /// \brief actionCardStack:
    /// holds all action cards which have not yet been drawn (deck)
    QVector<int> actionCardStack;
    ///
    /// \brief playerButtonsEnabled:
    ///  indicates when the player should select a target player for a card effect
    bool playerButtonsEnabled;
    //40 + 6
    // 2*2, 11*2, 12*4, 29*2
    ///
    /// \brief personCardStack:
    /// holds all player cards which have not yet been drawn (deck)
    QVector<int> personCardStack;
    ///
    /// \brief tableau
    /// holds IDs of every card in the tableau, in order
    QVector<int> tableau;
    ///
    /// \brief tableauCardIsEnabled
    /// holds whether each tableau card
    QVector<bool> tableauCardIsEnabled;
    ///
    /// \brief deserialize
    /// populates the values of this gameState using a JSON representation
    /// \param serializedGameState
    /// a QByteArray holding a JSON serialized representation of a gameState
    void deserialize(QByteArray serializedGameState);
    ///
    /// \brief serialize
    /// returns a JSON serialized representation of this gameState
    ///
    QByteArray serialize();
    ///
    /// \brief resetGameState
    /// resets everything to default (like using a default constructor)
    void resetGameState();



};

#endif // GAMESTATE_H
