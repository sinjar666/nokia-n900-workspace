#include "keygen.h"

KeyGen::KeyGen(QString *arg,QObject *parent) :
    QObject(parent)
{
    text = arg;
}

QStringList KeyGen::generate()
{
    QFile *fil = new QFile("words.txt");
    if(!fil->open(QIODevice::ReadOnly))
        qDebug()<< "file not found.";

    QStringList total;
    QStringList bad;
    QString *content = new QString();
    QTextStream stream(fil);
    stream >> *content;
    qDebug()<<*content;
    bad = content->split(";",QString::SkipEmptyParts);
    total = text->split(" ",QString::SkipEmptyParts);
    QStringList::iterator i;
    for(i=total.begin();i!=total.end();++i) {
        (*i)=(*i).toLower();
    }
    for(i=bad.begin();i!=bad.end();++i)  {
        qDebug()<<*i;
        total.removeAll((*i));
    }
    delete content;
    return total;
}

