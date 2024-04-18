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
    // if(color ==blue)
    //     vectorToBeSummed= bluePeoplePile;
    // else if(color == green)
    //     vectorToBeSummed = greenPeoplePile;
    // else if(color ==purple)
    //     vectorToBeSummed=purplePeoplePile;
    // else if(color ==red)
    //     vectorToBeSummed=redPeoplePile;

    // //sum that color pile
    // int pileSum=0;
    // foreach(person person ,vectorToBeSummed )
    // {
    //     int personCollectedId= std::get<0>(person);

    //     //crazy logic but this is to handle not searching for the same pair twice and doing the point boost twice
    //     //so if you only search when you find the even half you only do the pair adding once.
    //     if(personCollectedId<=8 && (personCollectedId%2==0) )
    //     {
    //         fullPair(person)

    //         if(fullPair)
    //         {
    //             //all pairs are 8 together, one pair is 2 other is 6
    //             pileSum+=person.second*3;
    //         }

    //     }
    //     else
    //     {
    //         pileSum+=person.second;
    //     }

    // }

    // if(manipultorEnabled)
    // {
    //     pileSum+=vectorToBeSummed.size();
    // }

    // // return pileSum;

    return 0;
}

bool Player::isPair(person firstHalf)
{

    // int color = std::get<1>(firstHalf);
    // bool fullPair;
    // if(personCollectedId==0)
    // {
    //     fullPair= isPersonInPlayerPile(vectorToBeSummed,personCollectedId-1);
    // }
    // else
    // {
    //     fullPair= isPersonInPlayerPile(vectorToBeSummed,personCollectedId+1);
    // }

    // foreach(person person, pileToSearch)
    // {
    //     if(std::get<0>(person)==personID)
    //         return true;
    // }
    return false;
}


