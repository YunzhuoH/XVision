#ifndef XOBJECTSET_H
#define XOBJECTSET_H

#include "XvDataGlobal.h"
#include <QList>

class XObject;
class XVDATA_EXPORT XObjectSet
{
public:
    XObjectSet();
    virtual ~XObjectSet();
public:
    ///子对象列表
    const  QList<XObject*> childObjects() const;
    ///获取子对象
    XObject *childObject(const QString &objectName);
     ///获取子对象
    template<typename T>
    T *childObject(const QString &objectName)
    {
        return dynamic_cast<T*>(childObject(objectName));
    }
    ///根据类型获取子对象
    QList<XObject*> childObjects(const QString &typeName);


    ///添加子对象
    bool addChildObject(XObject* object);
    ///删除子对象
    bool removeChildObject(XObject* object);
    ///是否存在子对象
    bool existChildObject(const QString &objectName);
protected:
    QList<XObject*> _ChildObjects;
};

#endif // XOBJECTSET_H
