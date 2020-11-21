#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setAttribute(Qt::WA_NativeWindow,true);
    w.show();

    return a.exec();
}
