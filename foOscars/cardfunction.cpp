#include "cardfunction.h"

CardFunction::CardFunction(int param1, int param2, int param3, cardFuncPtr func)
{
    parameters[0] = param1;
    parameters[1] = param2;
    parameters[2] = param3;
    function = func;

}
