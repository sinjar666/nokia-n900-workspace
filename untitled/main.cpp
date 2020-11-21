#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QKeyEvent>
#include "qmlapplicationviewer.h"

class Factorial : public QObject    {
    int x;

public:

   Q_INVOKABLE QString fact()  {
       int f=1;
        QString str;
        for(int i=x;i>0;i--)
            f=f*x;
        str="hell";
        return str;
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QmlApplicationViewer viewer;
    Factorial f;
    //ApplicationData data;
    //viewer.rootContext()->setContextProperty("applicationData",&data);
    viewer.rootContext()->setContextProperty("factorial", &f);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/untitled/main.qml"));
    //viewer.setSource(QUrl("qrc:///suji.png"));
    viewer.showExpanded();

    return app.exec();
}
