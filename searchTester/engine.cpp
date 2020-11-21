#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
}

void Engine::loadIndex()    {
    file = new QFile("index");
    if(!file->open(QIODevice::ReadOnly))    {
        qDebug() << "loadIndex():: Index file not found.";
    }
    QDataStream stream(file);
    stream >> index;
    file->close();
    delete(file);
}

void Engine::saveIndex()    {
    file = new QFile("index");
    if(!file->open(QIODevice::WriteOnly|QIODevice::Truncate))   {
        qDebug() << "saveIndex()::Unable to create file.";
    }
    QDataStream stream(file);
    stream << index;
    file->close();
    delete(file);
}

void Engine::createEmptyIndex() {
    file = new QFile("index");
    if(!file->open(QIODevice::WriteOnly|QIODevice::Truncate))   {
        qDebug() << "saveIndex()::Unable to create file.";
    }
}

void Engine::addEntry(QString keyword, IndexItem item)  {
    index.insert(keyword,item);
}

QList<IndexItem> Engine::getEntry(QString keyword) {
    QList<IndexItem> vals;
    if(index.contains(keyword))
        vals = index.values(keyword);
    return vals;
}

bool Engine::remove(QString key)    {
    if(index.remove(key)>0) {
        return true;
    }
    else return false;
}

bool Engine::remove(QString key, IndexItem val) {
    if(index.remove(key,val)>0) {
        return true;
    }
    else return false;
}

QList<IndexItem> Engine::getSubstringMatch(QString keyword) {
    QList<IndexItem> *results;
    results = new QList<IndexItem>();
    QMultiHash<QString,IndexItem>::const_iterator i;
    for(i=index.constBegin();i!=index.constEnd();++i)   {
        QString text = i.key();
        if(text.contains(keyword,Qt::CaseInsensitive))  {
            results->append(i.value());
        }
    }
    return *results;
    delete(results);
}
