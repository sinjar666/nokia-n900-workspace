#ifndef XDRUG_H
#define XDRUG_H

#include <QObject>

class XDrug : public QObject
{
    Q_OBJECT
    Drug *obj;
public:
    explicit XDrug(Drug *arg,QString path,QObject *parent = 0);
    void readData();
    void saveData();

signals:

public slots:

};

#endif // XDRUG_H
