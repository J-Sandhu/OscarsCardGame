#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <map>
#include "gamestate.h"

class Model
{
public:
    Model();
    GameState gameState;

    ///
    /// \brief Method used for testing model functionality.
    ///
    void modelTestMethod();

private:
    ///
    /// Function pointer type for action cards, takes 3 generic integer parameters
    /// which are to be defined later
    ///
    typedef void (*actionCardFuncPtr)(int param1, int param2, int param3);

    ///
    /// \brief map from card ID to function.
    /// functions must be of the type actionCardFuncPtr to match
    /// parameters
    ///
    std::map<int, actionCardFuncPtr> actionMap;

    ///
    /// \brief Method that will modify players score modifier(Chase's idea)
    /// \param victimPlayerID
    /// \param scoreModification
    /// \param unused paramter
    ///
    void addPointsFromActionCard(int scoreModification, int unused1, int unused2);


    ///
    /// \brief method that will modify players color multiplier/ adder
    /// \param index of color that will be modified
    /// \param scoreModification the amount the point values of that color are modified
    /// \param unused parameter
    ///
    void addPointsForColor(int color, int scoreModification, int unused1);


    ///
    /// \brief decrease the points of a victim player of your choosing
    /// \param index of player to be sabotaged
    /// \param scoreModification the amount the victim's score will be affected by
    /// \param unused1
    ///
    void decreaseOtherPlayerPoints(int victimPlayerIndex, int scoreModification, int unused1);

};

#endif // MODEL_H
