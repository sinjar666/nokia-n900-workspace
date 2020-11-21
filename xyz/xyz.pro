# Add more folders to ship with the application, here
folder_01.source = qml/xyz
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE67678FA

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
#CONFIG += mobility11
TEMPLATE=app
TARGET = xyz

maemo5  {
CONFIG += link_pkgconfig
PKGCONFIG += gtk+-2.0 \
            gstreamer-0.10 \
            gstreamer-plugins-bad-0.10 \
            gdigicam-0.3 \
            gdigicam-gst-camerabin-0.3
}
#QT_PLUGIN_PATH += /opt/qtm12/plugins
#MOBILITY += multimedia

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    ../../igalia/qtcamera/main.cpp \
    ../../igalia/qtcamera/camwindow.cpp
#TARGET = QmlCamera

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

HEADERS += \
    ../../igalia/qtcamera/camwindow.h
