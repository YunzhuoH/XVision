#include "BaseDataStringProcessWdg.h"
#include "ui_BaseDataStringProcessWdg.h"

BaseDataStringProcessWdg::BaseDataStringProcessWdg(BaseDataStringProcess *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::BaseDataStringProcessWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

BaseDataStringProcessWdg::~BaseDataStringProcessWdg()
{
    delete ui;
}

void BaseDataStringProcessWdg::initFrm()
{
    initFixedSize();
    auto func=getFunc<BaseDataStringProcess>();
    if(!func) return;



    initCmbByBool(ui->cmbBVal);
    initCmbByBool(ui->cmbRetB);

    updateLbTextWithXObject(ui->lbS1,func->param->stringParam1,":");
    updateLbTextWithXObject(ui->lbS2,func->param->stringParam2,":");
    updateLbTextWithXObject(ui->lbI1,func->param->intParam1,":");
    updateLbTextWithXObject(ui->lbI2,func->param->intParam2,":");
    updateLbTextWithXObject(ui->lbB,func->param->boolParam,":");
    updateLbTextWithXObject(ui->lbR,func->param->realParam,":");


    updateLbTextWithXObject(ui->lbRetB,func->result->boolResult,":");
    updateLbTextWithXObject(ui->lbRetI,func->result->intResult,":");
    updateLbTextWithXObject(ui->lbRetR,func->result->realResult,":");
    updateLbTextWithXObject(ui->lbRetS,func->result->stringResult,":");

    ui->lbProcessType->setText(getLang("XvFuncSystem_BaseDataStringProcess_lbProcessType","字符串操作")+":");
    auto cmbType=ui->cmbProcessType;
    cmbType->clear();
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeIsEqual","等于"),BaseDataStringProcess::EStringProcessType::IsEqual);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeIsNoEqual","不等于"),BaseDataStringProcess::EStringProcessType::IsNoEqual);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeContain","包含"),BaseDataStringProcess::EStringProcessType::Contain);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeAdd","相加"),BaseDataStringProcess::EStringProcessType::Add);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeLeft","左截取"),BaseDataStringProcess::EStringProcessType::Left);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeMid","中截取"),BaseDataStringProcess::EStringProcessType::Mid);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeRight","右截取"),BaseDataStringProcess::EStringProcessType::Right);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeLength","获取长度"),BaseDataStringProcess::EStringProcessType::Length);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeToLower","转为小写"),BaseDataStringProcess::EStringProcessType::ToLower);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeToUpper","转为大写"),BaseDataStringProcess::EStringProcessType::ToUpper);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeTryToBool","转换为布尔量"),BaseDataStringProcess::EStringProcessType::TryToBool);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeTryToInt","转换为整数值"),BaseDataStringProcess::EStringProcessType::TryToInt);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeTryToReal","转换为浮点数"),BaseDataStringProcess::EStringProcessType::TryToReal);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeBoolToString","布尔量转字符串"),BaseDataStringProcess::EStringProcessType::BoolToString);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeIntToString","整数值转字符串"),BaseDataStringProcess::EStringProcessType::IntToString);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataStringProcess_EStringProcessTypeRealToString","浮点数转字符串"),BaseDataStringProcess::EStringProcessType::RealToString);


    connect(ui->cmbProcessType,&QComboBox::currentIndexChanged,this,[=]()
    {
       auto idx=ui->cmbProcessType->currentIndex();
       func->setStringProcessType((BaseDataStringProcess::EStringProcessType)idx);
    });

    connect(ui->cmbS1,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbS1,ui->letS1,func->param->stringParam1->objectName());
    });
    connect(ui->cmbS2,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbS2,ui->letS2,func->param->stringParam2->objectName());
    });
    connect(ui->cmbI1,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbI1,ui->letI1,func->param->intParam1->objectName());
    });
    connect(ui->cmbI2,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbI2,ui->letI2,func->param->intParam2->objectName());
    });
    connect(ui->cmbR,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbR,ui->letR,func->param->realParam->objectName());
    });

    connect(ui->cmbB,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithCmbEnable(ui->cmbB,ui->cmbBVal,func->param->boolParam->objectName());
    });


    connect(ui->letS1,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbS1->currentIndex();
         if(idx==0)
         {
            func->param->stringParam1->setValue(ui->letS1->text());
         }
    });

    connect(ui->letS2,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbS2->currentIndex();
         if(idx==0)
         {
            func->param->stringParam2->setValue(ui->letS2->text());
         }
    });

    connect(ui->letI1,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbI1->currentIndex();
         if(idx==0)
         {
             bool bRet;
             auto val= ui->letI1->text().toInt(&bRet);
             if(bRet)
             {
                func->param->intParam1->setValue(val);
             }
         }
    });

    connect(ui->letI2,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbI2->currentIndex();
         if(idx==0)
         {
             bool bRet;
             auto val= ui->letI2->text().toInt(&bRet);
             if(bRet)
             {
                func->param->intParam2->setValue(val);
             }
         }
    });

    connect(ui->letR,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbR->currentIndex();
         if(idx==0)
         {
             bool bRet;
             auto val= ui->letR->text().toDouble(&bRet);
             if(bRet)
             {
                func->param->realParam->setValue(val);
             }
         }
    });

    connect(ui->cmbBVal,&QComboBox::currentIndexChanged,this,[=](){
         auto idx=ui->cmbB->currentIndex();
         if(idx==0)
         {
             func->param->boolParam->setValue(ui->cmbBVal->currentIndex());
         }
    });
}

void BaseDataStringProcessWdg::onFuncRunUpdate()
{
    auto func=getFunc<BaseDataStringProcess>();
    if(!func) return;
    ui->cmbRetB->setCurrentIndex(func->result->boolResult->value());
    ui->letRetI->setText(func->result->intResult->toString());
    ui->letRetR->setText(func->result->realResult->toString());
    ui->letRetS->setText(func->result->stringResult->toString());
}

void BaseDataStringProcessWdg::onShow()
{
    auto func=getFunc<BaseDataStringProcess>();
    if(!func) return;

//cmb

    auto cmbType=ui->cmbProcessType;
    cmbType->setCurrentIndex(func->stringProcessType());


    initCmbBindResultTag(func,ui->cmbS1,{XString::type()},true);
    initCmbBindResultTag(func,ui->cmbS2,{XString::type()},true);
    initCmbBindResultTag(func,ui->cmbI1,{XInt::type()},true);
    initCmbBindResultTag(func,ui->cmbI2,{XInt::type()},true);
    initCmbBindResultTag(func,ui->cmbB,{XBool::type()},true);
    initCmbBindResultTag(func,ui->cmbR,{XInt::type(),XReal::type()},true);

    setCmbBind(func->param->stringParam1,ui->cmbS1);
    setCmbBind(func->param->stringParam2,ui->cmbS2);
    setCmbBind(func->param->intParam1,ui->cmbI1);
    setCmbBind(func->param->intParam2,ui->cmbI2);
    setCmbBind(func->param->boolParam,ui->cmbB);
    setCmbBind(func->param->realParam,ui->cmbR);


 //let
    ui->letS1->setText(func->param->stringParam1->toString());
    ui->letS2->setText(func->param->stringParam2->toString());
    ui->letI1->setText(func->param->intParam1->toString());
    ui->letI2->setText(func->param->intParam2->toString());
    ui->cmbBVal->setCurrentIndex(func->param->boolParam->value());
    ui->letR->setText(func->param->realParam->toString());
    onFuncRunUpdate();

}
