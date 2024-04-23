#include "model.h"
Model::Model(QObject *parent) : QObject(parent){

    //populateGameState();

    gameIsStarted=false;
    std::cout << "########## OLD GAME STATE ############" << std::endl;
    //std::cout << gameState.serialize().toStdString() << std::endl;


    //gameState.deserialize(gameState.serialize());
    std::cout << "############### NEW GAME STATE ################" << std::endl;
    //std::cout << gameState.serialize().toStdString() << std::endl;


    populatePeopleMap();
    populateActionMap();

}

void Model::HandlePlayerName(long long id, QString message)
{
    if (message.toStdString()=="player")
    {
        message.append(to_string(id));
        cout<<message.toStdString()<<endl;
    }

    for (int i=0; i<gameState.players.size(); i++)
    {
        if (gameState.players.at(i).id==id)
        {
            gameState.players.at(i).name=message;
            cout<<"player found in naming! :"<<gameState.players.at(i).name.toStdString()<<endl;
        }
    }
    // foreach (Player p, gameState.players)
    // {
    //     if (p.id==id)
    //     {
    //         p.name=message;
    //         cout<<"player found in naming! :"<<p.name.toStdString()<<endl;

    //     }
    // }


}
void Model::HandleChatMessage(long long id, QString message)
{
    string sender;
    foreach (Player p, gameState.players)
        if (p.id==id)
            sender = p.name.toStdString()+": ";
    message.prepend(sender);
    foreach (Player p, gameState.players)
        emit sendChatToPlayers(message);
}
void Model::HandleTableauSelection(long long id, QString message)
{
    if(id !=gameState.players[gameState.currentPlayerIndex].id)
    {
        cout<<"ignored selection from non-current player"<<endl;
        return;
    }
    int returnedParam = message.toInt();
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;
    ((*this).*callback)(returnedParam);
}

void Model::HandleActionSelection(long long id, QString message)
{

    if(id !=gameState.players[gameState.currentPlayerIndex].id)
    {
        cout<<"ignored selection from non-current player"<<endl;
        return;
    }
    int actionIndex = message.toInt(); //index corresponds to tableau
    currentAID= gameState.players.at(gameState.currentPlayerIndex).actionPile[actionIndex];

    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;
    std::cout <<"############ Parameters in handleactionselection" << std::endl;
    std::cout<<params[0]<<std::endl;
    std::cout<<params[1]<<std::endl;
    std::cout<<params[2]<<std::endl;

    std::cout<<"get to action card selection being handled"<<std::endl;
    // selectedActionCardIDFromPersonalPile = actionCardID;
    // emit actionCardSelectedFromPersonalPile(selectedActionCard);
    cardFunction cardFunction= function;
    ((*this).*cardFunction)(params[0],params[1],params[2]);
}

void Model::HandleStartGame(long long id)
{
    std::cout<<"getting into handle start game" << std::endl;
    if (gameIsStarted)
    {
        std::cout <<"game is already started" << std::endl;
        return;
    }
    if (id==gameState.players.at(0).id)
    {
        //populate tableau
        std::cout<< "game has not yet started! calling populate methods"<<std::endl;
        populateGameState();
        //std::cout << gameState.serialize().toStdString() << std::endl;
    }

   // std::cout<<"gamestate.playerID != "<< id << " instead = " << gameState.players.at(0).id << std::endl;
}

void Model::HandleCallBack(long long id, QString message)
{

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


void Model::movementCardPlayed(int specifiedColor, int unused, int unused1)
{
    std::cout << "getting into move person card emission function" << std::endl;
    std::cout << specifiedColor << std::endl;

    //TODO: make it so that we dont go out of bounds if someone plays +4 in the first slot
    if (specifiedColor != -1){
        for (int i = 0; i<gameState.tableau.size(); i++){
            std::cout <<"before looking at people tuple" <<std::endl;
            std::cout <<"size of peoplemap: " << peopleMap.size() << std::endl;
            peopleTuple person = peopleMap.at(gameState.tableau.at(i));

            std::cout <<"getting past looking at people tuple" << std::endl;
            auto[value, color, specialFunc] = person;
            if(color == specifiedColor)
            {
                //enable card at index in tableau

                // intialize tableacardenabled array to false
                QVector<bool> newVector;
                for(int j =0; j<gameState.tableau.size(); j++)
                    newVector.push_back(false);

                gameState.tableauCardIsEnabled = newVector;
                std::cout <<"Right before enabling a card in gamestate through model" << std::endl;
                gameState.tableauCardIsEnabled.replace(i,true);
                std::cout <<"surviving it!" << std::endl;
            }
        }
    }
    else
    {
        QVector<bool> newEnabledVector;
        for(int i =0; i<gameState.tableau.size(); i++)
            newEnabledVector.push_back(true);
        std::cout <<"***************************************setting some cards to enabled" << std::endl;

        gameState.tableauCardIsEnabled = newEnabledVector;
    }
    //TODO: rn works with only a host bc it will send the 2nd part of the 2 parter to ALL players (not the one who played the card)
    //emit sendStateToPlayers(gameState.serialize());
    emit sendStatetoPlayer(gameState.serialize(),gameState.currentPlayerIndex);
}

void Model::movementCardComplete(int indexInTab)
{
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    // std::cout << "movementCardComplete is called as a callback. Paramters when I get to here is: " <<params[0]<<", "<<params[1]<<", "<<params[2]<<std::endl;
    // std::cout<<"indexInTab is: "<<indexInTab<<std::endl;

    std::cout << "getting into movement card played" << std::endl;
    if(indexInTab-params.at(1) < 0)
        gameState.tableau.move(indexInTab,0);
    else if(indexInTab+params.at(1) > gameState.tableau.size()-1)
        gameState.tableau.move(indexInTab, gameState.tableau.size()-1);
    else
        gameState.tableau.move(indexInTab, indexInTab - params.at(1));

    //gameState.currentPlayerIndex += 1; *talk to Jai about hadling other player turns
    emit sendStateToPlayers(gameState.serialize());

}

//reuse for 16, 17, 20
void Model::shuffleTableauPlayed(int numCardsToShuffle,int unused, int unused2)
{
    for (int i = 0; i < numCardsToShuffle / 2; i++) {
        // Calculate the index of the corresponding element from the end
        int j = numCardsToShuffle - 1 - i;

        // Swap elements at index i and j
        int temp =  gameState.tableau[i];
        gameState.tableau[i] =  gameState.tableau[j];
        gameState.tableau[j] = temp;
    }

    //notify other players
    emit sendStateToPlayers(gameState.serialize());
}

//for card 16
void Model::shuffleTableauPlayed16(int unused, int unused1, int unused2)
{
    shuffleTableauPlayed(4, 0, 0);
}

//for card 17
void Model::shuffleTableauPlayed17(int unused, int unused1, int unused2)
{
    shuffleTableauPlayed(5, 0, 0);
}

//for card 18
void Model::reverseCardPlayed(int unused, int unused1, int unused2)
{
    int start = 0;
    int end = gameState.tableau.size() - 1;

    while (start < end) {
        // Swap elements at start and end index
        auto temp = gameState.tableau[start];
        gameState.tableau[start] = gameState.tableau[end];
        gameState.tableau[end] = temp;

        start++;
        end--;
    }

    emit sendStateToPlayers((gameState.serialize()));
    // qDebug()<<"call reverse";
}


//for card 19
void Model::newLinePlayed(int unused, int unused1, int unused2)
{
    generateRandomTableau();
    emit sendStateToPlayers((gameState.serialize()));
}

//for card 20
void Model::escapeCardPlayed1stPart(int unused, int unused1, int unused2)
{
    //enable all the cards on tableau
    QVector<bool> newEnabledVector;
    for(int i =0; i<gameState.tableau.size(); i++)
        newEnabledVector.push_back(true);

    gameState.tableauCardIsEnabled = newEnabledVector;

    emit sendStateToPlayers(gameState.serialize());

}
//for card20 - remove and shuffle
void Model::escapeCardPlayed2ndPart(int chosenIndex)
{
    gameState.tableau.removeAt(chosenIndex);

    //disable cards
    QVector<bool> newEnabledVector;
    for(int i =0; i<gameState.tableau.size(); i++)
        newEnabledVector.push_back(false);
    gameState.tableauCardIsEnabled = newEnabledVector;

    shuffleTableauPlayed(gameState.tableau.size(), 0, 0);
}

//for card 21
//TODO:

//for card 22
void Model::addToTableau(int numCardsToAdd, int unused, int unused1)
{   numCardsToAdd = 3;
    if(gameState.personCardStack.size() < numCardsToAdd)
    {
        numCardsToAdd = gameState.personCardStack.size();
    }
    for (int i = 0; i<numCardsToAdd; i++)
    {
        int rand = std::rand() % gameState.personCardStack.size();
        gameState.tableauCardIsEnabled.push_back(false);
        gameState.tableau.push_back(gameState.personCardStack.at(rand));
        gameState.personCardStack.removeAt(rand);
    }
    emit sendStateToPlayers(gameState.serialize());
}

//for card 23
void Model::addFromTopThree(int unused, int unused1, int unused2){
    int numToChoose = 3;
    if(gameState.personCardStack.size() < numToChoose)
    {
        numToChoose = gameState.personCardStack.size();
    }
    int chosenIndex = std::rand() % numToChoose;

    gameState.tableauCardIsEnabled.push_back(false);
    gameState.tableau.push_back(gameState.personCardStack.at(chosenIndex));
    gameState.personCardStack.removeAt(chosenIndex);

    emit sendStateToPlayers(gameState.serialize());

}


//for card 34
void Model::merylToFront(int unused, int unused1, int unused2)
{
    //disable cards
    for (int i = 0; i < gameState.tableau.size(); i++) {
        gameState.tableauCardIsEnabled.push_back(false);
    }

    int merlyIndexInTableau;

    for (int i = 0; i< gameState.tableau.size(); i++)
    {
        //get merly card - id 36
        peopleTuple person = peopleMap[gameState.tableau.at(i)];
        auto[value, color, specialFunc] = person;

        if (gameState.tableau.at(i) == 36)
        {
            merlyIndexInTableau = i;
            gameState.tableau.move(merlyIndexInTableau, 0);
            break;
        }
    }
    endOfTurn();
}

// for card 35
void Model::moveClosestBlueToFront(int specifiedColor , int unused , int unused2)
{
    //disable cards
    for (int i = 0; i < gameState.tableau.size(); i++) {
        gameState.tableauCardIsEnabled.push_back(false);
    }

    //find a blue card
    int closestBlueIndex;

    for(int i=0; i<gameState.tableau.size(); i++)
    {
        std::cout<<"got into for loop" <<  std::endl;

        peopleTuple person = peopleMap[gameState.tableau.at(i)];
        auto[value, color, specialFunc] = person;

        std::cout<<" id of first blue: "<<gameState.tableau.at(i)<<std::endl;
        std::cout<<"get into " <<  std::endl;
        std::cout<<color <<  std::endl;


        if(color == specifiedColor) //if a blue card exists
        {
            closestBlueIndex = i;
            std::cout<<"blue: " << closestBlueIndex << std::endl;
            //move blue to front
            // gameState.tableau.insert(gameState.tableau.begin(), gameState.tableau.at(closestBlueIndex));
            // //delete where it was
            // gameState.tableau.removeAt(closestBlueIndex);

            gameState.tableau.move(closestBlueIndex, 0);

            break;
        }
    }
    endOfTurn();
}

//for card 37
void Model::crewToFront(int unused, int unused1, int unused2)
{
    //disable cards
    for (int i = 0; i < gameState.tableau.size(); i++) {
        gameState.tableauCardIsEnabled.push_back(false);
    }

    int closestCrewIndexTableau;
    for(int i=0; i<gameState.tableau.size(); i++)
    {
        //get crew card - id 12
        peopleTuple person = peopleMap[gameState.tableau.at(i)];
        auto[value, color, specialFunc] = person;

        if (gameState.tableau.at(i) == 12)
        {
            closestCrewIndexTableau = i;
            gameState.tableau.move(closestCrewIndexTableau, 0);
            break;
        }
    }
    endOfTurn();
 }

 //for card 46 - swap hands, 1
 void Model::swapHands1(int victimPlayer, int currentPlayer, int unused2)
 {
     //get seleceted player's action pile
     QVector<int> victimPile = gameState.players.at(victimPlayer).actionPile;

     //get this player's action pile
     QVector<int> playerPile = gameState.players.at(currentPlayer).actionPile;

     //swap
     victimPile.swap(&playerPile);
 }



//for card 42 - deal new action card for all players
void Model::dealNewActionCard(int unused2, int unused, int unused1)
{
    generateRandomHands();
}

//for card 44 - all players must discard 1 action card
void Model::discardOneAction(int unused, int unused1, int unused2)
{
    std::cout<<"getting into discard one action"<<std::endl;

    //for each player
    for(int i =0 ; i<gameState.players.size(); i++)
    {
        std::cout<<"player action pile before removing: "<< gameState.players.at(i).actionPile.size() <<std::endl;
        gameState.players.at(i).actionPile.removeAt(gameState.players.at(i).actionPile.at(gameState.players.at(i).selectedActionIndex));
        std::cout<<"player action pile: "<< gameState.players.at(i).actionPile.size() << std::endl;
    }
}

void Model::scoreManipulatorPlayed(int specifiedColor, int colorScoreBuff, int misc)
{
    if(specifiedColor ==anyColor)
    {
        gameState.players.at(gameState.currentPlayerIndex).score+=colorScoreBuff;
        return;
    }
    if(specifiedColor==purple)
    {
        int numberOfPurps= gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.size();
        drawActionCard(numberOfPurps);
        return;
    }
    else
    {
        gameState.players.at(gameState.currentPlayerIndex).scoreManipulators[specifiedColor]=colorScoreBuff;
    }
}



// void newTableau(int unused1, int unused2, int unused3)
// {
//     std::cout <<" getting into new Tableau function" << std::endl;
// }

void Model::populateGameState()
{
    std::cout <<"getting into populate game state" <<std::endl;

    //clear ppl stack
    gameState.personCardStack.clear();
    // probably get rid of this, but populate some players.
    //TODO: definitely get rid of this lol
    // for(int i = 0; i<4; i++)
    // {
    //     Player p;
    //     gameState.players.push_back(p);
    // }

    gameState.round=1;
    gameState.currentPlayerIndex=0;
    gameState.gameOver=false;

    // populate the vector with the ids of action cards
    for(int i=0; i<49; i++)
        gameState.actionCardStack.push_back(i);

    // push back values for the duplicate cards
    // 2, 3 4 8
    gameState.actionCardStack.push_back(2);
    gameState.actionCardStack.push_back(3);
    gameState.actionCardStack.push_back(4);
    gameState.actionCardStack.push_back(8);


    // populate the vector for the ids of people cards
    //40 + 6
    for(int i=0; i<41; i++)
        gameState.personCardStack.push_back(i);

    // add duplicate people cards
    gameState.personCardStack.push_back(2);
    gameState.personCardStack.push_back(11);
    gameState.personCardStack.push_back(29);

    for(int i=0; i<4; i++)
        gameState.personCardStack.push_back(12);



    // generate a random tableau
    generateRandomTableau();
    populatePeopleMap();

    // generate random hands
    generateRandomHands();

    //emit signal that game has been initialized and notify mainwindow to upload card images
    //emit gameInitializedSignal();
    std::cout <<"Getting to send state to players" << std::endl;
    emit sendStateToPlayers(gameState.serialize());

}

void Model::generateRandomTableau()
{
    std::cout << "getting into random tableau" << std::endl;
    gameState.tableau.clear();
    // gameState.tableau.push_back(gameState.personCardStack.at(2));


    for(int i=1; i<11; i++)
    {
        // generate a random index

        // int randomPersonIndex = QRandomGenerator::global()->bounded(gameState.personCardStack.size()-1);

        //not so random random
        int randomPersonIndex = 1;

        //std::rand() % (max - min + 1) + min;
        int randomTestVic = std::rand() % (19 - 10 +1) + 10 ; //using 10 - 19
        // put the ID from that index into the tableau
        gameState.tableau.push_back(gameState.personCardStack.at(i+12));
        // remove the ID at that index so that the same Person won't be included twice(except duplicate cards)
        //gameState.personCardStack.removeAt(randomPersonIndex);

    }
    gameState.tableau.push_back(gameState.personCardStack.at(12));

    QVector<bool> newVector;
    for(int i=0; i<gameState.tableau.size(); i++)
        newVector.push_back(false);

    gameState.tableauCardIsEnabled = newVector;
}


void Model::generateRandomHands()
{

    // I'm going to make a little thing to make hands only generate out of cards we have implemented.
    //std::cout << "getting into random hands" << std::endl;

    QVector<int> existingActionCards;

    for(std::map<int,cardTuple>::iterator it = actionMap.begin(); it != actionMap.end(); ++it)
        existingActionCards.push_back(it->first);

    // for each of the 4 players
    for(int i =0 ; i<gameState.players.size(); i++)
    {
        // put 5 unique action cards into their hand
        for(int j =0; j<6; j++)
        {
            // TODO: Fix card gen
            // generate a random index within the actionCardStack
            //int randomActionIndex = QRandomGenerator::global()->bounded(gameState.actionCardStack.size()-1);
            // gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(randomActionIndex));
            // gameState.actionCardStack.removeAt(randomActionIndex);

            int randomExistingActionIndex = QRandomGenerator::global()->bounded(existingActionCards.size()-1);
            //gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(randomExistingActionIndex));

            gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(37)); //hard coded to test AC#
        }
    }
}



void Model::populatePeopleMap()
{
    //(value, color, special func)


    //0 - the rock
    peopleTuple tuple(2,0, nullptr);
    //int= card id, tuple contains correspinding card's info
    peopleMap.insert(std::pair<int,peopleTuple>(0,tuple));

    //1- charlie chaplin
    peopleTuple tuple1(1,0, nullptr);
    //int= card id, tuple contains correspinding card's info
    peopleMap.insert(std::pair<int,peopleTuple>(1,tuple1));

    //2- Background Actor
    peopleTuple tuple2(1,0, nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(2,tuple2));

    //3-bob hope
    peopleTuple tuple3(3,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(3,tuple3));


    //4-Washed up action star
    peopleTuple tuple4(3,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(4,tuple4));


    //5-Peter O'tool
    peopleTuple tuple5(2,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(5,tuple5));

    //7-Kevin Hart
    peopleTuple tuple6(2,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(6,tuple6));

    //8- KILLEM murphey
    peopleTuple tuple7(2,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(7,tuple7));

    //9-Marlon Brando
    peopleTuple tuple8(2,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(8,tuple8));

    //10-Joaquin Pheonix
    peopleTuple tuple9(2,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(9,tuple9));

    //11-brad
    peopleTuple tuple10(2,0,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(10,tuple10));


    //GREEN LINE



    //12-Boom mike
    peopleTuple tuple11(1,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(11,tuple11));

    //13- Film Crew
    peopleTuple tuple12(1,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(12,tuple12));

    //14- Stunt Double
    peopleTuple tuple13(1,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(13,tuple13));

    //15- Some Thheater kid
    peopleTuple tuple14(1,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(14,tuple14));

    //16- Interviwer
    peopleTuple tuple15(1,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(15,tuple15));

    //17- eyelash
    peopleTuple tuple16(2,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(16,tuple16));

    //18- WOLFGANG
    peopleTuple tuple17(3,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(17,tuple17));

    //19- Phin
    peopleTuple tuple18(2,1,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(18,tuple18));

    //PURPLe

    //20- ROMAN
    peopleTuple tuple19(-5,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(19,tuple19));


    //21- John Ford
    peopleTuple tuple20(4,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(20,tuple20));

    //22- waititi
    peopleTuple tuple21(2,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(21,tuple21));

    //23- walt
    peopleTuple tuple22(4,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(22,tuple22));

    //24- aby
    peopleTuple tuple23(-4,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(23,tuple23));

    //25- james ivory
    peopleTuple tuple24(4,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(24,tuple24));

    //26- will wieler
    peopleTuple tuple25(4,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(25,tuple25));

    //27- Nolan
    peopleTuple tuple26(-5,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(26,tuple26));

    //28- greta Gerwig
    peopleTuple tuple27(4,purple,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(27,tuple27));

    //reds

    //29-emma watson
    peopleTuple tuple28(2, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(28,tuple28));


    //30-background actress
    peopleTuple tuple29(1, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(29,tuple29));

    //31-Greer Garson
    peopleTuple tuple30(1, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(30,tuple30));

    //32-Micheal yeoh
    peopleTuple tuple31(2, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(31,tuple31));

    //33-Tatum o'neal
    peopleTuple tuple32(2, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(32,tuple32));

    //34- the agles watrees
    peopleTuple tuple33(1, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(33,tuple33));

    //35-kat hep
    peopleTuple tuple34(3, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(34,tuple34));

    //36-jen law
    peopleTuple tuple35(3, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(35,tuple35));

    //37-Meryl
    peopleTuple tuple36(5, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(36,tuple36));


    //38-Margo Robbie
    peopleTuple tuple37(3, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(37,tuple37));

    //39-patricia art
    peopleTuple tuple38(2, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(38,tuple38));

    //40- emma stone
    peopleTuple tuple39(4, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(39,tuple39));

    //41- gaga
    peopleTuple tuple40(2, red,nullptr);
    peopleMap.insert(std::pair<int,peopleTuple>(40,tuple40));




}


void Model::drawActionCard(int numberOfCards)
{
    for(int i =0;i<numberOfCards;i++)
    {
        int randomActionIndex = QRandomGenerator::global()->bounded(gameState.actionCardStack.size()-1);

        int randomActionID= gameState.actionCardStack.at(randomActionIndex);
        gameState.actionCardStack.removeAt(randomActionIndex);

        gameState.players.at(gameState.currentPlayerIndex).actionPile.push_back(randomActionID);
    }

}


//for card
void Model::populateActionMap()
{
    //add card 2: back 1
    QVector<int> parameters2{-1,-1,0};
    cardTuple tuple2(&Model::movementCardPlayed, parameters2, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(2,tuple2));

    //add card 3: fan fav- forward 4
    QVector<int> parameters3{-1,4,0};
    cardTuple tuple3(&Model::movementCardPlayed, parameters3, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(3,tuple3));

    //add card 4: forward 2
    QVector<int> parameters4{-1,2,0};
    cardTuple tuple4(&Model::movementCardPlayed, parameters4, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(4,tuple4));

    // add card 5: forward 3
    QVector<int> parameters5{-1,3,0};
    cardTuple tuple5(&Model::movementCardPlayed, parameters5, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(5,tuple5));

    // add card 6: purple 2
    QVector<int> parameters6{2,4,0};
    cardTuple tuple6(&Model::movementCardPlayed, parameters6, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(6,tuple6));

    // add card 7: back 2
    QVector<int> parameters7{-1,-2,0};
    cardTuple tuple7(&Model::movementCardPlayed, parameters7, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(7,tuple7));

    // add card 8: speed walk-move forward 1
    QVector<int> parameters8{-1,1,0};//can change num of params later
    cardTuple tuple8(&Model::movementCardPlayed, parameters8, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(8,tuple8));

    // add card 9: forward 2 same as card 4
    actionMap.insert(std::pair<int, cardTuple>(9,tuple4));

    // add card 10: forward 3- same as card 5
    actionMap.insert(std::pair<int, cardTuple>(10,tuple5));

    // add card 11: back 3
    QVector<int> parameters11{-1,-3,0};
    cardTuple tuple11(&Model::movementCardPlayed, parameters11, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(11,tuple11));

    // add card 12: discard any noble

    // add card 13: winners walk
    QVector<int> parameters13{-1,100,0}; // enough to bring any card to the front
    cardTuple tuple13(&Model::movementCardPlayed, parameters13, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(13,tuple13));

    // add card 14: move the front card to the back
    //TODO: write this


    // add card 15: green up 2
    QVector<int> parameters15{1,2,0};
    cardTuple tuple15(&Model::movementCardPlayed, parameters15, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(15,tuple15));

    // add card 16: mix first 4
    QVector<int> parameters16{0,-1,0};
    cardTuple tuple16(&Model::shuffleTableauPlayed16, parameters16, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(16, tuple16));

    //add card 17: mix first 5
    QVector<int> parameters17{0,-1,0};
    cardTuple tuple17(&Model::shuffleTableauPlayed17, parameters17, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(17, tuple17));

    //add card 18: reverse line
    QVector<int> parameters18{0,-1,0};
    cardTuple tuple18(&Model::reverseCardPlayed, parameters18, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(18, tuple18));

    //add card 19: new line
    QVector<int> parameters19{0,-1,0};
    cardTuple tuple19(&Model::newLinePlayed, parameters19, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(19, tuple19));

    //add card 20: complete mix
    QVector<int> parameters20{0,-1,0};
    cardTuple tuple20(&Model::escapeCardPlayed1stPart, parameters20, &Model::escapeCardPlayed2ndPart);
    actionMap.insert(std::pair<int, cardTuple>(20, tuple20));

    //add card 21:
    //TODO:ask

    //add card 22: add 3 new people to tableau
    QVector<int> parameters22{0,-1,0};
    cardTuple tuple22(&Model::addToTableau, parameters22, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(22, tuple22));

    //add card 23: add top 3 from people stack
    QVector<int> parameters23{0,-1,0};
    cardTuple tuple23(&Model::addFromTopThree, parameters23, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(23, tuple23));

    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 24: green +1
    QVector<int> parameters24{green,1,0};
    cardTuple tuple24(&Model::scoreManipulatorPlayed, parameters24, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(24,tuple24));

    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 25: score +2
    QVector<int> parameters25{anyColor,2,0};
    cardTuple tuple25(&Model::scoreManipulatorPlayed, parameters25, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(25,tuple25));

    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 26: blue +1
    QVector<int> parameters26{blue,1,0};
    cardTuple tuple26(&Model::scoreManipulatorPlayed, parameters26, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(26,tuple26));

    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 27: score -2
    QVector<int> parameters27{anyColor,-2,0};
    cardTuple tuple27(&Model::scoreManipulatorPlayed, parameters27, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(27,tuple27));

    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 28: red +1
    QVector<int> parameters28{red,1,0};
    cardTuple tuple28(&Model::scoreManipulatorPlayed, parameters28, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(28,tuple28));

    //add card 29: nuetrlize grays, could get rid of

    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 30: +1 action for every purple
    QVector<int> parameters30{purple,0,0};
    cardTuple tuple30(&Model::scoreManipulatorPlayed, parameters30, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(30,tuple30));

    //add 34: Marie to front
    QVector<int> parameters34{-1,0,0};
    cardTuple tuple34(&Model::merylToFront, parameters34, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(34,tuple34));

    //add card 35: closest blue to front
    QVector<int> parameters35{0,0,0};
    cardTuple tuple35(&Model::moveClosestBlueToFront, parameters35, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(35,tuple35));

    //add card 36: move a card up 2
    QVector<int> parameters36{-1,2,0};
    cardTuple tuple36(&Model::movementCardPlayed, parameters36, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(36,tuple36));

    //add card 37: closest crew to front
    QVector<int> parameters37{-1,0,0};
    cardTuple tuple37(&Model::crewToFront, parameters37, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(37,tuple37));

    //add card 42: deal new action cards
    QVector<int> parameters42{-1,0,0};
    cardTuple tuple42(&Model::dealNewActionCard, parameters42, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(42,tuple42));

    // //add card 43: discard one action
    // QVector<int> parameters43{-1,0,0};
    // cardTuple tuple43(&Model::discardOneAction, parameters43, nullptr);
    // actionMap.insert(std::pair<int,cardTuple>(43,tuple43));

    // //add card 46: deal new action cards
    // QVector<int> parameters46{-1,0,0};
    // cardTuple tuple42(&Model::dealNewActionCard, parameters42, nullptr);
    // actionMap.insert(std::pair<int,cardTuple>(42,tuple42));
}


void Model::endOfTurn()
{
    int personCollectedId =gameState.tableau.at(0);

    gameState.tableau.removeAt(0);

    int color = std::get<1>(peopleMap.at(personCollectedId));

    //check which color
    if(color ==blue)
        gameState.players.at(gameState.currentPlayerIndex).bluePeoplePile.append(personCollectedId);
    else if(color == green)
        gameState.players.at(gameState.currentPlayerIndex).greenPeoplePile.append(personCollectedId);
    else if(color ==purple)
        gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.append(personCollectedId);
    else if(color ==red)
        gameState.players.at(gameState.currentPlayerIndex).redPeoplePile.append(personCollectedId);



    if(std::get<2>(peopleMap.at(personCollectedId))!=nullptr)
    {

        //currently only card with specialness is Greer Garson, so wouldnt be a loss to get rid of her or not
        //do her effect through a function
    }
    else
    {
        gameState.round+=1;
        if (gameState.round==4)
            endGame();
        else
        {
            //some function that puts 10 people cards from deck into tableau
        }
    }
    //could be more based on the people card picked up
    drawActionCard(1);

    //move to next players turn
    if(gameState.currentPlayerIndex+=1>gameState.players.size()-1)
        gameState.currentPlayerIndex=0;
    else
        gameState.currentPlayerIndex+=1;


    emit sendStateToPlayers(gameState.serialize());
}



void Model::recalculateScore()
{
    int updatedScore=0;

    //color pile sums
    for(int i=0;i<numberOfColors;i++)
    {
        updatedScore+= calulateColorSum(i, gameState.players.at(gameState.currentPlayerIndex).scoreManipulators.at(i));
    }

    //crew stuff
    int num_Of_Crew=0;
    int id_Of_Crew=12;

    foreach(int person ,gameState.players.at(gameState.currentPlayerIndex).greenPeoplePile )
    {
        if(person==id_Of_Crew)
        {
            num_Of_Crew++;
        }
    }
    gameState.players.at(gameState.currentPlayerIndex).score+= num_Of_Crew * num_Of_Crew;

    gameState.players.at(gameState.currentPlayerIndex).score= updatedScore;
}

int Model::calulateColorSum(int color, bool manipultorEnabled)
{
    QVector<int> vectorToBeSummed;

    //check which color
    if(color ==blue)
        vectorToBeSummed= gameState.players.at(gameState.currentPlayerIndex).bluePeoplePile;
    else if(color == green)
        vectorToBeSummed = gameState.players.at(gameState.currentPlayerIndex).greenPeoplePile;
    else if(color ==purple)
        vectorToBeSummed=gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile;
    else if(color ==red)
        vectorToBeSummed=gameState.players.at(gameState.currentPlayerIndex).redPeoplePile;

    //sum that color pile
    int pileSum=0;
    foreach(int person ,vectorToBeSummed )
    {

        //crazy logic but this is to handle not searching for the same pair twice and doing the point boost twice
        //so if you only search when you find the even half you only do the pair adding once.
        if(person<=8 &&person>0&& (person%2==0) )
        {

            if(person==8&& gameState.players.at(gameState.currentPlayerIndex).greenPeoplePile.contains(7))
            {
                pileSum+=std::get<0>(peopleMap.at(person))*3;
            }
            else if(gameState.players.at(gameState.currentPlayerIndex).bluePeoplePile.contains(person-1))
            {
                pileSum+=std::get<0>(peopleMap.at(person))*3;
            }

        }
        else
        {
            pileSum+=std::get<0>(peopleMap.at(person))*3;
        }

    }

    if(manipultorEnabled)
    {
        pileSum+=vectorToBeSummed.size();
    }

    return pileSum;
}


void Model::endGame()
{
    gameState.gameOver=true;
    emit sendStateToPlayers(gameState.serialize());

    emit displayWinnerAndConfetti();
}


void Model::addNewPlayer(long long id)
{
    Player newPlayer;
    newPlayer.id = id;

    gameState.players.push_back(newPlayer);

    emit sendStateToPlayers(gameState.serialize());
}
