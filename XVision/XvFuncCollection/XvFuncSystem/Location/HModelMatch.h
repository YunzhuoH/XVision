#ifndef HMODELMATCH_H
#define HMODELMATCH_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class HModelMatchWdg;
namespace XvCore
{
class HModelMatchParam:public XvBaseParam
{
public:
    HModelMatchParam()
    {
        inputImage=new XImage("inputImage",QImage(),this,getLang("XvFuncSystem_HModelMatch_InputImage","输入图像"));
    }
public:
    XImage *inputImage=nullptr;

};

class HModelMatchResult:public XvBaseResult
{
public:
    HModelMatchResult()
    {

    }
public:


};

class XVFUNCSYSTEM_EXPORT HModelMatch:public XvFunc
{
    Q_OBJECT
    friend class HModelMatchWdg;
public:
    Q_INVOKABLE explicit HModelMatch(QObject *parent = nullptr);
    ~HModelMatch();
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/HModelMatch.svg");}
    EXvFuncRunStatus run() override;
    XvBaseParam *getParam() const override { return param;};
    XvBaseResult *getResult() const override { return result;};
protected:
    HModelMatchParam *param=nullptr;
    HModelMatchResult *result=nullptr;
    HModelMatchWdg* m_frm=nullptr;




};
}



#endif // HMODELMATCH_H
