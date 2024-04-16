#ifndef CARD_H
#define CARD_H
#include <string>
#include <gamestate.h>

///
/// \brief This class provides a tuple-like representation for card functions.
/// It will allow us to generalize game rules down to a few basic functions.
///
class Card
{

public:
    typedef void (*cardFuncPtr)(int param1, int param2, int param3);

    int parameters[3];

    //action card operation
    cardFuncPtr function;

    int cardValue;
    bool isPerson;


    int colorType;

    // enum class PersonColor {red = 0, blue = 1, green = 2, purple = 3};

    // //right now it's hard coded to red, but we can change this later
    // PersonColor colorType = PersonColor::red;

    enum class ActionCardTypes {generalLineMovement = 0, lineOrder = 1, addToLine = 2, nobleWorth = 3,
                                 scorePile = 4, specificNoble = 5, actionCardManipulation = 6};

    //same for this
    ActionCardTypes cardType = ActionCardTypes::generalLineMovement;


    Card(int param1, int param2, int param3, cardFuncPtr func, bool isPerson);

    void addToLineFunction();
};



#endif // CARD_H
