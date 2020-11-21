#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include "engine.h"
#include "inpviewwidget.h"

class viewWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layout;
    InpViewWidget *w;
    QTextEdit *viewer;

    Engine *engine;
public:
    explicit viewWidget(QWidget *parent = 0);
    ~viewWidget();

signals:

public slots:
    void performSearch();

};

#endif // VIEWWIDGET_H
