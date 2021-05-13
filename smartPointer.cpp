#ifndef SMARTPOINTER
#define SMARTPONTER

template <typename Object>
class SmartPtr
{
    Object* item;
public:
    SmartPtr(Object *obj)
        : item(obj)
    {
    }
    ~SmartPtr()
    {
        delete item;
    }

    Object* getItem()
    {
        return item;
    }
    void setItem(Object *obj)
    {
        delete item;
        item = obj;
    }
    SmartPtr* operator=(const Object *obj)
    {
        delete item;
        item = obj;
        return this;
    }

};

#endif
