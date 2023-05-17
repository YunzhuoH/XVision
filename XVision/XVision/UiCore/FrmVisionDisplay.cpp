#include "FrmVisionDisplay.h"
#include "ui_FrmVisionDisplay.h"
#include <QMutexLocker>
#include <QVBoxLayout>

#include "XvViewManager.h"

#include "UiXvDisplayManager.h"
#include "XMatToolBar.h"
#include "XvDisplayView.h"


FrmVisionDisplay *FrmVisionDisplay::s_Instance = NULL;
FrmVisionDisplay *FrmVisionDisplay::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new FrmVisionDisplay();
    }
  }
  return s_Instance;
}


FrmVisionDisplay::FrmVisionDisplay(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmVisionDisplay)
{
    ui->setupUi(this);
    initFrm();
}

FrmVisionDisplay::~FrmVisionDisplay()
{
    delete ui;
}

void FrmVisionDisplay::initFrm()
{
    this->setWindowIcon(QIcon(":/images/Ui/FrmVisionDisplay.svg"));
    this->setWindowTitle(getLang(App_Ui_FrmVisionDisplay,"图像显示"));

    QVBoxLayout *vLayoutDisplay = new QVBoxLayout(this);
    vLayoutDisplay->setObjectName("vLayoutDisplay");
    vLayoutDisplay->setContentsMargins(0, 0, 0, 0);
    vLayoutDisplay->setSpacing(0);

    auto displayMgr=XvViewMgr->uiXvDisplayManager();
    if(displayMgr)
    {
        auto toolBar=displayMgr->displayToolBar();
        if(toolBar)
        {
            toolBar->setParent(this);
            vLayoutDisplay->addWidget(toolBar);
        }
        else
        {
           Log_Critical(getLang(App_XvDisplayToolBarIsNull,"显示工具栏为空"));
        }

        auto view=displayMgr->displayView();
        if(view)
        {
            view->setParent(this);
            vLayoutDisplay->addWidget(view);
        }
        else
        {
           Log_Critical(getLang(App_XvDisplayViewIsNull,"显示视图为空"));
        }

    }

}
