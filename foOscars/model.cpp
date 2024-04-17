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
    // int selectedPersonCardInTableau = message.toInt();
    // // int personCardID = gameState.tableau[selectedPersonCardInTableau];

    // actionMap.at(currentAID).function(&gameState, selectedPersonCardInTableau);
    // // emit updateTableauAfterActionCardSelect();
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


    int returnedParam = message.toInt();
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;
    ((*this).*callback)(returnedParam);
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
    else if(indexInTab+params.at(1) > tableau.size()-1)
        gameState.tableau.move(indexInTab, tableau.size()-1);
    else
        gameState.tableau.move(indexInTab, indexInTab - params.at(1));

    //gameState.currentPlayerIndex += 1; *talk to Jai about hadling other player turns
    emit sendStateToPlayers(gameState.serialize());

}


void Model::scoreManipulatorPlayed(int specifiedColor, int colorScoreBuff, int misc)
{

    if(misc==1)
    {
        int numberOfPurps= gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.size();
        drawActionCard(numberOfPurps);
        return;

    }
    else if(misc==2)
    {
        //todo: dealing with number of crew
        return;
    }
    else if(specifiedColor ==-1)
    {
        gameState.players.at(gameState.currentPlayerIndex).score+=colorScoreBuff;
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
    peopleTuple tuple(2,1, &Model::movementCardComplete);
    //int= card id, tuple contains correspinding card's info
    peopleMap.insert(std::pair<int,peopleTuple>(1,tuple));

    //can change num of params later
    peopleTuple tuple2(2,1, &Model::movementCardComplete);
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

void Model::populationActionMap()
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

    //
}

