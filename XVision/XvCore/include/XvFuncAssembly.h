#ifndef XVFUNCASSEMBLY_H
#define XVFUNCASSEMBLY_H

#include <QObject>
#include <QPixmap>

#include "XvFuncBase.h"
#include "XvFuncDef.h"

///算子基本信息(显示使用)
typedef struct S_XVFUNC_BASE_INFO
{
    S_XVFUNC_BASE_INFO()
    {

    }
    S_XVFUNC_BASE_INFO(const QString& _role,
                       const EXvFuncType& _type,
                       const QString& _name,
                       const QPixmap& _icon,
                       const QMetaObject& _meta):
        role(_role),type(_type), name(_name), icon(_icon), meta(_meta)
    {

    }
    QString role;  //算子功能
    EXvFuncType type;//算子分类
    QString name;  //算子名称
    QPixmap icon;  //算子图标
    QMetaObject meta;//算子元数据
}XvFuncBaseInfo,*PXvFuncBaseInfo;



#define XvFuncAsm XvFuncAssembly::getInstance()
///算子集合
class XVCORE_EXPORT XvFuncAssembly : public QObject
{
    Q_OBJECT
    friend class XvPluginMgr;
public:
    ///获取单例
    static XvFuncAssembly *getInstance();
private:
    explicit XvFuncAssembly(QObject *parent = nullptr);
    static XvFuncAssembly* s_Instance;

signals:
    void sgRegisterNewXvFunc(const S_XVFUNC_BASE_INFO &funcInfo);
    /***************算子模块***************/
public:

    ///通过标识符创建一个算子
    XvFuncBase* createNewXvFunc(QString role);
    ///获取算子标识符列表
    QList<QString> getRoleList();
protected:
    ///算子注册
    bool registerXvFunc(XvFuncBase* func);
protected:
    ///算子字典
    /// 1-QString:算子功能Role
    /// 2-QMetaObject:算子信息
    QMap<QString,XvFuncBaseInfo> m_mapXvFuncInfo;
};

#endif // XVFUNCASSEMBLY_H
