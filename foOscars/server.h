#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include "model.h"
#include "gamestate.h"

///
/// \brief Server class represents the "Controller" for this project
/// according to MVC architecture
///
class Server: public QObject
{
    Q_OBJECT

public:
    Server(QWidget *parent);
    QTcpServer* tcpServer= nullptr;
    QString ipAddress;
    int port;

    /// Vector of all the sockets of players connected
    QVector<QTcpSocket*> players;
    /// pointer to the model object
    Model* model;

    ///
    /// \brief sendMessage: sends the message the specified socket
    /// \param socket
    /// \param message
    ///
    void sendMessage(QTcpSocket* socket, string message);

signals:
    ///
    /// \brief errorOccured: alerts that ther has been a problem
    /// \param error
    ///
    void errorOccured(QString error);

    ///
    /// \brief displayMessage: displays message sent by player
    /// \param newMessage
    ///
    void displayMessage(QString newMessage);


public slots:

    ///
    /// \brief newConnection: new socket connected to server
    ///
    void newConnection();

    ///
    /// \brief discardSocket: remove dead/disconnected sockets
    ///
    void discardSocket();

    ///
    /// \brief readSocket: reads the data that has been sent by a socket
    ///
    void readSocket();

    ///
    /// \brief sendChat: sends a chat message to all the players
    /// \param message
    ///
    void sendChat(QString message);

    ///
    /// \brief sendState: sends the serialized gamestate to all connected clients
    /// \param buffer
    ///
    void sendState(QByteArray buffer);

    ///
    /// \brief sendStateToPlayer: sends the serialized gamestate to the client at the
    /// specified index.
    /// \param buffer
    /// \param playerIndex
    ///
    void sendStateToPlayer(QByteArray buffer, int playerIndex);

private:
    ///
    /// \brief sends a player its index within the gameStates player
    /// array upon connection
    /// \param indexInPlayers
    /// \param client
    ///
    void sendIndex(int indexInPlayers, QTcpSocket* client);

    /// socket message protocols.
    std::string protocolName;
    std::string protocolChat;
    std::string protocolAction;
    std::string protocolTableau;
    std::string protocolGameState;
    std::string protocolStartGame;
    std::string protocolCallBack;
    std::string protocolPlayerIndex;
    std::string protocolSelectedPlayer;


};

#endif // SERVER_H
