#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QWidget>
#include <QGroupBox>
#include "engine/indexitem.h"
#include "engine/engine.h"
#include "itembutton.h"

class ItemList : public QWidget
{
    Q_OBJECT
    QVBoxLayout *lay;
    QGroupBox *box;
    //ItemButton *temp;
public:
    explicit ItemList(QWidget *parent = 0);
    ItemList(QList<ItemButton *>l,QWidget *parent=0);
    void addButtons(QList<ItemButton *> l);
    //QSize sizeHint();

signals:

public slots:

};


#endif // ITEMLIST_H
