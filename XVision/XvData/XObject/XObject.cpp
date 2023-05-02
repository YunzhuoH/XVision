#include "XObject.h"
#include <QString>
#include "XObjectSet.h"

XObject::XObject(const QString &objectName, XObjectSet *parObjectSet, const QString &dispalyName)
    :_objectName(objectName),_dispalyName(dispalyName),_parObjectSet(parObjectSet)
{
    if(_parObjectSet)
    {
        _parObjectSet->addChildObject(this);
    }
}

XObject::XObject()
    :_objectName(""),_dispalyName(""),_parObjectSet(nullptr)
{

}

XObject::~XObject()
{  
    if(_parObjectSet)
    {
        _parObjectSet->removeChildObject(this);
    }
}

bool XObject::init(const QString &objectName, XObjectSet *parObjectSet, const QString &dispalyName)
{
    setObjectName(objectName);
    setDisplayName(dispalyName);
    return setParObjectSet(parObjectSet);
}

bool XObject::setParObjectSet(XObjectSet *parObjectSet)
{
    if(!parObjectSet) //父对象集为空，返回失败
    {
        return false;
    }
    if(_parObjectSet) //已对象父数据集，删除原有对象
    {
       _parObjectSet->removeChildObject(this);
    }
    _parObjectSet=parObjectSet;
    return _parObjectSet->addChildObject(this);
}

void XObject::setObjectName(const QString &objectName)
{
    _objectName=objectName;
}


void XObject::setDisplayName(const QString &displayName)
{
    _dispalyName=displayName;
}

void XObject::setTips(const QString &tips)
{
    _tips=tips;
}

