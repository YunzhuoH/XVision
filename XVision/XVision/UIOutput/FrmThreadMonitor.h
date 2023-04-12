#ifndef FRMTHREADMONITOR_H
#define FRMTHREADMONITOR_H

#include "BaseWidget.h"


#define UiThreadMonitor FrmThreadMonitor::getInstance()

namespace Ui {
class FrmThreadMonitor;
}
class XThread;
class FrmThreadMonitor : public BaseWidget
{
    Q_OBJECT

public:
    static FrmThreadMonitor* getInstance();
protected:
    ///初始化界面
    void initFrm() override;

    ///初始化线程监控表
    void initTableWdg();
    ///开始更新线程监控
    void startUpdate();
    ///停止更新线程监控
    void stopUpdate();

protected slots:
    ///定时器更新
    void onTimerUpdate();
    ///线程列表更新
    void onThreadUpdate();

    ///线程创建响应
    void onThreadCreate(XThread* thread);
    ///线程删除响应
    void onThreadRemove(XThread* thread);

private:
    explicit FrmThreadMonitor(QWidget *parent = nullptr);
    ~FrmThreadMonitor();
     Q_DISABLE_COPY(FrmThreadMonitor)

private:
    Ui::FrmThreadMonitor *ui;
    static FrmThreadMonitor* s_Instance;
    QTimer* m_timer=nullptr;


};

#endif // FRMTHREADMONITOR_H
