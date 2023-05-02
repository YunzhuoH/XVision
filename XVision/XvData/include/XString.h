#ifndef XSTRING_H
#define XSTRING_H

#include "XObject.h"

#define XStringType "XString"
class XVDATA_EXPORT XString:public XObject
{
public:
    XString(const QString &objectName,const QString &value="",XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XString(const QString &value);
    XString();
    ~XString();
    static QString type() { return XStringType;}
    XObject *clone() override { return new XString(*this);}
public://重载
    QString toString() const override {  return _value; }
    QString typeName() override { return XStringType;}
    bool getData(XObject *object) override;
    bool setData(XObject *object) override;

public://*[数据操作]*
    //设置数据
    void setValue(const QString &value);
    //获取数据
    QString value() const
    {
        return _value;
    }
public://重载]
//赋值运算
    void operator=(const QString &value)
    {
        this->_value=value;
    }

//判断运算
    bool operator==(const XString& xInt)
    {
        return this->_value == xInt._value;
    }
    bool operator==(const QString &value)
    {
        return this->_value == value;
    }

    bool operator!=(const XString& xInt)
    {
        return this->_value != xInt._value;
    }
    bool operator!=(const QString &value)
    {
        return this->_value != value;
    }


protected:
//*[数据区]*
    ///字符串数值
    QString _value;

};



#endif // XSTRING_H
