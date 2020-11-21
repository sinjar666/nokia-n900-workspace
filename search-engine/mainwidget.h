#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QDebug>
#include "searchwidget.h"
#include "itemlist.h"
#include "widgets/filterdialog.h"

class MainWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layout;
    QScrollArea *area;
    SearchWidget *w;
    ItemList *w2;
    QList<IndexItem> *results;
    Engine *engine;
    FilterDialog *dialog;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
private:

signals:

public slots:
    void performSearch();
    void displayFilterDialog();
};

#endif // MAINWIDGET_H
