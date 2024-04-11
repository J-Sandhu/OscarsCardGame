#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "player.h"

#include <iostream>
using namespace std;
class GameState
{
public:
    GameState();
    vector<Player> players;
    int currentPlayerIndex;

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
