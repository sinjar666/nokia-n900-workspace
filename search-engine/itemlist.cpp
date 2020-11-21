#include "itemlist.h"

ItemList::ItemList(QWidget *parent) :
    QWidget(parent)
{

    lay = new QVBoxLayout(this);

    //performSearch(QString());
}
ItemList::ItemList(QList<ItemButton *> l, QWidget *parent):
    QWidget(parent)
{
    lay=new QVBoxLayout(this);
    addButtons(l);
}


void ItemList::addButtons(QList<ItemButton *> l)    {
    ItemButton *i;
    foreach(i,l)    {
        lay->addWidget(i);
    }
}



