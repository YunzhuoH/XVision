#include "DelayerWdg.h"
#include "ui_DelayerWdg.h"

DelayerWdg::DelayerWdg(Delayer *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::DelayerWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

DelayerWdg::~DelayerWdg()
{
    delete ui;
}

void DelayerWdg::initFrm()
{
    this->setFixedSize(390,80);

    auto func=getFunc<Delayer>();
    if(!func) return;
    auto ms=func->param->dealyMs;
    ui->lbDelay->setText(ms->dispalyName()+":");

    auto funcSetCmb=[=](QComboBox* cmbV,QLineEdit* let, const QString &paramName)
    {
        auto idx=cmbV->currentIndex();
        if(idx<0) return;
        if(idx==0)
        {
            if(m_bShowing)
            {
                func->paramUnSubscribe(paramName);
            }
            let->setEnabled(true);
        }
        else
        {
            let->setEnabled(false);
            SBindResultTag tag;
            if(getCmbBindResultTag(cmbV,tag))
            {
                func->paramSubscribe(paramName,tag.func,tag.resultName);
            }

        }
    };



    connect(ui->cmbDelay,&QComboBox::currentIndexChanged,this,[=]()
    {
        funcSetCmb(ui->cmbDelay,ui->letDelay,ms->objectName());
    });

    connect(ui->letDelay,&QLineEdit::textChanged,this,[=]()
    {
        auto idx=ui->cmbDelay->currentIndex();
        if(idx==0)
        {
           bool bRet=false;
           auto newMs=ui->letDelay->text().toInt(&bRet);
           if(bRet)
           {
               ms->setValue(newMs);
           }
        }
    });
}

void DelayerWdg::onShow()
{
    auto func=getFunc<Delayer>();
    if(!func) return;
//cmb

    auto ms=func->param->dealyMs;

    auto cmbDelay=ui->cmbDelay;
    initCmbBindResultTag(func,cmbDelay,{XInt::type()});

    XvFunc::SubscribeInfo info;
    if(func->getParamSubscribe(ms->objectName(),info))
    {
      setCmbBindResultTag(cmbDelay,SBindResultTag(info.first,info.second));
    }

 //let
    auto letDelay=ui->letDelay;
    letDelay->setText(ms->toString());
}
