#include "allergen.h"

Allergen::Allergen(QObject *parent) :
    QObject(parent)
{
    name=new QString();
    date=new QDate();
    drug_id = NULL;
}

Allergen::~Allergen()   {
    delete(name);
    delete(date);
    delete(drug_id);
}

void Allergen::setName(QString arg) {
    *name=arg;
}
QString Allergen::getName()   {
    return *name;
}

void Allergen::setDate(int day, int month, int year)    {
    date->setDate(year,month,day);
}
void Allergen::setDate(QDate arg)   {
    *date=arg;
}
QDate Allergen::getDate()   {
    return *date;
}

void Allergen::setType(A_type arg)  {
    type=arg;
    if(type==drug_t)
        drug_id = new ID_TYPE();

}
Allergen::A_type Allergen::getType()  {
    return type;
}


void Allergen::setDrug(ID_TYPE arg) {
    if(type==drug_t)    {
        *drug_id = arg;
    }
}

ID_TYPE Allergen::getDrug() {
    if(type==drug_t)
        return *drug_id;
    else
        return "n/a";
}
