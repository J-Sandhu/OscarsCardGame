#include "gamestate.h"
#include <QDebug>

GameState::GameState() {}

void GameState::deserialize(QByteArray serializedGameState)
{
    resetGameState();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(serializedGameState);

    QJsonObject jsonObj = jsonDoc.object();

    QJsonArray jsonPlayerArr= jsonObj["Players"].toArray();

    for (int i=0; i< jsonPlayerArr.size(); i++)
    {
        // initialize a player to be copied into
        Player newPlayer;
        QJsonObject thisPlayer = jsonPlayerArr.at(i).toObject();
        newPlayer.score = thisPlayer["Score"].toInt();
        newPlayer.name = thisPlayer["Name"].toString();
        QJsonArray actionPileArray = thisPlayer["Action_Pile"].toArray();
        QJsonArray blueManGroup = thisPlayer["Blue_Pile"].toArray();
        QJsonArray redGroup = thisPlayer["Red_Pile"].toArray();
        QJsonArray greenGroup = thisPlayer["Green_Pile"].toArray();
        QJsonArray purpleGroup = thisPlayer["Purple_Pile"].toArray();

        for(auto action : actionPileArray)
            newPlayer.actionPile.push_back(action.toInt());

        for(auto blue : blueManGroup)
            newPlayer.bluePeoplePile.push_back(blue.toInt());

        for(auto red : redGroup)
            newPlayer.redPeoplePile.push_back(red.toInt());

        for(auto green : greenGroup)
            newPlayer.greenPeoplePile.push_back(green.toInt());

        for(auto purple : purpleGroup)
            newPlayer.purplePeoplePile.push_back(purple.toInt());

        players.push_back(newPlayer);

    }

    // deserialize the current player index
    currentPlayerIndex = jsonObj["Current_Player_Index"].toInt();

    round = jsonObj["Round"].toInt();

    gameOver = jsonObj["Game_over"].toBool();

    playerButtonsEnabled = jsonObj["Player_Buttons_Enabled"].toBool();

    QJsonArray actionCardStackArr = jsonObj["Action_Card_Stack"].toArray();


    for (auto action : actionCardStackArr){
        actionCardStack.append(action.toInt());
    }

    QJsonArray personCardStackArr = jsonObj["People_Card_Stack"].toArray();

    for (auto person : personCardStackArr){
        personCardStack.append(person.toInt());
    }

    QJsonArray tableauArr = jsonObj["Tableau"].toArray();

    for (auto person : tableauArr){
        tableau.append(person.toInt());
    }

    QJsonArray tableauEnabledArr = jsonObj["Tableau_Enabled"].toArray();
    tableauCardIsEnabled.clear();
    for (auto isEnabled : tableauEnabledArr){
        tableauCardIsEnabled.append(isEnabled.toBool());
    }
}

QByteArray GameState::serialize()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    QJsonArray jsonPlayerArr;

    for(int i =0; i<(int)players.size(); i++){
        Player player = players.at(i);

        QJsonObject playerObj;

        QJsonArray actionPileArray;
        std::copy (player.actionPile.begin(), player.actionPile.end(), std::back_inserter(actionPileArray));

        QJsonArray blueManGroup;
        std::copy (player.bluePeoplePile.begin(), player.bluePeoplePile.end(), std::back_inserter(blueManGroup));

        QJsonArray redGroup;
        std::copy (player.redPeoplePile.begin(), player.redPeoplePile.end(), std::back_inserter(redGroup));

        QJsonArray greenGroup;
        std::copy (player.greenPeoplePile.begin(), player.greenPeoplePile.end(), std::back_inserter(greenGroup));

        QJsonArray purpleGroup;
        std::copy (player.purplePeoplePile.begin(), player.purplePeoplePile.end(), std::back_inserter(purpleGroup));

        QJsonValue playerName(player.name);
        playerObj.insert("Action_Pile", actionPileArray);
        playerObj.insert("Blue_Pile", blueManGroup);
        playerObj.insert("Red_Pile", redGroup);
        playerObj.insert("Green_Pile", greenGroup);
        playerObj.insert("Purple_Pile", purpleGroup);

        playerObj.insert("Score", player.score);
        playerObj.insert("Name", playerName);

        jsonPlayerArr.append(playerObj);
    }

    // serialize the current player index
    jsonObj.insert("Current_Player_Index", currentPlayerIndex);

    jsonObj.insert("Round", round);

    jsonObj.insert("Game_over", gameOver);

    jsonObj.insert("Player_Buttons_Enabled", playerButtonsEnabled);

    // serialize the action card stack
    QJsonArray actionCardStackArr;
    std::copy (actionCardStack.begin(), actionCardStack.end(), std::back_inserter(actionCardStackArr));
    jsonObj.insert("Action_Card_Stack", actionCardStackArr);

    // serialize the person card stack
    QJsonArray personCardStackArr;
    std::copy (personCardStack.begin(), personCardStack.end(), std::back_inserter(personCardStackArr));
    jsonObj.insert("People_Card_Stack", personCardStackArr);

    // insert the tableau
    QJsonArray tableauArr;
    std::copy (tableau.begin(), tableau.end(), std::back_inserter(tableauArr));
    jsonObj.insert("Tableau", tableauArr);

    // insert the isEnabledArray
    QJsonArray tableauCardEnabledArr;
    std::copy (tableauCardIsEnabled.begin(), tableauCardIsEnabled.end(), std::back_inserter(tableauCardEnabledArr));
    jsonObj.insert("Tableau_Enabled", tableauCardEnabledArr);

    // insert the players array
    jsonObj.insert("Players", jsonPlayerArr);

    // serialize
    jsonDoc.setObject(jsonObj);
    return jsonDoc.toJson();
}

void GameState::resetGameState()
{
    players.clear();
    currentPlayerIndex = 0;
    actionCardStack.clear();
    personCardStack.clear();
    tableau.clear();
}


