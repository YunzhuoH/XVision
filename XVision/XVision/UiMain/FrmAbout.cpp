#include "FrmAbout.h"
#include "ui_FrmAbout.h"
#include "LangDef.h"

FrmAbout::FrmAbout(QWidget *parent) :
    XFramelessDialog(parent),
    ui(new Ui::FrmAbout)
{
    ui->setupUi(this->centralWidget());
    this->setWindowTitle(getLang(App_Ui_FrmAbout,"关于"));
}

FrmAbout::~FrmAbout()
{
    delete ui;
}
