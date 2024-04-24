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

    int selectedActionCardIDFromPersonalPile;
    bool gameIsStarted;
    explicit Model(QObject *parent = nullptr);

    ///
    /// \brief Method used for testing model functionality.
    ///
    void modelTestMethod();
    void HandleChatMessage(long long id, QString message);
    void HandleTableauSelection(long long id, QString message);
    void HandleActionSelection(long long id, QString message);
    void HandlePlayerName(long long id, QString message);
    void HandleStartGame(long long id);
    void addNewPlayer(long long id);

    void endGame();


    //chase's stuff
    void movementCardComplete(int indexInTab);
    void HandleSelectedPlayer(long long id, QString message);
    void scoreManipulatorPlayed(int specifiedColor, int colorScoreBuff, int misc);
    //card Tuple containns model's ptr function and callback
    typedef std::tuple<void(Model::*)(int, int, int), QVector<int>, void(Model::*)(int)> cardTuple; //function, array of params, callback (reference lines below)
    typedef void (Model::* cardFunction)(int, int, int);
    typedef void (Model::* cardCallBack)(int);
    int currentAID;
    void populationActionMap();

    typedef std::tuple<int, int, void (Model::*)(int)> peopleTuple; //cardTuple = correpsonding info (value, color, special func)
    std::map <int,peopleTuple> peopleMap; // int = person id
    std::map <int,cardTuple> actionMap;

    int calulateColorSum(int color, bool manipultorEnabled, int playerIndex);
    void recalculateScore();

    //line order cards
    void frontToBack(int, int, int);
    void shuffleTableauPlayed(int, int, int);
    void shuffleTableauPlayed16(int, int, int);
    void shuffleTableauPlayed17(int, int, int);
    void reverseCardPlayed(int, int, int);
    void newLinePlayed(int, int, int);
    void escapeCardPlayed1stPart(int, int, int);
    void escapeCardPlayed2ndPart(int);
    void addToTableau(int numCardsToShuffle, int, int);
    void addFromTopThree(int, int, int);
    void merylToFront(int, int, int);
    void takeDiscardedAction(int, int, int);
    void crewToFront(int, int, int);
    void moveClosestBlueToFront(int, int, int);
    void choosePlayer(int, int, int);
    void mixAfterTurn(int,int,int);
    void swapHandsComplete(int victimPlayer);
    void discardOneAction(int, int, int);
    void dealNewActionCard(int, int, int);
    void allRemoveAnAction(int, int, int);
    void drawThreeActionNoNoble(int, int, int);
    void endDay(int, int, int);
    void blockPlayer(int, int, int);
    void skipPlayer(int, int, int);

    void afterYou(int);
    void replacePerson(int);
    void discardPerson(int);
    void disqualification(int);


    //blue,green,purple,red
    int blue = 0;
    int green = 1;
    int purple = 2;
    int red = 3;
    int anyColor= -1;
    int numberOfColors= 4;

    void endOfTurn();






signals:
    void sendChatToPlayers(QString);
    void sendStateToPlayers(QByteArray);
    void actionCardSelectedFromPersonalPile(Card selectedActionCard);
    void updateTableauAfterActionCardSelect();
    void gameInitializedSignal();
    void sendStateToPlayer(QByteArray, int playerIndex);
    void displayWinnerAndConfetti();


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
    /// \brief For card 29. makes all negative cards no longer detriment score
    ///
    void neutralizeGrays(int unused,int unused1,int unused2);

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
    /// \brief Method for making a specific player discard a randumb action card
    /// \param victimPlayerIndex
    ///
    void makeDiscardAction(int victimPlayerIndex);

    ///
    /// \brief creates a random tableau and puts it into the game state
    ///  requires that game has been populated
    ///
    void generateRandomTableau(QVector<int> availablePeople, int size);

    ///
    /// \brief populates all player's hands with random action cards
    /// may need to modify this if we allow for less than 4 player to play
    /// for now this is a good test
    ///
    void generateRandomHands();

    ///
    /// \brief This method adds card information to the model
    /// including any special properties
    ///
    void populatePeopleMap();

    void drawActionCard(int numberOfCards);


    ///
    /// \brief adds action card information to the model
    /// this includes the function pointers to any
    /// effects they have
    ///
    void populateActionMap();




};

#endif // MODEL_H
