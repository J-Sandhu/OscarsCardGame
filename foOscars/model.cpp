#include "model.h"

Model::Model() {
    std::cout <<"getting into model constructor " <<std::endl;

    // this is one possible format for adding cards core logic.
    // I might turn these into a file that can be read in, but
    // for now this is fine.
    // CardFunction funcTuple(1,1,1,addPointsFromActionCard);
    // actionMap.insert(std::pair<int, CardFunction>(0,funcTuple));
}

void Model::addPointsFromActionCard(int scoreModification, int unused1, int unused2)
{
    std::cout << "modifying score by : " << scoreModification << std::endl;
    // Go into the current player's score manipulator and modify the "additional point" index within
    // score manipulator array.
    gameState.players.at(gameState.currentPlayerIndex).scoreManipulators[4] += scoreModification;
}

void Model::addPointsForColor(int color, int scoreModification, int unused1)
{
    std::cout << "adding : " << scoreModification << " to all cards at color index: " << color << std::endl;
    // go into the current player's score manipulator and modify the proper color's additional point field within
    // within the score manipulator array.
    gameState.players.at(gameState.currentPlayerIndex).scoreManipulators[color] = 1;
}

void Model::decreaseOtherPlayerPoints(int victimPlayerIndex, int scoreModification, int unused1)
{
    std::cout << "removing: " << scoreModification << " points from player at index: " << victimPlayerIndex << std::endl;
    // go into the victim players score manipulator and modify the "additional point" index within the score manipulator array
    gameState.players.at(victimPlayerIndex).scoreManipulators[4] += scoreModification;
}

void Model::modelTestMethod()
{
    std::cout << "getting into modelTest Method " << std::endl;
    int* params = actionMap.at(0).parameters;
    std::cout << " getting past parameter cast " << std::endl;
    auto func = actionMap.at(0).function;

    func(params[0], params[1], params[2]);
}

void Model::movementCardPlayed(int indexInTableau, int positionModification, int unused1)
{
    std::cout << "getting into move person card emission function" << std::endl;
    /*
     * This method and other ones like it may be kind of weird.
     * The series of events, will be as follows to avoid model logic in Client:
     * 1. the user selects a card that moves a person card and clicks "use"
     * 2. The server receives this input and emits something to enable the user to click cards
     *    in the tableau.
     *    - This signal will be emitted  by a CardFunction that will take a color parameter, all it does
     *    is emit a signal to the server to alert the view of which card buttons to activate.
     *    - if the Action card specifies a color of card to move, only those buttons will be enabled.
     * 3. The client receives that signal, enables the card buttons/labels/widgets
     *    - each button/label/widget whatever(card) will be connected to a unique slot for that button,
     *    this enables lookup within the tableau based on ButtonSignal=>TableauIndex=>cardIndex
     * 4. The player selects a card to move.
     * 5. The client emits the signal for the selected card.
     * 6. This signal is caught by the server which calls a gameUpdate method
     */
}

void newTableau(int unused1, int unused2, int unused3)
{
    std::cout <<" getting into new Tableau function" << std::endl;
}
