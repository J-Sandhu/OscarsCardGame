#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkInterface>
#include <QMessageBox>
#include<QString>
#include <Box2D/Box2D.h>
#include "confetti.h"
#include <QRect>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , clientSocket(new QTcpSocket(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // load all of the pictures so we don't have to do it at every turn
    loadResources();

    //enable the connection buttons and text
    ui->connectButton->setEnabled(true);
    ui->hostButton->setEnabled(true);
    ui->roundLabel->setText("Round: 0");

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
    clientSocket->connectToHost(ui->ipLine->text(), ui->portLine->text().toInt());

    if(clientSocket->waitForConnected())
    {
        ui->ipLine->setReadOnly(true);
        ui->portLine->setReadOnly(true);
        ui->playerNameLine->setReadOnly(true);
        ui->connectButton->setEnabled(false);
        ui->hostButton->setEnabled(false);
        clientSendMessage(protocolName + ui->playerNameLine->text().toStdString());            //we can figure out the protocol later
    }
    else
        cout<<tr("The following error occurred: %1.").arg(clientSocket->errorString()).toStdString()<<endl;

}

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
        displayMessage(message);
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
        updateView();
    }
    else if(message.toStdString().rfind(protocolPlayerIndex,0)==0)
    {
        buffer.remove(0,protocolPlayerIndex.length());
        clientIndexInPlayerArray = buffer.toInt();
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

void MainWindow::displayError()
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

void MainWindow::onStartClicked()
{
    clientSendMessage(protocolStartGame);
    ui->winnerNameLabel->setVisible(false);
    ui->endGameButton->setEnabled(true);
    ui->startbutton->setEnabled(false);
}

void MainWindow::showCardsOnTableau()
{
    // before we show the new cards in the tableau
    // we need to remove all of the buttons from the horizontal layout
    qDeleteAll(tableauScrollWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    tableauLayout->setSpacing(0);
    tableauLayout->setContentsMargins(0, 0, 0, 0);

    // update nominees remaining label
    QString nomineeCount("Nominees Remaining: ");
    nomineeCount.append(QString::number(gameState.tableau.size()));
    ui->nomineeCountLabel->setText(nomineeCount);

    for(int i = 0; i < gameState.tableau.size(); i++){
        int personCardID = gameState.tableau.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,350,490);
        button->setBaseSize(350,490);
        button->setFixedSize(350,490);
        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");
        button->setEnabled(gameState.tableauCardIsEnabled.at(i));
        connect(button, &QPushButton::clicked, this, &MainWindow::tableauCardClicked);

        label->setGeometry(0, 0, 350, 490);
        label->setPixmap(peopleImages.at(personCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));

        if(gameState.currentPlayerIndex != clientIndexInPlayerArray)
            button ->setEnabled(false);

        tableauLayout->addWidget(button);
    }

    tableauScrollWidget->setLayout(tableauLayout);
    ui->tableauScrollArea->setWidget(tableauScrollWidget);
}

void MainWindow::showCardsInHand()
{
    // before we show the new cards in the hand
    // we need to remove all of the buttons from the horizontallayout
    qDeleteAll(handScrollWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    handLayout->setSpacing(0);
    handLayout->setContentsMargins(0, 0, 0, 0);

    for(int i = 0; i < gameState.players.at(clientIndexInPlayerArray).actionPile.size(); i++){
        int actionCardID = gameState.players.at(clientIndexInPlayerArray).actionPile.at(i);

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,350,490);
        button->setBaseSize(350,490);
        button->setFixedSize(350,490);
        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 350, 490);
        label->setPixmap(actionImages.at(actionCardID).scaledToHeight(label->geometry().height(), Qt::FastTransformation));

        connect(button, &QPushButton::clicked, this, &MainWindow::actionCardClicked);

        if(gameState.currentPlayerIndex != clientIndexInPlayerArray)
            button->setEnabled(false);

        if(gameState.playerButtonsEnabled)
            button->setEnabled(false);

        handLayout->addWidget(button);
    }

    handScrollWidget->setLayout(handLayout);
    ui->handScrollArea->setWidget(handScrollWidget);
}



void MainWindow::tableauCardClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int cardIndex = tableauLayout->indexOf(button);
    clientSendMessage(protocolTableau + to_string(cardIndex));
}



void MainWindow::actionCardClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int actionCardIndex = handLayout->indexOf(button);
    clientSendMessage(protocolAction + to_string(actionCardIndex));
}

void MainWindow::updateView()
{
    if(gameState.gameOver)
        displayWinnerAndConfettiSlot();


    showCardsOnTableau();
    showCardsInHand();
    showPlayerButtons();

    QString round("Round: ");
    round.append(QString::number(gameState.round));

    ui->roundLabel->setText(round);
    QString nominees("Nominees Remaining: ");
    nominees.append(QString::number(gameState.tableau.size()));
    ui->nomineeLabel->setText(nominees);
}

void MainWindow::anotherPlayerClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int playerIndex = playerLayout->indexOf(button);
    clientSendMessage(protocolSelectedPlayer + to_string(playerIndex));
}

void MainWindow::showPlayerButtons()
{
    qDeleteAll(playerButtonWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    for(int i = 0; i <(int) gameState.players.size(); i++){
        QString playerName = gameState.players.at(i).name;
        QPushButton* button = new QPushButton(this);

        button->setGeometry(0,0,200,200);
        button->setBaseSize(200,200);
        button->setFixedSize(200,200);

        QString buttonSuffix("\n ---------------------- \n Score: ");
        buttonSuffix.append(QString::number(gameState.players.at(i).score));
        QString buttonText = playerName.append(buttonSuffix);

        button->setText(buttonText);
        connect(button, &QPushButton::clicked, this, &MainWindow::anotherPlayerClicked);

        button->setStyleSheet("font-size: 20px;");

        // if this button corresponds to the player whose turn it is
        if(i == gameState.currentPlayerIndex)
            button->setStyleSheet("border:3px solid #ffffff; font-size: 20px;");

        // if the button correspond to this player
        if(i == clientIndexInPlayerArray)
        {
            buttonText.prepend("Me: ");
            button->setText(buttonText);
            button->setEnabled(false);
        }

        // if player buttons should be disabled(not a choose a player card)
        if(!gameState.playerButtonsEnabled)
            button->setEnabled(false);
        else button->setEnabled(true);

        playerLayout->addWidget(button);
    }

    playerButtonWidget->setLayout(playerLayout);
    ui->playerButtonScrollArea->setWidget(playerButtonWidget);
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
    for (int i = 1; i <(int) gameState.players.size(); i++)
    {
        if (gameState.players.at(i).score > highScore)
        {
            highScore = gameState.players.at(i).score;
            gameState.indexOfWinner = i;
        }
    }

    QString winDisplay = gameState.players.at(gameState.indexOfWinner).name.toUpper() + " IS THE WINNER !!!";
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
    confetti.showConfettiCount++;
    ui->graphicsView->scene()->clear();
    if (confetti.showConfettiCount > 160) //8 seconds
    {
        timer.stop();
        ui->winnerNameLabel->setText("");
        return;
    }

    //colors array for confetti
    Qt::GlobalColor colors [] = {Qt::red, Qt::yellow, Qt::blue, Qt::green};
    confetti.doConfettiSimulation();
    for(int i = 0; i<confetti.confettiVectors.size(); i++)
    {
        QRectF rect(confetti.confettiVectors.at(i)->GetPosition().x, confetti.confettiVectors.at(i)->GetPosition().y, 10, 10);
        QPen pen(Qt::black); // Black outline
        QBrush brush (colors[i % 4]);
        ui->graphicsView->scene()->addRect(rect, pen, brush);
    }
    ui->graphicsView->scene()->update();
}
void MainWindow::endGameClicked()
{
    server->model->endGame();
}
