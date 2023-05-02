#ifndef XOBJECT_H
#define XOBJECT_H

#include "XvDataGlobal.h"
#include <QObject>

class XObjectSet;
class XVDATA_EXPORT XObject
{
public:
    XObject(const QString &objectName,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XObject();
    virtual ~XObject();

public: //*[对象基础操作]*
    ///初始化
    bool init(const QString &objectName,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    ///对象类型名称
    virtual  QString typeName()=0;
    ///是否为容器类型
    virtual bool isContainer() { return false; }
    ///转换为子对象
    template<typename T>
    T *toObject()
    {
        return dynamic_cast<T*>(this);
    }
    ///转换为字符串
    virtual QString toString() const { return ""; }
    ///克隆对象
    virtual XObject* clone()=0;

 public:  //*[对象属性操作]*
//父对象集
    ///设置父对象集
    bool setParObjectSet(XObjectSet* parObjectSet);
    ///父对象集
    XObjectSet* parObjectSet() const { return _parObjectSet;}
//对象对象名称
    ///设置对象名称
    void setObjectName(const QString &objectName);
    ///对象名称
    QString objectName() const { return _objectName; }
//对象显示名称
    ///设置对象显示名称
    void setDisplayName(const QString &displayName);
    ///对象显示名称
    QString dispalyName() const { return _dispalyName; }
//对象提示
    ///设置对象提示
    void setTips(const QString &tips);
    ///对象提示
    QString tips() const { return _tips; }

 public://*[对象数据获取更新]*

    ///获取数据
    virtual bool getData(XObject *object)=0;
    ///设置数据
    virtual bool setData(XObject *object)=0;


protected:
    XObjectSet* _parObjectSet=nullptr;//父对象集
    QString _objectName;//对象名称
    QString _dispalyName;//对象显示名称
    QString _tips;  //对象提示
};




#endif // XOBJECT_H
