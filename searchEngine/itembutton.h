#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>
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

    ItemButton(ItemButton::ItemType type,QString descr,QString subtype,QDate date,QWidget *parent=0);
    //void paintEvent(QPaintEvent *e);
    QSize sizeHint() const;
private:
//    QPixmap img;
//    QString *descr,*type;
//    QDate *date;
    ItemWidget *w;

signals:

public slots:

};

#endif // ITEMBUTTON_H
