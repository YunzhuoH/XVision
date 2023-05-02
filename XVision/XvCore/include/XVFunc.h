#ifndef XVFUNC_H
#define XVFUNC_H

#include "XvCoreGlobal.h"
#include <QObject>
#include "IXvTokenMsgAble.h"
#include "XvCoreDef.h"
#include "XvFuncData.h"

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
    friend class XvFunc;
    friend class XvFlow;
    friend class XvProject;
    friend class XvFuncAssembly;
public:
    Q_INVOKABLE explicit XvFunc(QObject *parent = nullptr);
    virtual ~XvFunc();
signals:
    void sgXvFuncDestroyed(XvFunc* func);
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
    virtual void setParFlow(XvFlow* flow);
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


/**********************算子连接定义**********************/
//算子与算子之间连接定义
/********************************************************/

public:

    ///获取父连接算子
    virtual QList<XvFunc*> fatherFuncs() const;
    ///获取子连接算子
    virtual QList<XvFunc*> sonFuncs() const;

    ///添加子连接算子
    virtual bool addSonFunc(XvFunc* sonFunc);
    ///删除子连接算子
    virtual bool delSonFunc(XvFunc* sonFunc);
    ///是否存在该子连接算子
    bool existSonFunc(XvFunc* sonFunc);

    ///添加父连接算子
    virtual bool addFatherFunc(XvFunc* fatherFunc);
    ///删除父连接算子
    virtual bool delFatherFunc(XvFunc* fatherFunc);    
    ///是否存在该父连接算子
    bool existFatherFunc(XvFunc*  fatherFunc);

    ///是否可以自我连接(默认不可)
    virtual bool canConnectSelf();

    ///是否存在祖先算子
    bool existAncestorFunc(XvFunc* ancestorFunc);
    ///是否存在后代算子
    bool existDescendantFunc(XvFunc* descendantFunc);

    ///获取所有祖先算子
    void getAncestorFuncs(QList<XvFunc*> &lst) const;
    ///获取所有后代算子
    void getDescendantFuncs(QList<XvFunc*> &lst) const;
signals:
    ///父连接算子添加信号
    void sgFatherFuncAdd(XvFunc* fatherFunc);
    ///父连接算子删除信号
    void sgFatherFuncDel(XvFunc* fatherFunc);
    ///父连接算子修改(添加删除信号)
    void sgFatherFuncChanged(XvFunc* changedFunc);


    ///子连接算子添加信号
    void sgSonFuncAdd(XvFunc* sonFunc);
    ///子连接算子删除信号
    void sgSonFuncDel(XvFunc* sonFunc);
    ///子连接算子修改(添加删除信号)
    void sgSonFuncChanged(XvFunc* changedFunc);

protected:
    ///父连接算子列表
    QList<XvFunc*> _lstFatherFunc;
    ///字连接算子列表
    QList<XvFunc*> _lstSonFunc;
protected slots:
    ///父连接算子delete事件
    void onFatherFuncDestroyed(XvFunc* func);
    ///子连接算子delete事件
    void onSonFuncDestroyed(XvFunc* func);
    ///流程中算子连接更新事件
    virtual void onXvFlowLinkRefresh();
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
    ///获取运行消息
    QString getXvFuncRunMsg() const
    {
        return _runInfo.runMsg;
    }
    ///获取运行状态
    EXvFuncRunStatus getXvFuncRunStatus() const
    {
        return _runInfo.runStatus;
    }
    ///获取运行耗时
    double getXvFuncRunElapsed() const
    {
        return _runInfo.runElapsed;
    }
signals:
    ///算子运行开始
    void sgFuncRunStart(XvFunc* func);
    ///算子运行结束
    void sgFuncRunEnd(XvFunc* func);

public slots:
    ///算子显示界面
    virtual void onShowFunc() {};
protected:
    ///算子运行虚接口
    virtual EXvFuncRunStatus run()
    {
        return _runInfo.runStatus;
    }
    ///设置运行耗时
    virtual void setRunElapsed(const double &time);
    ///设置运行消息
    virtual void setRunMsg(const QString &msg);
    ///设置运行状态
    virtual void setRunStatus(const EXvFuncRunStatus &status);
protected:
    ///算子运行信息
    XvFuncRunInfo _runInfo;
/****************************************************************/

/**********************算子参数结果定义**********************/
//算子输入参数和输出结果定义
//算子参数订阅
/********************************************************/
public:
    ///定义算子订阅信息
    using SubscribeInfo=std::pair<XvFunc*, QString>;

    ///获取算子输入参数
    virtual XvBaseParam* getParam() const { return nullptr; }

    ///获取算子输出结果
    virtual XvBaseResult* getResult() const { return nullptr; }

    ///更新参数
    virtual bool updataParam(const QString &paramName,XObject* object);

    ///通过对象名称获取参数
    XObject* getParamsByName(const QString &objectName);
    ///通过对象名称获取结果
    XObject* getResultsByName(const QString &objectName);

    ///通过类型获取参数
    QList<XObject*> getParamsByType(const QString &typeName);
    ///通过类型获取结果
    QList<XObject*> getResultsByType(const QString &typeName);

    ///根据类型获取祖先算子中的结果
    QMap<XvFunc*,QList<XObject*>> getAncestorsResultByType(const QString &typeName);

    ///获取参数订阅信息
    const QMap<QString,SubscribeInfo> getParamSubscribe() const {  return _mapParamSubscribe;  }
    ///获取参数订阅信息
    bool getParamSubscribe(const QString  &paramName,SubscribeInfo &subscribeInfo);

    ///参数是否进行订阅
    bool isParamSubscribe(const QString &paramName)
    {
        return _mapParamSubscribe.contains(paramName);
    }

protected://参数订阅(调用对象为本算子)
    ///参数进行订阅
    /// paramName:需要订阅的参数名称
    /// target：订阅的目标算子
    /// resultName：目标算子结果名称
    virtual bool paramSubscribe(const QString &paramName,XvFunc* target,const QString &resultName);
    ///参数取消订阅
    /// paramName:需要取消订阅的参数名称
    /// target:需要取消的订阅目标算子
    virtual bool paramUnSubscribe(const QString &paramName);

    ///是否存在订阅目标算子
    bool existParamSubscribe(XvFunc* target);
protected slots:
    ///刷新订阅目标算子(流程中算子断开事件进行更新)
    void onRefreshParamSubscribe();
    ///订阅目标算子父析构事件
    void onParamTargetDestroyed(XvFunc* target);
    ///订阅的目标算子运行完毕更新参数事件
    void onSubscribeTargetRunEndUpdataParam(XvFunc* target);
protected:
    /// QString-1:本算子参数名
    /// SubscribeInfo:
    /// XvFunc*:订阅的目标算子
    /// QString-2:订阅的目标算子结果名
    QMap<QString,SubscribeInfo> _mapParamSubscribe;//参数订阅连接映射

/*******************************************************/


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
