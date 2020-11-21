#include "indexitem.h"

IndexItem::IndexItem(const IndexItem &other)    {
    *this=other;
}

IndexItem::IndexItem(QDate date_arg, QString loc_arg, quint8 type_arg)  {
    date=date_arg;
    location=loc_arg;
    type=type_arg;
}

IndexItem & IndexItem::operator=(const IndexItem &o)   {
    date=o.getDate();
    location=o.getLocation();
    type=o.getType();
    return *this;
}

QDate IndexItem::getDate() const  {
    return date;
}
QString IndexItem::getLocation() const    {
    return location;
}
quint8 IndexItem::getType() const {
    return type;
}
