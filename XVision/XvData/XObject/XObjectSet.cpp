#include "XObjectSet.h"
#include "XObject.h"

XObjectSet::XObjectSet()
{

}

XObjectSet::~XObjectSet()
{
    foreach (auto obj, _ChildObjects)
    {
        delete obj;
        obj=nullptr;
    }
}

const QList<XObject *> XObjectSet::childObjects() const
{
    return _ChildObjects;
}

XObject *XObjectSet::childObject(const QString &objectName)
{
    foreach (auto object, _ChildObjects)
    {
        if(object->objectName()==objectName)
        {
            return object;
        }
    }
    return nullptr;
}

QList<XObject*> XObjectSet::childObjects(const QString &typeName)
{
    QList<XObject*> lst;
    foreach (auto object, _ChildObjects)
    {
        if(object->typeName()==typeName)
        {
            lst.append(object);
        }
    }
    return lst;
}

bool XObjectSet::addChildObject(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(_ChildObjects.contains(object))
    {
        return false;
    }
    _ChildObjects.append(object);
    return true;
}

bool XObjectSet::removeChildObject(XObject *object)
{
    if(!object)
    {
        return false;
    }
    if(!_ChildObjects.contains(object))
    {
        return false;
    }
    return _ChildObjects.removeOne(object);
}

bool XObjectSet::existChildObject(const QString &objectName)
{
    foreach (auto object, _ChildObjects)
    {
        if(object->objectName()==objectName)
        {
            return true;
        }
    }
    return false;
}
