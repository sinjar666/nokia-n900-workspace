#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    w = new Widget();
    addButton = new QPushButton("Add");
    m_layout = new QVBoxLayout(this);
    createButton = new QPushButton("Create New");
    m_layout->addWidget(w);
    m_layout->addWidget(addButton);
    m_layout->addWidget(createButton);
    engine = new Engine();
    connect(addButton,SIGNAL(clicked()),this,SLOT(performAdd()));
    connect(createButton,SIGNAL(clicked()),this,SLOT(performCreateNew()));
}

void MainWidget::performAdd()   {
    IndexItem *item;
    item = new IndexItem(w->getDate(),w->getLoc(),w->getType());

    engine->loadIndex();
    engine->addEntry(w->getKey(),*item);
    engine->saveIndex();
    delete(item);
}

void MainWidget::performCreateNew() {
    engine->createEmptyIndex();
}
