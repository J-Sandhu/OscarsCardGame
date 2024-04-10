#include "server.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
using namespace std;

Server::Server(QWidget *parent): QObject(parent)
{

    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen()) {
        cout<<(tr("Fortune Server Unable to start the server: %1.").arg(tcpServer->errorString())).toStdString()<<endl;
        tcpServer->close();
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
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    cout<<tr("The server is running on IP: %1 and port: %2 ").arg(ipAddress).arg(tcpServer->serverPort()).toStdString()<<endl;
    port=tcpServer->serverPort();


    // connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);

}

void Server::newConnection()
{

    while (tcpServer->hasPendingConnections())
    {
        QTcpSocket* socket = tcpServer->nextPendingConnection();
        players.insert(socket);

        cout<<"connection!!"<<endl;
        connect(socket, &QTcpSocket::readyRead, this, &Server::relayMessageToPlayers);
        connect(socket, &QTcpSocket::disconnected, this, &Server::discardSocket);
        // connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

        emit displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
    }

}

void Server::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = players.find(socket);
    if (it != players.end()){
        emit displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        players.remove(*it);
    }
    socket->deleteLater();
}


void Server::relayMessageToPlayers()
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

    QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));

    foreach (QTcpSocket* socket,players)
    {
        sendMessage(socket,message);
    }

}

void Server::sendMessage(QTcpSocket* socket, QString message)
{
    if(socket)
    {
        if(socket->isOpen())
        {

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_5);
            out.setDevice(socket);

            out<<message;

            socket->write(block);
        }
        else
            emit displayMessage("Socket doesn't seem to be opened");
    }
    else
        emit displayMessage("QTCP server not connected");
}




