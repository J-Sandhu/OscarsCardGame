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
#include <QtWidgets/QHBoxLayout>
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
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *hand;
    QLabel *ACardLabel1;
    QLabel *ACardLabel2;
    QLabel *SelectedACardLabel;
    QLabel *ACardLabel4;
    QLabel *ACardLabel5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *connectionLayout;
    QLineEdit *ipLine;
    QLineEdit *portLine;
    QPushButton *connectButton;
    QPushButton *hostButton;
    QPushButton *startbutton;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *chatLayout;
    QTextEdit *receivedMessageText;
    QPushButton *sendMessageButton;
    QLineEdit *messageLine;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *previousFrameButton;
    QPushButton *newFrameButton;
    QPushButton *nextFrameButton;
    QLineEdit *playerNameLine;
    QComboBox *otherPlayersHandsButton;
    QScrollArea *tableauScrollArea;
    QWidget *scrollAreaContents;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(970, 718);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(260, 520, 461, 142));
        hand = new QHBoxLayout(horizontalLayoutWidget);
        hand->setSpacing(0);
        hand->setObjectName("hand");
        hand->setContentsMargins(0, 0, 0, 0);
        ACardLabel1 = new QLabel(horizontalLayoutWidget);
        ACardLabel1->setObjectName("ACardLabel1");
        ACardLabel1->setMinimumSize(QSize(50, 70));
        ACardLabel1->setMaximumSize(QSize(50, 70));

        hand->addWidget(ACardLabel1);

        ACardLabel2 = new QLabel(horizontalLayoutWidget);
        ACardLabel2->setObjectName("ACardLabel2");
        ACardLabel2->setMinimumSize(QSize(50, 70));
        ACardLabel2->setMaximumSize(QSize(50, 70));

        hand->addWidget(ACardLabel2);

        SelectedACardLabel = new QLabel(horizontalLayoutWidget);
        SelectedACardLabel->setObjectName("SelectedACardLabel");
        SelectedACardLabel->setEnabled(true);
        SelectedACardLabel->setMinimumSize(QSize(100, 140));
        SelectedACardLabel->setMaximumSize(QSize(100, 100));

        hand->addWidget(SelectedACardLabel);

        ACardLabel4 = new QLabel(horizontalLayoutWidget);
        ACardLabel4->setObjectName("ACardLabel4");
        ACardLabel4->setMinimumSize(QSize(50, 70));
        ACardLabel4->setMaximumSize(QSize(50, 70));

        hand->addWidget(ACardLabel4);

        ACardLabel5 = new QLabel(horizontalLayoutWidget);
        ACardLabel5->setObjectName("ACardLabel5");
        ACardLabel5->setMinimumSize(QSize(50, 70));
        ACardLabel5->setMaximumSize(QSize(50, 70));

        hand->addWidget(ACardLabel5);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(180, 30, 461, 33));
        connectionLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        connectionLayout->setObjectName("connectionLayout");
        connectionLayout->setContentsMargins(0, 0, 0, 0);
        ipLine = new QLineEdit(horizontalLayoutWidget_2);
        ipLine->setObjectName("ipLine");

        connectionLayout->addWidget(ipLine);

        portLine = new QLineEdit(horizontalLayoutWidget_2);
        portLine->setObjectName("portLine");

        connectionLayout->addWidget(portLine);

        connectButton = new QPushButton(horizontalLayoutWidget_2);
        connectButton->setObjectName("connectButton");

        connectionLayout->addWidget(connectButton);

        hostButton = new QPushButton(horizontalLayoutWidget_2);
        hostButton->setObjectName("hostButton");

        connectionLayout->addWidget(hostButton);

        startbutton = new QPushButton(horizontalLayoutWidget_2);
        startbutton->setObjectName("startbutton");

        connectionLayout->addWidget(startbutton);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 141, 51));
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
        verticalLayoutWidget->setGeometry(QRect(20, 100, 141, 321));
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

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(740, 530, 116, 100));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        previousFrameButton = new QPushButton(verticalLayoutWidget_2);
        previousFrameButton->setObjectName("previousFrameButton");

        verticalLayout->addWidget(previousFrameButton);

        newFrameButton = new QPushButton(verticalLayoutWidget_2);
        newFrameButton->setObjectName("newFrameButton");

        verticalLayout->addWidget(newFrameButton);

        nextFrameButton = new QPushButton(verticalLayoutWidget_2);
        nextFrameButton->setObjectName("nextFrameButton");

        verticalLayout->addWidget(nextFrameButton);

        playerNameLine = new QLineEdit(centralwidget);
        playerNameLine->setObjectName("playerNameLine");
        playerNameLine->setGeometry(QRect(180, 10, 141, 20));
        otherPlayersHandsButton = new QComboBox(centralwidget);
        otherPlayersHandsButton->setObjectName("otherPlayersHandsButton");
        otherPlayersHandsButton->setGeometry(QRect(770, 30, 103, 32));
        tableauScrollArea = new QScrollArea(centralwidget);
        tableauScrollArea->setObjectName("tableauScrollArea");
        tableauScrollArea->setGeometry(QRect(180, 79, 571, 441));
        tableauScrollArea->setMouseTracking(true);
        tableauScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableauScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableauScrollArea->setWidgetResizable(true);
        scrollAreaContents = new QWidget();
        scrollAreaContents->setObjectName("scrollAreaContents");
        scrollAreaContents->setGeometry(QRect(0, 0, 569, 423));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaContents->sizePolicy().hasHeightForWidth());
        scrollAreaContents->setSizePolicy(sizePolicy);
        tableauScrollArea->setWidget(scrollAreaContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 970, 22));
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
        ACardLabel1->setText(QString());
        ACardLabel2->setText(QString());
        SelectedACardLabel->setText(QString());
        ACardLabel4->setText(QString());
        ACardLabel5->setText(QString());
        ipLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP address", nullptr));
        portLine->setText(QString());
        portLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        hostButton->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        startbutton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "FoOscars", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        previousFrameButton->setText(QCoreApplication::translate("MainWindow", "Previous Card", nullptr));
        newFrameButton->setText(QCoreApplication::translate("MainWindow", "Use Card", nullptr));
        nextFrameButton->setText(QCoreApplication::translate("MainWindow", "Next Card", nullptr));
        playerNameLine->setText(QCoreApplication::translate("MainWindow", "player", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
