#ifndef XBOOL_H
#define XBOOL_H

#include "XObject.h"

#define XBoolType "XBool"
class XVDATA_EXPORT XBool:public XObject
{
public:
    XBool(const QString &objectName,const bool &value=false,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XBool(const bool &value);
    XBool();
    ~XBool();
    static QString type() { return XBoolType;}
    XObject *clone() override { return new XBool(*this);}
public://重载
    QString toString() const override {  return QString("%1").arg(_value); }
    QString typeName() override { return XBoolType;}
    bool getData(XObject *object) override;
    bool setData(XObject *object) override;

public://*[数据操作]*
    //设置数据
    void setValue(const bool &value);
    //获取数据
    bool value() const
    {
        return _value;
    }
public://重载]
//赋值运算
    void operator=(const bool &value)
    {
        this->_value=value;
    }

//判断运算
    bool operator==(const XBool& xBool)
    {
        return this->_value == xBool._value;
    }
    bool operator==(const bool &value)
    {
        return this->_value == value;
    }

    bool operator!=(const XBool& xBool)
    {
        return this->_value != xBool._value;
    }
    bool operator!=(const bool &value)
    {
        return this->_value != value;
    }

protected:
//*[数据区]*
    ///布尔值
    bool _value;

};


#endif // XBOOL_H
