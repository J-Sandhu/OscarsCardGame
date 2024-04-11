#ifndef CARDFUNCTION_H
#define CARDFUNCTION_H

///
/// \brief This class provides a tuple-like representation for card functions.
/// It will allow us to generalize game rules down to a few basic functions.
///
class CardFunction
{

public:
    typedef void (*cardFuncPtr)(int param1, int param2, int param3);


    CardFunction(int param1, int param2, int param3, cardFuncPtr func);

    int parameters[3];
    cardFuncPtr function;
};



#endif // CARDFUNCTION_H
