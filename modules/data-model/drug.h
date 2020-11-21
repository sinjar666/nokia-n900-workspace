#ifndef DRUG_H
#define DRUG_H

#include <QObject>
#include <QString>
#include <QDate>

#define ID_TYPE QString
class Drug : public QObject
{
    Q_OBJECT

    ID_TYPE *id;
    QString *name;
    QDate *date;
    quint16 duration;
public:
    explicit Drug(QObject *parent = 0);
    explicit ~Drug();

    void setName(QString arg);
    QString getName();
    void setDate(QDate arg);
    void setDate(int day, int month, int year);
    QDate getDate();
    void setDuration(quint16 arg);
    quint16 getDuration();

signals:

public slots:

};

#endif // DRUG_H
