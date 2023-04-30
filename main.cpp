#include "mainwindow.h"

#include <QApplication>

//! Starting point of the programme.fdgdfg
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // New instance of QApplication.
    MainWindow w; // New instance of QMainWindow.
    w.show(); //  Toggle ON visibility of MainWindow.
    return a.exec();
}
