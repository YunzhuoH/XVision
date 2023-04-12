#ifndef XVFUNCTEST_H
#define XVFUNCTEST_H

#include "VFuncTest_A_global.h"
#include "XVFunc.h"
#include <thread>
#include <chrono>
namespace XvCore
{
class VFUNCTEST_A_EXPORT VFuncA:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncA(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncA";
        _funcName="算子-VFuncA";
        _funcType=EXvFuncType::Other;
    }

    // XvFunc interface
protected:
    EXvFuncRunStatus run() override
    {
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return EXvFuncRunStatus::Error;
    }
};

class VFUNCTEST_A_EXPORT VFuncB:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncB(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncB";
        _funcName="算子-VFuncB";
        _funcType=EXvFuncType::Other;
    }
protected:
    EXvFuncRunStatus run() override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return EXvFuncRunStatus::Fail;
    }
};

class VFUNCTEST_A_EXPORT VFuncC:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncC(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncC";
        _funcName="算子-VFuncC";
        _funcType=EXvFuncType::Other;
    }
protected:
    EXvFuncRunStatus run() override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return EXvFuncRunStatus::Ok;
    }
};
class VFUNCTEST_A_EXPORT VFuncC1:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncC1(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncC1";
        _funcName="算子-VFuncC1";
        _funcType=EXvFuncType::Other;
    }
protected:
    EXvFuncRunStatus run() override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return EXvFuncRunStatus::Running;
    }
};
class VFUNCTEST_A_EXPORT VFuncC2:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncC2(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncC2";
        _funcName="算子-VFuncC2";
        _funcType=EXvFuncType::Other;
    }
protected:
    EXvFuncRunStatus run() override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return EXvFuncRunStatus::Init;
    }
};
class VFUNCTEST_A_EXPORT VFuncZ:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncZ(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncZ";
        _funcName="算子-VFuncZ";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncY:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncY(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncY";
        _funcName="算子-VFuncY";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncX:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncX(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncX";
        _funcName="算子-VFuncX";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncW:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncW(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncW";
        _funcName="算子-VFuncW";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncV:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncV(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncV";
        _funcName="算子-VFuncV";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncU:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncU(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncU";
        _funcName="算子-VFuncU";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};


class VFUNCTEST_A_EXPORT VFuncQ1:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ1(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ1";
        _funcName="算子-VFuncQ1";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ2:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ2(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ2";
        _funcName="算子-VFuncQ2";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};


class VFUNCTEST_A_EXPORT VFuncQ3:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ3(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ3";
        _funcName="算子-VFuncQ3";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ4:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ4(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ4";
        _funcName="算子-VFuncQ4";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ5:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ5(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ5";
        _funcName="算子-VFuncQ5";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ6:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ6(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ6";
        _funcName="算子-VFuncQ6";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ7:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ7(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ7";
        _funcName="算子-VFuncQ7";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ8:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ8(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ8";
        _funcName="算子-VFuncQ8";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQ9:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQ9(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQ9";
        _funcName="算子-VFuncQ9";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};

class VFUNCTEST_A_EXPORT VFuncQA:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQA(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQA";
        _funcName="算子-VFuncQA";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};
class VFUNCTEST_A_EXPORT VFuncQB:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncQB(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncQB";
        _funcName="算子-VFuncQB";
        _funcType=EXvFuncType::ImageAcquisition;
    }
};



class VFUNCTEST_A_EXPORT VFuncW1:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncW1(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncW1";
        _funcName="算子-VFuncQ1";
        _funcType=EXvFuncType::Calibration;
    }
};
class VFUNCTEST_A_EXPORT VFuncW2:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncW2(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncW2";
        _funcName="算子-VFuncQ1";
        _funcType=EXvFuncType::Calibration;
    }
};
class VFUNCTEST_A_EXPORT VFuncW3:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncW3(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncW3";
        _funcName="算子-VFuncW3";
        _funcType=EXvFuncType::Calibration;
    }
};

class VFUNCTEST_A_EXPORT VFuncW4:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFuncW4(QObject *parent = nullptr)
    {
        _funcRole="V-VFuncW4";
        _funcName="算子-VFuncW4";
        _funcType=EXvFuncType::Calibration;
    }
};

}

#endif // XVFUNCTEST_H
