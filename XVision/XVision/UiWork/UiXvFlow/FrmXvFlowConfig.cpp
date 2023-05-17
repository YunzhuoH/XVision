#include "FrmXvFlowConfig.h"
#include "ui_FrmXvFlowConfig.h"
#include "XvFlow.h"
#include "LangDef.h"

FrmXvFlowConfig::FrmXvFlowConfig(XvFlow *flow,QWidget *parent) :
    XFramelessWidget(parent),m_flow(flow),
    ui(new Ui::FrmXvFlowConfig)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

FrmXvFlowConfig::~FrmXvFlowConfig()
{
    delete ui;
}

void FrmXvFlowConfig::initFrm()
{
    if(!m_flow) return;
    this->setWindowTitle(getLang(App_FrmXvFlowConfig_Title,"流程配置")+":"+m_flow->flowName());
    this->setFixedSize(this->centralWidget()->width()+20,this->centralWidget()->height()+10);
    ui->lbFlowLoopInterval->setText(getLang(App_FrmXvFlowConfig_FlowLoopInterval,"循环间隔(ms)")+":");
    ui->ckbFuncErrorInterruptRun->setText(getLang(App_FrmXvFlowConfig_FuncErrorInterruptRun,"算子错误中断运行"));
    auto config=m_flow->getFlowConfig();
    ui->spbFlowLoopInterval->setMinimum(0);
    ui->spbFlowLoopInterval->setMaximum(99999);
    ui->spbFlowLoopInterval->setValue(config->loopInterval);
    ui->ckbFuncErrorInterruptRun->setChecked(config->funcErrorInterruptRun);
    connect(ui->ckbFuncErrorInterruptRun,&XMatCheckBox::toggled,this,[=]()
    {
        auto bRet=ui->ckbFuncErrorInterruptRun->isChecked();
        config->funcErrorInterruptRun=bRet;
    });
    connect(ui->spbFlowLoopInterval,&QSpinBox::valueChanged,this,[=](int)
    {
        auto nVal=ui->spbFlowLoopInterval->value();
        config->loopInterval=nVal;
    });
}

void FrmXvFlowConfig::closeEvent(QCloseEvent *event)
{
    XFramelessWidget::closeEvent(event);
    this->deleteLater();
}
