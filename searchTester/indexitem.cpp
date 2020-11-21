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

QDataStream & operator<<(QDataStream & stream,const IndexItem & item)    {
    stream << item.getDate().toJulianDay() << item.getLocation() << item.getType();
    return stream;
}

QDataStream & operator>>(QDataStream & in,IndexItem & item) {
    quint32 jdate;
    QString loc_a;
    quint8 type_a;
    in >> jdate >> loc_a >> type_a;
    item = IndexItem(QDate::fromJulianDay((int)jdate),loc_a,type_a);
    return in;
}
