#include "server.h"

#include <iostream>
using namespace std;

Server::Server(QWidget *parent): QObject(parent)
{
    tcpServer = new QTcpServer(this);
    model = new Model(this);

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
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    port=tcpServer->serverPort();

    connect(model,&Model::sendChatToPlayers,this,&Server::sendChat);
    connect(model,&Model::sendStateToPlayers,this,&Server::sendState);
    connect(model,&Model::sendStateToPlayer, this, &Server::sendStateToPlayer);

    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
    protocolName = "~pname:";
    protocolChat = "~chat:";
    protocolAction= "~action:";
    protocolTableau="~tableau";
    protocolGameState="~gstate:";
    protocolStartGame="~startgame:";
    protocolCallBack= "~callback:";
    protocolPlayerIndex = "~index:";
    protocolSelectedPlayer = "~pselected:";


}

void Server::newConnection()
{

    while (tcpServer->hasPendingConnections())
    {
        QTcpSocket* socket = tcpServer->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &Server::readSocket);
        connect(socket, &QTcpSocket::disconnected, this, &Server::discardSocket);
        players.push_back(socket);

        // alert the model of the new player and add it to the gameState
        model->addNewPlayer(socket->socketDescriptor());
        // alert the player of its position within player array
        int newPlayerIndex = players.size()-1;
        sendIndex(newPlayerIndex,socket);
        sendState(model->gameState.serialize());
    }

}

void Server::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    for (int i=0; i<players.size();i++)
        if (players.at(i)->socketDescriptor()==socket->socketDescriptor())
            players.remove(i);

    socket->deleteLater();
}


void Server::readSocket()
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
    string message = buffer.toStdString();

    if (message.rfind(protocolName,0)==0)
    {
        QString m = QString::fromStdString(message.substr(protocolName.length()));
        model->HandlePlayerName(socket->socketDescriptor(),m);
    }
    else if (message.rfind(protocolChat,0)==0)
    {
        QString m= QString::fromStdString(message.substr(protocolChat.length()));
        model->HandleChatMessage(socket->socketDescriptor(), m);
    }
    else if (message.rfind(protocolAction,0)==0)
    {
        QString m= QString::fromStdString(message.substr(protocolAction.length()));
        model->HandleActionSelection(socket->socketDescriptor(),m);
    }
    else if (message.rfind(protocolSelectedPlayer,0)==0)
    {
        QString m= QString::fromStdString(message.substr(protocolSelectedPlayer.length()));
        model->HandleSelectedPlayer(socket->socketDescriptor(),m);
    }
    else if (message.rfind(protocolTableau,0)==0)
    {
        QString m= QString::fromStdString(message.substr(protocolTableau.length()));
        model->HandleTableauSelection(socket->socketDescriptor(),m);
    }
    else if (message.rfind(protocolStartGame,0)==0)
    {
        model->HandleStartGame(socket->socketDescriptor());
    }
    else
    {
        cout<<"Invalid message from client:"<<socket->socketDescriptor()<<" '"<<message<<"'"<<endl;
    }
}

void Server::sendMessage(QTcpSocket* socket, string message)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            socket->flush();

            QByteArray block;
            block.append(message);
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_5);
            out.setDevice(socket);

            out<<block;
        }
        else
            emit displayMessage("Socket doesn't seem to be opened");
    }
    else
        emit displayMessage("QTCP server not connected");
}
//this one is ONLY for when the model wants to send something in chat
void Server::sendChat(QString message)
{
    message.prepend(protocolChat);
    foreach(QTcpSocket* s, players)
        sendMessage(s,message.toStdString());


}
void Server::sendState(QByteArray buffer)
{
    buffer.prepend(protocolGameState);
    foreach(QTcpSocket* s, players)
        sendMessage(s,buffer.toStdString());

}

void Server::sendStateToPlayer(QByteArray buffer, int playerIndex)
{
    buffer.prepend(protocolGameState);
    sendMessage(players.at(playerIndex),buffer.toStdString());
}

void Server::sendIndex(int indexInPlayers, QTcpSocket* client)
{
    QString message = QString::number(indexInPlayers);
    message.prepend(protocolPlayerIndex);
    sendMessage(client,message.toStdString());
}
