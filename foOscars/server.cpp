#include "server.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
using namespace std;

Server::Server(QWidget *parent): QObject(parent)
{

    server = new QTcpServer(this);
    cout<<"state of the server after construction: "<<server->socketDescriptor()<<endl;
    if (!server->listen()) {
        emit errorOccured(server->errorString());
        server->close();
        return;
    }
    cout<<"state of the server after listen: "<<server->socketDescriptor()<<endl;

    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }

    port= server->serverPort();

    // connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);

}

void Server::newConnection()
{

    while (server->hasPendingConnections())
    {
        QTcpSocket* socket = server->nextPendingConnection();
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





