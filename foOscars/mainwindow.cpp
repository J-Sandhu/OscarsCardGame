#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkInterface>
#include <QMessageBox>
#include<QString>
#include "otherplayerhands.h"
#include <Box2D/Box2D.h>
#include "confetti.h"
#include <QRect>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // load all of the pictures so we don't have to do it at every turn
    loadResources();

    //std::cout << "people images size: " << peopleImages.size() << std::endl;

    //enable the connection buttons and text
    ui->connectButton->setEnabled(true);
    ui->hostButton->setEnabled(true);

    ui->ipLine->setEnabled(true);
    ui->ipLine->setEnabled(true);

    //BOX2D graphics view
    ui->graphicsView->setStyleSheet("background: transparent;");
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->graphicsView->setScene(&scene);

    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    //BOX2D -winner display
    ui->winnerNameLabel->setVisible(false);
    ui->endGameButton->setEnabled(false);
    connect(ui->endGameButton, &QPushButton::clicked, this, &MainWindow::endGameClicked);


    //connect the buttons to their respective actions
    connect(ui->hostButton, &QPushButton::clicked, this, &MainWindow::hostClicked);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectClicked);
    connect(ui->startbutton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->sendMessageButton, &QPushButton::clicked, this, &MainWindow::sendChatMessage);


    protocolName = "~pname:";
    protocolChat = "~chat:";
    protocolAction= "~action:";
    protocolTableau="~tableau";
    protocolGameState="~gstate:";
    protocolStartGame="~startgame:";
    protocolCallBack = "~callback:";
    protocolPlayerIndex = "~index:";
    protocolSelectedPlayer = "~pselected:";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tableauLayout;
}


void MainWindow::hostClicked()
{
    ui->connectButton->setEnabled(false);
    ui->hostButton->setEnabled(false);
    ui->startbutton->setEnabled(true);
    ui->ipLine->setReadOnly(true);
    ui->portLine->setReadOnly(true);

    server= new Server(this);

    //connect endTurn slots and signals -> ask Jai about end game protocol
    connect(server->model, &Model::displayWinnerAndConfetti, this, &MainWindow::displayWinnerAndConfettiSlot);

    ui->ipLine->setText(server->ipAddress);
    ui->portLine->setText(QString::number(server->port));

    serverPort=server->port;
    serverIpAddress= server->tcpServer->serverAddress();

    connect(server, &Server::displayMessage, this, &MainWindow::displayMessageFromServer);

    clientIndexInPlayerArray = 0;
    connectClicked();
}

void MainWindow::connectClicked()
{
    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);


    cout<<"state of the client socket: "<<clientSocket->socketDescriptor()<<endl;
    clientSocket->connectToHost(ui->ipLine->text(), ui->portLine->text().toInt());
    cout<<"state of the client socket after attempting to connect to host: "<<clientSocket->socketDescriptor()<<endl;

    if(clientSocket->waitForConnected())
    {
        cout<<"Connected to Server, sending name: "<<ui->playerNameLine->text().toStdString()<<endl;
        ui->ipLine->setReadOnly(true);
        ui->portLine->setReadOnly(true);
        ui->playerNameLine->setReadOnly(true);
        clientSendMessage(protocolName + ui->playerNameLine->text().toStdString());            //we can figure out the protocol later
    }
    else
        cout<<tr("The following error occurred: %1.").arg(clientSocket->errorString()).toStdString()<<endl;

}


//TODO: is this a client side exclusive
void MainWindow::displayMessageFromServer(QString newMessage)
{
    ui->receivedMessageText->append(newMessage);
}

void MainWindow::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;
    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit displayMessage(message);
        return;
    }
    QString message = QString::fromStdString(buffer.toStdString());     //get message

    //if message starts with chat tag
    if (message.toStdString().rfind(protocolChat,0)==0)
    {
        message.remove(0,protocolChat.length());
        emit newMessage(message);
    }
    else if(message.toStdString().rfind(protocolGameState,0)==0)
    {
        buffer.remove(0,protocolGameState.length());
        gameState.deserialize(buffer);
        std::cout << buffer.toStdString() << std::endl;
        updateView();
    }
    else if(message.toStdString().rfind(protocolPlayerIndex,0)==0)
    {
        buffer.remove(0,protocolPlayerIndex.length());
        clientIndexInPlayerArray = buffer.toInt();
        std::cout << "This client's index in the gameState player array is: " << clientIndexInPlayerArray << std::endl;
    }

    if(clientSocket->bytesAvailable() != 0)
    {
        readSocket();
    }

}

void MainWindow::displayMessage(const QString& str)
{
    ui->receivedMessageText->append(str);
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    cout<<clientSocket->errorString().toStdString()<<endl;
}

void MainWindow::sendChatMessage()
{
    clientSendMessage(protocolChat + ui->messageLine->text().toStdString());
    ui->messageLine->clear();
}

void MainWindow::clientSendMessage(std::string message)
{
    clientSocket->flush();

    QByteArray buffer;
    buffer.append(message);


    QDataStream socketStream(clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream << buffer;
}

// How does a client know what player it is?
void MainWindow::cardPlayed()
{
    // Send message via jai's communication method.
}

void MainWindow::updateActionHand(std::vector<QImage> images)
{
    // int nonSelectedHeight = ui->ACardLabel1->geometry().height();
    // int selectedHeight = ui->SelectedACardLabel->geometry().height();
    // ui->ACardLabel1->setPixmap(QPixmap::fromImage(images.at(0)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
    // ui->ACardLabel2->setPixmap(QPixmap::fromImage(images.at(1)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
    // ui->SelectedACardLabel->setPixmap(QPixmap::fromImage(images.at(2)).scaledToHeight(selectedHeight,Qt::FastTransformation));
    // ui->ACardLabel4->setPixmap(QPixmap::fromImage(images.at(3)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
    // ui->ACardLabel5->setPixmap(QPixmap::fromImage(images.at(4)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
}

void MainWindow::loadResources()
{
    for(int i = 0; i<49 ; i++)
    {
        QString filename = QString::number(i);
        filename.append(".png");
        filename.prepend(":/actions/");
        QPixmap assetImage(filename);
        actionImages.push_back(assetImage);
    }

    for(int i = 0; i<41; i++)
    {
        QString filename = QString::number(i);
        filename.append("p.png");
        filename.prepend(":/people/");
        QPixmap assetImage(filename);
        peopleImages.push_back(assetImage);
    }
}


void MainWindow::updateTableauAfterActionCardSelectSlot(){
    //redraw
    // for(int i = 0; i < gameState.tableau.size(); i++){
    //     int personCardID = gameState.tableau[i];

    //     std::string fileName = ":/people/" + std::to_string(personCardID) + "p.png";
    //     //pixmap??
    //     QPixmap pixmap(QString::fromStdString(fileName));
    //     currentCardsInTableau[i]->setPixmap(pixmap.scaledToHeight(currentCardsInTableau[i]->geometry().height(),Qt::FastTransformation));
    // }
}

void MainWindow::onStartClicked()
{
    //emit signal to populate tableau
    clientSendMessage(protocolStartGame);
    cout<<"start clicked, sending message to server"<<endl;
    //emit startGame();

    ui->winnerNameLabel->setVisible(false);
    ui->endGameButton->setEnabled(true);
}

void MainWindow::showCardsOnTableau()
{
    // before we show the new cards in the tableau
    // we need to remove all of the buttons from the horizontal
    // layout
    qDeleteAll(tableauScrollWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    // update nominees remaining label
    QString nomineeCount("Nominees Remaining: ");
    nomineeCount.append(QString::number(gameState.tableau.size()));
    ui->nomineeCountLabel->setText(nomineeCount);
    // for(int i =0; i<tableauLayout->count(); i++)
    // {
    //     //tableauLayout->
    // }

    for(int i = 0; i < gameState.tableau.size(); i++){
        int personCardID = gameState.tableau.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,350,490);
        button->setBaseSize(350,490);
        button->setFixedSize(350,490);

        //button->setText("");

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 350, 490);
        label->setPixmap(peopleImages.at(personCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));
        //label->setText("<l>Label</>");



        button->setEnabled(gameState.tableauCardIsEnabled.at(i));

        //label->setText("<b>Button</b> Test");
        connect(button, &QPushButton::clicked, this, &MainWindow::tableauCardClicked);
        //ui->tableauLayout->addWidget(label);

        if(gameState.currentPlayerIndex != clientIndexInPlayerArray)
            button ->setEnabled(false);

        tableauLayout->addWidget(button);
        //std::cout <<" adding labelbutton at: " << tableauLayout->indexOf(button) << std::endl;


        // It's important to read that a QScrollArea has a function called QScrollArea::setWidget.
        // Attempting to just call QWidget::setLayout will not work for a QScrollArea's intended usage.
        // You just need an intermediate QWidget parent that holds the layout, but is then also assigned to the QScrollArea.
    }

    tableauScrollWidget->setLayout(tableauLayout);
    ui->tableauScrollArea->setWidget(tableauScrollWidget);
}

void MainWindow::showCardsInHand()
{
    // before we show the new cards in the tableau
    // we need to remove all of the buttons from the horizontal
    // layout
    qDeleteAll(handScrollWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    // update nominees remaining label
    // for(int i =0; i<tableauLayout->count(); i++)
    // {
    //     //tableauLayout->
    // }

    cout<<"clientIndexInPlayerArray: "<<clientIndexInPlayerArray<<endl;

    // QString count("Your Hand: " );//+ gameState.players.at(clientIndexInPlayerArray).actionPile.size());
    // ui->label_2->setText(count);
        //TODO: look at how we are planning to identify which player we are.
    // for now I'm only showing player 0's hand which will ALWAYS be the server
    for(int i = 0; i < gameState.players.at(clientIndexInPlayerArray).actionPile.size(); i++){
        int actionCardID = gameState.players.at(clientIndexInPlayerArray).actionPile.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,350,490);
        button->setBaseSize(350,490);
        button->setFixedSize(350,490);

        //button->setText("");

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 350, 490);
        label->setPixmap(actionImages.at(actionCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));
        //label->setText("<l>Label</>");



        //label->setText("<b>Button</b> Test");
        connect(button, &QPushButton::clicked, this, &MainWindow::actionCardClicked);

        if(gameState.currentPlayerIndex != clientIndexInPlayerArray)
            button->setEnabled(false);

        if(gameState.playerButtonsEnabled)
            button->setEnabled(false);
        //ui->tableauLayout->addWidget(label);
        handLayout->addWidget(button);


        //std::cout <<" adding labelbutton at: " << tableauLayout->indexOf(button) << std::endl;


        // It's important to read that a QScrollArea has a function called QScrollArea::setWidget.
        // Attempting to just call QWidget::setLayout will not work for a QScrollArea's intended usage.
        // You just need an intermediate QWidget parent that holds the layout, but is then also assigned to the QScrollArea.
    }

    handScrollWidget->setLayout(handLayout);
    ui->handScrollArea->setWidget(handScrollWidget);
}



void MainWindow::displayPopUp(int index)
{
    //get chosen player
    Player* p = &gameState.players.at(index);

    //constuct pop up window
    otherPlayerHands* otherPlayersWindow = new otherPlayerHands(nullptr, p, &peopleImages);
    otherPlayersWindow->show();
}

void MainWindow::tableauCardClicked()
{

    // e.g. casting to the class you know its connected with
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    int cardIndex = tableauLayout->indexOf(button);

    clientSendMessage(protocolTableau + to_string(cardIndex));
}



void MainWindow::actionCardClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    int actionCardIndex = handLayout->indexOf(button);

    std::cout << "you clicked the action card at: " << actionCardIndex << std::endl;

    clientSendMessage(protocolAction + to_string(actionCardIndex));

}

void MainWindow::updateView()
{
    showCardsOnTableau();
    showCardsInHand();
    showPlayerButtons();
}

void MainWindow::anotherPlayerClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    int playerIndex = playerLayout->indexOf(button);

    std::cout << "you clicked the player button at: " << playerIndex << std::endl;

    clientSendMessage(protocolSelectedPlayer + to_string(playerIndex));

    //connect(button, &QPushButton::clicked, this, &MainWindow::an);
}

void MainWindow::showPlayerButtons()
{
    //TODO: make this highlight the player whose turn it is
    //qDeleteAll(ui->playerLayout->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    qDeleteAll(playerButtonWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    //std::cout <<"size of playerLayout after clearing: "<< ui->playerLayout->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly).size() <<std::endl;
    //std::cout <<"size of gameState players array when drawing: " << gameState.players.size() << std::endl;

    for(int i = 0; i < gameState.players.size(); i++){
        std::cout << "adding another player to the player buttons: " << i << std::endl;
        QString playerName = gameState.players.at(i).name;
        cout<<"pname in updateButton:"<<playerName.toStdString()<<endl;
        QPushButton* button = new QPushButton(this);
        //QLabel* label = new QLabel(button);
        button->setGeometry(0,0,200,200);
        button->setBaseSize(200,200);
        button->setFixedSize(200,200);

        QString buttonSuffix("\n ---------------------- \n Score: ");
        buttonSuffix.append(QString::number(gameState.players.at(i).score));
        QString buttonText = playerName.append(buttonSuffix);

        button->setText(buttonText);

        //label->setText("<b>Button</b> Test");
        connect(button, &QPushButton::clicked, this, &MainWindow::anotherPlayerClicked);

        button->setStyleSheet("font-size: 20px;");

        // if this button corresponds to the player whose turn it is
        if(i == gameState.currentPlayerIndex)
        {
            // QPalette pal = button->palette();
            // pal.setColor(QPalette::Button, QColor(Qt::darkGreen));
            // // pal.setBrush(QPalette::Text, QColor(Qt::black));
            // button->setAutoFillBackground(true);
            // button->setPalette(pal);
            // button->update();
            //button->setStyleSheet("background-color: solid #006400;");
            button->setStyleSheet("border:3px solid #ffffff; font-size: 20px;");

        }

        // if the button correspond to this player
        if(i == clientIndexInPlayerArray)
        {
            buttonText.prepend("Me: ");
            button->setText(buttonText);
            button->setEnabled(false);
            //button->setStyleSheet("border:3px solid #ffffff;");

        }
        // if player buttons should be disabled(not a choose a player card)
        cout<<"button enabled?: "<<gameState.playerButtonsEnabled<<endl;
        if(!gameState.playerButtonsEnabled)
            button->setEnabled(false);
        else button->setEnabled(true);




        playerLayout->addWidget(button);
    }

    playerButtonWidget->setLayout(playerLayout);
    ui->playerButtonScrollArea->setWidget(playerButtonWidget);
}

void MainWindow::playerButtonClicked()
{
    std::cout <<"getting into playerButton clicked" << std::endl;


}

//start the simulation -> only do when there are no cards in the tableau
void MainWindow::startConfetti()
{
    confetti = Confetti();
    //connect timer to show confetti
    connect(&timer, &QTimer::timeout, this, &MainWindow::showConfetti);
    timer.start(50);

}

void MainWindow::displayWinnerName()
{
    //get all scores of players and compare
    int highScore = gameState.players.at(0).score;

    // Iterate through  players to find highest score
    for (int i = 1; i < gameState.players.size(); i++)
    {
        if (gameState.players.at(i).score > highScore)
        {
            highScore = gameState.players.at(i).score;
            gameState.indexOfWinner = i;
        }
    }

    QString winDisplay = gameState.players.at(gameState.indexOfWinner).name.toUpper() + " IS THE WINNER !!!";
    //set font stuff later...
    ui->winnerNameLabel->setText(winDisplay);
    ui->winnerNameLabel->setVisible(true);
}

void MainWindow::displayWinnerAndConfettiSlot()
{
    startConfetti();
    displayWinnerName();
}

//draws the confetti
void MainWindow::showConfetti()
{
    std::cout <<"getting into show confetti" << std::endl;
    confetti.showConfettiCount++;
    ui->graphicsView->scene()->clear();
    if (confetti.showConfettiCount > 160)//8 seconds
    {
        std::cout <<"setting winner name label " << std::endl;
        timer.stop();
        ui->winnerNameLabel->setText("");
        return;
    }

    //colors array for confetti
    Qt::GlobalColor colors [] = {Qt::red, Qt::yellow, Qt::blue, Qt::green};
    confetti.doConfettiSimulation();
    for(int i = 0; i<confetti.confettiVectors.size(); i++)
    {
        //std::cout<<"getting into confetti loop" << std::endl;
        QRectF rect(confetti.confettiVectors.at(i)->GetPosition().x, confetti.confettiVectors.at(i)->GetPosition().y, 10, 10);
        QPen pen(Qt::black); // Black outline
        QBrush brush (colors[i % 4]);
        ui->graphicsView->scene()->addRect(rect, pen, brush);
    }
    std::cout << "updating confetti scene" << std::endl;
    ui->graphicsView->scene()->update();
}

//TODO: can delete later once end game protocol is figured out
void MainWindow::endGameClicked()
{
    server->model->endGame();
}
