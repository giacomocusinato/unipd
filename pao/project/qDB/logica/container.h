#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
using std::ostream;
using std::endl;

template <typename T> class container;
template <typename T> ostream& operator <<(ostream& os, const container<T>&);

template <typename T>
class container
{
    template <typename V>
    friend ostream& operator<< (ostream& os, const container<V>&);
    friend class iterator;
    friend class const_iterator;
public:
    container();

    class iterator
    {
        friend class container<T>;
    public:
        T& operator *() const;
        T* operator ->() const;
        bool operator ==(iterator) const;
        bool operator !=(iterator) const;
        iterator& operator ++();
        iterator operator++(int);
    private:
        typename container<T>::smartp _itPointer;
    };

    class const_iterator
    {
        friend class container<T>;
    public:
        const T& operator *() const;
        const T* operator ->() const;
        bool operator ==(const_iterator) const;
        bool operator !=(const_iterator) const;
        const_iterator& operator ++();
        const_iterator operator++(int);
    private:
        typename container<T>::smartp _itPointer;
    };


    bool empty() const;
    int size() const;
    void insert(const T&, int);
    void push_front(const T&);
    void push_back(const T&);
    void remove(const T&);
    bool contains(const T&) const;
    container<T>::iterator begin() const;
    container<T>::iterator end() const;
    container<T>::const_iterator const_begin() const;
    container<T>::const_iterator const_end() const;

    T operator [](const int) const;

private:
    class item;

    class smartp
    {
    public:
        smartp(item* p=0);
        smartp(const container<T>::smartp&);
        ~smartp();
        item* _pointer;

        smartp& operator=(const smartp&);
        item& operator *() const;
        item* operator ->() const;
        bool operator ==(const smartp&) const;
        bool operator !=(const smartp&) const;
    };

    class item
    {
    public:
        item();
        item(const T&, const smartp&);
        T _info;
        smartp _next;
        int _counting_reference;
    };

    // Campi dati di Container
    smartp _first;
    int _size;
};


// DEFINIZIONI DI Container

template <typename T>
container<T>::container(): _size(0) {}

template <typename T>
bool container<T>::empty() const
{
    return this->_size == 0;
}

template <typename T>
int container<T>::size() const
{
    return this->_size;
}

template <typename T>
void container<T>::push_front(const T& cont_item)
{
    this->_first = new container<T>::item(cont_item, this->_first);
    this->_size++;
}

template <typename T>
void container<T>::push_back(const T& cont_item)
{
    if (_first == 0)
    {
        _first = new container<T>::item(cont_item, 0);
        this->_size++;
        return;
    }

    smartp p = this->_first, prev, copy;
    this->_first = 0;

    while (p!=0)
    {
        copy = new container<T>::item(p->_info, p->_next);
        if (prev == 0)
            this->_first = copy;
        else
            prev->_next = copy;

        p = p->_next;
        prev = copy;
    }
    copy->_next = new container<T>::item(cont_item, 0);
    this->_size++;
}

template <typename T>
void container<T>::insert(const T& contItem, int index)
{
    if (index < 0)
        return;

    if (index == 0)
    {
        this->push_front (contItem);
        return;
    }
    // i > 0

    smartp copy, aux = this->_first, prev;

    for (int i=0; i != index; i++)
    {
        copy = new container<T>::item(aux->_info, aux->_next);
        if (i == 0)
            this->_first = copy;
        else
            prev->_next = copy;

        if (i != index - 1)
            aux = aux->_next;
        prev = copy;
    }

    copy->_next = new container<T>::item(contItem, aux->_next);
    this->_size++;
}

template <typename T>
void container<T>::remove(const T& cont_item)
{
    smartp p = this->_first, prev, copy;
    smartp original = this->_first;
    this->_first = 0;

    while (p!=0 && !(p->_info == cont_item))
    {
        copy = new container<T>::item(p->_info, p->_next);
        if (prev == 0)
            this->_first = copy;
        else
            prev->_next = copy;
        prev = copy;
        p = p->_next;
    }

    if (p == 0)
        this->_first = original;
    else if (prev == 0)
    {
        this->_first = p->_next;
        this->_size--;
    }
    else
    {
        prev->_next = p->_next;
        this->_size--;
    }
}

template <typename T>
bool container<T>::contains(const T& value) const
{
    container<T>::const_iterator it = this->const_begin();
    for (; it != this->const_end(); ++it)
    {
        if (*it == value)
            return true;
    }
    return false;
}

template <typename T>
ostream& operator <<(ostream& os, const container<T>& cont)
{
    if (cont.empty())
        os << "THE CONTAINER IS EMPTY";
    else
    {
        os << "ITEMS IN CONTAINER" << endl;
        typename container<T>::smartp outp = cont._first;
        int i = 1;
        while (outp != 0)
        {
            os << i << ". " << outp->_info << endl;
            outp = outp->_next;
            i++;
        }
    }
    return os;
}

template <typename T>
T container<T>::operator [](const int index) const
{
    int i=0;
    container<T>::const_iterator it = this->const_begin();
    for (; it != this->const_end(); ++it)
    {
        if (i == index)
            return *it;
        i++;
    }
}

template <typename T>
class container<T>::iterator container<T>::begin() const
{
    container<T>::iterator aux;
    aux._itPointer = _first;
    return aux;
}

template <typename T>
class container<T>::iterator container<T>::end() const
{
    container<T>::iterator aux;
    aux._itPointer = 0;
    return aux;
}

template <typename T>
class container<T>::const_iterator container<T>::const_begin() const
{
    container<T>::const_iterator aux;
    aux._itPointer = _first;
    return aux;
}

template <typename T>
class container<T>::const_iterator container<T>::const_end() const
{
    container<T>::const_iterator aux;
    aux._itPointer = 0;
    return aux;
}



// DEFINIZIONI DI item

template <class T>
container<T>::item::item(): _counting_reference(0) {}

template <class T>
container<T>::item::item(const T& info, const container<T>::smartp& next): _info(info), _next(next), _counting_reference(0) {}



// DEFINIZIONI DI smartp

template <class T>
container<T>::smartp::smartp(container::item* p): _pointer(p)
{
    if(_pointer)
        _pointer->_counting_reference++;
}

template <class T>
container<T>::smartp::smartp(const container<T>::smartp& p): _pointer(p._pointer)
{
    if (this->_pointer != 0)
        this->_pointer->_counting_reference++;
}

template <class T>
container<T>::smartp::~smartp()
{
    if (_pointer)
    {
        _pointer->_counting_reference--;
        if (_pointer->_counting_reference == 0)
            delete _pointer; // Ricorsiva
    }
}

template <class T>
class container<T>::smartp& container<T>::smartp::operator =(const smartp& p)
{
    if (this != &p)
    {
        item* temp = this->_pointer;
        this->_pointer = p._pointer;
        if (this->_pointer)
            this->_pointer->_counting_reference++;
        if (temp)
        {
            temp->_counting_reference--;
            if (temp->_counting_reference == 0)
                delete temp;
        }
    }

    return *this;
}

template <class T>
class container<T>::item& container<T>::smartp::operator *() const
{
    return this->*_pointer;
}

template <class T>
class container<T>::item* container<T>::smartp::operator ->() const
{
    return this->_pointer;
}

template <class T>
bool container<T>::smartp::operator ==(const smartp& p) const
{
    return this->_pointer == p._pointer;
}

template <class T>
bool container<T>::smartp::operator !=(const smartp& p) const
{
    return this->_pointer != p._pointer;
}


// DEFINIZIONI di iterator

template <typename T>
T& container<T>::iterator::operator *() const
{
    return _itPointer._pointer->_info;
}

template <typename T>
T* container<T>::iterator::operator ->() const
{
    return & _itPointer._pointer->_info;
}

template <typename T>
bool container<T>::iterator::operator ==(iterator i) const
{
    return _itPointer == i._itPointer;
}

template <typename T>
bool container<T>::iterator::operator !=(iterator i) const
{
    return _itPointer != i._itPointer;
}

template <typename T>
typename container<T>::iterator& container<T>::iterator::operator ++()
{
    if (this->_itPointer != 0)
        _itPointer = _itPointer->_next;
    return *this;
}

template <typename T>
typename container<T>::iterator container<T>::iterator::operator ++(int)
{
    iterator aux = *this;
    if (this->_itPointer != 0)
        _itPointer = _itPointer->_next;
    return aux;
}


// DEFINIZIONI di const_iterator

template <typename T>
const T& container<T>::const_iterator::operator *() const
{
    return _itPointer._pointer->_info;
}

template <typename T>
const T* container<T>::const_iterator::operator ->() const
{
    return & _itPointer._pointer->_info;
}

template <typename T>
bool container<T>::const_iterator::operator ==(const_iterator i) const
{
    return _itPointer == i._itPointer;
}

template <typename T>
bool container<T>::const_iterator::operator !=(const_iterator i) const
{
    return _itPointer != i._itPointer;
}

template <typename T>
typename container<T>::const_iterator& container<T>::const_iterator::operator ++()
{
    if (this->_itPointer != 0)
        _itPointer = _itPointer->_next;
    return *this;
}

template <typename T>
typename container<T>::const_iterator container<T>::const_iterator::operator ++(int)
{
    const_iterator aux = *this;
    if (this->_itPointer != 0)
        _itPointer = _itPointer->_next;
    return aux;
}


#endif // CONTAINER_H

