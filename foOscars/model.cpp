#include "model.h"
Model::Model(QObject *parent) : QObject(parent){

    //populateGameState();
    gameIsStarted=false;
    std::cout << "########## OLD GAME STATE ############" << std::endl;
    std::cout << gameState.serialize().toStdString() << std::endl;


    gameState.deserialize(gameState.serialize());
    std::cout << "############### NEW GAME STATE ################" << std::endl;
    std::cout << gameState.serialize().toStdString() << std::endl;

    //creating card 8: move forward 1
    int parameters [3] {-1,1,0}; //can change num of params later
    cardTuple tuple(&Model::movementCardPlayed, parameters, &Model::movementCardComplete);
    //int= card id, tuple contains correspinding card's info
    actionMap.insert(std::pair<int,cardTuple>(8,tuple));

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

    //cardCallBack test = callback;
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

// void Model::modelTestMethod()
// {
//     std::cout << "getting into modelTest Method " << std::endl;
//     int* params = actionMap.at(0).parameters;
//     std::cout << " getting past parameter cast " << std::endl;
//     auto func = actionMap.at(0).function;

//     // func(params[0], params[1], params[2]);
// }

void Model::movementCardPlayed(int specifiedColor, int unused, int unused1)
{
    std::cout << "getting into move person card emission function" << std::endl;

    if (specifiedColor != -1){
        for (int i = 0; i<gameState.tableau.size(); i++){
            peopleTuple person = peopleMap.at(gameState.tableau.at(i));

            auto[value, color, specialFunc] = person;
            if(color == specifiedColor)
            {
                //enable card at index in tableau
            }
        }
    }
    //TODO: rn works with only a host bc it will send the 2nd part of the 2 parter to ALL players (not the one who played the card)
    emit sendStateToPlayers(gameState.serialize());

}

void Model::movementCardComplete(int indexInTab)
{
    //gameState.tableau.move(indexInTab, indexInTab- actionMap.at(selectedActionCardIDFromPersonalPile).parameters[1]);
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    gameState.tableau.move(indexInTab, indexInTab - params[1]);
    //gameState.currentPlayerIndex += 1; *talk to Jai about hadling other player turns
    emit sendStateToPlayers(gameState.serialize());

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


