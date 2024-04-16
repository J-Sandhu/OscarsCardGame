#include "model.h"
Model::Model(QObject *parent) : QObject(parent){

    //populateGameState();
    gameIsStarted=false;
    std::cout << "########## OLD GAME STATE ############" << std::endl;
    std::cout << gameState.serialize().toStdString() << std::endl;


    gameState.deserialize(gameState.serialize());
    std::cout << "############### NEW GAME STATE ################" << std::endl;
    std::cout << gameState.serialize().toStdString() << std::endl;

    // this is one possible format for adding cards core logic.
    // I might turn these into a file that can be read in, but
    // for now this is fine.
    // CardFunction funcTuple(1,1,1,addPointsFromActionCard);
    // actionMap.insert(std::pair<int, CardFunction>(0,funcTuple));

    //Card test(1,1,1,movementCardPlayed, movementCardComplete, false);
    //actionMap.insert(std::pair<int, Card>(0,test));

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
    int selectedPersonCardInTableau = message.toInt();
    // int personCardID = gameState.tableau[selectedPersonCardInTableau];

    // actionMap.at(currentAID).function(&gameState, selectedPersonCardInTableau);
    // emit updateTableauAfterActionCardSelect();
}
void Model::HandleActionSelection(long long id, QString message)
{

    currentPlayerId= id;


    int actionIndex = message.toInt();
    currentAID = gameState.players.at(gameState.currentPlayerIndex).actionPile[actionIndex];

     Card actionCard = actionMap.at(currentAID);
     actionCard.function(actionCard.parameters[0],actionCard.parameters[1],actionCard.parameters[2]);



    // emit actionCardSelectedFromPersonalPile(actionCard);

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
void Model::HandleCallBack(long long id, QString message)
{
    // //as far as i know only one retrun param ever
    // int returnedParam = message.toInt();

    //  Card actionCard = actionMap.at(currentAID);

    //  actionCard.callback(returnedParam);





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

void Model::modelTestMethod()
{
    std::cout << "getting into modelTest Method " << std::endl;
    int* params = actionMap.at(0).parameters;
    std::cout << " getting past parameter cast " << std::endl;
    auto func = actionMap.at(0).function;
    // func(params[0], params[1], params[2]);
}

void Model::movementCardPlayed(int spefiedColor, int unused, int unused1)
{

    std::cout << "getting into move person card emission function" << std::endl;


    // //-1 will be for if there is no spefied color chosing
    // if(spefiedColor=!-1)
    // {
    //     for(int i =0; i<gameState.tableau.size();i++)
    //     {
    //         Card currentCard= personMap.at(gameState.tableau.at(i));
    //         if(currentCard.colorType ==spefiedColor)
    //         {
    //             gameState.tableauEnableds[i]=true;
    //         }
    //     }
    // }

    // //tell view to re-update
    // emit sendStateToPlayer(gameState.serialize(), currentPlayerId);


}

void Model::movementCardComplete(int indexInTab)
{

    // cardTuple actionCard = actionMap.at(currentAID);
    // auto [function, params, callback] = actionCard;
    // int* parameters = params;

    // gameState.tableau.move(indexInTab, indexInTab- parameters[1]);
    // gameState.currentPlayerIndex +=1;
    // emit sendStateToPlayers(gameState.serialize());
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

    // generate random hands
    generateRandomHands();

    //emit signal that game has been initialized and notify mainwindow to upload card images
    //emit gameInitializedSignal();
    emit sendStateToPlayers(gameState.serialize());

}

void Model::generateRandomTableau()
{
    std::cout << "getting into random tableau" << std::endl;
    for(int i=0; i<11; i++)
    {
        // generate a random index
        int randomPersonIndex = QRandomGenerator::global()->bounded(gameState.personCardStack.size()-1);
        // put the ID from that index into the tableau
        gameState.tableau.push_back(gameState.personCardStack.at(randomPersonIndex));
        // remove the ID at that index so that the same Person won't be included twice(except duplicate cards)
        gameState.personCardStack.removeAt(randomPersonIndex);

        //chase's test action
        gameState.tableauEnableds.push_back(false);

    }
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
            // generate a random index within the actionCardStack
            int randomActionIndex = QRandomGenerator::global()->bounded(gameState.actionCardStack.size()-1);
            gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(randomActionIndex));
            gameState.actionCardStack.removeAt(randomActionIndex);
        }
    }
}



