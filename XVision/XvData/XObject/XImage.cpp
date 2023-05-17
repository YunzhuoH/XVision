#include "XImage.h"

XImage::XImage(const QString &objectName, const QImage &value, XObjectSet *parObjectSet, const QString &dispalyName)
 :XObject{objectName,parObjectSet,dispalyName},_value(value)
{

}

XImage::XImage(const QImage &value)
 :XObject{},_value(value)
{

}

XImage::XImage()
  :XObject{},_value(QImage())
{

}

XImage::~XImage()
{

}

QString XImage::toString() const
{
   auto keys= _value.textKeys();
   QString str;
   foreach (auto key, keys)
   {
       str+=QString("[%1:%2]").arg(key).arg(_value.text(key));
   }
   return QString("%1*%2*%3 %4").arg(_value.width()).arg(_value.height()).arg(_value.depth()).arg(str);
}

bool XImage::getData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XImage*>(object);
    if(!temp)
    {
        return false;
    }
    temp->setValue(this->value());
    return true;
}

bool XImage::setData(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(object->typeName()!=this->typeName())
    {
        return false;
    }
    auto temp=dynamic_cast<XImage*>(object);
    if(!temp)
    {
        return false;
    }
    this->setValue(temp->value());
    return true;
}

void XImage::setValue(const QImage &value)
{
    this->_value=value;
}
