#include "XString.h"

XString::XString(const QString &objectName,const QString &value,XObjectSet *parObjectSet,const QString &dispalyName)
    :XObject{objectName,parObjectSet,dispalyName},_value(value)
{

}

XString::XString(const QString &value)
  :XObject{},_value(value)
{

}

XString::XString()
  :XObject{},_value("")
{

}


XString::~XString()
{

}

bool XString::getData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XString*>(object);
    if(!temp)
    {
        return false;
    }
    temp->setValue(this->value());
    return true;
}

bool XString::setData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XString*>(object);
    if(!temp)
    {
        return false;
    }
    this->setValue(temp->value());
    return true;
}



void XString::setValue(const QString &value)
{
    this->_value=value;
}


