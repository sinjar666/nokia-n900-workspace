#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "indexitem.h"
#include "engine.h"
#include "widget.h"
class MainWidget : public QWidget
{
    Q_OBJECT
    QPushButton *addButton;
    QPushButton *createButton;
    QVBoxLayout *m_layout;
    Widget *w;
    Engine *engine;

public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    void performAdd();
    void performCreateNew();

};

#endif // MAINWIDGET_H
