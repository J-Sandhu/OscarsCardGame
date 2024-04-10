#include "client.h"
#include <QWidget>
#include <iostream>

using namespace std;

Client::Client(QWidget *parent,QString ipAddress,int port): QObject(parent),ipAddress(ipAddress), port(port), tcpSocket(new QTcpSocket(this))
{
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_6_5);

    connect(tcpSocket, &QIODevice::readyRead, this, &Client::testClientRead);
    connect(tcpSocket, &QAbstractSocket::errorOccurred,this, &Client::errorOccured);
    connect(tcpSocket, &QAbstractSocket::disconnected,  tcpSocket, &QObject::deleteLater);



    //connect(ui->sendMessage, &QAbstractButton::clicked, this, &MainWindow::sendMessageClicked);
}

void Client::testJoin()
{
    tcpSocket->abort();
    tcpSocket->connectToHost(ipAddress,port);

    cout<<"Socket Descriptor in the Client Object after connectToHost is: "<< tcpSocket->socketDescriptor()<<endl;
}

void Client::testClientRead()
{
    cout<<"We get to test read in client!"<<endl;
    cout<<"Socket Descriptor in the Client Object is: "<< tcpSocket->state()<<endl;

    in.startTransaction();

    QString message;

    in >> message;

    if (!in.commitTransaction())
        return;

    cout<< "Message from the server: "<<message.toStdString() <<endl;
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
        cout<< (tr("The following error occurred: %1.").arg(tcpSocket->errorString())).toStdString()<<endl;
    }

}
