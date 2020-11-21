#include <QtGui/QApplication>
#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "this info.";
    return a.exec();
}
