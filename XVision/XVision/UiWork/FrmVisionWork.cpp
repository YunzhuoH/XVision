#include "FrmVisionWork.h"
#include "ui_FrmVisionWork.h"
#include <QMutexLocker>
#include <QHBoxLayout>

#include "UiXvFlowManager.h"
#include "XvViewManager.h"
#include "FrmXvFuncAsm.h"


FrmVisionWork *FrmVisionWork::s_Instance = NULL;
FrmVisionWork *FrmVisionWork::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new FrmVisionWork();
    }
  }
  return s_Instance;
}



FrmVisionWork::FrmVisionWork(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmVisionWork)
{
    ui->setupUi(this);
    initFrm();
}

FrmVisionWork::~FrmVisionWork()
{
    delete ui;
}

void FrmVisionWork::initFrm()
{

    this->setWindowIcon(QIcon(":/images/Ui/FrmVisionWork.svg"));
    this->setWindowTitle(getLang(App_Ui_FrmVisionWorkTitle,"视觉流程"));

    ///初始化左侧算子工具栏模块
    auto frmXvFuncAsm=ui->frmXvFuncAsm;
    m_frmXvFuncAsm=new FrmXvFuncAsm(this);
    m_frmXvFuncAsm->setDrawerParWidget(ui->frmFlow);

    QVBoxLayout *vLayoutXvFuncAsm = new QVBoxLayout(frmXvFuncAsm);
    vLayoutXvFuncAsm->setObjectName("vLayoutXvFuncAsm");
    vLayoutXvFuncAsm->setContentsMargins(0, 0, 0, 0);
    vLayoutXvFuncAsm->setSpacing(0);
    frmXvFuncAsm->setLayout(vLayoutXvFuncAsm);
    frmXvFuncAsm->setMinimumWidth(m_frmXvFuncAsm->minimumWidth());
    frmXvFuncAsm->setMaximumWidth(m_frmXvFuncAsm->maximumWidth());
    vLayoutXvFuncAsm->addWidget(m_frmXvFuncAsm);

    ///初始化流程窗口
    auto frmFlow=ui->frmFlow;
    QVBoxLayout *vLayoutFlow = new QVBoxLayout(frmFlow);
    vLayoutFlow->setObjectName("vLayoutFlow");
    vLayoutFlow->setContentsMargins(0, 0, 0, 0);
    vLayoutFlow->setSpacing(0);
    auto dockMgr=XvViewMgr->getUiXvFlowManager();
    if(dockMgr)
    {
        auto dockMain=dockMgr->dockFlowManager();
        if(dockMain)
        {
            dockMain->setParent(this);
            vLayoutFlow->addWidget(dockMain);
        }
        else
        {
           Log_Critical(getLang(App_XvFlowDockIsNull,"XvFlowDock为空"));
        }

        auto statusBar=dockMgr->dockStatusBar();
        if(statusBar)
        {
            statusBar->setParent(this);
            vLayoutFlow->addWidget(statusBar);
        }
        else
        {
           Log_Critical(getLang(App_XvFlowStatusBarIsNull,"XvFlow状态栏为空"));
        }
    }

}
