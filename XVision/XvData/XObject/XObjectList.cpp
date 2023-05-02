#include "XObjectList.h"

XObjectList::XObjectList(const QString &objectName,const QString &valueType,XObjectSet *parObjectSet, const QString &dispalyName)
 :XObject{objectName,parObjectSet,dispalyName},_valueType(valueType)
{

}

XObjectList::XObjectList()
    :XObject{}
{

}

XObjectList::~XObjectList()
{

}

bool XObjectList::init(const QString &objectName, const QString &valueType, XObjectSet *parObjectSet, const QString &dispalyName)
{
    _valueType=valueType;
    return XObject::init(objectName,parObjectSet,dispalyName);
}

bool XObjectList::getData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XObjectList*>(object);
    if(!temp)
    {
        return false;
    }
    if(temp->valueType()!=this->valueType())
    {
        return false;
    }
    temp->clear();
    foreach (auto obj, _lst)
    {
        temp->addValue(obj->clone());
    }
    return true;
}

bool XObjectList::setData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XObjectList*>(object);
    if(!temp)
    {
        return false;
    }
    if(temp->valueType()!=this->valueType())
    {
        return false;
    }
    clear();
    foreach (auto obj, temp->_lst)
    {
        addValue(obj->clone());
    }
    return true;
}

XObject *XObjectList::value(qsizetype idx)
{
    return _lst.at(idx);
}

bool XObjectList::addValue(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->valueType())
    {
        return false;
    }
    object->setParObjectSet(this);
    _lst.append(object);
    return true;
}

bool XObjectList::removeValue(XObject *object,bool del)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->valueType())
    {
        return false;
    }
    if(!_lst.contains(object))
    {
        return false;
    }
    bool bRet= _lst.removeOne(object);
    if(del)
    {
        delete object;
        object=nullptr;
    }
    return bRet;
}

void XObjectList::clear(bool del)
{
    foreach (auto obj, _lst)
    {
        bool bRet= _lst.removeOne(obj);
        if(del)
        {
            delete obj;
            obj=nullptr;
        }
    }
}

qsizetype XObjectList::count() const
{
    return _lst.count();
}
