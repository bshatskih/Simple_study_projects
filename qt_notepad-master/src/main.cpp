#include <QApplication>
#include <QDebug>
#include "mainwindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mainwindow w;
    w.show();
    return QApplication::exec();
}