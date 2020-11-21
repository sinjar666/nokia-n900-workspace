#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QMultiHash>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "indexitem.h"


class Engine : public QObject
{
    Q_OBJECT

    QMultiHash<QString,IndexItem> index;

    QFile *file;

public:
    explicit Engine(QObject *parent = 0);
    void loadIndex();
    void saveIndex();
    void createEmptyIndex();
    void addEntry(QString keyword,IndexItem item);
    QList<IndexItem> getEntry(QString keyword);
    QList<IndexItem> getSubstringMatch(QString keyword);
    bool remove(QString key,IndexItem val);
    bool remove(QString key);
signals:

public slots:

};

#endif // ENGINE_H
