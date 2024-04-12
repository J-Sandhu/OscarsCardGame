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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *person6;
    QLabel *person4;
    QLabel *person1;
    QLabel *person2;
    QLabel *person0;
    QLabel *person9;
    QLabel *person3;
    QLabel *person5;
    QLabel *person8;
    QLabel *person7;
    QLabel *person10;
    QLabel *person11;
    QLabel *person12;
    QLabel *person13;
    QLabel *person14;
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
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(179, 67, 701, 451));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        person6 = new QLabel(gridLayoutWidget);
        person6->setObjectName("person6");
        person6->setEnabled(true);
        person6->setMinimumSize(QSize(100, 140));
        person6->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person6, 1, 1, 1, 1);

        person4 = new QLabel(gridLayoutWidget);
        person4->setObjectName("person4");
        person4->setEnabled(true);
        person4->setMinimumSize(QSize(100, 140));
        person4->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person4, 0, 4, 1, 1);

        person1 = new QLabel(gridLayoutWidget);
        person1->setObjectName("person1");
        person1->setEnabled(true);
        person1->setMinimumSize(QSize(100, 140));
        person1->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person1, 0, 1, 1, 1);

        person2 = new QLabel(gridLayoutWidget);
        person2->setObjectName("person2");
        person2->setEnabled(true);
        person2->setMinimumSize(QSize(100, 140));
        person2->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person2, 0, 2, 1, 1);

        person0 = new QLabel(gridLayoutWidget);
        person0->setObjectName("person0");
        person0->setEnabled(true);
        person0->setMinimumSize(QSize(100, 140));
        person0->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person0, 0, 0, 1, 1);

        person9 = new QLabel(gridLayoutWidget);
        person9->setObjectName("person9");
        person9->setEnabled(true);
        person9->setMinimumSize(QSize(100, 140));
        person9->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person9, 1, 4, 1, 1);

        person3 = new QLabel(gridLayoutWidget);
        person3->setObjectName("person3");
        person3->setEnabled(true);
        person3->setMinimumSize(QSize(100, 140));
        person3->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person3, 0, 3, 1, 1);

        person5 = new QLabel(gridLayoutWidget);
        person5->setObjectName("person5");
        person5->setEnabled(true);
        person5->setMinimumSize(QSize(100, 140));
        person5->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person5, 1, 0, 1, 1);

        person8 = new QLabel(gridLayoutWidget);
        person8->setObjectName("person8");
        person8->setEnabled(true);
        person8->setMinimumSize(QSize(100, 140));
        person8->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person8, 1, 3, 1, 1);

        person7 = new QLabel(gridLayoutWidget);
        person7->setObjectName("person7");
        person7->setEnabled(true);
        person7->setMinimumSize(QSize(100, 140));
        person7->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person7, 1, 2, 1, 1);

        person10 = new QLabel(gridLayoutWidget);
        person10->setObjectName("person10");
        person10->setEnabled(true);
        person10->setMinimumSize(QSize(100, 140));
        person10->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person10, 2, 0, 1, 1);

        person11 = new QLabel(gridLayoutWidget);
        person11->setObjectName("person11");
        person11->setEnabled(true);
        person11->setMinimumSize(QSize(100, 140));
        person11->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person11, 2, 1, 1, 1);

        person12 = new QLabel(gridLayoutWidget);
        person12->setObjectName("person12");
        person12->setEnabled(true);
        person12->setMinimumSize(QSize(100, 140));
        person12->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person12, 2, 2, 1, 1);

        person13 = new QLabel(gridLayoutWidget);
        person13->setObjectName("person13");
        person13->setEnabled(true);
        person13->setMinimumSize(QSize(100, 140));
        person13->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person13, 2, 3, 1, 1);

        person14 = new QLabel(gridLayoutWidget);
        person14->setObjectName("person14");
        person14->setEnabled(true);
        person14->setMinimumSize(QSize(100, 140));
        person14->setMaximumSize(QSize(100, 100));

        gridLayout->addWidget(person14, 2, 4, 1, 1);

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
        label->setText(QCoreApplication::translate("MainWindow", "FoOscars", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        previousFrameButton->setText(QCoreApplication::translate("MainWindow", "Previous Card", nullptr));
        newFrameButton->setText(QCoreApplication::translate("MainWindow", "Use Card", nullptr));
        nextFrameButton->setText(QCoreApplication::translate("MainWindow", "Next Card", nullptr));
        playerNameLine->setText(QCoreApplication::translate("MainWindow", "player", nullptr));
        person6->setText(QString());
        person4->setText(QString());
        person1->setText(QString());
        person2->setText(QString());
        person0->setText(QString());
        person9->setText(QString());
        person3->setText(QString());
        person5->setText(QString());
        person8->setText(QString());
        person7->setText(QString());
        person10->setText(QString());
        person11->setText(QString());
        person12->setText(QString());
        person13->setText(QString());
        person14->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
