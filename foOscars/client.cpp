#include "client.h"
#include <QWidget>
#include <iostream>

using namespace std;

Client::Client(QWidget *parent,QString ipAddress,int port): QObject(parent),ipAddress(ipAddress), port(port), testSocket(new QTcpSocket(this))
{
    in.setDevice(testSocket);
    in.setVersion(QDataStream::Qt_6_5);

    connect(testSocket, &QIODevice::readyRead, this, &Client::testClientRead);
    connect(testSocket, &QAbstractSocket::errorOccurred,this, &Client::errorOccured);
}

void Client::testJoin()
{
    testSocket->connectToHost(ipAddress,port);
}

void Client::testClientRead()
{
    cout<<"We get to test read in client!"<<endl;

    in.startTransaction();

    QString message;
    in >> message;

    cout<< "Partial message from the server: " <<message.toStdString() <<endl;

    if (!in.commitTransaction())
        return;

    cout<< "Full message from the server: "<<message.toStdString() <<endl;
}

void Client::errorOccured(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        cout <<("The host was not found. Please check the host name and port settings.")<<endl;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        cout<< ("The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.")<<endl;
        break;
    default:
        cout<< (tr("The following error occurred: %1.").arg(testSocket->errorString())).toStdString()<<endl;
    }

}
