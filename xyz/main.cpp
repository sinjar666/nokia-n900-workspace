#include <QtGui/QApplication>
#include <QDeclarativeEngine>
#include "qmlapplicationviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
    viewer.engine()->addImportPath(QString("/opt/qtm12/imports"));
    viewer.setMainQmlFile(QLatin1String("qml/xyz/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
