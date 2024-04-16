#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkInterface>
#include <QMessageBox>
#include<QString>
#include "otherplayerhands.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    this->setWindowTitle("FoOscars");

    // load all of the pictures so we don't have to do it at every turn
    loadResources();

    //std::cout << "people images size: " << peopleImages.size() << std::endl;

    //enable the connection buttons and text
    ui->connectButton->setEnabled(true);
    ui->hostButton->setEnabled(true);

    ui->ipLine->setEnabled(true);
    ui->ipLine->setEnabled(true);


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
        cout<<"Connected to Server"<<endl;
        ui->ipLine->setReadOnly(true);
        ui->portLine->setReadOnly(true);
        ui->playerNameLine->setReadOnly(true);
        clientSendMessage("~pname:"+ui->playerNameLine->text().toStdString());            //we can figure out the protocol later
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
        updateView();
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

// void MainWindow::updateActionHand(std::vector<QImage> images)
// {
//     // int nonSelectedHeight = ui->ACardLabel1->geometry().height();
//     // int selectedHeight = ui->SelectedACardLabel->geometry().height();
//     // ui->ACardLabel1->setPixmap(QPixmap::fromImage(images.at(0)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
//     // ui->ACardLabel2->setPixmap(QPixmap::fromImage(images.at(1)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
//     // ui->SelectedACardLabel->setPixmap(QPixmap::fromImage(images.at(2)).scaledToHeight(selectedHeight,Qt::FastTransformation));
//     // ui->ACardLabel4->setPixmap(QPixmap::fromImage(images.at(3)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
//     // ui->ACardLabel5->setPixmap(QPixmap::fromImage(images.at(4)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
//}

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

void MainWindow::actionCardFromPersonalPileSelected(int cardID, Card actionCard){
    clientSendMessage(protocolAction + std::to_string(cardID));

    //get selected action card info
    switch(actionCard.cardType){
        case Card::ActionCardTypes::generalLineMovement:
            //find out which cards in tableau to make clickable
            for (int i = 0; i < gameState.tableau.size(); i++){

                //TODO: replace this with model logic that update gamestate with whether or not
                // a card is enabled.

                // int personCardID = gameState.tableau.at(i);
                // if(model->personMap.at(personCardID).colorType == actionCard.colorType){
                //     currentCardsInTableau[i]->setEnabled(true);
                // }
            }
            break;

        case Card::ActionCardTypes::lineOrder:
            //enable all cards in tableau
            for (auto i : currentCardsInTableau){
                i->setEnabled(true);
            }
            break;

        case Card::ActionCardTypes::addToLine:

            // currentCurrentInTableau.add();
            break;

        case Card::ActionCardTypes::scorePile:
            //some stuff
            break;

        case Card::ActionCardTypes::specificNoble:
            //some stuff
            break;

        case Card::ActionCardTypes::actionCardManipulation:
            //some stuff
            break;
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



        //label->setText("<b>Button</b> Test");
        connect(button, &QPushButton::clicked, this, &MainWindow::tableauCardClicked);
        //ui->tableauLayout->addWidget(label);
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

    //TODO: look at how we are planning to identify which player we are.
    // for now I'm only showing player 0's hand which will ALWAYS be the server
    for(int i = 0; i < gameState.players.at(0).actionPile.size(); i++){
        int actionCardID = gameState.players.at(0).actionPile.at(i);

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

void MainWindow::updateOtherPlayersHandsBox(){
    //at this point, we know how many players are currently in the game
    for(int i = 0; i < gameState.players.size(); i++){
        ui->otherPlayersHandsButton->addItem(gameState.players.at(i).name);
    }
    //connect to popup window
    connect(ui->otherPlayersHandsButton, &QComboBox::currentIndexChanged, this, &MainWindow::displayPopUp);

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

    //std::cout << "you clicked the card at: " << cardIndex << std::endl;

}

void MainWindow::actionCardClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    int actionCardIndex = handLayout->indexOf(button);

    std::cout << "you clicked the action card at: " << actionCardIndex << std::endl;

}

void MainWindow::updateView()
{
    showCardsOnTableau();
    showCardsInHand();
}

void MainWindow::anotherPlayerPersonCardClicked()
{
    std::cout <<"you clicked someone else's person card" << std::endl;
}
