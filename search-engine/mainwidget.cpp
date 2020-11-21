#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    engine = new Engine(QString("/home/user/MyDocs/"));
    engine->loadIndex();
    results = new QList<IndexItem>();
    w= new SearchWidget();
    w2 = new ItemList();
    area=new QScrollArea();
    area->setWidget(w2);
    layout = new QVBoxLayout(this);
    layout->addWidget(w);
    layout->addWidget(area);
    connect(w,SIGNAL(searchPressed()),this,SLOT(performSearch()));
    connect(w,SIGNAL(filter()),this,SLOT(displayFilterDialog()));
}
MainWidget::~MainWidget()   {
    engine->saveIndex();
    delete(engine);
    delete(results);
}


void MainWidget::performSearch()    {
    QList<ItemButton *> l;
    IndexItem item;
    results->clear();
    results->append(engine->getEntry(w->getKey()));
    results->append(engine->getSubstringMatch(w->getKey()));
    foreach(item,*results)  {
        ItemButton::ItemType t;
        switch((int)item.getType()) {
        case 0:
            t=ItemButton::None;
            break;
        case 1:
            t=ItemButton::Symptom;
            break;
        case 2:
            t=ItemButton::Allergen;
            break;
        case 3:
            t=ItemButton::Drug;
            break;
        case 4:
            t=ItemButton::Investigation;
            break;
        case 5:
            t=ItemButton::Surgery;
            break;
        case 6:
            t=ItemButton::FamilyHistory;
            break;
        default:
            t=ItemButton::Misc;
            break;
        }
        qDebug() << item.getDisease();
        l.append(new ItemButton(t,"Some Sample Description",ItemButton::Other,item.getDate(),item.getDisease()));
        //change above while making final
        //ie use item.getLocation() and open file in xml module then get descriptions...
    }
    delete(area->takeWidget());
    w2 = new ItemList(l);
    area->setWidget(w2);
}

void MainWidget::displayFilterDialog()  {
    dialog = new FilterDialog(engine,engine->getFilters(),this);
    dialog->exec();
    delete(dialog);
    performSearch();
}
