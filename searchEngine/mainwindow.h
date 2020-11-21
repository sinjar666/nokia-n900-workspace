#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QGroupBox>
#include <QScrollArea>
#include "itembutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private:
    ItemButton *button,*b2,*b3,*b4,*b5,*b6;
    QScrollArea *area;
    QGroupBox *group;
    QVBoxLayout *lay;

};

#endif // MAINWINDOW_H
