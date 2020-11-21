#include "itembutton.h"

ItemButton::ItemButton(ItemButton::ItemType type, QString descr, QString subtype, QDate date, QWidget *parent)
    :QPushButton(parent)
{
    //setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    QImage temp("searchEngine.png");
    w = new ItemWidget(QPixmap::fromImage(temp),descr,subtype,date,this);
}

QSize ItemButton::sizeHint() const  {
    return(QSize(790,100));
}

//void ItemButton::paintEvent(QPaintEvent *e) {

//}
