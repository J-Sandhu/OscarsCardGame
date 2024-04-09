#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMap>
#include "client.h"

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
    QTcpServer* server;
    QString ipAddress;
    int port;

    Client* testClient;


public slots:
    void testClientClicked();
    void onPlayerConnect();

private:
    Ui::MainWindow *ui;
    QMap<int, QTcpSocket*> players;
    QByteArray outputBuffer;


};
#endif // MAINWINDOW_H
