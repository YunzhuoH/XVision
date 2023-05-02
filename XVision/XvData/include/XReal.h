#ifndef XREAL_H
#define XREAL_H

#include "XObject.h"

#define XRealType "XReal"
class XVDATA_EXPORT XReal:public XObject
{
public:
    XReal(const QString &objectName,const double &value=0,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XReal(const double &value);
    XReal();
    ~XReal();
    static QString type() { return XRealType;}
    XObject *clone() override { return new XReal(*this);}
public://重载
    QString toString() const override {  return QString::number(_value,'f'); }
    QString typeName() override { return XRealType;}
    bool getData(XObject *object) override;
    bool setData(XObject *object) override;

public://*[数据操作]*
    //设置数据
    void setValue(const double &value);
    //获取数据
    double value() const
    {
        return _value;
    }
public://重载]
//赋值运算
    void operator=(const double &value)
    {
        this->_value=value;
    }
//运算
    double operator+(const double &value)
    {
       return this->_value+value;
    }

    XReal operator+(const XReal &value)
    {
        XReal temp;
        temp._value=this->_value+value._value;
        return temp;
    }


    double operator-(const double &value)
    {
       return this->_value-value;
    }

    XReal operator-(const XReal &value)
    {
        XReal temp;
        temp._value=this->_value-value._value;
        return temp;
    }

    double operator*(const double &value)
    {
       return this->_value*value;
    }

    XReal operator*(const XReal &value)
    {
        XReal temp;
        temp._value=this->_value*value._value;
        return temp;
    }

    double operator/(const double &value)
    {
       return this->_value/value;
    }

    XReal operator/(const XReal &value)
    {
        XReal temp;
        temp._value=this->_value/value._value;
        return temp;
    }
//判断运算
bool operator==(const XReal& xInt)
{
    return this->_value == xInt._value;
}
bool operator==(const double &value)
{
    return this->_value == value;
}

bool operator!=(const XReal& xInt)
{
    return this->_value != xInt._value;
}
bool operator!=(const double &value)
{
    return this->_value != value;
}


bool operator>(const XReal& xInt)
{
    return this->_value > xInt._value;
}
bool operator>(const double &value)
{
    return this->_value > value;
}

bool operator>=(const XReal& xInt)
{
    return this->_value >= xInt._value;
}
bool operator>=(const double &value)
{
    return this->_value >= value;
}


bool operator<(const XReal& xInt)
{
    return this->_value < xInt._value;
}
bool operator<(const double &value)
{
    return this->_value < value;
}

bool operator<=(const XReal& xInt)
{
    return this->_value <= xInt._value;
}
bool operator<=(const double &value)
{
    return this->_value <= value;
}

protected:
//*[数据区]*
    ///浮点数值
    double _value;

};


#endif // XREAL_H
