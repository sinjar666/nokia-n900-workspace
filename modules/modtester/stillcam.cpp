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



#include "stillcam.h"

//DBUS PATHS
#define DBUS_SHUTTER_RELEASE "/org/freedesktop/Hal/devices/platform_cam_launch"
#define DBUS_FOCUS_LOCK "/org/freedesktop/Hal/devices/platform_cam_focus"
#define DBUS_CAM_SHUTTER "/org/freedesktop/Hal/devices/platform_cam_shutter"

QDBusArgument &operator<<(QDBusArgument &argument, const Property &arg2)    {
    argument.beginStructure();
    argument << arg2.name << arg2.added << arg2.removed;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Property &arg2)    {
    argument.beginStructure();
    argument >> arg2.name >> arg2.added >> arg2.removed;
    argument.endStructure();
    return argument;
}

QSize StillCam::minimumSizeHint() const
{
        return QSize(100, 100);
}

QSize StillCam::sizeHint() const
{
        return QSize(200, 200);
}

void StillCam::paintEvent(QPaintEvent *event)   {
    if(isShutterOpen()) {
        QPainter painter(this);
        //QBrush brush;
        QColor color((colorkey & 0x00ff0000) >> 16,
                 (colorkey & 0x0000ff00) >> 8,
                 colorkey & 0x000000ff);

        painter.save();
        painter.fillRect(0, 0, width(), height(), color);
        painter.setPen(pencolor);
        painter.drawRect(375,165,100,75);
        painter.restore ();
    }
}

void StillCam::closeEvent(QCloseEvent *event)
{
        g_digicam_manager_stop_bin(manager, NULL);
        process->execute("/usr/sbin/dsmetool -t /usr/bin/camera-ui");
        delete(process);
}

void StillCam::setFlashMode(GDigicamFlashmode mode)  {
    GDigicamCamerabinFlashModeHelper *helper=NULL;
    helper = g_slice_new(GDigicamCamerabinFlashModeHelper);
    helper->flash_mode=mode;
    if(!g_digicam_manager_set_flash_mode(manager,helper->flash_mode,NULL,helper))   {
        qDebug() << "Error:Unable to set flash mode";
    }
    g_slice_free(GDigicamCamerabinFlashModeHelper,helper);
}

void StillCam::setResolution(GDigicamResolution res, GDigicamAspectratio ratio) {
    GDigicamCamerabinAspectRatioResolutionHelper *helper = g_slice_new(GDigicamCamerabinAspectRatioResolutionHelper);

    helper->aspect_ratio=ratio;
    helper->resolution=res;
    if(!g_digicam_manager_set_aspect_ratio_resolution(manager,helper->aspect_ratio,helper->resolution,NULL,helper))  {
        qDebug() << "ERROR: Unable to set aspect ratio and resolution. ";
    }

    g_slice_free(GDigicamCamerabinAspectRatioResolutionHelper,helper);
}

void StillCam::setLock(GDigicamLock lock)   {
    qDebug() << "In set lock function.";
    GDigicamCamerabinLocksHelper *helper=g_slice_new(GDigicamCamerabinLocksHelper);


    helper->locks=lock;

    if(!g_digicam_manager_set_locks(manager,helper->locks,NULL,helper)) {
        qDebug() << "Error: unabble to set lock";

    }
    g_slice_free(GDigicamCamerabinLocksHelper,helper);
}

void StillCam::previewStatus(bool status)   {
    GDigicamCamerabinPreviewHelper *helper = g_slice_new(GDigicamCamerabinPreviewHelper);

    if(status)
        helper->mode=G_DIGICAM_PREVIEW_ON;
    else
        helper->mode=G_DIGICAM_PREVIEW_OFF;

    if(!g_digicam_manager_set_preview_mode(manager,helper->mode,NULL,helper))    {
        qDebug() << "Error: Unable to set preview mode";
    }

    g_slice_free(GDigicamCamerabinPreviewHelper,helper);
}

void StillCam::startCapture(GDigicamManager *manager, gpointer data)    {
    qDebug() << "Capture start signal received.";
}

void StillCam::endCapture(GDigicamManager *manager, gpointer data)  {
    qDebug() << "Capture end signal received";
}

void StillCam::captureDone(GDigicamManager *manager, GString *fname, gpointer data) {
    qDebug() << "Capture done signal received.";
}

void StillCam::preview(GDigicamManager *manager, GdkPixbuf *pixbuf, gpointer data)  {
    qDebug() << "Preview signal received";

    QLabel *label_=new QLabel();
    label_->setAttribute(Qt::WA_DeleteOnClose);
    label_->setWindowFlags(label_->windowFlags() | Qt::Window);

    QImage image(gdk_pixbuf_get_pixels(pixbuf),
                             gdk_pixbuf_get_width(pixbuf),
                             gdk_pixbuf_get_height(pixbuf),
                             gdk_pixbuf_get_rowstride(pixbuf),
                             QImage::Format_RGB888);
    QPixmap pixmap(QPixmap::fromImage(image));
    label_->setPixmap(pixmap);
    label_->show();
}

void StillCam::getPicture() {
    qDebug()<< "in get picture";
    GDigicamCamerabinPictureHelper *helper;

    helper = g_slice_new(GDigicamCamerabinPictureHelper);
    helper->file_path=g_strdup((const gchar *)Path);
    helper->metadata=NULL;
    if(!g_digicam_manager_capture_still_picture(manager,helper->file_path,NULL,helper))  {
        qDebug() << "Error: Unable to capture picture";
    }

    g_slice_free(GDigicamCamerabinPictureHelper,helper);
}

void StillCam::setupCameraBin() {
    GstElement *bin;
    GDigicamDescriptor *descriptor=NULL;
    manager = g_digicam_manager_new();
    colorkey=1;

    //standard gstreamer bin setup for nokia-n900

    bin = g_digicam_camerabin_element_new ("v4l2camsrc",
                                           "dspmp4venc",
                                           "hantromp4mux",
                                           "pulsesrc",
                                           "nokiaaacenc",
                                           "jpegenc",
                                           NULL,
                                           "xvimagesink",
                                           &colorkey);
    descriptor = g_digicam_camerabin_descriptor_new(bin);
    descriptor = g_digicam_camerabin_descriptor_new (bin);
    descriptor->max_zoom_macro_enabled = 6;
    descriptor->max_zoom_macro_disabled = 6;
    descriptor->max_digital_zoom = 6;
    descriptor->supported_modes = descriptor->supported_modes |
            G_DIGICAM_MODE_STILL | G_DIGICAM_MODE_VIDEO;
    descriptor->supported_iso_sensitivity_modes = descriptor->supported_iso_sensitivity_modes |
            G_DIGICAM_ISOSENSITIVITYMODE_MANUAL |
            G_DIGICAM_ISOSENSITIVITYMODE_AUTO;
    descriptor->supported_white_balance_modes = descriptor->supported_white_balance_modes |
            G_DIGICAM_WHITEBALANCEMODE_MANUAL       |
            G_DIGICAM_WHITEBALANCEMODE_AUTO         |
            G_DIGICAM_WHITEBALANCEMODE_SUNLIGHT     |
            G_DIGICAM_WHITEBALANCEMODE_CLOUDY       |
            G_DIGICAM_WHITEBALANCEMODE_SHADE        |
            G_DIGICAM_WHITEBALANCEMODE_TUNGSTEN     |
            G_DIGICAM_WHITEBALANCEMODE_FLUORESCENT  |
            G_DIGICAM_WHITEBALANCEMODE_INCANDESCENT |
            G_DIGICAM_WHITEBALANCEMODE_FLASH        |
            G_DIGICAM_WHITEBALANCEMODE_SUNSET;
    descriptor->supported_audio_states = descriptor->supported_audio_states |
            G_DIGICAM_AUDIO_RECORDON |
            G_DIGICAM_AUDIO_RECORDOFF;
    descriptor->supported_preview_modes = descriptor->supported_preview_modes |
            G_DIGICAM_PREVIEW_ON |
            G_DIGICAM_PREVIEW_OFF;
    descriptor->supported_features = descriptor->supported_features |
            G_DIGICAM_CAPABILITIES_VIEWFINDER  |
            G_DIGICAM_CAPABILITIES_RESOLUTION  |
            G_DIGICAM_CAPABILITIES_ASPECTRATIO  |
            G_DIGICAM_CAPABILITIES_MANUALFOCUS |
            G_DIGICAM_CAPABILITIES_AUTOFOCUS   |
            G_DIGICAM_CAPABILITIES_MACROFOCUS  |
            G_DIGICAM_CAPABILITIES_DIGITALZOOM |
            G_DIGICAM_CAPABILITIES_MANUALEXPOSURE |
            G_DIGICAM_CAPABILITIES_AUTOEXPOSURE |
            G_DIGICAM_CAPABILITIES_AUTOWHITEBALANCE |
            G_DIGICAM_CAPABILITIES_MANUALWHITEBALANCE |
            G_DIGICAM_CAPABILITIES_AUTOISOSENSITIVITY |
            G_DIGICAM_CAPABILITIES_MANUALISOSENSITIVITY|
            G_DIGICAM_CAPABILITIES_FLASH |
            G_DIGICAM_CAPABILITIES_AUDIO |
            G_DIGICAM_CAPABILITIES_PREVIEW;
    descriptor->supported_flash_modes = descriptor->supported_flash_modes |
            G_DIGICAM_FLASHMODE_OFF  |
            G_DIGICAM_FLASHMODE_ON   |
            G_DIGICAM_FLASHMODE_AUTO |
            G_DIGICAM_FLASHMODE_REDEYEREDUCTION |
            G_DIGICAM_FLASHMODE_REDEYEREDUCTIONAUTO |
            G_DIGICAM_FLASHMODE_FILLIN;
    descriptor->supported_resolutions = descriptor->supported_resolutions |
            G_DIGICAM_RESOLUTION_HIGH |
            G_DIGICAM_RESOLUTION_MEDIUM |
            G_DIGICAM_RESOLUTION_LOW;
    descriptor->supported_aspect_ratios = descriptor->supported_aspect_ratios |
            G_DIGICAM_ASPECTRATIO_4X3 |
            G_DIGICAM_ASPECTRATIO_16X9;



    if(!g_digicam_manager_set_gstreamer_bin(manager,bin,descriptor,NULL))
        qDebug() << "Fatal Error: unable to set gstreamer bin";
    g_signal_connect(manager,"pict-done",(GCallback)captureDone,NULL);
    g_signal_connect(manager,"capture-start",(GCallback)startCapture,NULL);
    g_signal_connect(manager,"capture-end",(GCallback)endCapture,NULL);
    g_signal_connect(manager,"image-preview",(GCallback)preview,this);

    GDigicamCamerabinModeHelper *m_helper = g_slice_new(GDigicamCamerabinModeHelper);
    m_helper->mode=G_DIGICAM_MODE_STILL;
    if(!g_digicam_manager_set_mode(manager,m_helper->mode,NULL,m_helper))
        qDebug() << "Error: unable to set to still mode.";
    g_slice_free(GDigicamCamerabinModeHelper,m_helper);

    setFlashMode(G_DIGICAM_FLASHMODE_OFF);
    //to scan a paper placed close we should not use flash otherwise glare occurs
    //hence flash is set off

    setResolution(G_DIGICAM_RESOLUTION_HIGH,G_DIGICAM_ASPECTRATIO_4X3);

    //Set the exposure to automatically adjust depending on external lighting conditions
    GDigicamCamerabinExposureModeHelper *e_helper=g_slice_new(GDigicamCamerabinExposureModeHelper);
    e_helper->exposure_mode=G_DIGICAM_EXPOSUREMODE_AUTO;
    if(!g_digicam_manager_set_exposure_mode(manager,e_helper->exposure_mode,NULL,NULL,e_helper))
        qDebug() << "Error:unable to set exposure mode";
    g_slice_free(GDigicamCamerabinExposureModeHelper,e_helper);


    //Set autofocus to on and set macro focus mode enabled
    GDigicamCamerabinFocusModeHelper *f_helper=g_slice_new(GDigicamCamerabinFocusModeHelper);
    f_helper->focus_mode=G_DIGICAM_FOCUSMODE_CENTROID;
    f_helper->macro_enabled=true;
    if(!g_digicam_manager_set_focus_mode(manager,f_helper->focus_mode,f_helper->macro_enabled,NULL,f_helper))
        qDebug() << "Unable to set autofocus";
    g_slice_free(GDigicamCamerabinFocusModeHelper,f_helper);

    previewStatus(true);


}


void StillCam::shutter_released(int num_updates, QList<Property> updates)   {
    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_SHUTTER_RELEASE,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
    bool pressed=propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
    if(pressed) {
        getPicture();
    }
}

void StillCam::focus_locked(int num_updates, QList<Property> updates)   {
    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_FOCUS_LOCK,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
    bool pressed = propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
    if(pressed) {
        pencolor=Qt::green;
        repaint();
        setLock(G_DIGICAM_LOCK_AUTOFOCUS);
    }
    else    {
        pencolor=Qt::white;
        repaint();
        setLock(G_DIGICAM_LOCK_AUTOFOCUS_NONE);
    }

}

void StillCam::cam_shutter(int num_updates, QList<Property> updates)    {
    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_CAM_SHUTTER,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
    bool closed=propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
    if(!closed)  {
        qDebug() << "Ready to play bin.";
        message->hide();
        delete(message);
        g_digicam_manager_play_bin(manager,winId(),NULL);
    }
    else    {
        qDebug() << "Ready to stop bin";
        g_digicam_manager_stop_bin(manager,NULL);
        close();
    }
}

StillCam::StillCam(char *path, QWidget *parent) :
    QWidget(parent)
{
    process=new QProcess();
    process->execute("/usr/sbin/dsmetool -k /usr/bin/camera-ui");
    qDBusRegisterMetaType<Property>();
    qDBusRegisterMetaType< QList<Property> >();

    Path=path;
    pencolor=Qt::white;

    //Connecting slots for camera button to dbus signals
    QDBusConnection::systemBus().connect(QString(),DBUS_SHUTTER_RELEASE,"org.freedesktop.Hal.Device","PropertyModified",this,
                                         SLOT(shutter_released(int,QList<Property>)));

    QDBusConnection::systemBus().connect(QString(),DBUS_FOCUS_LOCK,"org.freedesktop.Hal.Device","PropertyModified",
                                         this,SLOT(focus_locked(int,QList<Property>)));

    QDBusConnection::systemBus().connect(QString(),DBUS_CAM_SHUTTER,"org.freedesktop.Hal.Device","PropertyModified",
                                         this,SLOT(cam_shutter(int,QList<Property>)));
    setupCameraBin();
    if(isShutterOpen())
        g_digicam_manager_play_bin(manager, winId(), NULL);
    else    {
        lay = new QVBoxLayout(this);
        message = new QLabel();
        message->setTextFormat(Qt::RichText);
        message->setAlignment(Qt::AlignCenter);
        message->setText("<font size=10><b> <p align='center'> Please open the shutter </p> </b></font>");
        lay->addWidget(message);
       // message->show();
    }

}

bool StillCam::isShutterOpen()    {
    QFile *temp = new QFile("/sys/devices/platform/gpio-switch/cam_shutter/state");
    if(!temp->open(QIODevice::ReadOnly)) {
        qDebug() << "Thats strange.";
    }
    QTextStream stream(temp);
    QString state;
    stream >> state;
    temp->close();
    delete(temp);
    if(state=="open")
        return true;
    else return false;
}

StillCam::~StillCam()   {
    g_digicam_manager_stop_bin(manager,NULL);
    process->execute("/usr/sbin/dsmetool -t /usr/bin/camera-ui");
    //deleteLater(process);
}
