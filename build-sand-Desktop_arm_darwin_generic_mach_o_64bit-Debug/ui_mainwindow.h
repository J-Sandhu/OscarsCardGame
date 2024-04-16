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
    QLineEdit *playerNameLine;
    QComboBox *otherPlayersHandsButton;
    QScrollArea *tableauScrollArea;
    QWidget *scrollAreaContents;
    QLabel *nomineeCountLabel;
    QScrollArea *handScrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1184, 718);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
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
        startbutton->setEnabled(false);

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

        playerNameLine = new QLineEdit(centralwidget);
        playerNameLine->setObjectName("playerNameLine");
        playerNameLine->setGeometry(QRect(180, 10, 141, 20));
        otherPlayersHandsButton = new QComboBox(centralwidget);
        otherPlayersHandsButton->setObjectName("otherPlayersHandsButton");
        otherPlayersHandsButton->setGeometry(QRect(770, 30, 103, 32));
        tableauScrollArea = new QScrollArea(centralwidget);
        tableauScrollArea->setObjectName("tableauScrollArea");
        tableauScrollArea->setGeometry(QRect(170, 160, 571, 490));
        tableauScrollArea->setMouseTracking(true);
        tableauScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableauScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableauScrollArea->setWidgetResizable(true);
        scrollAreaContents = new QWidget();
        scrollAreaContents->setObjectName("scrollAreaContents");
        scrollAreaContents->setGeometry(QRect(0, 0, 569, 472));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaContents->sizePolicy().hasHeightForWidth());
        scrollAreaContents->setSizePolicy(sizePolicy);
        tableauScrollArea->setWidget(scrollAreaContents);
        nomineeCountLabel = new QLabel(centralwidget);
        nomineeCountLabel->setObjectName("nomineeCountLabel");
        nomineeCountLabel->setEnabled(false);
        nomineeCountLabel->setGeometry(QRect(340, 110, 261, 31));
        QFont font1;
        font1.setPointSize(24);
        nomineeCountLabel->setFont(font1);
        handScrollArea = new QScrollArea(centralwidget);
        handScrollArea->setObjectName("handScrollArea");
        handScrollArea->setGeometry(QRect(760, 160, 350, 490));
        handScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        handScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        handScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 348, 472));
        handScrollArea->setWidget(scrollAreaWidgetContents);
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
        ipLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP address", nullptr));
        portLine->setText(QString());
        portLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        hostButton->setText(QCoreApplication::translate("MainWindow", "Host", nullptr));
        startbutton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "FoOscars", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        playerNameLine->setText(QCoreApplication::translate("MainWindow", "player", nullptr));
        nomineeCountLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
