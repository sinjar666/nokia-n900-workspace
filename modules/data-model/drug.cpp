#include "drug.h"

Drug::Drug(QObject *parent) :
    QObject(parent)
{
    id = new ID_TYPE();
    date = new QDate();
    name = new QString();
}

Drug::~Drug()   {
    delete(id);
    delete(name);
    delete(date);
}

void Drug::setDate(int day, int month, int year) {
    date->setDate(year,month,day);
}

void Drug::setDate(QDate arg)    {
    *date=arg;
}

QDate Drug::getDate()    {
    return *date;
}

void Drug::setName(QString arg) {
    *name=arg;
}

QString Drug::getName() {
    return *name;
}

void Drug::setDuration(quint16 arg) {
    duration=arg;
}
quint16 Drug::getDuration() {
    return duration;
}
