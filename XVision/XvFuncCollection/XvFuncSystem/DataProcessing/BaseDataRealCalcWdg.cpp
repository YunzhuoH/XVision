#include "BaseDataRealCalcWdg.h"
#include "ui_BaseDataRealCalcWdg.h"

BaseDataRealCalcWdg::BaseDataRealCalcWdg(BaseDataRealCalc *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::BaseDataRealCalcWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

BaseDataRealCalcWdg::~BaseDataRealCalcWdg()
{
    delete ui;
}

void BaseDataRealCalcWdg::initFrm()
{
    initFixedSize();
    auto func=getFunc<BaseDataRealCalc>();
    if(!func) return;
    auto p1=func->param->realParam1;
    auto p2=func->param->realParam2;
    auto r1=func->result->realResult;

    updateLbTextWithXObject(ui->lbV1,p1,":");
    updateLbTextWithXObject(ui->lbV2,p2,":");
    updateLbTextWithXObject(ui->lbRet,r1,":");

    ui->lbType->setText(getLang("XvFuncSystem_BaseDataRealCalc_lbType","计算类型")+":");
    auto cmbType=ui->cmbType;
    cmbType->clear();
    cmbType->addItem(getLang("XvFuncSystem_BaseDataRealCalc_ERealCalaTypeAdd","加法"),BaseDataRealCalc::ERealCalaType::Add);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataRealCalc_ERealCalaTypeSub","减法"),BaseDataRealCalc::ERealCalaType::Sub);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataRealCalc_ERealCalaTypeMul","乘法"),BaseDataRealCalc::ERealCalaType::Mul);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataRealCalc_ERealCalaTypeDiv","除法"),BaseDataRealCalc::ERealCalaType::Div);

    connect(ui->cmbType,&QComboBox::currentIndexChanged,this,[=]()
    {
       auto idx=ui->cmbType->currentIndex();
       func->setRealCalaType((BaseDataRealCalc::ERealCalaType)idx);
    });

    connect(ui->cmbV1,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbV1,ui->letV1,p1->objectName());
    });

    connect(ui->cmbV2,&QComboBox::currentIndexChanged,this,[=]()
    {
        setCmbWithLetEnable(ui->cmbV2,ui->letV2,p2->objectName());
    });

    connect(ui->letV1,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbV1->currentIndex();
         if(idx==0)
         {
             bool bRet;
             auto val= ui->letV1->text().toDouble(&bRet);
             if(bRet)
             {
                p1->setValue(val);
             }
         }
    });
    connect(ui->letV2,&QLineEdit::textChanged,this,[=](){
         auto idx=ui->cmbV2->currentIndex();
         if(idx==0)
         {
             bool bRet;
             auto val= ui->letV2->text().toDouble(&bRet);
             if(bRet)
             {
                p2->setValue(val);
             }
         }
    });
}

void BaseDataRealCalcWdg::onFuncRunUpdate()
{
    auto func=getFunc<BaseDataRealCalc>();
    if(!func) return;
    auto r1=func->result->realResult;
    ui->letRet->setText(r1->toString());
}

void BaseDataRealCalcWdg::onShow()
{
    auto func=getFunc<BaseDataRealCalc>();
    if(!func) return;
//cmb
    auto p1=func->param->realParam1;
    auto p2=func->param->realParam2;
    auto r1=func->result->realResult;
    auto cmbType=ui->cmbType;
    cmbType->setCurrentIndex(func->realCalaType());

    auto cmbV1=ui->cmbV1;
    auto cmbV2=ui->cmbV2;
    initCmbBindResultTag(func,cmbV1,{XReal::type(),XInt::type()},true);
    initCmbBindResultTag(func,cmbV2,{XReal::type(),XInt::type()},true);

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
 //let
    auto letV1=ui->letV1;
    auto letV2=ui->letV2;
    auto letRet=ui->letRet;
    letV1->setText(p1->toString());
    letV2->setText(p2->toString());
    letRet->setText(r1->toString());
}
