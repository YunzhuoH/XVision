#include "XReal.h"
#include "XInt.h"

XReal::XReal(const QString &objectName, const double &value,XObjectSet *parObjectSet,  const QString &dispalyName)
    :XObject{objectName,parObjectSet,dispalyName},_value(value)
{

}

XReal::XReal(const double &value)
  :XObject{},_value(value)
{

}

XReal::XReal()
  :XObject{},_value(0)
{

}

XReal::~XReal()
{

}

bool XReal::getData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(!(object->typeName()==XInt::type()||object->typeName()==XReal::type()))
    {
        return false;
    }
    if(object->typeName()==XInt::type())
    {
        auto temp=dynamic_cast<XInt*>(object);
        if(!temp)
        {
            return false;
        }
        temp->setValue(this->value());
        return true;
    }
    else if(object->typeName()==XReal::type())
    {
        auto temp=dynamic_cast<XReal*>(object);
        if(!temp)
        {
            return false;
        }
        temp->setValue(this->value());
        return true;
    }
    else
    {
        return false;
    }
}

bool XReal::setData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(!(object->typeName()==XInt::type()||object->typeName()==XReal::type()))
    {
        return false;
    }
    if(object->typeName()==XInt::type())
    {
        auto temp=dynamic_cast<XInt*>(object);
        if(!temp)
        {
            return false;
        }
        this->setValue(temp->value());
        return true;
    }
    else if(object->typeName()==XReal::type())
    {
        auto temp=dynamic_cast<XReal*>(object);
        if(!temp)
        {
            return false;
        }
        this->setValue(temp->value());
        return true;
    }
    else
    {
        return false;
    }
}


void XReal::setValue(const double &value)
{
    this->_value=value;
}
