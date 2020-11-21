#ifndef INDEXITEM_H
#define INDEXITEM_H

#include <QString>
#include <QDate>

class IndexItem
{
    QDate date;
    QString location;
    quint8 type;
    /*-----type spec-----------------
            ---0x00 = <none>
            ---0x01 = symptom
            ---0x02 = allergen
            ---0x03 = drug
            ---0x04 = investigation
            ---0x05 = surgery
            ---0x06 = family history
            ---0x07 = misc------------------*/

public:
    IndexItem()    {}
    IndexItem(const IndexItem &other);
    IndexItem(QDate date_arg,QString loc_arg,quint8 type_arg);

    IndexItem &operator=(const IndexItem &o);

    QDate getDate() const;
    QString getLocation() const;
    quint8 getType() const;
};

#endif // INDEXITEM_H
