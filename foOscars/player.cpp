#include "player.h"
#include <QVector>

Player::Player()
{
}

void Player::recalculateScore()
{
    // int updatedScore=0;

    // //color pile sums
    // for(int i=0;i<numberOfColors;i++)
    // {
    //     updatedScore+= calulateColorSum(i, scoreManipulators.at(i));
    // }

    // //crew stuff
    // score+= crewPile.size() *crewPile.size();

    // score= updatedScore;
}

//blue,green,purple,red
int Player::calulateColorSum(int color, bool manipultorEnabled)
{
    // QVector<person> vectorToBeSummed;

    // //check which color
    // if(color ==0)
    //     vectorToBeSummed= bluePeoplePile;
    // else if(color == 1)
    //     vectorToBeSummed = greenPeoplePile;
    // else if(color ==2)
    //     vectorToBeSummed=purplePeoplePile;
    // else if(color ==3)
    //     vectorToBeSummed=redPeoplePile;

    // //sum that color pile
    // int pileSum=0;
    // foreach(person person ,vectorToBeSummed )
    // {
    //     pileSum+=person.second;
    // }

    // if(manipultorEnabled)
    // {
    //     pileSum+=vectorToBeSummed.size();
    // }

    // return pileSum;

    return 0;
}


