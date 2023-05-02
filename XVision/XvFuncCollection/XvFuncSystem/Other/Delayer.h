#ifndef DELAYER_H
#define DELAYER_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class DelayerWdg;

namespace XvCore
{
class DelayerParam:public XvBaseParam
{
public:
    DelayerParam()
    {
        dealyMs=new XInt("dealyMs",1000,this,getLang("XvFuncSystem_Delayer_DealyMs","延迟时间(ms)"));
    }
public:
    XInt *dealyMs=nullptr;

};


class XVFUNCSYSTEM_EXPORT Delayer:public XvFunc
{
    Q_OBJECT
    friend class DelayerWdg;
public:
    Q_INVOKABLE explicit Delayer(QObject *parent = nullptr);
    ~Delayer();
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/Delayer.svg");}
    EXvFuncRunStatus run() override;
    XvBaseParam *getParam() const override { return param;};
protected:
    DelayerParam *param=nullptr;
    DelayerWdg* m_frm=nullptr;



};
}


#endif // DELAYER_H
