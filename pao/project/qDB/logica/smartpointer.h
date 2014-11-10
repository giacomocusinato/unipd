#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "storeitem.h"

class SmartPointer
{
private:
    StoreItem* ptr;
public:
    SmartPointer(StoreItem *);
    SmartPointer(const SmartPointer&);
    ~SmartPointer();

    // Operators overloading
    SmartPointer& operator =(const SmartPointer&);
    const StoreItem& operator *() const;
    StoreItem& operator *();
    const StoreItem* operator ->() const;
    StoreItem* operator ->();
    bool operator ==(const SmartPointer&) const;
};

#endif // SMARTPOINTER_H
