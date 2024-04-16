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
    , clientSocket(new QTcpSocket(this))
    , ui(new Ui::MainWindow)
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


    //connect the buttons to their respective actions
    connect(ui->hostButton, &QPushButton::clicked, this, &MainWindow::hostClicked);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectClicked);
    connect(ui->startbutton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->sendMessageButton, &QPushButton::clicked, this, &MainWindow::sendChatMessage);

    //test for action cards -chase
    connect(ui->testActionCard, &QPushButton::clicked, this, &MainWindow::actionCardPlayed);

    protocolName = "~pname:";
    protocolChat = "~chat:";
    protocolAction= "~action:";
    protocolCallBack = "~callback";
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
    cout<< socketError <<endl;
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
    for(int i = 0; i < gameState.tableau.size(); i++){
        int personCardID = gameState.tableau[i];

        std::string fileName = ":/people/" + std::to_string(personCardID) + "p.png";
        //pixmap??
        QPixmap pixmap(QString::fromStdString(fileName));
        currentCardsInTableau[i]->setPixmap(pixmap.scaledToHeight(currentCardsInTableau[i]->geometry().height(),Qt::FastTransformation));
    }
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
    //tableauLayout->setHorizontalSpacing(0);

    for(int i = 0; i < gameState.tableau.size(); i++){
        int personCardID = gameState.tableau.at(i);

        //std::cout <<"looking for person card of id: " << personCardID << std::endl;



        //std::string fileName = ":/people/" + std::to_string(personCardID) + "p.png";
        //pixmap??
        //QPixmap pixmap(QString::fromStdString(fileName));

        //currentCardsInTableau[i]->setPixmap(pixmap.scaledToHeight(currentCardsInTableau[i]->geometry().height(),Qt::FastTransformation));

        //ui->tableauHLayout->addWidget
        //create QLabels

        QPushButton* button = new QPushButton(this);
        QLabel* label = new QLabel(button);
        button->setGeometry(0,0,300,420);
        button->setBaseSize(300,420);
        button->setFixedSize(300,420);

        //button->setText("");

        button->setStyleSheet("border: none; color: palette(window-text); background: transparent;");

        label->setGeometry(0, 0, 300, 420);
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
    otherPlayerHands* otherPlayersWindow = new otherPlayerHands(nullptr, p);
    otherPlayersWindow->show();
}

void MainWindow::tableauCardClicked()
{

    // e.g. casting to the class you know its connected with
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    int cardIndex = tableauLayout->indexOf(button);

    //Chase's tab
    ui->selectedTab->setText(QString::number(cardIndex));

    //std::cout << "you clicked the card at: " << cardIndex << std::endl;

}

void MainWindow::updateView()
{
    showCardsOnTableau();

    connect(ui->testPush, &QPushButton::clicked, this, &MainWindow::tabSelected);
}


//evan doesnt have his magic scroll view on the actions yet, so hard coding what index that card was.
void MainWindow::actionCardPlayed()
{
    //hardcoding the first card as played
    clientSendMessage(protocolAction + "0");
}

void MainWindow::tabSelected()
{
   clientSendMessage(protocolCallBack + ui->selectedTab->text().toStdString());
}



