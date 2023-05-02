#ifndef XINT_H
#define XINT_H

#include "XObject.h"

#define XIntType "XInt"
class XVDATA_EXPORT XInt:public XObject
{
public:
    XInt(const QString &objectName,const int &value=0,XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XInt(const int &value);
    XInt();
    ~XInt();
    static QString type() { return XIntType;}
    XObject *clone() override { return new XInt(*this);}
public://重载
    QString toString() const override {  return QString::number(_value); }
    QString typeName() override { return XIntType;}
    bool getData(XObject *object) override;
    bool setData(XObject *object) override;

public://*[数据操作]*
    //设置数据
    void setValue(const int &value);
    //获取数据
    int value() const
    {
        return _value;
    }
public://重载]
//赋值运算
    void operator=(const int &value)
    {
        this->_value=value;
    }
//运算
    int operator+(const int &value)
    {
       return this->_value+value;
    }

    XInt operator+(const XInt &value)
    {
        XInt temp;
        temp._value=this->_value+value._value;
        return temp;
    }


    int operator-(const int &value)
    {
       return this->_value-value;
    }

    XInt operator-(const XInt &value)
    {
        XInt temp;
        temp._value=this->_value-value._value;
        return temp;
    }

    int operator*(const int &value)
    {
       return this->_value*value;
    }

    XInt operator*(const XInt &value)
    {
        XInt temp;
        temp._value=this->_value*value._value;
        return temp;
    }

    int operator/(const int &value)
    {
       return this->_value/value;
    }

    XInt operator/(const XInt &value)
    {
        XInt temp;
        temp._value=this->_value/value._value;
        return temp;
    }
//判断运算
    bool operator==(const XInt& xInt)
    {
        return this->_value == xInt._value;
    }
    bool operator==(const int &value)
    {
        return this->_value == value;
    }

    bool operator!=(const XInt& xInt)
    {
        return this->_value != xInt._value;
    }
    bool operator!=(const int &value)
    {
        return this->_value != value;
    }


    bool operator>(const XInt& xInt)
    {
        return this->_value > xInt._value;
    }
    bool operator>(const int &value)
    {
        return this->_value > value;
    }

    bool operator>=(const XInt& xInt)
    {
        return this->_value >= xInt._value;
    }
    bool operator>=(const int &value)
    {
        return this->_value >= value;
    }


    bool operator<(const XInt& xInt)
    {
        return this->_value < xInt._value;
    }
    bool operator<(const int &value)
    {
        return this->_value < value;
    }

    bool operator<=(const XInt& xInt)
    {
        return this->_value <= xInt._value;
    }
    bool operator<=(const int &value)
    {
        return this->_value <= value;
    }



//自加减运算
    XInt& operator ++()
    {
        this->_value++;
        return *this;
    }

    XInt operator ++(int) {
        XInt temp = *this;
        ++*this;
        return temp;
    }

    XInt& operator --()
    {
        this->_value--;
        return *this;
    }

    XInt operator --(int) {
        XInt temp = *this;
        --*this;
        return temp;
    }

protected:
//*[数据区]*
    ///整数值
    int _value;


};

#endif // XINT_H
