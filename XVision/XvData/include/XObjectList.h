#ifndef XOBJECTLIST_H
#define XOBJECTLIST_H

#include "XObject.h"
#include "XObjectSet.h"

#define XObjectListType "XObjectList"

class XVDATA_EXPORT XObjectList:public XObject,public XObjectSet
{
public:
    XObjectList(const QString &objectName,const QString &valueType,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XObjectList();
    ~XObjectList();

    ///类型
    static QString type() { return XObjectListType;}
    ///初始化
    bool init(const QString &objectName,const QString &valueType,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
public://重载
    XObject *clone() override { return nullptr;}
    QString typeName() override { return XObjectListType;}
    bool isContainer() override { return true; }
    bool getData(XObject *object) override;
    bool setData(XObject *object) override;

public://*[数据操作]*
    ///列表数据类型
    QString valueType() const { return _valueType;}
    ///获取数据
    const QList<XObject*> values() const { return _lst;}
    ///获取数据
    XObject* value(qsizetype idx);
    ///添加数据
    bool addValue(XObject* object);
    ///移除数据
    bool removeValue(XObject* object,bool del=true);
    ///移除所有数据
    void clear(bool del=true);
    ///数据大小
    qsizetype count() const;
protected:
    QString _valueType;//列表类型
    QList<XObject*> _lst;//数据列表


};

#endif // XOBJECTLIST_H
