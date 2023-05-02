#include "BaseDataBoolCalcWdg.h"
#include "ui_BaseDataBoolCalcWdg.h"

BaseDataBoolCalcWdg::BaseDataBoolCalcWdg(BaseDataBoolCalc *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::BaseDataBoolCalcWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

BaseDataBoolCalcWdg::~BaseDataBoolCalcWdg()
{
    delete ui;
}

void BaseDataBoolCalcWdg::initFrm()
{
    this->setFixedSize(390,180);

    auto func=getFunc<BaseDataBoolCalc>();
    if(!func) return;
    auto p1=func->param->boolParam1;
    auto p2=func->param->boolParam2;
    auto r1=func->result->boolResult;

    updateLbTextWithXObject(ui->lbV1,p1,":");
    updateLbTextWithXObject(ui->lbV2,p2,":");
    updateLbTextWithXObject(ui->lbRet,r1,":");

    ui->lbType->setText(getLang("XvFuncSystem_BaseDataBoolCalc_lbType","计算类型")+":");
    auto cmbType=ui->cmbType;
    cmbType->clear();
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeIsEqual","等于"),BaseDataBoolCalc::EBoolCalaType::IsEqual);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeIsNoEqual","不等于"),BaseDataBoolCalc::EBoolCalaType::IsNoEqual);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeAnd","与运算"),BaseDataBoolCalc::EBoolCalaType::And);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeOr","或运算"),BaseDataBoolCalc::EBoolCalaType::Or);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeNand","与非运算"),BaseDataBoolCalc::EBoolCalaType::Nand);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeNor","或非运算"),BaseDataBoolCalc::EBoolCalaType::Nor);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeXor","异或运算"),BaseDataBoolCalc::EBoolCalaType::Xor);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataBoolCalc_EBoolCalaTypeXnor","同或运算"),BaseDataBoolCalc::EBoolCalaType::Xnor);

    auto cmbB1=ui->cmbB1;
    auto cmbB2=ui->cmbB2;
    auto cmbRet=ui->cmbRet;

    auto funcInitCmb=[=](QComboBox* cmb)
    {
        cmb->clear();
        cmb->addItem("False");
        cmb->addItem("True");
    };
    funcInitCmb(cmbB1);
    funcInitCmb(cmbB2);
    funcInitCmb(cmbRet);

    auto funcSetCmb=[=](QComboBox* cmbV,QComboBox* cmbB, const QString &paramName)
    {
        auto idx=cmbV->currentIndex();
        if(idx<0) return;
        if(idx==0)
        {
            if(m_bShowing)
            {
                func->paramUnSubscribe(paramName);
            }
            cmbB->setEnabled(true);
        }
        else
        {
            cmbB->setEnabled(false);
            SBindResultTag tag;
            if(getCmbBindResultTag(cmbV,tag))
            {
                func->paramSubscribe(paramName,tag.func,tag.resultName);
            }

        }
    };

    connect(ui->cmbType,&QComboBox::currentIndexChanged,this,[=]()
    {
       auto idx=ui->cmbType->currentIndex();
       func->setBoolCalaType((BaseDataBoolCalc::EBoolCalaType)idx);
    });

    connect(ui->cmbV1,&QComboBox::currentIndexChanged,this,[=]()
    {
        funcSetCmb(ui->cmbV1,ui->cmbB1,p1->objectName());
    });

    connect(ui->cmbV2,&QComboBox::currentIndexChanged,this,[=]()
    {
        funcSetCmb(ui->cmbV2,ui->cmbB2,p2->objectName());
    });

    connect(ui->cmbB1,&QComboBox::currentIndexChanged,this,[=]()
    {
         auto idx=ui->cmbV1->currentIndex();
         if(idx==0)
         {
             auto idx= ui->cmbB1->currentIndex();
             p1->setValue((bool)idx);
         }
    });
    connect(ui->cmbB2,&QComboBox::currentIndexChanged,this,[=]()
    {
        auto idx=ui->cmbV2->currentIndex();
        if(idx==0)
        {
            auto idx= ui->cmbB2->currentIndex();
            p2->setValue((bool)idx);
        }
    });
}

void BaseDataBoolCalcWdg::onFuncRunUpdate()
{
    auto func=getFunc<BaseDataBoolCalc>();
    if(!func) return;
    auto r1=func->result->boolResult;
    ui->cmbRet->setCurrentIndex(r1->value());
}


void BaseDataBoolCalcWdg::onShow()
{
    auto func=getFunc<BaseDataBoolCalc>();
    if(!func) return;
//cmbV

    auto p1=func->param->boolParam1;
    auto p2=func->param->boolParam2;
    auto r1=func->result->boolResult;
    auto cmbType=ui->cmbType;
    cmbType->setCurrentIndex(func->boolCalaType());

    auto cmbV1=ui->cmbV1;
    auto cmbV2=ui->cmbV2;
    initCmbBindResultTag(func,cmbV1,{XBool::type()},true);
    initCmbBindResultTag(func,cmbV2,{XBool::type()},true);

    XvFunc::SubscribeInfo info1;
    if(func->getParamSubscribe(p1->objectName(),info1))
    {
      setCmbBindResultTag(cmbV1,SBindResultTag(info1.first,info1.second));
    }
    XvFunc::SubscribeInfo info2;
    if(func->getParamSubscribe(p2->objectName(),info2))
    {
      setCmbBindResultTag(cmbV2,SBindResultTag(info2.first,info2.second));
    }
 //cmbB
    auto cmbB1=ui->cmbB1;
    auto cmbB2=ui->cmbB2;
    auto cmbRet=ui->cmbRet;
    cmbB1->setCurrentIndex(p1->value());
    cmbB2->setCurrentIndex(p2->value());
    cmbRet->setCurrentIndex(r1->value());
}
