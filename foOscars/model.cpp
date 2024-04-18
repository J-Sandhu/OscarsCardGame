#include "model.h"
Model::Model(QObject *parent) : QObject(parent){

    //populateGameState();
    gameIsStarted=false;
    std::cout << "########## OLD GAME STATE ############" << std::endl;
    std::cout << gameState.serialize().toStdString() << std::endl;


    gameState.deserialize(gameState.serialize());
    std::cout << "############### NEW GAME STATE ################" << std::endl;
    std::cout << gameState.serialize().toStdString() << std::endl;


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
    Player p;
    p.id=id;
    p.name= message;
    gameState.players.push_back(p);

    message.append(" joined the game!");
    emit sendChatToPlayers(message);

}
void Model::HandleChatMessage(long long id, QString message)
{
    string sender;
    foreach (Player p, gameState.players)
        if (p.id==id)
            sender = p.name.toStdString()+": ";
    message.prepend(sender);
    foreach (Player p, gameState.players)
        sendChatToPlayers(message);
}
void Model::HandleTableauSelection(long long id, QString message)
{
    int returnedParam = message.toInt();
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;
    ((*this).*callback)(returnedParam);
}

void Model::HandleActionSelection(long long id, QString message)
{
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
    if (gameIsStarted)
        return;
    if (id==gameState.players[0].id)
    {
        //populate tableau
        populateGameState();
        std::cout << gameState.serialize().toStdString() << std::endl;
    }
}

void Model::HandleCallBack(long long id, QString message){

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
    emit sendStateToPlayers(gameState.serialize());
}

void Model::movementCardComplete(int indexInTab)
{

    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    // std::cout << "movementCardComplete is called as a callback. Paramters when I get to here is: " <<params[0]<<", "<<params[1]<<", "<<params[2]<<std::endl;
    // std::cout<<"indexInTab is: "<<indexInTab<<std::endl;

    if(indexInTab-params.at(1) < 0)
        gameState.tableau.move(indexInTab,0);
    else if(indexInTab+params.at(1) > gameState.tableau.size()-1)
        gameState.tableau.move(indexInTab, gameState.tableau.size()-1);
    else
        gameState.tableau.move(indexInTab, indexInTab - params.at(1));

    //gameState.currentPlayerIndex += 1; *talk to Jai about hadling other player turns
    emit sendStateToPlayers(gameState.serialize());

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



void newTableau(int unused1, int unused2, int unused3)
{
    std::cout <<" getting into new Tableau function" << std::endl;
}

void Model::populateGameState()
{
    std::cout <<"getting into populate game state" <<std::endl;

    // probably get rid of this, but populate some players.
    //TODO: definitely get rid of this lol
    for(int i = 0; i<4; i++)
    {
        Player p;
        gameState.players.push_back(p);
    }

    gameState.round=1;
    gameState.currentPlayerIndex=0;

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
    emit sendStateToPlayers(gameState.serialize());

}

void Model::generateRandomTableau()
{
    std::cout << "getting into random tableau" << std::endl;

    gameState.tableau.push_back(gameState.personCardStack.at(2));

    for(int i=1; i<11; i++)
    {
        // generate a random index

        // int randomPersonIndex = QRandomGenerator::global()->bounded(gameState.personCardStack.size()-1);

        //not so random random
        int randomPersonIndex =1;

        // put the ID from that index into the tableau
        gameState.tableau.push_back(gameState.personCardStack.at(randomPersonIndex));
        // remove the ID at that index so that the same Person won't be included twice(except duplicate cards)
        //gameState.personCardStack.removeAt(randomPersonIndex);

    }

    QVector<bool> newVector;
    for(int i=0; i<11; i++)
       newVector.push_back(false);

    gameState.tableauCardIsEnabled = newVector;
}

void Model::generateRandomHands()
{
    std::cout << "getting into random hands" << std::endl;
    // for each of the 4 players
    for(int i =0 ; i<4; i++)
    {
        // put 5 unique action cards into their hand
        for(int j =0; j<6; j++)
        {
            // TODO: Fix card gen
            // generate a random index within the actionCardStack
            // int randomActionIndex = QRandomGenerator::global()->bounded(gameState.actionCardStack.size()-1);
            // gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(randomActionIndex));
            // gameState.actionCardStack.removeAt(randomActionIndex);
            gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(8));
        }
    }
}



void Model::populatePeopleMap()
{
    //(value, color, special func)


    //can change num of params later
    peopleTuple tuple(2,1, nullptr);
    //int= card id, tuple contains correspinding card's info
    peopleMap.insert(std::pair<int,peopleTuple>(1,tuple));

    //can change num of params later
    peopleTuple tuple2(2,1, nullptr);
    //int= card id, tuple contains correspinding card's info
    peopleMap.insert(std::pair<int,peopleTuple>(2,tuple2));
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

void Model::populateActionMap()
{
    // add card 2: forward 1, draw another action card


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
        //some function that puts 10 people cards from deck into tableau
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

