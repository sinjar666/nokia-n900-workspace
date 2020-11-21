#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QMultiHash>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "../modules/search-engine/indexitem.h"


class Engine : public QObject
{
    Q_OBJECT

    QMultiHash<QString,IndexItem> *index;

    QFile *file;
    QDataStream *stream;

public:
    explicit Engine(QObject *parent = 0);
    void loadIndex();
    void saveIndex();
    void createEmptyIndex();
    void addEntry(QString keyword,IndexItem item);
    QList<IndexItem> getEntry(QString keyword);
    QList<IndexItem> getSubstringMatch(QString keyword);
signals:

public slots:

};

#endif // ENGINE_H
