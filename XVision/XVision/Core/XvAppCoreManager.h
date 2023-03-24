#ifndef XVAPPCOREMANAGER_H
#define XVAPPCOREMANAGER_H

#include <QObject>

#define XvAppCoreMgr XvAppCoreManager::getInstance()
///App核心管理器 管理视觉方案/流程/算子
class XvAppCoreManager:public QObject
{
    Q_OBJECT
public:
    ///获取单例
    static XvAppCoreManager *getInstance();
    ///初始化
    void init();
    ///反初始化
    void uninit();
private:
    explicit XvAppCoreManager(QObject *parent = nullptr);
    static XvAppCoreManager* s_Instance;
};

#endif // XVAPPCOREMANAGER_H
