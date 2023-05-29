#include "HModelMatchWdg.h"
#include "ui_HModelMatchWdg.h"


HModelMatchWdg::HModelMatchWdg(HModelMatch *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::HModelMatchWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}

HModelMatchWdg::~HModelMatchWdg()
{
    delete ui;
}

void HModelMatchWdg::initFrm()
{
    initFixedSize();

}

void HModelMatchWdg::onShow()
{

}
