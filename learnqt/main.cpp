#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "work.h"

QString Worker::perform(QString fname)   {
    QString out;
    char ch;
    //fname=fname;
    file=new QFile(fname);
    if (!(file->open(QIODevice::ReadOnly | QIODevice::Text)))   {
            return "error";
    }

    QTextStream istrm(file);
    while(!istrm.atEnd())   {
        istrm>>ch;
        out.append(ch);
    }
    file->close();
    return out;

}

int Worker::performWrite(QString fname, QString content)   {
    file=new QFile(fname);
    //fname="~/"+fname;
    if(!file->open(QIODevice::WriteOnly | QIODevice::Truncate))
        return -1;
    QTextStream ostrm(file);
    ostrm<<content;
    file->close();
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Worker w;
    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("worker",&w);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/learnqt/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
