#ifndef INVESTIGATION_H
#define INVESTIGATION_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>

#define ID_TYPE QString
class Investigation : public QObject
{
    Q_OBJECT
    ID_TYPE *id;
    QDate *date;
    QTime *time;

    QString *details;
    QList<ID_TYPE> *linkedTo;
    QString *report;
public:
    typedef enum    {
        BLOODTEST_T,URINETEST_T,MRI_T,CT_T,XRAY_T,USG_T,THROATSWAB_T,
        ECG_T,ECHO_T,ANGIOGRAPHY_T,TREADMILL_T,EEG_T,FUNDUSCOPY_T,
        ENDOSCOPY_T,COLONOSCOPY_T,STOOLTEST_T,SPUTUM_T,FNAC_T,BIOPSY_T
    } Type;
    explicit Investigation(QObject *parent = 0);
    ~Investigation();

    void setDate(QDate arg);
    void setDate(int day, int month, int year);
    QDate getDate();

    void setTime(QTime arg);
    void setTime(int hour,int min);
    QTime getTime();

    void setType(Type arg);
    Type getType();

    void setDetails(QString arg);
    QString getDetails();

    void setReport(QString arg);
    QString getReport();

    QList<ID_TYPE> getLinkedTo();
    bool addLink(ID_TYPE arg);
    bool removeLink(ID_TYPE arg);

private:
     Type type;
signals:

public slots:

};

#endif // INVESTIGATION_H
