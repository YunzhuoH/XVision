#ifndef XVFLOW_H
#define XVFLOW_H

#include "XvCoreGlobal.h"
#include <QObject>
#include "IXvTokenMsgAble.h"
#include "XvCoreDef.h"

namespace XvCore
{
class XvFunc;
class XvProject;
class XvFlowPrivate;
class XVCORE_EXPORT XvFlow : public QObject,public IXvTokenMsgAble
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(XvFlow)
    Q_PROPERTY(QString flowId READ flowId)
    Q_PROPERTY(QString flowName READ flowName WRITE setFlowName NOTIFY sgFlowNameChanged)

    friend class XvFunc;
    friend class XvProject;
public:
    explicit XvFlow(XvProject *project,const QString &name="Flow",QObject *parent = nullptr);
    ~XvFlow();


 /**********************字段/属性定义**********************/
 //流程基本定义属性 序列号/名称 归属的项目
 /********************************************************/
public:
    ///流程Id
    inline QString flowId() const;
    ///流程名称
    inline QString flowName() const;
    ///设置名称
    void setFlowName(const QString &name);

    ///TokenMsgAble
    QString tokenMsgId() override { return flowId(); }
    ///父项目
    XvProject* parProject() const { return m_parProject; }
protected:
    ///设置父流程
    void setParProject(XvProject* project);
signals:
    ///信号:流程名称更改
    void sgFlowNameChanged(XvFlow* flow);
protected:
    ///流程唯一ID
    QString _flowId;

    ///流程名称
    QString _flowName;

    ///父项目
    XvProject* m_parProject=nullptr;

/**********************算子操作**********************/
//算子增删查-改
/****************************************************/
public:
    ///通过ID获取算子
    XvFunc* getXvFunc(const QString &id);
    ///获取所有算子
    QList<XvFunc*> getXvFuncs() const;
    ///算子数量
    int xvFuncCount() const;
public slots:
    ///通过标识符创建算子
    XvFunc* createXvFunc(const QString &role);
    ///通过ID移除算子
    bool removeXvFunc(const QString &id);

signals:
    ///算子添加信号
    void sgXvFuncCreated(XvFunc* func);
    ///算子开始删除信号
    void sgRemoveXvFuncStart(XvFunc* func);
    ///算子完成删除信号
    void sgRemoveXvFuncEnd(const QString &funcId);


/**********************算子运行操作及其状态更新**********************/
public:
    ///流程运行接口
    RetXv runOnce();
    ///流程循环运行
    RetXv runLoop();
    ///流程停止运行
    RetXv stop();
    ///获取运行信息
    XvFlowRunInfo getXvFuncRunInfo() const
    {
        return _runInfo;
    }

    ///获取运行状态
    EXvFlowRunStatus getXvFuncRunStatus() const
    {
        return _runInfo.runStatus;
    }
signals:
    ///流程运行开始
    void sgFlowRunStart();
    ///流程运行结束
    void sgFlowRunEnd();
    ///流程运行停止
    void sgFlowRunStop();


protected:
    ///流程运行信息
    XvFlowRunInfo _runInfo;

 /**********************流程操作**********************/
 //流程操作:运行释放
 /****************************************************/

public:
    ///流程资源释放(删除前必需调用进行判断)
    /// RET_XV_SUCCESS:能删除 !RET_XV_SUCCESS:不可删除
    RetXv release();

protected:
    const QScopedPointer<XvFlowPrivate> d_ptr;

};

inline QString XvFlow::flowId() const
{
    return _flowId;
}

inline QString XvFlow::flowName() const
{
    return _flowName;
}
}
#endif // XVFLOW_H
