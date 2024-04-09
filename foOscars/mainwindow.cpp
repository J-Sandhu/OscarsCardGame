#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkInterface>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString ipAddress;
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }

    server.listen(QHostAddress::Any,1200 );
    std::cout<<"server IP: "<<server.serverAddress().toIPv4Address()<<std::endl;

    connect(&server, &QTcpServer::newConnection, this, &MainWindow::onPlayerConnect);

    if (!server.isListening()) {
        // QMessageBox::critical(this, tr("Fortune Server"),
        //                       tr("Unable to start the server: %1.")
        //                           .arg(tcpServer->errorString()));
        // server is not listening
        close();
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::onPlayerConnect()
{
    if (players.size()==4)
    {
        std::cout<<"rejecting player"<<std::endl;
        server.close();                              //stop listening for new connections.
        return;
    }
    players.push_back(server.nextPendingConnection());  //put newly connected player into vector
    if (players.size()==2)
    {
        //enable some UI button that starts the game
    }


}

void MainWindow::testJoin()
{
    QTcpSocket a;
    //a.connectToHost()
    //connect some socket
}
