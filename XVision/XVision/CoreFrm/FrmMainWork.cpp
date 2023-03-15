#include "FrmMainWork.h"
#include "ui_FrmMainWork.h"

FrmMainWork::FrmMainWork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmMainWork)
{
    ui->setupUi(this);
}

FrmMainWork::~FrmMainWork()
{
    delete ui;
}
