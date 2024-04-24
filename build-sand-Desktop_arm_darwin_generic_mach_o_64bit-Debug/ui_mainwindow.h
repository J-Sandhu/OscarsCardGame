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
    QFrame *gameplayFrame;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *nomineeLayout;
    QScrollArea *tableauScrollArea;
    QWidget *scrollAreaContents;
    QLabel *nomineeCountLabel;
    QScrollArea *handScrollArea;
    QWidget *scrollAreaWidgetContents;
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
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *textLayout;
    QLabel *roundLabel;
    QLabel *nomineeLabel;
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
        gameplayFrame = new QFrame(centralwidget);
        gameplayFrame->setObjectName("gameplayFrame");
        gameplayFrame->setGeometry(QRect(170, 80, 1200, 750));
        gameplayFrame->setFrameShape(QFrame::Box);
        gameplayFrame->setFrameShadow(QFrame::Plain);
        verticalLayoutWidget_2 = new QWidget(gameplayFrame);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(70, 240, 16777215, 1025));
        nomineeLayout = new QVBoxLayout(verticalLayoutWidget_2);
        nomineeLayout->setObjectName("nomineeLayout");
        nomineeLayout->setContentsMargins(0, 0, 0, 0);
        tableauScrollArea = new QScrollArea(verticalLayoutWidget_2);
        tableauScrollArea->setObjectName("tableauScrollArea");
        tableauScrollArea->setMinimumSize(QSize(0, 490));
        tableauScrollArea->setMaximumSize(QSize(700, 490));
        tableauScrollArea->setMouseTracking(true);
        tableauScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableauScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableauScrollArea->setWidgetResizable(true);
        tableauScrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaContents = new QWidget();
        scrollAreaContents->setObjectName("scrollAreaContents");
        scrollAreaContents->setGeometry(QRect(0, 8, 698, 472));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaContents->sizePolicy().hasHeightForWidth());
        scrollAreaContents->setSizePolicy(sizePolicy);
        tableauScrollArea->setWidget(scrollAreaContents);

        nomineeLayout->addWidget(tableauScrollArea);

        nomineeCountLabel = new QLabel(verticalLayoutWidget_2);
        nomineeCountLabel->setObjectName("nomineeCountLabel");
        nomineeCountLabel->setEnabled(true);
        QFont font1;
        font1.setPointSize(20);
        nomineeCountLabel->setFont(font1);
        nomineeCountLabel->setAlignment(Qt::AlignCenter);

        nomineeLayout->addWidget(nomineeCountLabel);

        handScrollArea = new QScrollArea(gameplayFrame);
        handScrollArea->setObjectName("handScrollArea");
        handScrollArea->setGeometry(QRect(790, 240, 350, 490));
        handScrollArea->setMinimumSize(QSize(350, 490));
        handScrollArea->setMaximumSize(QSize(350, 490));
        handScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        handScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        handScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 348, 472));
        handScrollArea->setWidget(scrollAreaWidgetContents);
        playerButtonScrollArea = new QScrollArea(gameplayFrame);
        playerButtonScrollArea->setObjectName("playerButtonScrollArea");
        playerButtonScrollArea->setGeometry(QRect(30, 10, 1141, 221));
        playerButtonScrollArea->setWidgetResizable(true);
        playerList = new QWidget();
        playerList->setObjectName("playerList");
        playerList->setGeometry(QRect(0, 0, 1139, 219));
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
        winnerNameLabel->setGeometry(QRect(180, 160, 1021, 221));
        QFont font2;
        font2.setPointSize(60);
        winnerNameLabel->setFont(font2);
        endGameButton = new QPushButton(centralwidget);
        endGameButton->setObjectName("endGameButton");
        endGameButton->setGeometry(QRect(660, 10, 101, 61));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(170, 0, 3000, 3000));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(789, 9, 331, 61));
        textLayout = new QVBoxLayout(verticalLayoutWidget_3);
        textLayout->setSpacing(0);
        textLayout->setObjectName("textLayout");
        textLayout->setContentsMargins(0, 0, 0, 0);
        roundLabel = new QLabel(verticalLayoutWidget_3);
        roundLabel->setObjectName("roundLabel");

        textLayout->addWidget(roundLabel);

        nomineeLabel = new QLabel(verticalLayoutWidget_3);
        nomineeLabel->setObjectName("nomineeLabel");

        textLayout->addWidget(nomineeLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1184, 22));
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
        roundLabel->setText(QString());
        nomineeLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
