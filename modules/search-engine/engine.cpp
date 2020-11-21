#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    index = new QMultiHash<QString,IndexItem>();
}

void Engine::loadIndex()    {
    file = new QFile("index");
    if(!file->open(QIODevice::ReadOnly))    {
        qDebug() << "loadIndex():: Index file not found.";
    }
    stream = new QDataStream(file);
    stream->readRawData((char *)index,file->size());
    file->close();
    delete(stream);
    delete(file);
}

void Engine::saveIndex()    {
    file = new QFile("index");
    if(!file->open(QIODevice::WriteOnly|QIODevice::Truncate))   {
        qDebug() << "saveIndex()::Unable to create file.";
    }
    stream = new QDataStream(file);
    stream->writeRawData((const char *)index,sizeof(index));
    file->close();
    delete(stream);
    delete(file);
}

void Engine::createEmptyIndex() {
    file = new QFile("index");
    if(!file->open(QIODevice::WriteOnly|QIODevice::Truncate))   {
        qDebug() << "saveIndex()::Unable to create file.";
    }
}

void Engine::addEntry(QString keyword, IndexItem item)  {
    index->insert(keyword,item);
}

QList<IndexItem> Engine::getEntry(QString keyword) {
    QList<IndexItem> vals;
    if(index->contains(keyword))
        vals = index->values(keyword);
    return vals;
}

QList<IndexItem> Engine::getSubstringMatch(QString keyword) {
    QList<IndexItem> *results;
    results = new QList<IndexItem>();
    QMultiHash<QString,IndexItem>::const_iterator i;
    for(i=index->constBegin();i!=index->constEnd();++i)   {
        QString text = i.key();
        if(text.contains(keyword,Qt::CaseInsensitive))  {
            results->append(i.value());
        }
    }
    delete(results);
}
