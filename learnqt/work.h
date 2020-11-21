#ifndef WORK_H
#define WORK_H
#include <QtCore>
#include <QDeclarativeContext>
#include <QFile>

class Worker : public QObject   {
    Q_OBJECT
    QFile *file;
public:
    Q_INVOKABLE QString perform(QString fname);
    Q_INVOKABLE int performWrite(QString fname,QString content);
};

#endif // WORK_H
