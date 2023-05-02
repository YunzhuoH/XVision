#include "BaseDataWriterWdg.h"
#include "ui_BaseDataWriterWdg.h"

using namespace XvCore;
BaseDataWriterWdg::BaseDataWriterWdg(BaseDataWriter *fun,QWidget *parent) :
    BaseSystemFuncWdg(fun,parent),
    ui(new Ui::BaseDataWriterWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

BaseDataWriterWdg::~BaseDataWriterWdg()
{
    delete ui;
}

void BaseDataWriterWdg::initFrm()
{
    this->setFixedSize(300,160);
    auto func=getFunc<BaseDataWriter>();
    if(!func) return;
    auto rBool=func->result->boolResult;
    auto rInt=func->result->intResult;
    auto rReal=func->result->realResult;
    auto rString=func->result->stringResult;

    updateLbTextWithXObject(ui->lbBool,rBool,":");
    updateLbTextWithXObject(ui->lbInt,rInt,":");
    updateLbTextWithXObject(ui->lbReal,rReal,":");
    updateLbTextWithXObject(ui->lbString,rString,":");


    ui->cmbBool->clear();
    ui->cmbBool->addItem("False");
    ui->cmbBool->addItem("True");

    connect(ui->cmbBool,&QComboBox::currentIndexChanged,this,[=](){
        rBool->setValue(ui->cmbBool->currentIndex());
    });
    connect(ui->letInt,&QLineEdit::textChanged,this,[=]()
    {
        bool bOk=false;
        int val=ui->letInt->text().toInt(&bOk);
        if(bOk)
        {
           rInt->setValue(val);
        }

    });
    connect(ui->letReal,&QLineEdit::textChanged,this,[=]()
    {
        bool bOk=false;
        double val=ui->letReal->text().toDouble(&bOk);
        if(bOk)
        {
           rReal->setValue(val);
        }
    });
    connect(ui->letString,&QLineEdit::textChanged,this,[=]()
    {
        rString->setValue(ui->letString->text());
    });

}

void BaseDataWriterWdg::onShow()
{
    auto result=getFunc<BaseDataWriter>()->result;
    ui->cmbBool->setCurrentIndex(result->boolResult->value());
    ui->letInt->setText(QString("%1").arg(result->intResult->value()));
    ui->letReal->setText(QString("%1").arg(result->realResult->value()));
    ui->letString->setText(QString("%1").arg(result->stringResult->value()));
}
