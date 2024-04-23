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
    QVector<QTcpSocket*> players;
    Model* model;

    void sendMessage(QTcpSocket* socket, string message);




signals:
    void errorOccured(QString error);
    void displayMessage(QString newMessage);


public slots:

    void newConnection();
    void discardSocket();
    void readSocket();
    void sendChat(QString message);
    void sendState(QByteArray buffer);
    void sendStateToPlayer(QByteArray buffer, int playerIndex);

private:
    ///
    /// \brief sends a player its index within the gameStates player
    /// array upon connection
    /// \param indexInPlayers
    /// \param client
    ///
    void sendIndex(int indexInPlayers, QTcpSocket* client);
    std::string protocolName;
    std::string protocolChat;
    std::string protocolAction;
    std::string protocolTableau;
    std::string protocolGameState;
    std::string protocolStartGame;
    std::string protocolCallBack;
    std::string protocolPlayerIndex;

};

#endif // SERVER_H
