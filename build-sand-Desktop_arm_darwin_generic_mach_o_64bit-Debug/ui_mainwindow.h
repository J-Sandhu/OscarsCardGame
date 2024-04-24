/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *chatLayout;
    QTextEdit *receivedMessageText;
    QPushButton *sendMessageButton;
    QLineEdit *messageLine;
    QLineEdit *playerNameLine;
    QComboBox *otherPlayersHandsButton;
    QFrame *gameplayFrame;
    QScrollArea *tableauScrollArea;
    QWidget *scrollAreaContents;
    QScrollArea *handScrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *nomineeCountLabel;
    QLabel *label_2;
    QScrollArea *playerButtonScrollArea;
    QWidget *playerList;
    QPushButton *connectButton;
    QPushButton *hostButton;
    QPushButton *startbutton;
    QFrame *IPframe;
    QLabel *label_3;
    QLineEdit *ipLine;
    QFrame *portFrame;
    QLabel *label_4;
    QLineEdit *portLine;
    QLabel *winnerNameLabel;
    QPushButton *endGameButton;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1184, 718);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 141, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Rockwell Extra Bold")});
        font.setPointSize(22);
        font.setBold(true);
        label->setFont(font);
        label->setFrameShape(QFrame::Panel);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 80, 141, 481));
        chatLayout = new QVBoxLayout(verticalLayoutWidget);
        chatLayout->setObjectName("chatLayout");
        chatLayout->setContentsMargins(0, 0, 0, 0);
        receivedMessageText = new QTextEdit(verticalLayoutWidget);
        receivedMessageText->setObjectName("receivedMessageText");

        chatLayout->addWidget(receivedMessageText);

        sendMessageButton = new QPushButton(verticalLayoutWidget);
        sendMessageButton->setObjectName("sendMessageButton");

        chatLayout->addWidget(sendMessageButton);

        messageLine = new QLineEdit(verticalLayoutWidget);
        messageLine->setObjectName("messageLine");

        chatLayout->addWidget(messageLine);

        playerNameLine = new QLineEdit(centralwidget);
        playerNameLine->setObjectName("playerNameLine");
        playerNameLine->setGeometry(QRect(170, 10, 261, 20));
        otherPlayersHandsButton = new QComboBox(centralwidget);
        otherPlayersHandsButton->setObjectName("otherPlayersHandsButton");
        otherPlayersHandsButton->setGeometry(QRect(770, 20, 103, 32));
        gameplayFrame = new QFrame(centralwidget);
        gameplayFrame->setObjectName("gameplayFrame");
        gameplayFrame->setGeometry(QRect(170, 80, 1200, 750));
        gameplayFrame->setFrameShape(QFrame::Box);
        gameplayFrame->setFrameShadow(QFrame::Plain);
        tableauScrollArea = new QScrollArea(gameplayFrame);
        tableauScrollArea->setObjectName("tableauScrollArea");
        tableauScrollArea->setGeometry(QRect(10, 250, 751, 490));
        tableauScrollArea->setMouseTracking(true);
        tableauScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableauScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableauScrollArea->setWidgetResizable(true);
        scrollAreaContents = new QWidget();
        scrollAreaContents->setObjectName("scrollAreaContents");
        scrollAreaContents->setGeometry(QRect(0, 0, 749, 472));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaContents->sizePolicy().hasHeightForWidth());
        scrollAreaContents->setSizePolicy(sizePolicy);
        tableauScrollArea->setWidget(scrollAreaContents);
        handScrollArea = new QScrollArea(gameplayFrame);
        handScrollArea->setObjectName("handScrollArea");
        handScrollArea->setGeometry(QRect(770, 250, 351, 491));
        handScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        handScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        handScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 349, 473));
        handScrollArea->setWidget(scrollAreaWidgetContents);
        nomineeCountLabel = new QLabel(gameplayFrame);
        nomineeCountLabel->setObjectName("nomineeCountLabel");
        nomineeCountLabel->setEnabled(false);
        nomineeCountLabel->setGeometry(QRect(10, 210, 261, 31));
        QFont font1;
        font1.setPointSize(24);
        nomineeCountLabel->setFont(font1);
        label_2 = new QLabel(gameplayFrame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(770, 220, 81, 21));
        playerButtonScrollArea = new QScrollArea(gameplayFrame);
        playerButtonScrollArea->setObjectName("playerButtonScrollArea");
        playerButtonScrollArea->setGeometry(QRect(0, 0, 991, 211));
        playerButtonScrollArea->setWidgetResizable(true);
        playerList = new QWidget();
        playerList->setObjectName("playerList");
        playerList->setGeometry(QRect(0, 0, 989, 209));
        playerButtonScrollArea->setWidget(playerList);
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");
        connectButton->setGeometry(QRect(460, 40, 81, 32));
        hostButton = new QPushButton(centralwidget);
        hostButton->setObjectName("hostButton");
        hostButton->setGeometry(QRect(460, 10, 81, 32));
        startbutton = new QPushButton(centralwidget);
        startbutton->setObjectName("startbutton");
        startbutton->setEnabled(false);
        startbutton->setGeometry(QRect(550, 10, 98, 61));
        IPframe = new QFrame(centralwidget);
        IPframe->setObjectName("IPframe");
        IPframe->setGeometry(QRect(170, 30, 151, 41));
        IPframe->setFrameShape(QFrame::Box);
        IPframe->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(IPframe);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 0, 71, 16));
        ipLine = new QLineEdit(IPframe);
        ipLine->setObjectName("ipLine");
        ipLine->setGeometry(QRect(10, 20, 141, 21));
        portFrame = new QFrame(centralwidget);
        portFrame->setObjectName("portFrame");
        portFrame->setGeometry(QRect(330, 30, 101, 41));
        portFrame->setFrameShape(QFrame::Box);
        portFrame->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(portFrame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 0, 58, 16));
        portLine = new QLineEdit(portFrame);
        portLine->setObjectName("portLine");
        portLine->setGeometry(QRect(10, 20, 91, 21));
        winnerNameLabel = new QLabel(centralwidget);
        winnerNameLabel->setObjectName("winnerNameLabel");
        winnerNameLabel->setGeometry(QRect(250, 160, 521, 221));
        QFont font2;
        font2.setPointSize(60);
        winnerNameLabel->setFont(font2);
        endGameButton = new QPushButton(centralwidget);
        endGameButton->setObjectName("endGameButton");
        endGameButton->setGeometry(QRect(660, 10, 101, 61));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(0, -20, 651, 471));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1184, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "FoOscars", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        playerNameLine->setText(QCoreApplication::translate("MainWindow", "player", nullptr));
        nomineeCountLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Your Hand", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        hostButton->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        startbutton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "IP address:", nullptr));
        ipLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP address", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        portLine->setText(QString());
        portLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        winnerNameLabel->setText(QString());
        endGameButton->setText(QCoreApplication::translate("MainWindow", "End Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
