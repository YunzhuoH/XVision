#include "FrmXvFuncResult.h"
#include "ui_FrmXvFuncResult.h"
#include <QMutexLocker>
#include "XMatScrollBar.h"

#include "XvViewManager.h"
#include "UiXvWorkManager.h"

#include "XvFunc.h"
#include "XvCoreHelper.h"

using namespace XvCore;
FrmXvFuncResult *FrmXvFuncResult::s_Instance = NULL;
FrmXvFuncResult *FrmXvFuncResult::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new FrmXvFuncResult();
    }
  }
  return s_Instance;
}


FrmXvFuncResult::FrmXvFuncResult(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmXvFuncResult)
{
    ui->setupUi(this);
    initFrm();
}

FrmXvFuncResult::~FrmXvFuncResult()
{
    delete ui;
}

void FrmXvFuncResult::initFrm()
{
    this->setWindowIcon(QIcon(":/images/Ui/FrmXvFuncResult.svg"));
    this->setWindowTitle(getLang(App_Ui_FrmXvFuncResult,"算子结果"));

    auto tb=ui->tbwXvFuncResult;
    //自适应宽度
    tb->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //使行列头自适应宽度，最后一列将会填充空白部分
    tb->horizontalHeader()->setStretchLastSection(true);
    tb->verticalHeader()->setVisible(false);
    //设置行选中
    tb->setSelectionBehavior(QAbstractItemView::SelectRows);
    tb->setSelectionMode(QAbstractItemView::SingleSelection);
    //禁止编辑
    tb->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置右键菜单
    tb->setContextMenuPolicy(Qt::NoContextMenu);
    //设置隔行变色
    tb->setAlternatingRowColors(true);
    auto bar=new XMatScrollBar(tb);
    bar->setHideOnMouseOut(false);
    tb->setVerticalScrollBar(bar);

    QStringList  lstHeader;
    lstHeader.clear();
    lstHeader<<getLang(App_Ui_FrmXvFuncResultIdx,"序号")
             <<getLang(App_Ui_FrmXvFuncResultName,"参数名称")
               <<getLang(App_Ui_FrmXvFuncResultVal,"当前值");

    tb->setColumnCount(lstHeader.count());
    tb->setHorizontalHeaderLabels(lstHeader);

    auto uiWorkMgr=XvViewMgr->uiXvWorkManager();
    if(!uiWorkMgr)
    {
        Log_Critical("FrmXvFuncResult::initFrm:uiXvWorkManager==nullptr");
    }
    else
    {
        connect(uiWorkMgr,&UiXvWorkManager::sgFlowSceneMouseClickWithXvFunc,this,&FrmXvFuncResult::onUpdateXvFunc);
    }
}


void FrmXvFuncResult::onUpdateXvFunc(XvFunc *func)
{
    if(!func)
    {
       return;
    }
    if(m_curFunc)
    {
        disconnect(m_curFunc,&XvFunc::sgFuncRunEnd,this,&FrmXvFuncResult::onUpdateXvFuncResult);
    }
    m_curFunc=func;
    connect(m_curFunc,&XvFunc::sgFuncRunEnd,this,&FrmXvFuncResult::onUpdateXvFuncResult);
    connect(m_curFunc,&XvFunc::destroyed,this,[=]()
    {
        m_curFunc=nullptr;
    });
    onUpdateXvFuncResult();
}


void FrmXvFuncResult::onUpdateXvFuncResult()
{
    auto func=m_curFunc;
    if(!func) return;
    static QMap<EXvFuncRunStatus,QString> map=XvCoreHelper::getXvFuncRunStatusLang();
    auto funcNewItem=[&](const QString &text)
    {
        auto  item=new QTableWidgetItem(text);
        item->setText(text);
        item->setToolTip(text);
        return item;
    };

    auto funcSetItemText=[&](QTableWidget* tb, int nRow,const QString &name,const QString &val)
    {
        tb->setItem(nRow,0,funcNewItem(QString::number(nRow+1)));
        tb->setItem(nRow,1,funcNewItem(name));
        tb->setItem(nRow,2,funcNewItem(val));

    };

    auto tb=ui->tbwXvFuncResult;
    auto results=func->getResult();
    int nRetCount=0;
    if(results)
    {
        nRetCount=results->childObjects().count();
    }
    tb->setRowCount(2+nRetCount);

    funcSetItemText(tb,0,getLang(App_Ui_FrmXvFuncResultFuncName,"算子名称") ,func->funcName());
    funcSetItemText(tb,1,getLang(App_Ui_FrmXvFuncResultFuncStatus,"算子状态") ,map[func->getXvFuncRunStatus()]);
    if(results)
    {
        for (int i = 0; i < results->childObjects().count(); ++i)
        {
            auto ret=results->childObjects()[i];
            funcSetItemText(tb,i+2,ret->dispalyName(),ret->toString());
        }

    }
}
