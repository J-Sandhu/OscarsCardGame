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
{
    ui->setupUi(this);

   //enable the connection buttons and text
    ui->connectButton->setEnabled(true);
    ui->hostButton->setEnabled(true);

    ui->ipLine->setEnabled(true);
    ui->ipLine->setEnabled(true);


    //connect the buttons to their respective actions
    // connect(ui->hostButton, &QPushButton::clicked, server, &Server::createServer);
    connect(ui->hostButton, &QPushButton::clicked, this, &MainWindow::hostClicked);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectClicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::hostClicked()
{

    ui->connectButton->setEnabled(false);
    ui->hostButton->setEnabled(false);
    ui->ipLine->setEnabled(false);
    ui->portLine->setEnabled(false);

    server= new Server(this);

    ui->ipLine->setText(server->ipAddress);
    ui->portLine->setText(QString::number(server->port));

    serverPort=server->port;
    serverIpAddress= server->server->serverAddress();


    // connect(server->server, &QTcpServer::newConnection, server, &Server::newConnection);
    connect(server, &Server::displayMessage, this, &MainWindow::displayMessageFromServer);

    connectClicked();
}

void MainWindow::connectClicked()
{
    cout<<"state of the server: "<<server->server->socketDescriptor()<<endl;


    clientSocket = new QTcpSocket(this);


    cout<<"state of the client socket: "<<clientSocket->socketDescriptor()<<endl;
    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);

    clientSocket->connectToHost(serverIpAddress,serverPort);
    cout<<"state of the client socket after attempting to connect to host: "<<clientSocket->socketDescriptor()<<endl;
}



void MainWindow::displayMessageFromServer(QString newMessage)
{
    ui->receivedMessageText->append(newMessage);
}

void MainWindow::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(clientSocket->socketDescriptor());
        emit newMessage(message);
        return;
    }


    QString message = QString("%1 :: %2").arg(clientSocket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
    emit newMessage(message);


}

void MainWindow::displayMessage(const QString& str)
{
    ui->receivedMessageText->append(str);
}


