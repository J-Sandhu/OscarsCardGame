#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkInterface>
#include <QMessageBox>
#include<QString>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    //enable the connection buttons and text
    ui->connectButton->setEnabled(true);
    ui->hostButton->setEnabled(true);

    ui->ipLine->setEnabled(true);
    ui->ipLine->setEnabled(true);


    //connect the buttons to their respective actions
    connect(ui->hostButton, &QPushButton::clicked, this, &MainWindow::hostClicked);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectClicked);

    connect(ui->sendMessageButton, &QPushButton::clicked, this, &MainWindow::sendChatMessage);

    // connect(clientSocket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    protocolName = "~pname:";
    protocolChat = "~chat:";
    protocolAction= "~action:";
    protocolTableau="~tableau";
    pc = QString("~chat:");
}

MainWindow::~MainWindow()
{
    delete ui;
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

    string s = buffer.toStdString();
    // for(int i =0; i<s.length(); i++)
    // {
    //     if (s.at(i)=='')
    //         s.erase(i);
    // }
    cout<<"raw string size: "<<s.length();
    QString message = QString::fromStdString(s);     //get message
    //message.remove(QChar(""));
    cout<<message.toStdString()<<endl;
    cout<<"Size on receive: "<<message.toStdString().length()<<endl;
    //if message starts with chat tag
    cout<<"check "<<message.toStdString()<<" & "<<protocolChat<<endl;
    cout<<protocolChat<<" has size "<<protocolChat.length()<<endl;
    for(int i=0; i<protocolChat.length(); i++)
    {
        cout<<"comparing: '"<<message.toStdString().at(i)<<"' '"<<protocolChat.at(i)<<"'"<<endl;
        if (message.toStdString().at(i) == protocolChat.at(i))
            cout<<message.toStdString().at(i)<<" matches!"<<endl;
        else cout<<message.toStdString().at(i)<<" doesn't match!!"<<endl;
    }
    cout<<"match: "<<message.toStdString().rfind(protocolChat,0)<<endl;
    cout<<"match2: "<<message.startsWith(pc)<<endl;
//    if (message.toStdString().rfind(protocolChat,0)==0)
//    if(message.startsWith(pc))
    {
        cout<<"receiving chat"<<endl;
        message.remove(0,protocolChat.length());
        cout<<message.toStdString()<<endl;
        emit newMessage(message);
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

}
void MainWindow::nextActionClicked()
{

}
void MainWindow::PreviousActionClicked()
{

}

