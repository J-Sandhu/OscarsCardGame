#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

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
    QTcpServer server;

private:
    Ui::MainWindow *ui;
    QVector<QTcpSocket*> players;
    QByteArray outputBuffer;

    void onPlayerConnect();
    void testJoin();
};
#endif // MAINWINDOW_H
