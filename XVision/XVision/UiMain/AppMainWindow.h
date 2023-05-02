#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QWidget>
#include "XFramelessWidget.h"

class AppMainWindowPrivate;
class XvSingleApplication;
class AppMainWindow : public XFramelessWidget
{
    Q_OBJECT

public:
    explicit AppMainWindow(XvSingleApplication *app=nullptr,QWidget *parent = nullptr);
    ~AppMainWindow();

public:
    ///添加工具栏Action
    bool addToolBarAction(QAction *act);
    ///获取App
    XvSingleApplication *getApp() const { return m_app; }
protected:
    const QScopedPointer<AppMainWindowPrivate> d_ptr;
private:
    Q_DISABLE_COPY(AppMainWindow)
    Q_DECLARE_PRIVATE(AppMainWindow)
public slots:
//*[文件/项目]*
    ///新建项目
    void newProject();
    ///打开项目
    void openProject();
    ///保存项目
    void saveProject();
    ///项目单次运行
    void projectOnceRun();
    ///项目重复运行
    void projectLoopRun();
    ///项目停止
    void projectStop();
//*[设置]*
    ///项目设置
    void projectSetting();
    ///系统设置
    void systemSetting();
//*[帮助]*
    ///关于
    void about();

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    XvSingleApplication* m_app;
};

#endif // APPMAINWINDOW_H
