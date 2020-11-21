#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QDate>
#include <QFile>
#include <QTextStream>

class SearchEngine : public QObject
{
    Q_OBJECT

    typedef struct  {
        QDate date;
        QString location;
        quint8 type;
    } ItemContent;
    /*-----type spec-----------------
            ---0x00 = <none>
            ---0x01 = symptom
            ---0x02 = allergen
            ---0x03 = drug
            ---0x04 = investigation
            ---0x05 = surgery
            ---0x06 = family history
            ---0x07 = misc------------------*/

    typedef struct  {
        QString keyword;
        ItemContent items[100];
    } IndexItem;

    int a,b,c,d,n,size;
    //size-->size of the index
    //n --> no. of items in the index
    IndexItem **index;
    QFile *file;

    quint32 golden[] = {53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613};
    //For these sizes bucket size is optimal

    quint32 h1(QString text);
    quint32 h2(QString text);

    bool insert(QString key,ItemContent content,quint32 loc1,quint32 loc2);
    //Use this function to add a new keyword that does not exist in the index
    //Not to be used to add more Content to an existing item in the index

    void loadIndex(); //First thing to be done
    void saveIndex(); //Last thing to be done
    void rehash();
    /*We shall dynamically increase size of index when it is more than 75 % full.*/


public:
    explicit SearchEngine(QObject *parent = 0);
    void addItem(QString Keyword,QDate Date,QString Location,quint8 Type);
    QString searchExact(QString Keyword);



signals:

public slots:

};

#endif // SEARCHENGINE_H
