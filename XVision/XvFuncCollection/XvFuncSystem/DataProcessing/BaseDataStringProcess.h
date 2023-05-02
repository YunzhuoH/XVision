#ifndef BASEDATASTRINGPROCESS_H
#define BASEDATASTRINGPROCESS_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class BaseDataStringProcessWdg;

namespace XvCore
{
class BaseDataStringProcessParam:public XvBaseParam
{
public:
    BaseDataStringProcessParam()
    {
        stringParam1=new XString("stringParam1","",this,getLang("XvFuncSystem_BaseDataStringProcess_StringParam1","字符串参数1"));
        stringParam2=new XString("stringParam2","",this,getLang("XvFuncSystem_BaseDataStringProcess_StringParam2","字符串参数2"));

        intParam1=new XInt("intParam1",0,this,getLang("XvFuncSystem_BaseDataStringProcess_IntParam1","整数参数1"));
        intParam2=new XInt("intParam2",0,this,getLang("XvFuncSystem_BaseDataStringProcess_IntParam2","整数参数2"));

        boolParam=new XBool("boolParam",false,this,getLang("XvFuncSystem_BaseDataStringProcess_BoolParam","布尔参数"));
        realParam=new XReal("realParam",0,this,getLang("XvFuncSystem_BaseDataStringProcess_RealParam","浮点参数"));

    }
public:
    XString *stringParam1=nullptr;
    XString *stringParam2=nullptr;

    XInt    *intParam1=nullptr;
    XInt    *intParam2=nullptr;

    XBool   *boolParam=nullptr;
    XReal   *realParam=nullptr;

};



class BaseDataStringProcessResult:public XvBaseResult
{
public:
    BaseDataStringProcessResult()
    {
        boolResult=new XBool("boolResult",false,this,getLang("XvFuncSystem_BaseDataStringProcess_BoolResult","布尔结果"));
        intResult=new XInt("intResult",0,this,getLang("XvFuncSystem_BaseDataStringProcess_IntResult","整数结果"));
        realResult=new XReal("realResult",0,this,getLang("XvFuncSystem_BaseDataStringProcess_RealResult","浮点结果"));
        stringResult=new XString("stringResult","",this,getLang("XvFuncSystem_BaseDataStringProcess_Stringesult","字符串结果"));
    }
public:
    XBool *boolResult=nullptr;

    XInt *intResult=nullptr;

    XReal *realResult=nullptr;

    XString *stringResult=nullptr;

};

class XVFUNCSYSTEM_EXPORT BaseDataStringProcess:public XvFunc
{
    Q_OBJECT
    Q_PROPERTY(BaseDataStringProcess::EStringProcessType stringProcessType WRITE setStringProcessType READ stringProcessType)
    friend class BaseDataStringProcessWdg;
public:
    Q_INVOKABLE explicit BaseDataStringProcess(QObject *parent = nullptr);
    ~BaseDataStringProcess();
public:
    enum EStringProcessType
    {
        IsEqual=0,  // 等于 Rb
        IsNoEqual=1,// 不等于 Rb

        Contain=2,//包含 Rb

        Add=3,//相加  Rs
        Left=4,//截取左边 Rs
        Mid=5,//截取中间 Rs
        Right=6,//截取右边 Rs

        Length=7,//长度 Ri

        ToLower=8,//转为小写 Rs
        ToUpper=9,//转为大写 Rs

        TryToBool=10,//尝试转换为布尔量
        TryToInt=11,//尝试转换为整数值
        TryToReal=12,//尝试转换为浮点数

        BoolToString=13,//将布尔量转换为字符串
        IntToString=14,//将整数转换为字符串
        RealToString=15,//将浮点数转换为字符串


    };
    Q_ENUMS(EStringProcessType);
    EStringProcessType stringProcessType() const {return m_stringProcessType;}
    void setStringProcessType(EStringProcessType type){ m_stringProcessType=type;}
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/BaseDataStringProcess.svg");}
    EXvFuncRunStatus run() override;

    XvBaseParam *getParam() const override { return param;};
    XvBaseResult *getResult() const override { return result;};

protected:
    void resetResult();//重置结果
protected:
    BaseDataStringProcessParam *param=nullptr;
    BaseDataStringProcessResult *result=nullptr;
    BaseDataStringProcessWdg* m_frm=nullptr;
    EStringProcessType m_stringProcessType=EStringProcessType::IsEqual;


};
}


#endif // BASEDATASTRINGPROCESS_H
