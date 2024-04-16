#include "mainwindow.h"

#include <QApplication>
#include "model.h" //TODO: remove this evil evil code

int main(int argc, char *argv[])
{
    // //TODO: remove this test code
    // std::cout << "creating a model" << std::endl;
    // Model model;
    //model.modelTestMethod();
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.show();
    return a.exec();
}
