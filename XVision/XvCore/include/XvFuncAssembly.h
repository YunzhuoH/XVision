#ifndef XVFUNCASSEMBLY_H
#define XVFUNCASSEMBLY_H

#include "XvCoreGlobal.h"
#include <QObject>
#include <QPixmap>

#include "XvFuncDef.h"

#define XvFuncAsm XvCore::XvFuncAssembly::getInstance()
namespace XvCore
{
class XvFuncBase;
///算子集合
class XVCORE_EXPORT XvFuncAssembly : public QObject
{
    Q_OBJECT
    friend class XvPluginManager;
public:
    ///获取单例
    static XvFuncAssembly *getInstance();
private:
    explicit XvFuncAssembly(QObject *parent = nullptr);
    static XvFuncAssembly* s_Instance;

signals:
    void sgRegisterNewXvFunc(const XvFuncBaseInfo &info);
    /***************算子模块***************/
public:
//*[算子类型]*
    ///获取算子类型信息列表
    static QList<XvFuncTypeInfo> getXvFuncTypeInfos();
    ///获取算子类型信息
    static XvFuncTypeInfo getXvFuncTypeInfo(const XvCore::EXvFuncType& type);


//*[算子]*
    ///通过标识符创建一个算子
    XvFuncBase* createNewXvFunc(QString role);
    ///通过标识符获取算子信息
    XvFuncBaseInfo getXvFuncInfo(QString role);
    ///通过信息创建一个算子
    inline XvFuncBase* createNewXvFunc(const XvFuncBaseInfo &info);

    ///获取算子信息列表
    QList<XvFuncBaseInfo> getXvFuncInfos();
    ///通过类型获取算子信息列表
    QList<XvFuncBaseInfo> getXvFuncInfos(const EXvFuncType &type);
    ///通过类型获取算子信息列表
    QList<XvFuncBaseInfo> getXvFuncInfos(const XvFuncTypeInfo &info);
protected:
    ///算子注册
    bool registerXvFunc(XvFuncBase* func);
protected:
    ///算子字典
    /// 1-QString:算子功能Role
    /// 2-QMetaObject:算子信息
    QMap<QString,XvFuncBaseInfo> m_mapXvFuncInfo;
};

inline XvFuncBase *XvFuncAssembly::createNewXvFunc(const XvFuncBaseInfo &info)
{
    return createNewXvFunc(info.name);
}

inline QList<XvFuncBaseInfo> XvFuncAssembly::getXvFuncInfos(const XvFuncTypeInfo &info)
{
    return getXvFuncInfos(info.type);
}
}
#endif // XVFUNCASSEMBLY_H
