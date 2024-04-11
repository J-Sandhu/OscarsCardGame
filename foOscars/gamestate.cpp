#include "gamestate.h"

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

        players.at(i).score = thisPlayer["Score"].toInt();

        QJsonArray actionPileArray = thisPlayer["Action_Pile"].toArray();
        QVector<int> actionPileVector;
        QJsonArray blueManGroup = thisPlayer["Blue_Pile"].toArray();
        QJsonArray redGroup = thisPlayer["Red_Pile"].toArray();
        QJsonArray greenGroup = thisPlayer["Green_Pile"].toArray();
        QJsonArray purpleGroup = thisPlayer["Purple_Pile"].toArray();



        // std::copy (actionPileArray.begin(), actionPileArray.end(), std::back_inserter(players.at(i).actionPile));
        // std::copy (blueManGroup.begin(), blueManGroup.end(), std::back_inserter(players.at(i).bluePeoplePile));
        // std::copy (redGroup.begin(), redGroup.end(), std::back_inserter(players.at(i).redPeoplePile));
        // std::copy (greenGroup.begin(), greenGroup.end(), std::back_inserter(players.at(i).greenPeoplePile));
        // std::copy (purpleGroup.begin(), purpleGroup.end(), std::back_inserter(players.at(i).purplePeoplePile));

        //std::copy (actionPileArray.begin(), actionPileArray.end(), std::back_inserter(actionPileVector));
        // std::copy (blueManGroup.begin(), blueManGroup.end(), std::back_inserter(newPlayer.bluePeoplePile));
        // std::copy (redGroup.begin(), redGroup.end(), std::back_inserter(newPlayer.redPeoplePile));
        // std::copy (greenGroup.begin(), greenGroup.end(), std::back_inserter(newPlayer.greenPeoplePile));
        // std::copy (purpleGroup.begin(), purpleGroup.end(), std::back_inserter(newPlayer.purplePeoplePile));

        for (int i = 0; i< actionPileArray.size(); i++)
            actionPileVector.append(actionPileArray.at(i));

        // players.push_back(newPlayer);

    }

    // deserialize the current player index
    currentPlayerIndex = jsonObj["Current_Player_Index"].toInt();

    QJsonArray actionCardStackArr = jsonObj["Action_Card_Stack"].toArray();
    std::copy (actionCardStackArr.begin(), actionCardStackArr.end(), std::back_inserter(actionCardStack));

    QJsonArray personCardStackArr = jsonObj["People_Card_Stack"].toArray();
    std::copy (personCardStackArr.begin(), personCardStackArr.end(), std::back_inserter(personCardStack));

    QJsonArray tableauArr = jsonObj["Tableau"].toArray();
    std::copy (tableau.begin(), tableau.end(), std::back_inserter(tableauArr));
}

QByteArray GameState::serialize()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    QJsonArray jsonPlayerArr;

    for(auto player : players){

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


        playerObj.insert("Action_Pile", actionPileArray);
        playerObj.insert("Blue_Pile", blueManGroup);
        playerObj.insert("Red_Pile", redGroup);
        playerObj.insert("Green_Pile", greenGroup);
        playerObj.insert("Purple_Pile", purpleGroup);

        playerObj.insert("Score", player.score);

        jsonPlayerArr.append(playerObj);


        // frameObj.insert("Size", frame.size);
        // std::cout << "saving frame size : " << frame.size << std::endl;
        // // QString pixelDataString = QString::fromStdString(byteArr.toStdString());
        // frameObj.insert("Pixels", QLatin1String(byteArr.toBase64()));
        // jsonFrameArr.append(frameObj);
    }

    // serialize the current player index
    jsonObj.insert("Current_Player_Index", currentPlayerIndex);

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

    // insert the players array
    jsonObj.insert("Players", jsonPlayerArr);

    // serialize
    jsonDoc.setObject(jsonObj);
    return jsonDoc.toJson();




    // jsonObj.insert("Model_Frame_Size", model.frameSize);
    // std::cout << "saving with model frame size " << model.frameSize << std::endl;
    // jsonObj.insert("Frames", jsonFrameArr);
    // jsonDoc.setObject(jsonObj);

    // //write to file
    // QFile file(fileName);
    // file.open(QIODevice::WriteOnly);
    // file.write(jsonDoc.toJson());
    // file.close();
}

void GameState::resetGameState()
{
    players.clear();
    currentPlayerIndex = 0;
    actionCardStack.clear();
    personCardStack.clear();
    tableau.clear();
}


