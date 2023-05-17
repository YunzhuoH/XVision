#ifndef UIXVDISPLAYMANAGER_H
#define UIXVDISPLAYMANAGER_H

#include <QObject>

#define DisplayViewSceneSize 20000

namespace XvCore
{
class XvFunc;
}

class XMatToolBar;
class XMatComboBox;

class XvDisplayView;
class XvDisplayScene;
class UiXvDisplayManagerPrivate;
class UiXvDisplayManager:public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(UiXvDisplayManager)

public:
    UiXvDisplayManager(QObject* parent=nullptr);
    ~UiXvDisplayManager();

protected:
    const QScopedPointer<UiXvDisplayManagerPrivate> d_ptr;

public:
    ///获取显示视图
    XvDisplayView* displayView() const { return m_displayView;}
    ///获取显示场景
    XvDisplayScene* displayScene() const;
    ///获取显示工具栏
    XMatToolBar* displayToolBar() const;

protected: //初始化接口
    ///初始化
    void init();
    ///初始化视图
    void initView();
    ///初始化工具栏
    void initToolBar();
    ///初始化连接
    void initConnect();

public slots:
    ///绑定当前显示的算子
    void onBindXvFunc(XvCore::XvFunc* func);
    ///更新绑定的算子
    void onUpdateXvFunc();
    ///更新绑定算子显示
    void onUpdateXvFuncDisplay();
private:
    XvDisplayView* m_displayView=nullptr;//显示View
    XMatToolBar*   m_displayToolBar=nullptr;//显示工具栏
    XMatComboBox*  m_displayComboBox=nullptr;//显示cmb

    XvCore::XvFunc *m_curBindFunc=nullptr;//当前绑定算子

};

#endif // UIXVDISPLAYMANAGER_H
