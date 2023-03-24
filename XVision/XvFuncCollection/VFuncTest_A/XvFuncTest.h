#ifndef XVFUNCTEST_H
#define XVFUNCTEST_H

#include "VFuncTest_A_global.h"
#include "XVFuncBase.h"

namespace XvCore
{
class VFUNCTEST_A_EXPORT VFuncA:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncA(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncA";
        _VFuncName="算子-VFuncA";
        _VFuncType=EXvFuncType::Other;
    }
};

class VFUNCTEST_A_EXPORT VFuncB:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncB(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncB";
        _VFuncName="算子-VFuncB";
        _VFuncType=EXvFuncType::Other;
    }
};

class VFUNCTEST_A_EXPORT VFuncC:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncC(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncC";
        _VFuncName="算子-VFuncC";
        _VFuncType=EXvFuncType::Other;
    }
};
class VFUNCTEST_A_EXPORT VFuncC1:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncC1(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncC1";
        _VFuncName="算子-VFuncC1";
        _VFuncType=EXvFuncType::Other;
    }
};
class VFUNCTEST_A_EXPORT VFuncC2:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncC2(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncC2";
        _VFuncName="算子-VFuncC2";
        _VFuncType=EXvFuncType::Other;
    }
};
class VFUNCTEST_A_EXPORT VFuncZ:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncZ(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncZ";
        _VFuncName="算子-VFuncZ";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncY:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncY(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncY";
        _VFuncName="算子-VFuncY";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncX:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncX(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncX";
        _VFuncName="算子-VFuncX";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncW:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncW(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncW";
        _VFuncName="算子-VFuncW";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncV:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncV(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncV";
        _VFuncName="算子-VFuncV";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncU:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncU(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncU";
        _VFuncName="算子-VFuncU";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};


class VFUNCTEST_A_EXPORT VFuncQ1:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ1(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ1";
        _VFuncName="算子-VFuncQ1";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ2:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ2(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ2";
        _VFuncName="算子-VFuncQ2";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};


class VFUNCTEST_A_EXPORT VFuncQ3:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ3(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ3";
        _VFuncName="算子-VFuncQ3";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ4:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ4(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ4";
        _VFuncName="算子-VFuncQ4";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ5:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ5(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ5";
        _VFuncName="算子-VFuncQ5";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ6:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ6(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ6";
        _VFuncName="算子-VFuncQ6";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ7:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ7(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ7";
        _VFuncName="算子-VFuncQ7";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ8:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ8(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ8";
        _VFuncName="算子-VFuncQ8";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ9:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ9(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQ9";
        _VFuncName="算子-VFuncQ9";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQA:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQA(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQA";
        _VFuncName="算子-VFuncQA";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};
class VFUNCTEST_A_EXPORT VFuncQB:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQB(QObject *parent = nullptr)
    {
        _VFuncRole="V-VFuncQB";
        _VFuncName="算子-VFuncQB";
        _VFuncType=EXvFuncType::ImageAcquisition;
    }
};
}

#endif // XVFUNCTEST_H
