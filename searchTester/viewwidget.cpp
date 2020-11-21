#include "viewwidget.h"

viewWidget::viewWidget(QWidget *parent) :
    QWidget(parent)
{
    w = new InpViewWidget();
    viewer = new QTextEdit();
    viewer->setReadOnly(true);
    layout = new QVBoxLayout(this);
    layout->addWidget(w);
    layout->addWidget(viewer);
    engine = new Engine();
    engine->loadIndex();
    connect(w,SIGNAL(clicked()),this,SLOT(performSearch()));
}

void viewWidget::performSearch()    {
    QList<IndexItem> res;
    IndexItem item;
    QString str;
    res=engine->getEntry(w->getKey());
    res.append(engine->getSubstringMatch(w->getKey()));
    foreach(item,res)   {
        viewer->append(item.getDate().toString() + item.getLocation() + QString::number(item.getType()));
    }

}

viewWidget::~viewWidget()   {
    delete(engine);
}
