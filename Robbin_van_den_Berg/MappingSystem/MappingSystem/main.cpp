#include "mainwindow.h"
#include <QApplication>
#include "Logic.h"

int main(int argc, char *argv[])
{
    Logic logic;
    delete logic;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
