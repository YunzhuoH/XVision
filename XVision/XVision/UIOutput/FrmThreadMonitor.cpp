#include "FrmThreadMonitor.h"
#include "ui_FrmThreadMonitor.h"
#include <QMutexLocker>
#include "XConcurrentManager.h"
#include "XMatScrollBar.h"
//定时器间隔
#define Timer_Interval          50

//列表索引
#define ColIdx_ThreadId         0
#define ColIdx_ThreadGroup      1
#define ColIdx_ThreadName       2
#define ColIdx_ThreadPriority   3
#define ColIdx_ThreadRunElapsed 4
#define ColIdx_ThreadRunState   5
#define ColIdx_ThreadMsg        6

FrmThreadMonitor *FrmThreadMonitor::s_Instance = NULL;
FrmThreadMonitor *FrmThreadMonitor::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new FrmThreadMonitor();
    }
  }
  return s_Instance;
}



FrmThreadMonitor::FrmThreadMonitor(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmThreadMonitor)
{
    ui->setupUi(this);
    initFrm();
}

FrmThreadMonitor::~FrmThreadMonitor()
{
    delete ui;
}

void FrmThreadMonitor::initFrm()
{
    this->setWindowIcon(QIcon(":/images/Ui/FrmThreadMonitor.svg"));
    this->setWindowTitle(getLang(App_Ui_FrmThreadMonitor,"线程监控"));
//初始化tablewidget
    auto tb=ui->tbwThreadMonitor;
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
    lstHeader<<getLang(App_Ui_FrmThreadMonitorThreadId,"线程Id")
             <<getLang(App_Ui_FrmThreadMonitorThreadGroup,"线程组")
               <<getLang(App_Ui_FrmThreadMonitorThreadName,"线程名")
                 <<getLang(App_Ui_FrmThreadMonitorThreadPriority,"线程优先权")
                   <<getLang(App_Ui_FrmThreadMonitorThreadRunElapsed,"线程运行耗时")
                     <<getLang(App_Ui_FrmThreadMonitorThreadRunState,"线程运行状态")
                       <<getLang(App_Ui_FrmThreadMonitorThreadMsg,"线程消息");

    tb->setColumnCount(lstHeader.count());
    tb->setHorizontalHeaderLabels(lstHeader);

//初始化定时器
    m_timer=new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&FrmThreadMonitor::onTimerUpdate);
//连接线程管理器
    connect(XConcurrentMgr,&XConcurrentManager::sgXThreadCreate,this,&FrmThreadMonitor::onThreadUpdate);
    connect(XConcurrentMgr,&XConcurrentManager::sgXThreadRemove,this,&FrmThreadMonitor::onThreadUpdate);
    connect(XConcurrentMgr,&XConcurrentManager::sgXThreadStart,this,&FrmThreadMonitor::onThreadUpdate);
    connect(XConcurrentMgr,&XConcurrentManager::sgXThreadEnd,this,&FrmThreadMonitor::onThreadUpdate);

    connect(XConcurrentMgr,&XConcurrentManager::sgXThreadCreate,this,&FrmThreadMonitor::onThreadCreate);
    connect(XConcurrentMgr,&XConcurrentManager::sgXThreadRemove,this,&FrmThreadMonitor::onThreadRemove);
//启动监控
    onThreadUpdate();
}

void FrmThreadMonitor::onThreadCreate(XThread* thread)
{
    if(thread)
    {
        QString str=QString("Create Thread:Group<%1> Name<%2>").arg(thread->group()).arg(thread->name());
        Log_Trace(str);
    }
}

void FrmThreadMonitor::onThreadRemove(XThread* thread)
{
    if(thread)
    {
        QString str=QString("Remove Thread:Group<%1> Name<%2>").arg(thread->group()).arg(thread->name());
        Log_Trace(str);
    }
}



void FrmThreadMonitor::startUpdate()
{
    if(!m_timer->isActive())
    {
        m_timer->start(Timer_Interval);
    }
}

void FrmThreadMonitor::stopUpdate()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
}


void FrmThreadMonitor::onThreadUpdate()
{
    stopUpdate();
    initTableWdg();
    startUpdate();
}



void FrmThreadMonitor::initTableWdg()
{
    auto tbw=ui->tbwThreadMonitor;
    auto ths=XConcurrentMgr->threads();
    tbw->setRowCount(ths.count());
}

void FrmThreadMonitor::onTimerUpdate()
{
    auto funcSetItemText=[&](QTableWidget* tb, int nRow,int nCol,QString text)
    {
        auto item=tb->item(nRow,nCol);
        if(item==nullptr)
        {
            item=new QTableWidgetItem(text);
            tb->setItem(nRow,nCol,item);
        }
        item->setText(text);
        item->setToolTip(text);
        return item;
    };

    QString strRunning=getLang(App_Ui_FrmThreadMonitorThreadRuning,"线程运行");
    QString strStop=getLang(App_Ui_FrmThreadMonitorThreadStop,"线程停止");
    auto tbw=ui->tbwThreadMonitor;
    auto ths=XConcurrentMgr->threads();
    for (int i = 0; i < ths.count(); ++i)
    {
        auto th=ths[i];
        if(!th)
        {
            continue;
        }
        funcSetItemText(tbw,i,ColIdx_ThreadId,QString("%1").arg(th->id()));
        funcSetItemText(tbw,i,ColIdx_ThreadGroup,th->group());
        funcSetItemText(tbw,i,ColIdx_ThreadName,th->name());
        funcSetItemText(tbw,i,ColIdx_ThreadPriority,QString("%1").arg(th->priority()));
        funcSetItemText(tbw,i,ColIdx_ThreadRunElapsed,QString("%1ms").arg(th->runElapsed()));
        funcSetItemText(tbw,i,ColIdx_ThreadRunState,th->isRunning()?strRunning:strStop);
        funcSetItemText(tbw,i,ColIdx_ThreadMsg,th->msg());

    }
}
