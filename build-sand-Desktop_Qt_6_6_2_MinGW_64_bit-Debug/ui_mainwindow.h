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
    QHBoxLayout *action_tableau;
    QLabel *frameLabel1;
    QLabel *frameLabel2;
    QFrame *frame_2;
    QLabel *frameLabel3;
    QLabel *frameLabel4;
    QLabel *frameLabel5;
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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(180, 330, 411, 102));
        action_tableau = new QHBoxLayout(horizontalLayoutWidget);
        action_tableau->setSpacing(0);
        action_tableau->setObjectName("action_tableau");
        action_tableau->setContentsMargins(0, 0, 0, 0);
        frameLabel1 = new QLabel(horizontalLayoutWidget);
        frameLabel1->setObjectName("frameLabel1");
        frameLabel1->setMinimumSize(QSize(100, 100));
        frameLabel1->setMaximumSize(QSize(100, 100));

        action_tableau->addWidget(frameLabel1);

        frameLabel2 = new QLabel(horizontalLayoutWidget);
        frameLabel2->setObjectName("frameLabel2");
        frameLabel2->setMinimumSize(QSize(100, 100));
        frameLabel2->setMaximumSize(QSize(100, 100));

        action_tableau->addWidget(frameLabel2);

        frame_2 = new QFrame(horizontalLayoutWidget);
        frame_2->setObjectName("frame_2");
        frame_2->setEnabled(true);
        frame_2->setMinimumSize(QSize(100, 100));
        frame_2->setMaximumSize(QSize(100, 100));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(2);
        frameLabel3 = new QLabel(frame_2);
        frameLabel3->setObjectName("frameLabel3");
        frameLabel3->setEnabled(true);
        frameLabel3->setGeometry(QRect(0, 0, 100, 100));
        frameLabel3->setMinimumSize(QSize(100, 100));
        frameLabel3->setMaximumSize(QSize(100, 100));
        frameLabel4 = new QLabel(frame_2);
        frameLabel4->setObjectName("frameLabel4");
        frameLabel4->setGeometry(QRect(0, 0, 100, 100));
        frameLabel4->setMinimumSize(QSize(100, 100));
        frameLabel4->setMaximumSize(QSize(100, 100));

        action_tableau->addWidget(frame_2);

        frameLabel5 = new QLabel(horizontalLayoutWidget);
        frameLabel5->setObjectName("frameLabel5");
        frameLabel5->setMinimumSize(QSize(100, 100));
        frameLabel5->setMaximumSize(QSize(100, 100));

        action_tableau->addWidget(frameLabel5);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(180, 30, 461, 31));
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
        verticalLayoutWidget_2->setGeometry(QRect(600, 330, 101, 91));
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
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
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
        frameLabel1->setText(QString());
        frameLabel2->setText(QString());
        frameLabel3->setText(QString());
        frameLabel4->setText(QString());
        frameLabel5->setText(QString());
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
