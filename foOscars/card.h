#ifndef CARD_H
#define CARD_H
#include <string>

///
/// \brief This class provides a tuple-like representation for card functions.
/// It will allow us to generalize game rules down to a few basic functions.
///
class Card
{

public:
    typedef void (*cardFuncPtr)(int param1, int param2, int param3);
    int parameters[3];
    cardFuncPtr function;

    int cardValue;
    bool isPerson;

    Card(int param1, int param2, int param3, cardFuncPtr func, bool isPerson);

};



#endif // CARD_H
