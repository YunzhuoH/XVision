#ifndef BASEDATABOOLCALC_H
#define BASEDATABOOLCALC_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class BaseDataBoolCalcWdg;

namespace XvCore
{
class BaseDataBoolCalcParam:public XvBaseParam
{
public:
    BaseDataBoolCalcParam()
    {
        boolParam1=new XBool("boolParam1",false,this,getLang("XvFuncSystem_BaseDataBoolCalc_BoolParam1","布尔计算值1"));
        boolParam2=new XBool("boolParam2",false,this,getLang("XvFuncSystem_BaseDataBoolCalc_BoolParam2","布尔计算值2"));
    }
public:
    XBool *boolParam1=nullptr;
    XBool *boolParam2=nullptr;

};



class BaseDataBoolCalcResult:public XvBaseResult
{
public:
    BaseDataBoolCalcResult()
    {
        boolResult=new XBool("boolResult",false,this,getLang("XvFuncSystem_BaseDataBoolCalc_BoolResult","布尔计算结果"));
    }
public:
    XBool *boolResult=nullptr;

};

class XVFUNCSYSTEM_EXPORT BaseDataBoolCalc:public XvFunc
{
    Q_OBJECT
    Q_PROPERTY(BaseDataBoolCalc::EBoolCalaType boolCalaType WRITE setBoolCalaType READ boolCalaType)
    friend class BaseDataBoolCalcWdg;
public:
    Q_INVOKABLE explicit BaseDataBoolCalc(QObject *parent = nullptr);
    ~BaseDataBoolCalc();
public:
    enum EBoolCalaType
    {
        IsEqual=0,  // 等于
        IsNoEqual=1,// 不等于
        And=2,      // &与
        Or=3,       // 或
        Nand=4,     // 与非
        Nor=5,      //或非
        Xor=6,      //异或
        Xnor=7,     //同或
    };
    Q_ENUMS(EBoolCalaType);
    EBoolCalaType boolCalaType() const {return m_boolCalaType;}
    void setBoolCalaType(EBoolCalaType type){ m_boolCalaType=type;}
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/BaseDataBoolCalc.svg");}
    EXvFuncRunStatus run() override;

    XvBaseParam *getParam() const override { return param;};
    XvBaseResult *getResult() const override { return result;};
protected:
    BaseDataBoolCalcParam *param=nullptr;
    BaseDataBoolCalcResult *result=nullptr;
    BaseDataBoolCalcWdg* m_frm=nullptr;
    EBoolCalaType m_boolCalaType=EBoolCalaType::IsEqual;


};
}




#endif // BASEDATABOOLCALC_H
