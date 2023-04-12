#include "FrmLogShow.h"
#include "ui_FrmLogShow.h"
#include <QMutexLocker>
#include <QScrollBar>
#include <QMenu>
#include <QDesktopServices>

FrmLogShow *FrmLogShow::s_Instance = NULL;
FrmLogShow *FrmLogShow::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new FrmLogShow();
    }
  }
  return s_Instance;
}



FrmLogShow::FrmLogShow(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmLogShow)
{
    ui->setupUi(this);
    initFrm();
}

FrmLogShow::~FrmLogShow()
{
    delete ui;
}

void FrmLogShow::initFrm()
{
    this->setWindowIcon(QIcon(":/images/Ui/FrmLogShow.svg"));
    this->setWindowTitle(getLang(App_Ui_FrmLogShow,"日志显示"));
    ui->ptxtLog->setRippleStyle(XMatCommonDef::NoRipple);
    connect(XLog,&XLogger::signalLog,this,&FrmLogShow::onSignalLog);
    m_mapType[XLogger::Trace]=getLang(App_LogType_Trace,"追踪");
    m_mapType[XLogger::Debug]=getLang(App_LogType_Debug,"调试");
    m_mapType[XLogger::Info]=getLang(App_LogType_Info,"信息");
    m_mapType[XLogger::Event]=getLang(App_LogType_Event,"事件");
    m_mapType[XLogger::Warn]=getLang(App_LogType_Warn,"警告");
    m_mapType[XLogger::Error]=getLang(App_LogType_Error,"错误");
    m_mapType[XLogger::Critical]=getLang(App_LogType_Critical,"致命");


    QPlainTextEdit *ptxtLog=ui->ptxtLog;
    //设置自定义菜单
    ptxtLog->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ptxtLog, &QPlainTextEdit::customContextMenuRequested, this,&FrmLogShow::onLogcustomContextMenuRequested);
    //设置日志最多显示一百行
    ptxtLog->setMaximumBlockCount(LOG_MAX_COUNT);
    //设置只读
    if(!ptxtLog->isReadOnly())
    {
        ptxtLog->setReadOnly(true);
    }
}

void FrmLogShow::onSignalLog(const QString &log, const XLogger::ELogType &logType)
{
    QTextCharFormat fmt;
    QColor color=QColor(0,0,0);
    //字体大小
    fmt.setFontWeight(QFont::Normal);
    auto *ptxt=ui->ptxtLog;
    switch (logType)
    {
    case XLogger::Trace:
        color=QColor(0,255,255,200);
        break;
    case XLogger::Debug:
        color=QColor(255,0,255,200);
        break;
    case XLogger::Info:
        color=QColor(0,255,0,230);
        break;
    case XLogger::Event:
        color=QColor(0,128,255,230);
        break;
    case XLogger::Warn:
        color=QColor(255,128,0,230);
        break;
    case XLogger::Error:
        color=QColor(255,30,0,230);
        break;
    case XLogger::Critical:
        color=QColor(128,0,0,230);
        break;
    }
    //字体色
    fmt.setForeground(QBrush(color));
    //设置光标到文本末尾
    ptxt->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    //文本框使用以上设定
    ptxt->mergeCurrentCharFormat(fmt);
    QString logShow=m_mapType[logType]+":"+log;
    ptxt->appendPlainText(logShow);
    //移动滚动条到底部
    QScrollBar *scrollbar =  ptxt->verticalScrollBar();
    if(scrollbar)
    {
       scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

void FrmLogShow::onLogcustomContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    auto action=menu.addAction(getLang(App_Ui_FrmLogShowClearLog,"清除日志"),this,SLOT(onClearLog()));
    action->setIcon(QIcon(":/images/Ui/FrmLogShowActionClearLog.svg"));
    action=menu.addAction(getLang(App_Ui_FrmLogOpenLogDir,"打开日志目录"),this,SLOT(onOpenLogDir()));
    action->setIcon(QIcon(":/images/Ui/FrmLogShowActionOpenLogDir.svg"));
    menu.exec(QCursor::pos());
}

void FrmLogShow::onClearLog()
{
    ui->ptxtLog->clear();
}

void FrmLogShow::onOpenLogDir()
{
    QDesktopServices deskSer;
    QString logDir=qApp->applicationDirPath()+"/Log";
    deskSer.openUrl(QUrl("file:///"+logDir));
}

