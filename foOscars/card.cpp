#include "card.h"

Card::Card(int param1, int param2, int param3, cardFuncPtr func, bool isPerson) : isPerson(isPerson)
{

    parameters[0] = param1;
    parameters[1] = param2;
    parameters[2] = param3;
    function = func;
}


// void Card::addToLineFunction(GameState* gamestate){
//     int randomPersonIndex = QRandomGenerator::global()->bounded(gameState.personCardStack.size()-1);
//     gameState.tableau.push_back(gameState.personCardStack.at(randomPersonIndex));
//     gameState.personCardStack.removeAt(randomPersonIndex);

// }
