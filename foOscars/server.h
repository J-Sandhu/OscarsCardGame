#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "client.h"
#include "model.h"


class Server: public QObject
{
    Q_OBJECT

public:
    Server(QWidget *parent);

    QTcpServer* tcpServer= nullptr;
    QString ipAddress;
    int port;
    QSet<QTcpSocket*> players;

    void sendMessage(QTcpSocket* socket, QString message);



signals:
    void errorOccured(QString error);
    void displayMessage(QString newMessage);


public slots:

    void newConnection();
    void discardSocket();
    void relayMessageToPlayers();


};

#endif // SERVER_H
