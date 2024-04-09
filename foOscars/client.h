#ifndef CLIENT_H
#define CLIENT_H


#include <QMainWindow>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMap>
#include <QDialog>
#include <QMessageBox>


class Client: public QObject
{

 Q_OBJECT

public:
 Client(QWidget *parent,QString ipAddress,int port);

    QString ipAddress;
    int port;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    void testJoin();

public slots:
    void testClientRead();
    void errorOccured(QAbstractSocket::SocketError socketError);


};

#endif // CLIENT_H
