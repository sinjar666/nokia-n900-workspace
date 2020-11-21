#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDate>
#include <QPushButton>
#include "indexitem.h"
#include "engine.h"

class Widget : public QWidget
{
    Q_OBJECT

    Engine *engine;
    QLabel *key_l,*loc_l,*date_l,*type_l;
    QLineEdit *key_e,*loc_e;
    QDateEdit *date_e;
    QComboBox *type_b;
    QGridLayout *layout;

public:
    Widget(QWidget *parent = 0);
    QDate getDate();
    QString getKey();
    QString getLoc();
    quint8 getType();
    ~Widget();

};

#endif // WIDGET_H
