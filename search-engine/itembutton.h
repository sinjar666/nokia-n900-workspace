#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>
#include <QMenu>
#include "widgets/itemwidget.h"

class ItemButton : public QPushButton
{
    Q_OBJECT
public:
    enum ItemType   {
        None=0,
        Symptom=1,
        Allergen=2,
        Drug=3,
        Investigation=4,
        Surgery=5,
        FamilyHistory=6,
        Misc=7
    };

    enum InvestigationType  {
        Angiography=0,
        Biopsy=1,
        BloodTest=2,
        Colonoscopy=3,
        CT=4,
        ECG=5,
        Echo=6,
        EEG=7,
        Endoscopy=8,
        FNAC=9,
        Funduscopy=10,
        HalterTest=11,
        MRI=12,
        Sputum=13,
        StoolTest=14,
        ThroatSwab=15,
        Treadmill=16,
        UrineTest=17,
        USG=18,
        Xray=19,
        Other=20
    };


    ItemButton(ItemButton::ItemType type_a,
               QString descr_a,InvestigationType subtype_a,
               QDate date_a,QString disease_a,QWidget *parent=0);
    QSize sizeHint() const;
private:
    QStringList InvestigationTypeNames;
    ItemType type;
    QString *descr;
    QString *subtype;
    QDate *date;
    ItemWidget *w;
    QMenu *menu;
    bool eventFilter(QObject *, QEvent *);

signals:

public slots:
   // void performAction(QAction *action);

};

#endif // ITEMBUTTON_H
