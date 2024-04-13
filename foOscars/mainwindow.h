#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMap>
#include <QImage>
#include "server.h"
#include "gamestate.h"
#include "model.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Model* model = nullptr);
    Model* model;
    ~MainWindow();
    Server* server;
    QHostAddress serverIpAddress;
    int serverPort;

    QTcpSocket* clientSocket;
    GameState gameState;
    int selectedActionCardIndex;
    QVector<QImage> actionImages;
    QVector<QLabel*> currentCardsInTableau;


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
    void updateTableauAfterActionCardSelectSlot();
    void actionCardFromPersonalPileSelected(int cardID, Card actionCard);

signals:
    void newMessage(QString message);




private:
    Ui::MainWindow *ui;
    //for when client wants to send a message to the server
    void clientSendMessage(std::string message);
    std::vector<QImage> getActionCardHand();
    //QString makeActionCardFilename(int actionCardID);
    void updateActionHand(std::vector<QImage> images);
    ///
    /// \brief Method that will load the images for all action cards
    /// and eventually the images for all player cards
    ///
    void loadResources();
    //protocol header for sending player's name
    std::string protocolName;
    //protocol header for sending a chat message
    std::string protocolChat;
    //protocol header for sending index of played card in hand vector
    std::string protocolAction;
    //protocol header for sending index of selected card in tableau
    std::string protocolTableau;
    //protocol header for receiving game state from the server
    std::string protocolGameState;

};
#endif // MAINWINDOW_H
