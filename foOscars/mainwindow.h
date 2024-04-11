#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMap>
#include "server.h"
#include "gamestate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Server* server;
    QHostAddress serverIpAddress;
    int serverPort;

    QTcpSocket* clientSocket;
    GameState gameState;



public slots:

    void hostClicked();
    void displayMessageFromServer(QString newMessage);
    void connectClicked();
    void readSocket();
    void displayMessage(const QString& str);
    void displayError(QAbstractSocket::SocketError socketError);
    void sendChatMessage();
    void cardPlayed();
    void nextActionClicked();
    void PreviousActionClicked();

signals:
    void newMessage(QString message);




private:
    Ui::MainWindow *ui;
    //for when client wants to send a message to the server
    void clientSendMessage(std::string message);



};
#endif // MAINWINDOW_H
