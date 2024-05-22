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
#include <Box2D/Box2D.h>
#include "confetti.h"
#include <QTimer>


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
    int clientIndexInPlayerArray;

    QTcpSocket* clientSocket;
    GameState gameState;

    int selectedActionCardIndex;

    QVector<QPixmap> actionImages;
    QVector<QPixmap> peopleImages;
    QVector<QLabel*> currentCardsInTableau;

    // create layouts for tableau, hand, and player buttons
    QHBoxLayout* tableauLayout = new QHBoxLayout;
    QWidget* tableauScrollWidget = new QWidget;

    QHBoxLayout* handLayout = new QHBoxLayout;
    QWidget* handScrollWidget = new QWidget;

    QHBoxLayout* playerLayout = new QHBoxLayout;
    QWidget* playerButtonWidget = new QWidget;



    void showCardsOnTableau();
    void showCardsInHand();
    void updateView();
    void showPlayerButtons();

    // Box2D related members
    QTimer timer;
    Confetti confetti;
    QGraphicsScene scene;
    void startConfetti();
    void showConfetti();
    void displayWinnerName();



public slots:
    ///
    /// \brief hostClicked
    /// called when the player clicks host on the view.
    /// creates server, model, and gamestate
    void hostClicked();

    ///
    /// \brief displayMessageFromServer
    /// \param
    ///
    void displayMessageFromServer(QString newMessage);

    ///
    /// \brief connectClicked
    /// called when a client chooses to connect to the server
    /// handles networking initiation.
    void connectClicked();

    ///
    /// \brief readSocket
    /// Used to read messages from server to client
    void readSocket();

    ///
    /// \brief displayMessage
    /// \param str message to be written to view
    /// writes message to view
    void displayMessage(const QString& str);

    ///
    /// \brief displayError
    /// \param socketError
    /// Alerts the user that something has gone wrong with
    /// network connection
    void displayError();

    ///
    /// \brief sendChatMessage
    /// Uses socket to send message to server with the appropriate
    /// protocol prefix
    void sendChatMessage();

    ///
    /// \brief onStartClicked
    /// Sends message to server when the user clicks "start game"
    void onStartClicked();

    ///
    /// \brief tableauCardClicked
    /// Sends a message to the server alerting it of the index in the
    /// tableau layout the user clicked
    void tableauCardClicked();

    ///
    /// \brief actionCardClicked
    /// Sends a message to the server alerting it of the index
    /// in the action card layout the player kicked
    void actionCardClicked();

    ///
    /// \brief anotherPlayerClicked
    /// sends a message to the server alerting it of the index
    /// in the player card button layout the player clicked
    void anotherPlayerClicked();

    ///
    /// \brief displayWinnerAndConfettiSlot
    /// called at the end of the game, used to draw Box2D confetti
    /// animation
    void displayWinnerAndConfettiSlot();

    ///
    /// \brief endGameClicked
    /// called when the game ends
    void endGameClicked();

signals:
    ///
    /// \brief newMessage
    /// \param message
    /// alerts the client that a new message has been typed
    /// in view
    void newMessage(QString message);




private:
    Ui::MainWindow *ui;

    ///
    /// \brief clientSendMessage
    /// \param message
    /// sends message to server
    void clientSendMessage(std::string message);

    ///
    /// \brief getActionCardHand
    /// \return
    /// retrieves the action card hand of this player
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
    //protocol for a callback
    std::string protocolCallBack;
    // protocol for catching index in player array
    std::string protocolPlayerIndex;
    //protocol for selecting a player
    std::string protocolSelectedPlayer;

};
#endif // MAINWINDOW_H
