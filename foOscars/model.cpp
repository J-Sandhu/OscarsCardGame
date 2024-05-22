#include "model.h"
Model::Model(QObject *parent) : QObject(parent){
    gameIsStarted=false;
    populatePeopleMap();
    populateActionMap();
}

void Model::HandlePlayerName(long long id, QString message)
{
    if (message.toStdString()=="player")
        message.append(to_string(id));


    for (int i=0; i<(int)gameState.players.size(); i++)
        if (gameState.players.at(i).id==id)
        {
            gameState.players.at(i).name=message;
            emit sendChatToPlayers(message.append(" has joined the game"));
            emit sendStateToPlayers(gameState.serialize());
        }

}

void Model::HandleChatMessage(long long id, QString message)
{
    string sender;
    foreach (Player p, gameState.players)
        if (p.id==id)
            sender = p.name.toStdString()+": ";
    message.prepend(sender);

    emit sendChatToPlayers(message);
}

void Model::HandleTableauSelection(long long id, QString message)
{
    if(id !=gameState.players[gameState.currentPlayerIndex].id)
        return;

    int returnedParam = message.toInt();
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    std::cout<<"Current AID: "<<currentAID<<" and returned param: "<<returnedParam<<std::endl;

    ((*this).*callback)(returnedParam);
}

void Model::HandleActionSelection(long long id, QString message)
{
    if(id !=gameState.players.at(gameState.currentPlayerIndex).id)
        return;


    int actionIndex = message.toInt(); //index corresponds to the current player's hand.
    currentAID = gameState.players.at(gameState.currentPlayerIndex).actionPile.at(actionIndex);
    gameState.actionCardStack.push_back(currentAID);

    //remove action card from player's hand.
    gameState.players.at(gameState.currentPlayerIndex).actionPile.removeAt(actionIndex);
    emit sendStateToPlayer(gameState.serialize(), gameState.currentPlayerIndex);


    cardFunction cardFunction= std::get<0>(actionMap.at(currentAID));


    ((*this).*cardFunction)();
}

void Model::HandleStartGame(long long id)
{
    if (gameIsStarted)
        return;

    if (id==gameState.players.at(0).id)
        populateGameState();
}

void Model::HandleSelectedPlayer(long long id, QString message)
{

    if(id !=gameState.players[gameState.currentPlayerIndex].id)
        return;

    int returnedParam = message.toInt();
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;
    ((*this).*callback)(returnedParam);
}


void Model::movementCardPlayed()
{
    auto params= std::get<1>(actionMap.at(currentAID));
    int enabledColor = params.at(0);

    if (enabledColor == anyColor){
        for(int i =0; i<gameState.tableau.size(); i++)
            gameState.tableauCardIsEnabled.replace(i,true);
    }
    else
    {
        for (int i = 0; i<gameState.tableau.size(); i++)
        {
            int colorOfPersonCard = std::get<1>(peopleMap.at(gameState.tableau.at(i)));

            if(colorOfPersonCard == enabledColor)
                gameState.tableauCardIsEnabled.replace(i,true);
            else
                gameState.tableauCardIsEnabled.replace(i,false);
        }
    }

    emit sendStateToPlayer(gameState.serialize(), gameState.currentPlayerIndex);
}

void Model::movementCardComplete(int locationInTab)
{
    auto params = std::get<1>(actionMap.at(currentAID));
    int numMovements =params.at(1);

    std::cout<<"Location in Tab: "<<locationInTab<<" and numOfMovemnets: "<<numMovements<<endl;
    if(locationInTab-numMovements<0)
        gameState.tableau.move(locationInTab,0);
    else if(locationInTab-numMovements > gameState.tableau.size()-1)
        gameState.tableau.move(locationInTab, gameState.tableau.size()-1);
    else
        gameState.tableau.move(locationInTab, locationInTab -numMovements);

    endOfTurn();

}

//for card 14
void Model::frontToBack()
{
    int firstCard=gameState.tableau.first();
    gameState.tableau.removeFirst();
    gameState.tableau.push_back(firstCard);
    endOfTurn();
}

//reuse for 16, 17, 20
void Model::shuffleTableauPlayed()
{
    auto params = std::get<1>(actionMap.at(currentAID));
    int numOfCardsToShuffle =params.at(1)-1;

    if(gameState.tableau.size() < numOfCardsToShuffle)
        random_shuffle(&gameState.tableau[0], &gameState.tableau[gameState.tableau.size()]);
    else
        random_shuffle(&gameState.tableau[0], &gameState.tableau[numOfCardsToShuffle]);

    //notify other players
    endOfTurn();
}

//for card 18
void Model::reverseLine()
{

    std::reverse(gameState.tableau.begin(), gameState.tableau.end());
    endOfTurn();
}


//for card 19
void Model::newLine()
{
    generateRandomTableau(10);
    endOfTurn();
}

//for card 20
void Model::escapeCardPlayed()
{
    //enable all the cards on tableau
    for(int i =0; i<gameState.tableau.size(); i++)
        gameState.tableauCardIsEnabled.replace(i,true);

    emit sendStateToPlayers(gameState.serialize());

}
//for card20 - remove and shuffle
void Model::escapeCardPlayedCallBack(int chosenIndex)
{
    gameState.tableau.removeAt(chosenIndex);

    //disable cards
    for(int i =0; i<gameState.tableau.size(); i++)
        gameState.tableauCardIsEnabled.replace(i,false);

    shuffleTableauPlayed();
}



//for card 22
void Model::addToTableau(){

    auto params = std::get<1>(actionMap.at(currentAID));
    int numCardsToAdd =params.at(1);

    if(gameState.personCardStack.size() < numCardsToAdd)
        numCardsToAdd = gameState.personCardStack.size();

    for (int i = 0; i<numCardsToAdd; i++)
    {
        int rand = std::rand() % gameState.personCardStack.size();
        gameState.tableauCardIsEnabled.push_back(false);
        gameState.tableau.push_back(gameState.personCardStack.at(rand));
        gameState.personCardStack.removeAt(rand);
    }

    endOfTurn();
}

//for card 31
void Model::disqualification(int victimPlayerIndex)
{
    Player* victim = &gameState.players.at(victimPlayerIndex);
    int peopleCardAmount = victim->purplePeoplePile.size();
    peopleCardAmount += victim->bluePeoplePile.size();
    peopleCardAmount += victim->redPeoplePile.size();
    peopleCardAmount += victim->greenPeoplePile.size();

    if (peopleCardAmount==0)
    {
        endOfTurn();
        return;
    }

    int cardNum= QRandomGenerator::global()->bounded(peopleCardAmount)+1;
    if (cardNum<= victim->purplePeoplePile.size())
    {
        victim->purplePeoplePile.removeAt(cardNum-1);
        endOfTurn();
        return;
    }

    cardNum -= victim->purplePeoplePile.size();

    if (cardNum<= victim->bluePeoplePile.size())
    {
        victim->bluePeoplePile.removeAt(cardNum-1);
        endOfTurn();
        return;
    }
    cardNum -= victim->bluePeoplePile.size();

    if (cardNum<= victim->redPeoplePile.size())
    {
        victim->redPeoplePile.removeAt(cardNum-1);
        endOfTurn();
        return;
    }
    cardNum -= victim->redPeoplePile.size();

    victim->greenPeoplePile.removeAt(cardNum-1);

    endOfTurn();
}

//for card 34
void Model::personToFront()
{
    auto params = std::get<1>(actionMap.at(currentAID));
    int idToFront = params.at(0);

    //disable cards
    for (int i = 0; i < gameState.tableau.size(); i++) {
        gameState.tableauCardIsEnabled.replace(i,false);
    }

    int indexInTableau;

    for (int i = 0; i< gameState.tableau.size(); i++)
    {
        if (gameState.tableau.at(i) == idToFront)
        {
            indexInTableau = i;
            gameState.tableau.move(indexInTableau, 0);
            break;
        }
    }

    endOfTurn();
}

// for card 35
void Model::moveClosestColorToFront()
{
    auto params = std::get<1>(actionMap.at(currentAID));
    int color = params.at(0);

    //disable cards
    for (int i = 0; i < gameState.tableau.size(); i++) {
        gameState.tableauCardIsEnabled.replace(i,false);
    }

    //find a blue card
    int closestColorIndex;

    for(int i=0; i<gameState.tableau.size(); i++)
    { 
        int personColor = std::get<1>(peopleMap[gameState.tableau.at(i)]);

        if(color == personColor) //if a blue card exists
        {
            closestColorIndex = i;
            gameState.tableau.move(closestColorIndex, 0);
            break;
        }
    }
    endOfTurn();
}


//for card 38
void Model::skipPlayer(){
    endOfTurn(false, true,false,0);
    endOfTurn(false, false, true, 0);

}



//for card 39 - take discarded action (random)
void Model::takeDiscardedAction()
{
    int randomIndex = std::rand() % gameState.actionCardStack.size();
    gameState.players.at(gameState.currentPlayerIndex).actionPile.push_back(gameState.actionCardStack.at(randomIndex));
    gameState.actionCardStack.removeAt(randomIndex);
    endOfTurn();
}

//for card 41 - draw 3 action, don't take a noble
void Model::drawExtraActionNoNoble()
{
    auto params =std::get<1>(actionMap.at(currentAID));
    int numberOfExtraAction= params[0];

    endOfTurn(false, false, numberOfExtraAction);
}


//for card 43 - everyone remove an action
void Model::allRemoveAnAction()
{
    for(int i = 0; i < (int)gameState.players.size(); i++)
        gameState.players.at(i).actionPile.removeAt(std::rand() % gameState.players.size());

    endOfTurn();
}

//for card 46 - swap hands, 1
void Model::choosePlayer()
{
    gameState.playerButtonsEnabled=true;

    emit sendStateToPlayer(gameState.serialize(),gameState.currentPlayerIndex);
}

void Model::swapHandsComplete(int victimPlayer)
{
    //swap victim and current player's action piles
    gameState.players.at(victimPlayer).actionPile.swap(
        gameState.players.at(gameState.currentPlayerIndex).actionPile);

    endOfTurn();
}

//for card 42 - deal new action card for all players
void Model::dealNewActionCard()
{
    for(int i = 0; i< (int)gameState.players.size(); i++)
    {
        for(int j=0; j<gameState.players.at(i).actionPile.size();i++)
        {
            int id = gameState.players.at(i).actionPile.at(j);
            gameState.players.at(i).actionPile.removeAt(j);
            gameState.actionCardStack.push_back(id);
        }
    }
    generateRandomHands();
    endOfTurn();
}

//for card 44 - all players must discard 1 action card
void Model::discardOneAction()
{
    //for each player
    for(int i =0 ; i<(int)gameState.players.size(); i++)
        gameState.players.at(i).actionPile.removeAt(gameState.players.at(i).actionPile.at(gameState.players.at(i).selectedActionIndex));

    endOfTurn();
}

void Model::afterYou(int victimPlayerIndex)
{
    int attackerID= gameState.currentPlayerIndex;
    gameState.currentPlayerIndex = victimPlayerIndex;
    collectPerson();

    gameState.currentPlayerIndex = attackerID;
    endOfTurn();
}

void Model::scoreManipulatorPlayed()
{
    auto params =std::get<1>(actionMap.at(currentAID));
    int specifiedColor= params[0];
    int colorScoreBuff= params[1];

    if(specifiedColor ==anyColor)
    {
        gameState.players.at(gameState.currentPlayerIndex).miscPoint+=colorScoreBuff;
        endOfTurn();
        return;
    }
    else if(specifiedColor==purple)
    {
        int numberOfPurps= gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.size();
        endOfTurn(false,numberOfPurps);
        return;
    }
    else if(specifiedColor==gray)
    {
        neutralizeGrays();
        endOfTurn();
        return;
    }
    else
    {
        gameState.players.at(gameState.currentPlayerIndex).scoreManipulators[specifiedColor]=colorScoreBuff;
        endOfTurn();
    }
}


void Model::populateGameState()
{

    //clear ppl stack
    gameState.personCardStack.clear();

    gameState.round=1;
    gameState.currentPlayerIndex=0;
    gameState.gameOver=false;

    // populate the vector with the ids of action cards
    for(int i=0; i<49; i++)
    {
        // cards we no longer want 20, 42, 17, 45
        if(i == 20 || i == 42 || i == 17 ||i == 45)
            continue;

        gameState.actionCardStack.push_back(i);
    }

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

    generateRandomTableau(10);
    populatePeopleMap();

    // generate random hands
    generateRandomHands();

    //emit signal that game has been initialized and notify mainwindow to upload card images
    emit sendStateToPlayers(gameState.serialize());

}

void Model::generateRandomTableau(int size)
{
    gameState.tableau.clear();

    // Only populate tableau with people cards that exist according to available people
    for(int i=0; i<size; i++)
    {
        // generate a random index
        int randomExistingPersonIndex = QRandomGenerator::global()->bounded(gameState.personCardStack.size());
        gameState.tableau.push_back(gameState.personCardStack.at(randomExistingPersonIndex));//availablePeople.at(randomExistingPersonIndex));
        gameState.personCardStack.remove(randomExistingPersonIndex);
    }

    QVector<bool> newVector;
    for(int i=0; i<gameState.tableau.size(); i++)
        newVector.push_back(false);

    gameState.tableauCardIsEnabled = newVector;
}

void Model::generateRandomHands()
{
    // Only populate hands with aciton cards that exist
    QVector<int> existingActionCards;

    for(std::map<int,cardTuple>::iterator it = actionMap.begin(); it != actionMap.end(); ++it)
        existingActionCards.push_back(it->first);

    // for each of the joined players
    for(int i =0 ; i<(int)gameState.players.size(); i++)
    {
        // put 5 unique action cards into their hand
        for(int j =0; j<5; j++)
        {
            int randomExistingActionIndex = QRandomGenerator::global()->bounded(gameState.actionCardStack.size());
            gameState.players.at(i).actionPile.push_back(gameState.actionCardStack.at(randomExistingActionIndex));
            gameState.actionCardStack.removeAt(randomExistingActionIndex);
        }
    }
}



void Model::populatePeopleMap()
{
    QFile file(":/people/peopleInfo");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!file.atEnd())
    {
        QString personInfo = file.readLine();
        QStringList list = personInfo.split(",");

        peopleTuple tuple(list.at(1).toInt(),list.at(2).toInt(),list.at(3));
        peopleMap.insert(std::pair<int,peopleTuple>(list.at(0).toInt(),tuple));
    }
    file.close();
}


void Model::drawActionCard(int numberOfCards)
{
    for(int i =0;i<numberOfCards;i++)
    {
        int randomActionIndex = QRandomGenerator::global()->bounded(gameState.actionCardStack.size());

        int randomActionID= gameState.actionCardStack.at(randomActionIndex);

        gameState.players.at(gameState.currentPlayerIndex).actionPile.push_back(randomActionID);
        gameState.actionCardStack.removeAt(randomActionIndex);
    }

}

void Model::replacePerson(int indexInTab)
{

    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    int randomPersonID= QRandomGenerator::global()->bounded(gameState.personCardStack.size());

    gameState.tableau.replace(indexInTab, gameState.personCardStack.at(randomPersonID));
    gameState.personCardStack.removeAt(randomPersonID);

    endOfTurn();

}

void Model::discardPerson(int indexInTab)
{
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    gameState.tableau.remove(indexInTab);

    endOfTurn();
}


void Model::mixAfterTurn()
{
    //end of turn allows two default params, shuffle after turn and pick up extra actions.
    endOfTurn(true,true,0);
}


void Model::populateActionMap()
{

    QFile file(":/actions/actionInfo");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!file.atEnd())
    {

        QString cardInfo = file.readLine();
        QStringList list = cardInfo.split(",");

        QVector<int> parameters{list.at(2).toInt(),list.at(3).toInt(),list.at(4).toInt()};

        cardTuple tuple;



        if(list.at(5).trimmed()=="nullptr")
            tuple= cardTuple(functionMap[list.at(1)],parameters,nullptr);
        else
            tuple= cardTuple(functionMap[list.at(1)],parameters,callBackMap[list.at(5).trimmed()]);

        actionMap.insert(std::pair<int,cardTuple>(list.at(0).toInt(),tuple));
    }
    file.close();


}


void Model::endOfTurn(bool mixAfterPlayerTurn, bool collectOnTurn, bool emitOnTurn, int extraActions)
{
    if(collectOnTurn)
        collectPerson();

    //could be more based on the people card picked up
    drawActionCard(1+extraActions);

    //move to next players turn

    incrementPlayerTurn();

    if(mixAfterPlayerTurn)
        shuffleTableauPlayed();

    // return the tableauCardEnabled vector for false
    for(int i=0; i<gameState.tableau.size(); i++)
        gameState.tableauCardIsEnabled.replace(i,false);

    recalculateScore();

    gameState.playerButtonsEnabled = false;

    if(emitOnTurn)
        emit sendStateToPlayers(gameState.serialize());
}

void Model::collectPerson()
{
    int personCollectedId =gameState.tableau.at(0);

    gameState.tableau.removeAt(0);


    int color = std::get<1>(peopleMap.at(personCollectedId));
    int score = std::get<0>(peopleMap.at(personCollectedId));

    //check which color
    if(color == blue)
        gameState.players.at(gameState.currentPlayerIndex).bluePeoplePile.append(personCollectedId);
    else if(color == green)
        gameState.players.at(gameState.currentPlayerIndex).greenPeoplePile.append(personCollectedId);
    else if(color ==purple)
        gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.append(personCollectedId);
    else if(color ==red)
        gameState.players.at(gameState.currentPlayerIndex).redPeoplePile.append(personCollectedId);

    QString playerCollectionMessage= gameState.players.at(gameState.currentPlayerIndex).name;
    playerCollectionMessage.append(tr(" collected "));
    playerCollectionMessage.append(std::get<2>(peopleMap.at(personCollectedId)));
    playerCollectionMessage.append(tr(", worth "));
    playerCollectionMessage.append(QString::number(score));
    playerCollectionMessage.append(tr(" points"));


    emit sendChatToPlayers(playerCollectionMessage);

    if(gameState.tableau.empty())
    {
        if (gameState.round==4)
            endGame();
        else
        {
            gameState.round+=1;
            generateRandomTableau(10);
        }
    }
}

void Model::incrementPlayerTurn()
{
    if(gameState.currentPlayerIndex+1>(int)gameState.players.size()-1)
        gameState.currentPlayerIndex=0;
    else
        gameState.currentPlayerIndex+=1;
}





void Model::recalculateScore()
{
    for (int playerIndex=0; playerIndex<(int)gameState.players.size();playerIndex++)
    {
        int updatedScore=0;

        //color pile sums
        for(int i=0;i<numberOfColors;i++)
            updatedScore += calulateColorSum(i, gameState.players.at(playerIndex).scoreManipulators.at(i), playerIndex);

        //crew stuff
        int num_Of_Crew=0;
        int id_Of_Crew=12;
        for(int person : gameState.players.at(playerIndex).greenPeoplePile)
        {
            if(person==id_Of_Crew)
                num_Of_Crew++;   
        }


        gameState.players.at(playerIndex).score+= num_Of_Crew * num_Of_Crew;
        updatedScore+= gameState.players.at(playerIndex).miscPoint;

        gameState.players.at(playerIndex).score= updatedScore;
    }
}

int Model::calulateColorSum(int color, bool manipultorEnabled, int playerIndex)
{
    QVector<int> vectorToBeSummed;

    //check which color
    if(color ==blue)
        vectorToBeSummed= gameState.players.at(playerIndex).bluePeoplePile;
    else if(color == green)
        vectorToBeSummed = gameState.players.at(playerIndex).greenPeoplePile;
    else if(color ==purple)
        vectorToBeSummed=gameState.players.at(playerIndex).purplePeoplePile;
    else if(color ==red)
        vectorToBeSummed=gameState.players.at(playerIndex).redPeoplePile;

    //sum that color pile
    int pileSum=0;
    for(int person : vectorToBeSummed )
    {
        // hard coded special pairs
        if(person==0 && gameState.players.at(playerIndex).bluePeoplePile.contains(6))
            pileSum+=std::get<0>(peopleMap.at(person))*3;
        if(person==7 && gameState.players.at(playerIndex).redPeoplePile.contains(37))
            pileSum+=std::get<0>(peopleMap.at(person))*3;
        if(person==10 && gameState.players.at(playerIndex).redPeoplePile.contains(40))
            pileSum+=std::get<0>(peopleMap.at(person))*3;
        if(person==16 && gameState.players.at(playerIndex).greenPeoplePile.contains(18))
            pileSum+=std::get<0>(peopleMap.at(person))*3;
        else
            pileSum+=std::get<0>(peopleMap.at(person));
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

void Model::endDay()
{
    endOfTurn();
    endGame();
}

void Model::addNewPlayer(long long id)
{
    Player newPlayer;
    newPlayer.id = id;

    gameState.players.push_back(newPlayer);

    emit sendStateToPlayers(gameState.serialize());
}

void Model::neutralizeGrays()
{

    if (gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.contains(19))
    {
        int romanIndex= gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.indexOf(19);
        gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.removeAt(romanIndex);
    }
    if (gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.contains(23))
    {
        int ALMIndex= gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.indexOf(23);
        gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.removeAt(ALMIndex);
    }

    endOfTurn();
}

void Model::makeDiscardAction(int victimPlayerIndex)
{

    // if its a negative 1, its take one have one taken
    if(std::get<1>(actionMap.at(currentAID))[0] == -1)
    {
        // choose random action in victim
        int randomActionIndex = QRandomGenerator::global()->bounded(gameState.players.at(victimPlayerIndex).actionPile.size());
        int otherActionCard = gameState.players.at(victimPlayerIndex).actionPile.at(randomActionIndex);

        // choose random action in yourself
        int otherRandomIndex = QRandomGenerator::global()->bounded(gameState.players.at(gameState.currentPlayerIndex).actionPile.size());
        int yourActionCard = gameState.players.at(gameState.currentPlayerIndex).actionPile.at(otherRandomIndex);

        gameState.players.at(victimPlayerIndex).actionPile.removeAt(randomActionIndex);
        gameState.players.at(victimPlayerIndex).actionPile.push_back(yourActionCard);

        gameState.players.at(gameState.currentPlayerIndex).actionPile.removeAt(otherRandomIndex);
        gameState.players.at(gameState.currentPlayerIndex).actionPile.push_back(otherActionCard);

    }
    // otherwise, proceed as normal where first parameter is the number of cards to be taken from victim
    else
    {
        for(int i=0; i<std::get<1>(actionMap.at(currentAID))[0]; i++)
        {
            int randomActionIndex = QRandomGenerator::global()->bounded(gameState.players.at(victimPlayerIndex).actionPile.size());
            gameState.players.at(victimPlayerIndex).actionPile.removeAt(randomActionIndex);
        }
    }

    endOfTurn();
}

