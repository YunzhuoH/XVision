#include "ImageAcquisitionWdg.h"
#include "ui_ImageAcquisitionWdg.h"
#include <QFileDialog>
#include "XMatTabs.h"
#include "ImageAcquisition_p.h"

ImageAcquisitionWdg::ImageAcquisitionWdg(ImageAcquisition *func,QWidget *parent) :
    BaseSystemFuncWdg(func,parent),
    ui(new Ui::ImageAcquisitionWdg)
{
    ui->setupUi(this->centralWidget());
    initFrm();
}



ImageAcquisitionWdg::~ImageAcquisitionWdg()
{
    delete ui;
}

void ImageAcquisitionWdg::initFrm()
{
    initFixedSize();

    auto func=getFunc<ImageAcquisition>();
    if(!func) return;

    auto lyWdg= (QVBoxLayout*)this->centralWidget()->layout();
    if(!lyWdg) return;

    m_tabs=new XMatTabs(this);
    m_tabs->setObjectName("tabsAcqType");
    m_tabs->setHaloVisible(false);
    m_tabs->addTab(getLang("XvFuncSystem_ImageAcquisitionc_AcqTypeFile","文件"));
    m_tabs->addTab(getLang("XvFuncSystem_ImageAcquisitionc_AcqTypeDir","目录"));
    m_tabs->addTab(getLang("XvFuncSystem_ImageAcquisitionc_AcqTypeCamera","相机"));
    lyWdg->insertWidget(0,m_tabs);
    connect(m_tabs,&XMatTabs::currentChanged,this,[=]()
    {
        int idx=m_tabs->currentIndex();
        if(idx<0||idx>2)
        {
            return;
        }
        ui->staWdg->setCurrentIndex(idx);
        func->setAcqType(ImageAcquisition::AcqType(idx));
    });


    ui->btnLocalImageOpen->setText(getLang("XvFuncSystem_ImageAcquisitionc_OpenFile","打开文件"));
    ui->btnLocalDirOpen->setText(getLang("XvFuncSystem_ImageAcquisitionc_OpenDir","打开目录"));
    ui->btnLocalDirLast->setToolTip(getLang("XvFuncSystem_ImageAcquisitionc_LastImage","上一张"));
    ui->btnLocalDirLast->setIcon(QIcon(":/images/ImageAcquisitionWdgDirLast.svg"));
    ui->btnLocalDirNext->setToolTip(getLang("XvFuncSystem_ImageAcquisitionc_NextImage","下一张"));
    ui->btnLocalDirNext->setIcon(QIcon(":/images/ImageAcquisitionWdgDirNext.svg"));

    connect(ui->btnLocalImageOpen,&QAbstractButton::clicked,this,[=]()
    {
        QString openFile;
        openFile = QFileDialog::getOpenFileName(this,
                "",
                "",
                "Image Files(*.*)");
        if(openFile != "")
        {
            func->setLocalFile(openFile);
            ui->ptxLocalImage->setPlainText(openFile);
        }
    });

    connect(ui->btnLocalDirOpen,&QAbstractButton::clicked,this,[=]()
    {
        QString openDir = QFileDialog::getExistingDirectory(this,"","");
        if(openDir != "")
        {
            func->setLocalDir(openDir);
            ui->ptxLocalDir->setPlainText(openDir);
        }
    });


    connect(ui->btnLocalDirLast,&QAbstractButton::clicked,this,[=]()
    {
        int idx=func->m_sDirImage->getIdx();
        func->m_sDirImage->setIdx(idx-1);
        func->runXvFunc();
        idx=func->m_sDirImage->getIdx();
        func->m_sDirImage->setIdx(idx-1);
    });

    connect(ui->btnLocalDirNext,&QAbstractButton::clicked,this,[=]()
    {
        int idx=func->m_sDirImage->getIdx();
        func->m_sDirImage->setIdx(idx+1);
        func->runXvFunc();
        idx=func->m_sDirImage->getIdx();
        func->m_sDirImage->setIdx(idx-1);
    });
}

void ImageAcquisitionWdg::onShow()
{
    auto func=getFunc<ImageAcquisition>();
    if(!func) return;
    auto acqType=func->acqType();
    m_tabs->setCurrentTab(acqType);
    ui->ptxLocalImage->setPlainText(func->localFlie());
    ui->ptxLocalDir->setPlainText(func->localDir());
}



