#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkInterface>
#include <QMessageBox>
#include<QString>
#include "otherplayerhands.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent, Model* model)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientSocket(new QTcpSocket(this))
    , model(model)
{
    ui->setupUi(this);

    // load all of the pictures so we don't have to do it at every turn
    loadResources();

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

    //connect(this, &MainWindow::startGame, model, &Model::startGameSlot);

    //connect(model, &Model::gameInitializedSignal, this, &MainWindow::showCardsOnTableau);

    //connect(model, &Model::gameInitializedSignal, this, &MainWindow::updateOtherPlayersHandsBox);

    // connect(clientSocket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    protocolName = "~pname:";
    protocolChat = "~chat:";
    protocolAction= "~action:";
    protocolTableau="~tableau";
    protocolGameState="~gstate:";
    protocolStartGame="~startgame:";

    //add to tableau vector
    // currentCardsInTableau.push_back(ui->person0);
    // currentCardsInTableau.push_back(ui->person1);
    // currentCardsInTableau.push_back(ui->person2);
    // currentCardsInTableau.push_back(ui->person3);
    // currentCardsInTableau.push_back(ui->person4);
    // currentCardsInTableau.push_back(ui->person5);
    // currentCardsInTableau.push_back(ui->person6);
    // currentCardsInTableau.push_back(ui->person7);
    // currentCardsInTableau.push_back(ui->person8);
    // currentCardsInTableau.push_back(ui->person9);
    // currentCardsInTableau.push_back(ui->person10);
    // currentCardsInTableau.push_back(ui->person11);
    // currentCardsInTableau.push_back(ui->person12);
    // currentCardsInTableau.push_back(ui->person13);
    // currentCardsInTableau.push_back(ui->person14);



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
        cout<<"receiving gameState"<<endl;
        buffer.remove(0,protocolGameState.length());
        gameState.deserialize(buffer);
        cout<<buffer.toStdString()<<endl;
        cout<<"gamestate tableau size: "<<gameState.tableau.size()<<endl;
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
    clientSendMessage(ui->messageLine->text().toStdString());
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
void MainWindow::nextActionClicked()
{
    selectedActionCardIndex++;
    updateActionHand(getActionCardHand());

}
void MainWindow::PreviousActionClicked()
{
    selectedActionCardIndex--;
    updateActionHand(getActionCardHand());
}

std::vector<QImage> MainWindow::getActionCardHand()
{
    std::vector<QImage> previewFrames;

    /// Grab jai's code to get the index of interest
    /// replace the zero
    QVector<int> pileOfInterest = gameState.players.at(0).actionPile;

    // create a blank image to fill empty frame preview slots
    QImage blankImage;
    QColor transparent(255,255,255,255);
    blankImage.fill(transparent);

    // handles selected frame and frames to the left
    // if there are less than 2 frames to the left
    if(selectedActionCardIndex < 2)
    {
        // if there is 1 frame to the left
        if(selectedActionCardIndex == 1)
        {
            // push back a blank Qimage, then the image at 0, then the preview frame
            //std::cout << "finding 1 frame to the left " <<std::endl;

            // right now this pushes back an integer, we need it to push back
            // an image with the filename of the specified.



            previewFrames.push_back(blankImage);

            //QImage image1(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex-1)));
            previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex-1)));

            //QImage image2(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex)));
            previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex)));
        }
        if(selectedActionCardIndex == 0)
        {
            //std::cout <<"finding no frames to the left" << std::endl;
            // push back 2 blank Qimages, then the selected frame
            previewFrames.push_back(blankImage);
            previewFrames.push_back(blankImage);
            previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex)));
        }
    }
    // if there are at least two frames to the left
    else
    {
        // push the 2 frames before and the current frame
        // std::cout << "finding 2 frames to the left" <<std::endl;
        // previewFrames.push_back(animationFrames.at(currentFrame-2).imageData);
        // previewFrames.push_back(animationFrames.at(currentFrame-1).imageData);

        //QImage image1(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex-2)));
        previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex-2)));

        //QImage image2(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex-1)));
        previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex-1)));

        //QImage image3(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex)));
        previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex)));

        //previewFrames.push_back(animationFrames.at(currentFrame).imageData);
    }

    // handles frames to the right
    // if there are less than two frames to the right
    if(pileOfInterest.size() - selectedActionCardIndex < 3)
    {
        // there is only 1 frame to the right
        if(pileOfInterest.size()-selectedActionCardIndex == 2)
        {
            // push back the next frame then 1 empty frame
            // std::cout <<"finding 1 frame to right" << std::endl;
            //QImage image(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex+1)));
            previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex+1)));
            //previewFrames.push_back(animationFrames.at(currentFrame+1).imageData);
            previewFrames.push_back(blankImage);
        }
        // if there are no frames to the right
        // the same as the selected frame being the last frame
        if(selectedActionCardIndex == pileOfInterest.size()-1)
        {
            // push back two empty frames
            //std::cout <<"No frames to the right" << std::endl;
            previewFrames.push_back(blankImage);
            previewFrames.push_back(blankImage);
        }
    }
    // if there are at least two frames to the right
    else
    {
        //std::cout << "finding at least two frames to the right" << std::endl;
        //push back the two frames to the right

        //QImage image1(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex+1)));
        previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex+1)));

        //QImage image2(makeActionCardFilename(pileOfInterest.at(selectedActionCardIndex+2)));
        previewFrames.push_back(actionImages.at(pileOfInterest.at(selectedActionCardIndex+2)));

        // previewFrames.push_back(animationFrames.at(currentFrame+1).imageData);
        // previewFrames.push_back(animationFrames.at(currentFrame+2).imageData);
    }

    return previewFrames;
}

// QString MainWindow::makeActionCardFilename(int actionCardID)
// {
//     QString filename = QString::number(actionCardID);
//     filename.append(".png");
//     filename.prepend(":/actions/");
//     return filename;
// }

void MainWindow::updateActionHand(std::vector<QImage> images)
{
    int nonSelectedHeight = ui->ACardLabel1->geometry().height();
    int selectedHeight = ui->SelectedACardLabel->geometry().height();
    ui->ACardLabel1->setPixmap(QPixmap::fromImage(images.at(0)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
    ui->ACardLabel2->setPixmap(QPixmap::fromImage(images.at(1)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
    ui->SelectedACardLabel->setPixmap(QPixmap::fromImage(images.at(2)).scaledToHeight(selectedHeight,Qt::FastTransformation));
    ui->ACardLabel4->setPixmap(QPixmap::fromImage(images.at(3)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
    ui->ACardLabel5->setPixmap(QPixmap::fromImage(images.at(4)).scaledToHeight(nonSelectedHeight,Qt::FastTransformation));
}

void MainWindow::loadResources()
{
    for(int i = 0; i<49 ; i++)
    {
        QString filename = QString::number(i);
        filename.append(".png");
        filename.prepend(":/actions/");
        QImage assetImage(filename);
        actionImages.push_back(assetImage);
    }
}

void MainWindow::actionCardFromPersonalPileSelected(int cardID, Card actionCard){
    clientSendMessage(protocolAction + std::to_string(cardID));

    //get selected action card info
    switch(actionCard.cardType){
        case Card::ActionCardTypes::generalLineMovement:
            //find out which cards in tableau to make clickable
            for (int i = 0; i < currentCardsInTableau.size(); i++){
                int personCardID = model->gameState.tableau[i];
                if(model->personMap.at(personCardID).colorType == actionCard.colorType){
                    currentCardsInTableau[i]->setEnabled(true);
                }
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
        int personCardID = gameState.tableau[i];

        std::string fileName = ":/people/" + std::to_string(personCardID) + "p.png";
        //pixmap??
        QPixmap pixmap(QString::fromStdString(fileName));

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
        label->setPixmap(pixmap.scaledToHeight(label->geometry().height(), Qt::FastTransformation));
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
    Player* p = &model->gameState.players.at(index);

    //constuct pop up window
    otherPlayerHands* otherPlayersWindow = new otherPlayerHands(nullptr, p);
    otherPlayersWindow->show();
}

void MainWindow::tableauCardClicked()
{

    //std::cout << "******************************getting into tableau card clicked" << std::endl;

    // e.g. check with member variable _foobarButton
    //QObject* obj = sender();

    // e.g. casting to the class you know its connected with
    QPushButton* button = qobject_cast<QPushButton*>(sender());



    int cardIndex = tableauLayout->indexOf(button);



    std::cout << "you clicked the card at: " << cardIndex << std::endl;

}

void MainWindow::updateView()
{
    showCardsOnTableau();
}
