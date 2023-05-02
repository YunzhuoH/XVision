#include "XInt.h"
#include "XReal.h"
XInt::XInt(const QString &objectName,const int &value,XObjectSet *parObjectSet,const QString &dispalyName)
    :XObject{objectName,parObjectSet,dispalyName},_value(value)
{

}

XInt::XInt(const int &value)
  :XObject{},_value(value)
{

}

XInt::XInt()
  :XObject{},_value(0)
{

}


XInt::~XInt()
{

}


bool XInt::getData(XObject *object)
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

bool XInt::setData(XObject *object)
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



void XInt::setValue(const int &value)
{
    this->_value=value;
}
