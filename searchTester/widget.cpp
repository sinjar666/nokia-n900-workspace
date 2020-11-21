#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //engine = new Engine();
    key_l = new QLabel("Keyword");
    loc_l = new QLabel("Location");
    date_l = new QLabel("Date");
    type_l = new QLabel("Type");
    key_e = new QLineEdit();
    loc_e = new QLineEdit();
    date_e = new QDateEdit(QDate::currentDate());
    type_b = new QComboBox();
    type_b->addItem("Symptom");
    type_b->addItem("Allergen");
    type_b->addItem("Drug");
    type_b->addItem("Investigation");
    type_b->addItem("Surgery");
    type_b->addItem("Family History");
    type_b->addItem("Misc");
    layout = new QGridLayout(this);
    layout->addWidget(key_l,0,0);
    layout->addWidget(key_e,1,0);
    layout->addWidget(loc_l,0,1);
    layout->addWidget(loc_e,1,1);
    layout->addWidget(date_l,2,0);
    layout->addWidget(date_e,3,0);
    layout->addWidget(type_l,2,1);
    layout->addWidget(type_b,3,1);

}

QString Widget::getKey()    {
    return key_e->text();
}

QDate Widget::getDate()   {
    return date_e->date();
}

QString Widget::getLoc()    {
    return loc_e->text();
}

quint8 Widget::getType()    {
    return type_b->currentIndex()+1;
}

Widget::~Widget()
{
    delete(layout);
}
