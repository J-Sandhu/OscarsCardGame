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

    server = new QTcpServer(this);

    connect(ui->testClient, &QPushButton::clicked, this, &MainWindow::testClientClicked );
    connect(server, &QTcpServer::newConnection, this, &MainWindow::onPlayerConnect);



    if (!server->listen()) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                                 .arg(server->errorString()));
        close();
        return;
    }

    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }

    port=server->serverPort();
    ui->hostPort->setText(QString::number(port));
    ui->hostIP->setText(QString(ipAddress));


    cout<< ipAddress.toStdString() <<endl;
    cout<< server->serverPort() <<endl;


   testClient = new Client(this,ipAddress, port);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::onPlayerConnect()
{

    players.insert(players.size()+1,server->nextPendingConnection());  //put newly connected player into vector


    cout<<"accepting player with socket desriptor: "<< players[players.size()]->socketDescriptor()<<endl;

    if(players.size()!=4)
    {
        server->close();

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_5);

        out<<QString("You Are Connected");

        // for(QTcpSocket *playerSocket: players.values())
        // {
        //     cout<<"Writing to player with socket desriptor : "<< players[players.size()]->socketDescriptor()<<endl;
        //     cout<<"Number of Bytes Written: "<<playerSocket->write(block)<<endl;
        // }

        cout<<"Number of Bytes Written to just Test Client: "<<testClient->testSocket->write(block)<<endl;

        emit testClient->testSocket->readyRead();

    }

}

void MainWindow::testClientClicked()
{

    connect(testClient->testSocket, &QIODevice::readyRead, testClient, &Client::testClientRead);
    connect(testClient->testSocket, &QAbstractSocket::errorOccurred,testClient, &Client::errorOccured);

    testClient->testJoin();

}

