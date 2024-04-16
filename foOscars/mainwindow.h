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
#include <QPixmap>


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
    //Model* model;
    ~MainWindow();
    Server* server;
    QHostAddress serverIpAddress;
    int serverPort;
    int clientIndexInPlayerArray;

    QTcpSocket* clientSocket;
    GameState gameState;
    int selectedActionCardIndex;
    QVector<QPixmap> actionImages;
    QVector<QPixmap> peopleImages;
    QVector<QLabel*> currentCardsInTableau;

    //create tableau layout
    // this has to be done here because idk
    QHBoxLayout* tableauLayout = new QHBoxLayout;
    QWidget* tableauScrollWidget = new QWidget;

    QHBoxLayout* handLayout = new QHBoxLayout;
    QWidget* handScrollWidget = new QWidget;

    void showCardsOnTableau();
    void showCardsInHand();
    void updateOtherPlayersHandsBox();
    void updateView();



public slots:

    void hostClicked();
    void displayMessageFromServer(QString newMessage);
    void connectClicked();
    void readSocket();
    void displayMessage(const QString& str);
    void displayError(QAbstractSocket::SocketError socketError);
    void sendChatMessage();
    void cardPlayed();
    void updateTableauAfterActionCardSelectSlot();
    void actionCardFromPersonalPileSelected(int cardID, Card actionCard);
    void onStartClicked();
    void displayPopUp(int index);
    void tableauCardClicked();
    void actionCardClicked();
    void anotherPlayerPersonCardClicked();


    void actionCardPlayed();
    void tabSelected();

signals:
    void newMessage(QString message);
    //void startGame();



private:
    Ui::MainWindow *ui;
    //for when client wants to send a message to the server
    void clientSendMessage(std::string message);
    std::vector<QImage> getActionCardHand();
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
    //protocol header for host to start game
    std::string protocolStartGame;

    std::string protocolCallBack;

};
#endif // MAINWINDOW_H
