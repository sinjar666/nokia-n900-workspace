/*-----------------------------------------------------------------------/
/--------------------------MODULE--STILLCAM------------------------------/
/---------file:stillcam.h------------------------------------------------/
/---Author :: Srijan Mukherjee-------------------------------------------/
/-This module allows the user to scan a document or paper using----------/
/-the phone's camera.----------------------------------------------------/
/------------CAM SETTINGS ARE--------------------------------------------/
/----FOCUS MODE = AUTO, MACROFOCUS ENABLED-------------------------------/
/---------EXPOSURE MODE = AUTO ------------------------------------------/
/----------FLASH= OFF----------------------------------------------------/
/Makes use of gdigicam camerabin api and gstreamer plugins from bad set--/
/DO NOT FORCEFULLY END THE APPLICATION AS THIS DISABLES THE DEFAULT------/
/camera-ui AND LATER ENABLES IT ON CLOSING APP AS IT BINDS TO DBUS SIGNALS
/FOR SHUTTER RELEASE AND FOCUS LOCK--------------------------------------/
/IN THE EVENT OF SUCH FORCEFULLY ENDING THE APPLICATION USE dsmetool to--/
/restart camera-ui-------------------------------------------------------/
/----$ /usr/sbin/dsmetool -t /usr/bin/camera-ui--------------------------/
/Above to resume the normal functioning of the default camera application/
/To be used only on supported linux based os, eg Maemo5-fremantle-pr1.3-*/




#ifndef STILLCAM_H
#define STILLCAM_H

#include <QWidget>
#include <QList>
#include <gdigicam-0.3/gdigicam/gdigicam-manager.h>
#include <gdigicam-0.3/gdigicam/gdigicam-error.h>
#include <gdigicam-0.3/gdigicam/gst-camerabin/gdigicam-camerabin.h>
#include <gdigicam-0.3/gdigicam/gdigicam-util.h>
#include <glib.h>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusArgument>
#include <QtDBus/QDBusInterface>
#include <QProcess>
struct Property {
    QString name;
    bool added;
    bool removed;
};

Q_DECLARE_METATYPE(Property)
Q_DECLARE_METATYPE(QList<Property>)

QDBusArgument &operator<<(QDBusArgument &argument, const Property &arg2);
const QDBusArgument &operator>>(const QDBusArgument &argument, Property &arg2);

class StillCam : public QWidget
{
    Q_OBJECT

    QProcess *process;
    gchar *Path;
    Qt::GlobalColor pencolor;
private:
    void setFlashMode(GDigicamFlashmode mode);
    void setResolution(GDigicamResolution res, GDigicamAspectratio ratio);
    void setLock(GDigicamLock lock);
    void previewStatus(bool status);
    void setupCameraBin();
    //void drawFrame(Qt::GlobalColor color);

protected:
        void paintEvent(QPaintEvent *event);
        void closeEvent(QCloseEvent *event);

public:
    explicit StillCam(char *path,QWidget *parent = 0);
    ~StillCam();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    static void startCapture(GDigicamManager *manager, gpointer data);
    static void endCapture(GDigicamManager *manager, gpointer data);
    static void captureDone(GDigicamManager *manager, GString *fname, gpointer data);
    static void preview(GDigicamManager *manager, GdkPixbuf *pixbuf, gpointer data);

    GDigicamManager *manager;
    int colorkey;


private slots:
    void getPicture();

public slots:
    void shutter_released(int num_updates, QList<Property> updates);
    void focus_locked(int num_updates, QList<Property> updates);

};

#endif // STILLCAM_H
