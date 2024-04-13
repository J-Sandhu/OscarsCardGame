#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <map>
#include "card.h"
#include "gamestate.h"
#include <QRandomGenerator>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    GameState gameState;

    std::map <int, Card> personMap;

    int selectedActionCardIDFromPersonalPile;

    explicit Model(QObject *parent = nullptr);

    ///
    /// \brief Method used for testing model functionality.
    ///
    void modelTestMethod();
    void HandleChatMessage(long long id, QString message);
    void HandleTableauSelection(long long id, QString message);
    void HandleActionSelection(long long id, QString message);
    void HandlePlayerName(long long id, QString message);

public slots:
    void startGameSlot();

signals:
    void sendChatToPlayers(QString);
    void actionCardSelectedFromPersonalPile(Card selectedActionCard);
    void updateTableauAfterActionCardSelect();
    void gameInitializedSignal();

private:
    ///
    /// Function pointer type for action cards, takes 3 generic integer parameters
    /// which are to be defined later
    ///
    typedef void (*actionCardFuncPtr)(int param1, int param2, int param3);

    ///
    /// \brief map from card ID to function.
    /// functions must be of the type actionCardFuncPtr to match
    /// parameters
    ///
    std::map<int, Card> actionMap;

    ///
    /// \brief Adds additional points to the current players score calculator
    /// \param victimPlayerID
    /// \param scoreModification
    /// \param unused paramter
    ///
    void addPointsFromActionCard(int scoreModification, int unused1, int unused2);

    ///
    /// \brief Modifies color multiplier of the current players score calculator
    /// \param index of color that will be modified
    /// \param scoreModification the amount the point values of that color are modified
    /// \param unused parameter
    ///
    void addPointsForColor(int color, int scoreModification, int unused1);

    ///
    /// \brief modifies the specified player's score calculator.
    /// \param index of player to be sabotaged
    /// \param scoreModification the amount the victim's score will be affected by
    /// \param unused parameter
    ///
    void decreaseOtherPlayerPoints(int victimPlayerIndex, int scoreModification, int unused1);

    ///
    /// \brief modifies the position of the specified card within the tableau
    /// this method will not be hard coded into the game because it will need to receive
    /// parameters from the client. I.E. it doesn't have the exact same effect every time
    /// \param indexInTableau index of the selected card within the tableau
    /// \param positionModification number of positions the card is being used
    /// \param unused parameter
    ///
    void movementCardPlayed(int requiredColor, int unused1, int unused2);

    ///
    /// \brief This method will replace the line
    /// \param unused1
    /// \param unused2
    /// \param unused3
    ///
    void newTableau(int unused1, int unused2, int unused3);

    ///
    /// \brief fills the game state with the required card ids
    ///
    void populateGameState();

    ///
    /// \brief creates a random tableau and puts it into the game state
    ///  requires that game has been populated
    ///
    void generateRandomTableau();

    ///
    /// \brief populates all player's hands with random action cards
    /// may need to modify this if we allow for less than 4 player to play
    /// for now this is a good test
    ///
    void generateRandomHands();




};

#endif // MODEL_H
