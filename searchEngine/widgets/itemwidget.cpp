#include "itemwidget.h"

ItemWidget::ItemWidget(const QPixmap img, QString descr, QString type, QDate date, QWidget *parent) :
    QWidget(parent)
{
    icon = new QLabel();
    icon->setPixmap(img);
    w = new RWid(descr,type,date);
    layout = new QHBoxLayout(this);
    layout->addWidget(icon);
    layout->addWidget(w);
    //setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
}
QSize ItemWidget::sizeHint() const  {
    return(QSize(790,100));
}
