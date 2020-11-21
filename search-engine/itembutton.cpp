#include "itembutton.h"

ItemButton::ItemButton(ItemButton::ItemType type_a, QString descr_a,
                       InvestigationType subtype_a, QDate date_a, QString disease_a,
                       QWidget *parent)
    :QPushButton(parent)
{
    InvestigationTypeNames << "Angiography" <<
                                            "Biopsy" << "Blood Test" <<
                                            "Colonoscopy" <<
                                            "CT" <<
                                            "ECG" <<
                                            "Echo Cardiography" <<
                                            "Electro Encephalography (EEG)" <<
                                            "Endoscopy" <<
                                            "FNAC" <<
                                            "Funduscopy" <<
                                            "Holter Test" <<
                                            "MRI" <<
                                            "Sputum Test" <<
                                            "Stool Test" <<
                                            "Throat Swab" <<
                                            "Treadmill" <<
                                            "Urine Test" <<
                                            "Ultrasonography (USG)" <<
                                            "X-Ray" <<
                                            "Other";

    QImage temp;
    switch(type_a)  {
    case Symptom:
        temp = QImage(":/icons/symptom-icon.jpg");
        break;
    case Allergen:
        temp = QImage(":/icons/allergen-icon.jpg");
        break;
    case Drug:
        temp = QImage(":/icons/drug-icon.jpg");
        break;
    case Investigation:
        temp = QImage(":/icons/investigation-icon.jpg");
        break;
    case Surgery:
        temp = QImage(":/icons/surgery-icon.jpg");
        break;
    case FamilyHistory:
        temp = QImage(":/icons/familyHist-icon.jpg");
        break;
    case Misc:
        temp=QImage(":/icons/misc-icon.jpg");
        break;
    default:
        break;
    }
    type=type_a;
    descr= new QString(descr_a);
    date=new QDate(date_a);
    if(subtype_a == Other)  {
        subtype = new QString();
    }
    else  {
        subtype = new QString(InvestigationTypeNames.at((int)subtype_a));
    }
    //qDebug() << subtype;

    menu = new QMenu(this);
    menu->addAction(new QAction("Edit",this));
    menu->addAction(new QAction("Delete",this));
    w = new ItemWidget(QPixmap::fromImage(temp),*descr,*subtype,*date,disease_a,this);
    installEventFilter(this);
}

QSize ItemButton::sizeHint() const  {
    return(QSize(780,100));
}

bool ItemButton::eventFilter(QObject *obj, QEvent *event)   {
    if(event->type() == QEvent::ContextMenu)    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (event);

        menu->exec(mouseEvent->globalPos());

         return false;
    }
    else return QPushButton::eventFilter(obj,event);
}

/*void ItemButton::performAction(QAction *action) {

}*/
