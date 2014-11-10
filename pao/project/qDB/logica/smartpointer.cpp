#include "smartpointer.h"

SmartPointer::SmartPointer(StoreItem* s): ptr(s) {}

SmartPointer::SmartPointer(const SmartPointer& smartp): ptr(smartp->clone()) {}

SmartPointer::~SmartPointer()
{
    delete ptr;
}

SmartPointer& SmartPointer::operator =(const SmartPointer& smartp)
{
    if (this != &smartp)
    {
        delete ptr;
        ptr = smartp->clone();
    }
    return *this;
}

const StoreItem& SmartPointer::operator *() const
{
    return *ptr;
}
StoreItem& SmartPointer::operator *()
{
    return *ptr;
}
const StoreItem* SmartPointer::operator ->() const
{
    return ptr;
}
StoreItem* SmartPointer::operator ->()
{
    return ptr;
}

bool SmartPointer::operator ==(const SmartPointer& p) const
{
    return ptr->getTitle() == p.ptr->getTitle();
}
