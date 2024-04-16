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
    QSet<QTcpSocket*> players;
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

private:
    std::string protocolName;
    std::string protocolChat;
    std::string protocolAction;
    std::string protocolTableau;
    std::string protocolGameState;
    std::string protocolStartGame;

};

#endif // SERVER_H
