#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;



    server.listen(QHostAddress::Any,1200 );



    connect(&server, &QTcpServer::newConnection, this, &MainWindow::onPlayerConnect);

    if (!server.isListening()) {
        // QMessageBox::critical(this, tr("Fortune Server"),
        //                       tr("Unable to start the server: %1.")
        //                           .arg(tcpServer->errorString()));
        // server is not listening
        close();
        return;
    }
}



void MainWindow::onPlayerConnect()
{


}
