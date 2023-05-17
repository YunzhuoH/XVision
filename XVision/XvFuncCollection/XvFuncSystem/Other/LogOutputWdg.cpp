#include "LogOutputWdg.h"
#include "ui_LogOutputWdg.h"
#include <QMetaEnum>
#include <XLogger>

LogOutputWdg::LogOutputWdg(LogOutput *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::LogOutputWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

LogOutputWdg::~LogOutputWdg()
{
    delete ui;
}

void LogOutputWdg::initFrm()
{
    initFixedSize();
    auto func=getFunc<LogOutput>();
    if(!func) return;
    auto cmbLogTypeVal=ui->cmbLogTypeVal;
    QMetaEnum meta = QMetaEnum::fromType<XLogger::ELogType>();
    cmbLogTypeVal->clear();
    for (int i = XLOG_LEVEL_TRACE; i <= XLOG_LEVEL_CRITICAL; ++i)
    {
        cmbLogTypeVal->addItem(meta.valueToKey(i),XLogger::ELogType(i));
    }
    
    auto type=func->param->outputType;
    auto msg=func->param->outputMsg;
    ui->lbLogType->setText(type->dispalyName()+":");
    ui->lbMsg->setText(msg->dispalyName()+":");
    
    connect(ui->cmbLogTypeBind,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithCmbEnable(ui->cmbLogTypeBind,ui->cmbLogTypeVal,type->objectName());
    });

    connect(ui->cmbLogTypeVal,&QComboBox::currentIndexChanged,this,[=]()
    {
        auto idx=ui->cmbLogTypeBind->currentIndex();
        if(idx==0)
        {
            auto idx= ui->cmbLogTypeVal->currentIndex();
            type->setValue((int)idx);
        }
    });

    connect(ui->cmbMsg,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithPetEnable(ui->cmbMsg,ui->ptxMsg,msg->objectName());
    });
    connect(ui->ptxMsg,&QPlainTextEdit::textChanged,this,[=]()
    {
        auto idx=ui->cmbMsg->currentIndex();
        if(idx==0)
        {
            auto str= ui->ptxMsg->document()->toPlainText();
            msg->setValue(str);
        }

    });

}

void LogOutputWdg::onShow()
{
    auto func=getFunc<LogOutput>();
    if(!func) return;

//bind
   auto type=func->param->outputType;
   auto msg=func->param->outputMsg;
   auto cmbLogTypeBind=ui->cmbLogTypeBind;
   auto cmbMsg=ui->cmbMsg;
   initCmbBindResultTag(func,cmbLogTypeBind,{XInt::type()},true);
   initCmbBindResultTag(func,cmbMsg,{XString::type()},true);
   XvFunc::SubscribeInfo info;
   if(func->getParamSubscribe(type->objectName(),info))
   {
     setCmbBindResultTag(cmbLogTypeBind,SBindResultTag(info.first,info.second));
   }
   if(func->getParamSubscribe(msg->objectName(),info))
   {
     setCmbBindResultTag(cmbMsg,SBindResultTag(info.first,info.second));
   }
//val
   auto cmbLogTypeVal=ui->cmbLogTypeVal;
   int idx=-1;
   if(type->value()>=XLOG_LEVEL_TRACE&&type->value()<=XLOG_LEVEL_CRITICAL)
   {
       idx=type->value();
   }
   cmbLogTypeVal->setCurrentIndex(idx);

   auto ptxMsg=ui->ptxMsg;
   ptxMsg->setPlainText(msg->value());
}
