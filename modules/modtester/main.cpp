#include <QApplication>
#include "stillcam.h"

int main(int argc, char *argv[])
{
    g_digicam_init(&argc,&argv);
    QApplication app(argc, argv);

    app.setAttribute(Qt::AA_NativeWindows,true);
    StillCam cam("/home/user/sample.jpg");
    cam.show();

    return app.exec();
}
