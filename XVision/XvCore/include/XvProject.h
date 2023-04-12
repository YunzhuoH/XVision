#ifndef XVPROJECT_H
#define XVPROJECT_H

#include "XvCoreGlobal.h"
#include <QObject>
#include "IXvTokenMsgAble.h"
#include "XvError.h"

namespace XvCore
{
class XvFlow;
class XvProjectPrivate;
class XVCORE_EXPORT XvProject : public QObject,public IXvTokenMsgAble
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(XvProject)
    Q_PROPERTY(QString projectId READ projectId)
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
public:
    explicit XvProject(const QString &name="Project",QObject *parent = nullptr);
    ~XvProject();

public:
//*[项目操作]*
    ///进行释放(删除前必需调用进行判断)
    /// RET_XV_SUCCESS:能删除 !RET_XV_SUCCESS:不可删除
    RetXv release();


 /**********************流程操作**********************/
 //流程增删查
 /***************************************************/
public:
    ///通过ID获取流程
    XvFlow* getXvFlow(const QString &id);
    ///通过名称获取流程列表
    QList<XvFlow*> getXvFlows(const QString &name) const;
    ///获取所有流程
    QList<XvFlow*> getXvFlows() const;
    ///流程数量
    int xvFlowCount() const;
public slots:
    ///创建流程
    XvFlow* createXvFlow(const QString &name="Flow");
    ///通过ID移除流程
    bool removeXvFlow(const QString &id);
    ///通过名称移除多个流程
    /// Rt:移除的流程个数
    int removeXvFlows(const QString &name);
 signals:
    ///流程添加完成信号
    void sgXvFlowCreated(XvFlow* flow);
    ///流程开始删除信号
    void sgRemoveXvFlowStart(XvFlow* flow);
    ///流程完成删除信号
    void sgRemoveXvFlowEnd(const QString &flowId);

/**********************字段/属性定义**********************/
//项目基本定义属性 序列号/名称
/********************************************************/
public:
    ///流程Id
    inline QString projectId() const;
    ///流程名称
    inline QString projectName() const;
    ///设置名称
    void setProjectName(const QString &name);
    ///TokenMsgAble
    QString tokenMsgId() override { return projectId();}
signals:
    void projectNameChanged(const QString &name);
protected:
    ///项目唯一ID
    QString _projectId;

    ///项目名称
    QString _projectName;
protected:
    const QScopedPointer<XvProjectPrivate> d_ptr;

};

inline QString XvProject::projectId() const
{
    return _projectId;
}

inline QString XvProject::projectName() const
{
    return _projectName;
}
}
#endif // XVPROJECT_H
