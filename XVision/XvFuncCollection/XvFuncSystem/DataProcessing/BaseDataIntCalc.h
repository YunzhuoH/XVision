#ifndef BASEDATAINTCALC_H
#define BASEDATAINTCALC_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class BaseDataIntCalcWdg;
namespace XvCore
{
class BaseDataIntCalcParam:public XvBaseParam
{
public:
    BaseDataIntCalcParam()
    {
        intParam1=new XInt("intParam1",0,this,getLang("XvFuncSystem_BaseDataIntCalc_IntParam1","整数计算值1"));
        intParam2=new XInt("intParam2",0,this,getLang("XvFuncSystem_BaseDataIntCalc_IntParam2","整数计算值2"));
    }
public:
    XInt *intParam1=nullptr;
    XInt *intParam2=nullptr;

};



class BaseDataIntCalcResult:public XvBaseResult
{
public:
    BaseDataIntCalcResult()
    {
        intResult=new XInt("intResult",0,this,getLang("XvFuncSystem_BaseDataIntCalc_IntResult","整数计算结果"));
    }
public:
    XInt *intResult=nullptr;

};

class XVFUNCSYSTEM_EXPORT BaseDataIntCalc:public XvFunc
{
    Q_OBJECT
    Q_PROPERTY(BaseDataIntCalc::EIntCalaType intCalaType WRITE setIntCalaType READ intCalaType)
    friend class BaseDataIntCalcWdg;
public:
    Q_INVOKABLE explicit BaseDataIntCalc(QObject *parent = nullptr);
    ~BaseDataIntCalc();
public:
    enum EIntCalaType
    {
        Add=0,//+
        Sub=1,//-
        Mul=2,//×
        Div=3,//÷
        SelfAdd=4,//++
        SelfSub=5,//--
    };
    Q_ENUMS(EIntCalaType);
    EIntCalaType intCalaType() const {return m_intCalaType;}
    void setIntCalaType(EIntCalaType type){ m_intCalaType=type;}
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/BaseDataIntCalc.svg");}
    EXvFuncRunStatus run() override;

    XvBaseParam *getParam() const override { return param;};
    XvBaseResult *getResult() const override { return result;};
protected:
    BaseDataIntCalcParam *param=nullptr;
    BaseDataIntCalcResult *result=nullptr;
    BaseDataIntCalcWdg* m_frm=nullptr;
    EIntCalaType m_intCalaType=EIntCalaType::Add;


};
}




#endif // BASEDATAINTCALC_H
