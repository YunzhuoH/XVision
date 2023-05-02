#include "XBool.h"

XBool::XBool(const QString &objectName,const bool &value,XObjectSet *parObjectSet,const QString &dispalyName)
    :XObject{objectName,parObjectSet,dispalyName},_value(value)
{

}

XBool::XBool(const bool &value)
  :XObject{},_value(value)
{

}

XBool::XBool()
  :XObject{},_value(0)
{

}


XBool::~XBool()
{

}

bool XBool::getData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XBool*>(object);
    if(!temp)
    {
        return false;
    }
    temp->setValue(this->value());
    return true;
}

bool XBool::setData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XBool*>(object);
    if(!temp)
    {
        return false;
    }
    this->setValue(temp->value());
    return true;
}



void XBool::setValue(const bool &value)
{
    this->_value=value;
}
