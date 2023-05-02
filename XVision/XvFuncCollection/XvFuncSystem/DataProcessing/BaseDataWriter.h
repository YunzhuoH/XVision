#ifndef BASEDATAWRITER_H
#define BASEDATAWRITER_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class BaseDataWriterWdg;
namespace XvCore
{
class BaseDataWriterResult:public XvBaseResult
{
public:
    BaseDataWriterResult()
    {
        boolResult=new XBool("boolResult",false,this,getLang("XvFuncSystem_BaseDataWriter_BoolResult","布尔量"));
        intResult=new XInt("intResult",0,this,getLang("XvFuncSystem_BaseDataWriter_IntResult","整数值"));
        realResult=new XReal("realResult",0,this,getLang("XvFuncSystem_BaseDataWriter_RealResult","浮点值"));
        stringResult=new XString("stringResult","",this,getLang("XvFuncSystem_BaseDataWriter_StringResult","字符串"));
    }
public:
    XBool *boolResult=nullptr;

    XInt *intResult=nullptr;

    XReal *realResult=nullptr;

    XString *stringResult=nullptr;
};

class XVFUNCSYSTEM_EXPORT BaseDataWriter:public XvFunc
{
    Q_OBJECT
    friend class BaseDataWriterWdg;
public:
    Q_INVOKABLE explicit BaseDataWriter(QObject *parent = nullptr);
    ~BaseDataWriter();
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/BaseDataWriter.svg");}
    EXvFuncRunStatus run() override;
    XvBaseResult *getResult() const override { return result;};
protected:
    BaseDataWriterResult *result=nullptr;
    BaseDataWriterWdg* m_frm=nullptr;
};
}



#endif // BASEDATAWRITER_H
