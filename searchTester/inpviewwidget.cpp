#include "inpviewwidget.h"

InpViewWidget::InpViewWidget(QWidget *parent) :
    QWidget(parent)
{
    key_e = new QLineEdit();
    searchButton = new QPushButton("Search");
    layout = new QHBoxLayout(this);
    layout->addWidget(key_e);
    layout->addWidget(searchButton);
    connect(searchButton,SIGNAL(clicked()),this,SLOT(onSearchClicked()));
}

QString InpViewWidget::getKey()    {
    return key_e->text();
}

void InpViewWidget::onSearchClicked()   {
    emit clicked();
}
