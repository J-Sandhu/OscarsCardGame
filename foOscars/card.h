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

    enum class PersonColor {red = 0, blue = 1, green = 2, purple = 3};

    //right now it's hard coded to red, but we can change this later
    PersonColor colorType = PersonColor::red;


    Card(int param1, int param2, int param3, cardFuncPtr func, bool isPerson);

};



#endif // CARD_H
