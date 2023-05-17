#include "BaseDataIntCalcWdg.h"
#include "ui_BaseDataIntCalcWdg.h"

BaseDataIntCalcWdg::BaseDataIntCalcWdg(BaseDataIntCalc *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::BaseDataIntCalcWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

BaseDataIntCalcWdg::~BaseDataIntCalcWdg()
{
    delete ui;
}

void BaseDataIntCalcWdg::initFrm()
{
    initFixedSize();

    auto func=getFunc<BaseDataIntCalc>();
    if(!func) return;
    auto p1=func->param->intParam1;
    auto p2=func->param->intParam2;
    auto r1=func->result->intResult;

    updateLbTextWithXObject(ui->lbV1,p1,":");
    updateLbTextWithXObject(ui->lbV2,p2,":");
    updateLbTextWithXObject(ui->lbRet,r1,":");

    ui->lbType->setText(getLang("XvFuncSystem_BaseDataIntCalc_lbType","计算类型")+":");
    auto cmbType=ui->cmbType;
    cmbType->clear();
    cmbType->addItem(getLang("XvFuncSystem_BaseDataIntCalc_EIntCalaTypeAdd","加法"),BaseDataIntCalc::EIntCalaType::Add);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataIntCalc_EIntCalaTypeSub","减法"),BaseDataIntCalc::EIntCalaType::Sub);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataIntCalc_EIntCalaTypeMul","乘法"),BaseDataIntCalc::EIntCalaType::Mul);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataIntCalc_EIntCalaTypeDiv","除法"),BaseDataIntCalc::EIntCalaType::Div);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataIntCalc_EIntCalaTypeSelfAdd","自加"),BaseDataIntCalc::EIntCalaType::SelfAdd);
    cmbType->addItem(getLang("XvFuncSystem_BaseDataIntCalc_EIntCalaTypeSelfSub","自减"),BaseDataIntCalc::EIntCalaType::SelfSub);


    connect(ui->cmbType,&QComboBox::currentIndexChanged,this,[=]()
    {
       auto idx=ui->cmbType->currentIndex();
       func->setIntCalaType((BaseDataIntCalc::EIntCalaType)idx);
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
             auto val= ui->letV1->text().toInt(&bRet);
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
             auto val= ui->letV2->text().toInt(&bRet);
             if(bRet)
             {
                p2->setValue(val);
             }
         }
    });
}

void BaseDataIntCalcWdg::onFuncRunUpdate()
{
    auto func=getFunc<BaseDataIntCalc>();
    if(!func) return;
    auto r1=func->result->intResult;
    ui->letRet->setText(r1->toString());
}


void BaseDataIntCalcWdg::onShow()
{
    auto func=getFunc<BaseDataIntCalc>();
    if(!func) return;
//cmb
    auto p1=func->param->intParam1;
    auto p2=func->param->intParam2;
    auto r1=func->result->intResult;
    auto cmbType=ui->cmbType;
    cmbType->setCurrentIndex(func->intCalaType());

    auto cmbV1=ui->cmbV1;
    auto cmbV2=ui->cmbV2;
    initCmbBindResultTag(func,cmbV1,{XInt::type()},true);
    initCmbBindResultTag(func,cmbV2,{XInt::type()},true);

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
    letRet->setText(func->result->intResult->toString());
}
