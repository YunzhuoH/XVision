#ifndef BASEDATAREALCALC_H
#define BASEDATAREALCALC_H


#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class BaseDataRealCalcWdg;
namespace XvCore
{
class BaseDataRealCalcParam:public XvBaseParam
{
public:
    BaseDataRealCalcParam()
    {
        realParam1=new XReal("realParam1",0,this,getLang("XvFuncSystem_BaseDataRealCalc_RealParam1","浮点计算值1"));
        realParam2=new XReal("realParam2",0,this,getLang("XvFuncSystem_BaseDataRealCalc_realParam2","浮点计算值2"));
    }
public:
    XReal *realParam1=nullptr;
    XReal *realParam2=nullptr;

};



class BaseDataRealCalcResult:public XvBaseResult
{
public:
    BaseDataRealCalcResult()
    {
        realResult=new XReal("realResult",0,this,getLang("XvFuncSystem_BaseDataRealCalc_RealResult","浮点计算结果"));
    }
public:
    XReal *realResult=nullptr;

};

class XVFUNCSYSTEM_EXPORT BaseDataRealCalc:public XvFunc
{
    Q_OBJECT
    friend class BaseDataRealCalcWdg;
public:
    Q_INVOKABLE explicit BaseDataRealCalc(QObject *parent = nullptr);
    ~BaseDataRealCalc();
public:
    enum ERealCalaType
    {
        Add=0,//+
        Sub=1,//-
        Mul=2,//×
        Div=3,//÷
    };
    Q_ENUMS(ERealCalaType);
    ERealCalaType realCalaType() const {return m_realCalaType;}
    void setRealCalaType(ERealCalaType type){ m_realCalaType=type;}
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/BaseDataRealCalc.svg");}
    EXvFuncRunStatus run() override;
    XvBaseParam *getParam() const override { return param;};
    XvBaseResult *getResult() const override { return result;};
protected:
    BaseDataRealCalcParam *param=nullptr;
    BaseDataRealCalcResult *result=nullptr;
    BaseDataRealCalcWdg* m_frm=nullptr;
    ERealCalaType m_realCalaType=ERealCalaType::Add;


};

}


#endif // BASEDATAREALCALC_H
