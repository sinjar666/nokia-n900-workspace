#ifndef KEYGEN_H
#define KEYGEN_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class KeyGen : public QObject
{
    Q_OBJECT
    QString *text;
    QStringList keywords;
public:
    explicit KeyGen(QString *arg,QObject *parent = 0);
    QStringList generate();

signals:

public slots:

};

#endif // KEYGEN_H
