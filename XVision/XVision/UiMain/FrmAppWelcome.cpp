#include "FrmAppWelcome.h"
#include "ui_FrmAppWelcome.h"
#include "XvSingleApplication.h"

#include <QMovie>

#include <thread>
#include <chrono>

FrmAppWelcome::FrmAppWelcome(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmAppWelcome)
{
    ui->setupUi(this);
    initFrm();
}

FrmAppWelcome::~FrmAppWelcome()
{
    delete ui;
}

void FrmAppWelcome::onShow()
{
    this->show();
}

void FrmAppWelcome::onHide()
{
    this->hide();
}


void FrmAppWelcome::initFrm()
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    auto lb=ui->lbMovie;
    QMovie *pMovie = new QMovie(":/images/App/Loading.gif");
   // lb->setScaledContents(true);
    lb->setMovie(pMovie);
    pMovie->start();

}

