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


    for (int i=0; i<gameState.players.size(); i++)
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

    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;
    cardFunction cardFunction= function;
    ((*this).*cardFunction)(params[0],params[1],params[2]);
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

void Model::addPointsFromActionCard(int scoreModification, int unused1, int unused2)
{
    // Go into the current player's score manipulator and modify the "additional point" index within
    // score manipulator array.
    gameState.players.at(gameState.currentPlayerIndex).scoreManipulators[4] += scoreModification;
    endOfTurn();
}

void Model::addPointsForColor(int color, int scoreModification, int unused1)
{
    // go into the current player's score manipulator and modify the proper color's additional point field within
    // within the score manipulator array.
    gameState.players.at(gameState.currentPlayerIndex).scoreManipulators[color] = 1;
    endOfTurn();
}

void Model::decreaseOtherPlayerPoints(int victimPlayerIndex, int scoreModification, int unused1)
{
    // go into the victim players score manipulator and modify the "additional point" index within the score manipulator array
    gameState.players.at(victimPlayerIndex).scoreManipulators[4] += scoreModification;
    endOfTurn();
}


void Model::movementCardPlayed(int specifiedColor, int unused, int unused1)
{
    if (specifiedColor != -1){
        // create the vector of non-enabled tableau
        QVector<bool> newVector;

        for(int j =0; j<gameState.tableau.size(); j++)
            newVector.push_back(false);

        for (int i = 0; i<gameState.tableau.size(); i++)
        {
            int colorOfPerson = std::get<1>(peopleMap.at(gameState.tableau.at(i)));

            if(colorOfPerson == specifiedColor)
                gameState.tableauCardIsEnabled.replace(i,true);
            else
                gameState.tableauCardIsEnabled.replace(i,false);
        }
    }
    else
    {
     for(int i =0; i<gameState.tableau.size(); i++)
        gameState.tableauCardIsEnabled.replace(i,true);
    }

    emit sendStateToPlayer(gameState.serialize(), gameState.currentPlayerIndex);
}

void Model::movementCardComplete(int indexInTab)
{
    cardTuple actionCard = actionMap.at(currentAID);
    auto[function, params, callback] = actionCard;

    if(indexInTab-params.at(1) < 0)
        gameState.tableau.move(indexInTab,0);
    else if(indexInTab-params.at(1) > gameState.tableau.size()-1)
        gameState.tableau.move(indexInTab, gameState.tableau.size()-1);
    else
        gameState.tableau.move(indexInTab, indexInTab - params.at(1));

    endOfTurn();

}

//for card 14
void Model::frontToBack(int unused, int unused1, int unused2)
{
    int firstCard=gameState.tableau.first();
    gameState.tableau.removeFirst();
    gameState.tableau.push_back(firstCard);
    endOfTurn();
}

//reuse for 16, 17, 20
void Model::shuffleTableauPlayed(int numCardsToShuffle,int unused, int unused2)
{
    if(gameState.tableau.size() < numCardsToShuffle)
        numCardsToShuffle = gameState.tableau.size();

    for (int i = 0; i < numCardsToShuffle / 2; i++) {
        // Calculate the index of the corresponding element from the end
        int j = numCardsToShuffle - 1 - i;

        // Swap elements at index i and j
        int temp =  gameState.tableau[i];
        gameState.tableau[i] =  gameState.tableau[j];
        gameState.tableau[j] = temp;
    }

    //notify other players
    endOfTurn();
}

//for card 16
void Model::shuffleTableauPlayed16(int unused, int unused1, int unused2)
{
    shuffleTableauPlayed(4, 0, 0);
    endOfTurn();
}

//for card 17
void Model::shuffleTableauPlayed17(int unused, int unused1, int unused2)
{
    shuffleTableauPlayed(5, 0, 0);
    endOfTurn();
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

    endOfTurn();
}


//for card 19
void Model::newLinePlayed(int unused, int unused1, int unused2)
{
    generateRandomTableau(gameState.personCardStack, 10);
    endOfTurn();
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
    endOfTurn();
}



//for card 22
void Model::addToTableau(int numCardsToAdd, int unused, int unused1){

    numCardsToAdd = 3;

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

//for card 23
void Model::addFromTopThree(int unused, int unused1, int unused2){
    int numToChoose = 3;
    if(gameState.personCardStack.size() < numToChoose)
        numToChoose = gameState.personCardStack.size();

    int chosenIndex = std::rand() % numToChoose;

    gameState.tableauCardIsEnabled.push_back(false);
    gameState.tableau.push_back(gameState.personCardStack.at(chosenIndex));
    gameState.personCardStack.removeAt(chosenIndex);

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
        peopleTuple person = peopleMap[gameState.tableau.at(i)];
        auto[value, color, specialFunc] = person;

        if(color == specifiedColor) //if a blue card exists
        {
            closestBlueIndex = i;
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
\
//for card 38
void Model::skipPlayer(int unused, int unused1, int unused2){
    endOfTurn();
    endOfTurn();
}

//for card 47
void Model::blockPlayer(int unused, int unused1, int unused2){
    skipPlayer(0,0,0);
}

//for card 39 - take discarded action (random)
void Model::takeDiscardedAction(int unused, int unused1, int unused2)
{
    int randomIndex = std::rand() % gameState.actionCardStack.size();
    gameState.players.at(gameState.currentPlayerIndex).actionPile.push_back(gameState.actionCardStack.at(randomIndex));
    gameState.actionCardStack.removeAt(randomIndex);
    endOfTurn();
}

//for card 41 - draw 3 action, don't take a noble
void Model::drawThreeActionNoNoble(int unused, int unused1, int unused3)
{
    drawActionCard(3);
    if(gameState.tableau.empty())
    {
        if (gameState.round==4)
            endGame();
        else
        {
            gameState.round+=1;
            generateRandomTableau(gameState.personCardStack,10);
        }
    }


    //move to next players turn
    if(gameState.currentPlayerIndex+=1>gameState.players.size()-1)
        gameState.currentPlayerIndex=0;
    else
        gameState.currentPlayerIndex+=1;

    // return the tableauCardEnabled vector for false
    QVector<bool> enabledVec;
    for(int i=0; i<gameState.tableau.size(); i++)
        enabledVec.push_back(false);

    gameState.tableauCardIsEnabled = enabledVec;

    recalculateScore();

    emit sendStateToPlayers(gameState.serialize());
}


//for card 43 - everyone remove an action
void Model::allRemoveAnAction(int unused, int unused1, int unused2)
{
    for(int i = 0; i < gameState.players.size(); i++)
        gameState.players.at(i).actionPile.removeAt(std::rand() % gameState.players.size());

    endOfTurn();
}

//for card 46 - swap hands, 1
void Model::choosePlayer( int unuse, int unused, int unused2)
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
void Model::dealNewActionCard(int unused2, int unused, int unused1)
{
    for(int i = 0; i< gameState.players.size(); i++)
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
void Model::discardOneAction(int unused0, int unused1, int unused2)
{
    //for each player
    for(int i =0 ; i<gameState.players.size(); i++)
        gameState.players.at(i).actionPile.removeAt(gameState.players.at(i).actionPile.at(gameState.players.at(i).selectedActionIndex));

    endOfTurn();
}

void Model::afterYou(int victimPlayerIndex)
{
    int firstCardID = gameState.tableau.at(0);          //get the id of the first card
    peopleTuple person = peopleMap[firstCardID];        //get the card associated with first card
    auto[value, color, specialFunc] = person;           //get details of card
    gameState.tableau.removeFirst();                    //remove card

    if(color==purple)
        gameState.players.at(victimPlayerIndex).purplePeoplePile.push_back(firstCardID);
    else if (color==blue)
        gameState.players.at(victimPlayerIndex).bluePeoplePile.push_back(firstCardID);
    else if (color==red)
        gameState.players.at(victimPlayerIndex).redPeoplePile.push_back(firstCardID);
    else if (color==green)
        gameState.players.at(victimPlayerIndex).greenPeoplePile.push_back(firstCardID);

    endOfTurn();
}

void Model::scoreManipulatorPlayed(int specifiedColor, int colorScoreBuff, int misc)
{
    if(specifiedColor ==anyColor)
    {
        gameState.players.at(gameState.currentPlayerIndex).miscPoint+=colorScoreBuff;
        endOfTurn();
        return;
    }
    if(specifiedColor==purple)
    {
        int numberOfPurps= gameState.players.at(gameState.currentPlayerIndex).purplePeoplePile.size();
        drawActionCard(numberOfPurps);
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

    gameState.round=2;
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

    generateRandomTableau(gameState.personCardStack, 10);
    populatePeopleMap();

    // generate random hands
    generateRandomHands();

    //emit signal that game has been initialized and notify mainwindow to upload card images
    emit sendStateToPlayers(gameState.serialize());

}

void Model::generateRandomTableau(QVector<int> availablePeople, int size)
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

void Model::shuffleTableau()
{
    QVector<int> tableauCopy(gameState.tableau);

    gameState.tableau.clear();
    for(int i = 0; i<tableauCopy.size(); i++)
    {
        int randomTableauIndex = QRandomGenerator::global()->bounded(tableauCopy.size());
        gameState.tableau.push_back(tableauCopy.at(randomTableauIndex));
        tableauCopy.removeAt(randomTableauIndex);
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
    for(int i =0 ; i<gameState.players.size(); i++)
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


void Model::mixAfterTurn(int unused, int unused1, int unuesed2)
{

    //this is not going to call end of turn
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




    gameState.round+=1;
        if (gameState.round==4)
            endGame();
        else
        {
            //some function that puts 10 people cards from deck into tableau
        }

    //could be more based on the people card picked up
    drawActionCard(1);

    //move to next players turn
    if(gameState.currentPlayerIndex+=1>gameState.players.size()-1)
        gameState.currentPlayerIndex=0;
    else
        gameState.currentPlayerIndex+=1;

    shuffleTableau();


    emit sendStateToPlayers(gameState.serialize());

}

void Model::populateActionMap()
{
    //add card 0: after you
    QVector<int> parameters0{0,0,0};
    cardTuple tuple0(&Model::choosePlayer,parameters0,&Model::afterYou);
    actionMap.insert(std::pair<int,cardTuple>(0,tuple0));


    // add card 1: Re-cast
    QVector<int> parameters1{-1,0,0};
    cardTuple tuple1(&Model::movementCardPlayed,parameters1,&Model::replacePerson);
    actionMap.insert(std::pair<int,cardTuple>(1,tuple1));

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
    QVector<int> parameters6{2,2,0};
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

    // add card 12: Jell Cell Tengo
    QVector<int> parameters12{-1,0,0};
    cardTuple tuple12(&Model::movementCardPlayed,parameters12,&Model::discardPerson);
    actionMap.insert(std::pair<int,cardTuple>(12,tuple12));



    // add card 13: winners walk
    QVector<int> parameters13{-1,100,0}; // enough to bring any card to the front
    cardTuple tuple13(&Model::movementCardPlayed, parameters13, &Model::movementCardComplete);
    actionMap.insert(std::pair<int,cardTuple>(13,tuple13));

    // add card 14: move the front card to the back
    QVector<int> parameters14{-1,0,0}; // enough to bring any card to the front
    cardTuple tuple14(&Model::frontToBack, parameters14, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(14,tuple14));

    // add card 15: green up 3
    QVector<int> parameters15{1,3,0};
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

    //add card 21: mislabled envelops
    QVector<int> parameters21{0,-1,0};
    cardTuple tuple21(&Model::mixAfterTurn, parameters21, nullptr);
    actionMap.insert(std::pair<int, cardTuple>(21, tuple21));

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
    QVector<int> parameters29{anyColor,0,0};
    cardTuple tuple29(&Model::neutralizeGrays,parameters29, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(29, tuple29));


    //(int specifiedColor, int colorScoreBuff, int misc)
    //add card 30: +1 action for every purple
    QVector<int> parameters30{purple,0,0};
    cardTuple tuple30(&Model::scoreManipulatorPlayed, parameters30, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(30,tuple30));

    //add card 31: disqualified
    QVector<int> parameters31{0,0,0};
    cardTuple tuple31(&Model::choosePlayer,parameters31,&Model::disqualification);
    actionMap.insert(std::pair<int,cardTuple>(31,tuple31));

    QVector<int> parameters32{-1,0,0};
    cardTuple tuple32(&Model::choosePlayer, parameters32, &Model::makeDiscardAction);
    actionMap.insert(std::pair<int,cardTuple>(32, tuple32));

    // add card 33: the same as card 14. sorry chase :(
    actionMap.insert(std::pair<int,cardTuple>(33,tuple14));

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

    //add card 38: eastwood
    QVector<int> parameters38{-1,0,0};
    cardTuple tuple38(&Model::skipPlayer, parameters38, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(38,tuple38));

    //add card 39: choose AC from discarded pile
    QVector<int> parameters39{-1,0,0};
    cardTuple tuple39(&Model::takeDiscardedAction, parameters39, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(39,tuple39));



    // add card 40: choose a players action card to discard
    QVector<int> parameters40{1,0,0};
    cardTuple tuple40(&Model::choosePlayer, parameters40, &Model::makeDiscardAction);
    actionMap.insert(std::pair<int,cardTuple>(40, tuple40));

    //add card 41: draw 3 actions
    QVector<int> parameters41{-1,0,0};
    cardTuple tuple41(&Model::drawThreeActionNoNoble, parameters41, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(41,tuple41));

    //add card 42: deal new action cards
    QVector<int> parameters42{-1,0,0};
    cardTuple tuple42(&Model::dealNewActionCard, parameters42, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(42,tuple42));

    // //add card 43: discard two action
    QVector<int> parameters43{2,0,0};
    cardTuple tuple43(&Model::choosePlayer, parameters43, &Model::makeDiscardAction);
    actionMap.insert(std::pair<int,cardTuple>(43, tuple43));

    //add card 44: all players discard a random action
    QVector<int> parameters44{-1,0,0};
    cardTuple tuple44(&Model::allRemoveAnAction, parameters44, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(44,tuple44));

    // add card 45: blacklisted choose a player and discards on of them
    QVector<int> parameters45{1,0,0};
    cardTuple tuple45(&Model::choosePlayer, parameters45, &Model::makeDiscardAction);
    actionMap.insert(std::pair<int,cardTuple>(45, tuple45));

    //add card 46: deal new action cards
    QVector<int> parameters46{-1,0,0};
    cardTuple tuple46(&Model::choosePlayer, parameters46, &Model::swapHandsComplete);
    actionMap.insert(std::pair<int,cardTuple>(46,tuple46));

    //add card 47: block player
    QVector<int> parameters47{-1,0,0};
    cardTuple tuple47(&Model::blockPlayer, parameters47, nullptr);
    actionMap.insert(std::pair<int,cardTuple>(47,tuple47));

    //add card 48: scarlet pimpernel
    QVector<int> parameters48{-1,0,0};
    cardTuple tuple48(&Model::endDay, parameters48,nullptr);
    actionMap.insert(std::pair<int,cardTuple>(48,tuple48));
}


void Model::endOfTurn()
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
            generateRandomTableau(gameState.personCardStack,10);
        }
    }

    //could be more based on the people card picked up
    drawActionCard(1);

    //move to next players turn
    if(gameState.currentPlayerIndex+1>gameState.players.size()-1)
        gameState.currentPlayerIndex=0;
    else
        gameState.currentPlayerIndex+=1;

    // return the tableauCardEnabled vector for false
    QVector<bool> enabledVec;
    for(int i=0; i<gameState.tableau.size(); i++)
        enabledVec.push_back(false);

    gameState.tableauCardIsEnabled = enabledVec;

    recalculateScore();

    gameState.playerButtonsEnabled = false;

    emit sendStateToPlayers(gameState.serialize());
}



void Model::recalculateScore()
{
    for (int playerIndex=0; playerIndex<gameState.players.size();playerIndex++)
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

void Model::endDay(int, int, int)
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

void Model::neutralizeGrays(int unused,int unused1,int unused2)
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

