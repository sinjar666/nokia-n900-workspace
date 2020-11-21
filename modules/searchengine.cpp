#include "searchengine.h"

SearchEngine::SearchEngine(QObject *parent) :
    QObject(parent)
{
    a=7,b=4,c=3,d=11;
    loadIndex();
}
void SearchEngine::loadIndex()  {
    file=new QFile("index.conf");
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))    {
        qDebug()<<"File not found.";
    }
    QTextStream strm(file);
    strm >> size >> n;
    file->close();
    delete(file);
    file = new QFile("index");
    if(!file->open(QIODevice::ReadOnly))    {
        qDebug << "Error in opening index file.";
    }
    index = new IndexItem[n][50];
    strm(file);
    strm >> index;
    if(sizeof(index) == 0)  {
        qDebug << "Error reading index.";
    }
    file->close();
    delete(file);

}

void SearchEngine::saveIndex()  {
    file=new QFile("index.conf");
    if(!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))   {
        qDebug() << "File creation error.";
    }
    QTextStream strm(file);
    strm << size << n;
    file->close();
    delete(file);
    file = new QFile("index");
    if(!file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "File creation error.";
    }
    strm(file);
    strm << index;
    file->close();
    delete(file);
    delete(index);
}

quint32 SearchEngine::h1(QString text)  {
    quint32 res=0;
    char ch;
    for(int m=0;m<text.size();m++)  {
        ch=text.at(m).toAscii();
        res=157*res+ch;
        res=(res+a)^(res<<b);
        res=(res^c)^(res>>d);
    }
    return res;
}

quint32 SearchEngine::h2(QString text)  {
    quint32 res=0;
    char ch;
    for(int m=0;m<text.size();m++)  {
        ch=text.at(m).toAscii();
        res=151*res+ch;
        res=(res+b)^(res<<c);
        res=(res^d)^(res>>a);
    }
    return res;
}

bool SearchEngine::insert(QString key,ItemContent content, quint32 loc1, quint32 loc2)  {
    if(index[loc1][0].keyword=="")  {
        index[loc1][0].keyword=key;
        index[loc1][0].items[0]=content;
        return 1;
    }
    else if(index[loc2][0].keyword=="") {
        index[loc2][0].keyword=key;
        index[loc2][0].items[0]=content;
        return 1;
    }
    else if()
}
