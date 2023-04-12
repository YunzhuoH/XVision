#ifndef XVFUNCASSEMBLY_H
#define XVFUNCASSEMBLY_H

#include "XvCoreGlobal.h"
#include <QObject>
#include <QPixmap>
#include "XvCoreDef.h"

#define XvFuncAsm XvCore::XvFuncAssembly::getInstance()
namespace XvCore
{
class XvFunc;
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
    void sgRegisterNewXvFunc(const XvFuncInfo &info);
    /***************算子模块***************/
public:
//*[算子类型]*
    ///获取算子类型信息列表
    static QList<XvFuncTypeInfo> getXvFuncTypeInfos();
    ///获取算子类型信息
    static XvFuncTypeInfo getXvFuncTypeInfo(const XvCore::EXvFuncType& type);


//*[算子]*
    ///通过标识符创建一个算子
    XvFunc* createNewXvFunc(QString role);
    ///通过标识符获取算子信息
    XvFuncInfo getXvFuncInfo(QString role);
    ///通过信息创建一个算子
    inline XvFunc* createNewXvFunc(const XvFuncInfo &info);

    ///获取算子信息列表
    QList<XvFuncInfo> getXvFuncInfos();
    ///通过类型获取算子信息列表
    QList<XvFuncInfo> getXvFuncInfos(const EXvFuncType &type);
    ///通过类型获取算子信息列表
    QList<XvFuncInfo> getXvFuncInfos(const XvFuncTypeInfo &info);
//*[所有算子信息]*
    ///获取类型-算子列表映射
    QMap<EXvFuncType,QList<XvFuncInfo>> getMapXvFuncTypeInfo();
protected:
    ///算子注册
    bool registerXvFunc(XvFunc* func);
protected:
    ///算子字典
    /// 1-QString:算子功能Role
    /// 2-XvFuncInfo:算子信息
    QMap<QString,XvFuncInfo> m_mapXvFuncInfo;
};

inline XvFunc *XvFuncAssembly::createNewXvFunc(const XvFuncInfo &info)
{
    return createNewXvFunc(info.role);
}

inline QList<XvFuncInfo> XvFuncAssembly::getXvFuncInfos(const XvFuncTypeInfo &info)
{
    return getXvFuncInfos(info.type);
}
}
#endif // XVFUNCASSEMBLY_H
