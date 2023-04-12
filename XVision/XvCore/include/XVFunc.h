#ifndef XVFUNC_H
#define XVFUNC_H

#include "XvCoreGlobal.h"
#include <QObject>
#include "IXvTokenMsgAble.h"
#include "XvCoreDef.h"

#define XvFuncName  "XvFunc"

namespace XvCore
{
class XvFuncAssembly;
class XvProject;
class XvFlow;
class XVCORE_EXPORT XvFunc:public QObject,public IXvTokenMsgAble
{
    Q_OBJECT
    Q_PROPERTY(QString funcName READ funcName WRITE setFuncName NOTIFY funcNameChanged)
    friend class XvFlow;
    friend class XvProject;
    friend class XvFuncAssembly;
public:
    Q_INVOKABLE explicit XvFunc(QObject *parent = nullptr);
    ~XvFunc();

/**********************字段/属性定义**********************/
//算子基本定义属性 序列号/功能/归类/名称/提示/ 归属的流程
/********************************************************/
public:
    ///算子ID
    QString funcId () const
    {
        return _funcId;
    }
    ///算子功能
    QString funcRole () const
    {
        return _funcRole;
    }
    ///算子类型
    EXvFuncType funcType () const
    {
        return _funcType;
    }
    ///算子名称
    QString funcName () const
    {
        return _funcName;
    }
    ///设置名称
    void setFuncName(const QString &name);

    ///算子图标
    virtual QPixmap funcIcon();

    ///TokenMsgAble
    QString tokenMsgId() override { return funcId();}

    ///父流程
    XvFlow* parFlow() const {return m_parFlow;}
protected:
    ///设置父流程
    void setParFlow(XvFlow* flow);
signals:
    void funcNameChanged(const QString &name);
protected:
    ///算子唯一ID
    QString _funcId;

    ///算子功能标识符
    QString _funcRole;

    ///算子类型
    EXvFuncType _funcType;

    ///算子名称
    QString _funcName;

    ///父流程
    XvFlow* m_parFlow=nullptr;
/********************************************************/


/**********************算子运行操作及其状态更新**********************/
public:
    ///算子运行接口
    virtual EXvFuncRunStatus runXvFunc();

    ///获取运行信息
    XvFuncRunInfo getXvFuncRunInfo() const
    {
        return _runInfo;
    }

    ///获取运行状态
    EXvFuncRunStatus getXvFuncRunStatus() const
    {
        return _runInfo.runStatus;
    }
signals:
    ///算子运行开始
    void sgFuncRunStart();
    ///算子运行结束
    void sgFuncRunEnd();

    ///算子显示界面
    void sgShowFunc();
protected:
    ///算子运行虚接口
    virtual EXvFuncRunStatus run()
    {
        return _runInfo.runStatus;
    }
protected:
    ///算子运行信息
    XvFuncRunInfo _runInfo;
/****************************************************************/

/**********************算子操作**********************/
//算子操作:运行释放
/****************************************************/

public:
   ///算子资源释放(删除前必需调用进行判断)
   /// t:能删除 f:不可删除
   virtual bool release();
};
}
#endif // XVFUNC_H
