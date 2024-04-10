#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMap>
#include "client.h"
#include "server.h"

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



public slots:

    void hostClicked();
    void displayMessageFromServer(QString newMessage);
    void connectClicked();
    void readSocket();
    void displayMessage(const QString& str);
signals:
    void newMessage(QString message);




private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
