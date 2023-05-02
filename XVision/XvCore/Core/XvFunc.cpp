#include "XvFunc.h"
#include <QUuid>
#include <QElapsedTimer>
#include <QPixmap>

#include "XvFuncAssembly.h"
#include "XvFlow.h"
#include "XObject.h"

using namespace XvCore;


XvFunc::XvFunc(QObject *parent)
    :QObject{parent},
      _funcId(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
      _funcRole(""),
      _funcType(EXvFuncType::Null),
      _funcName("")
{
    registerTokenMsgAble();
}

XvFunc::~XvFunc()
{
    unRegisterTokenMsgAble();
    emit sgXvFuncDestroyed(this);
}

/**********************字段/属性定义**********************/
void XvFunc::setFuncName(const QString &name)
{
    if(_funcName!=name)
    {
        _funcName=name;
        emit funcNameChanged(_funcName);
    }

}

QPixmap XvFunc::funcIcon()
{
    return QPixmap(":/image/XvFuncIcon.svg");
}

void XvFunc::setParFlow(XvFlow *flow)
{
    m_parFlow=flow;
}


/**********************算子连接定义**********************/

QList<XvFunc *> XvFunc::fatherFuncs() const
{
    return _lstFatherFunc;
}

QList<XvFunc *> XvFunc::sonFuncs() const
{
    return _lstSonFunc;
}

bool XvFunc::addSonFunc(XvFunc *sonFunc)
{
    if(sonFunc==nullptr) return false;
    if(this->parFlow()!=sonFunc->parFlow())//非同流程算子无法连接
    {
        return false;
    }
    if(!_lstSonFunc.contains(sonFunc))
    {
        _lstSonFunc.append(sonFunc);
        connect(sonFunc,&XvFunc::sgXvFuncDestroyed,this,&XvFunc::onSonFuncDestroyed);
        if(!sonFunc->existFatherFunc(this))//子连接算子不存在本算子父连接算子,进行添加
        {
            sonFunc->addFatherFunc(this);
        }
        emit this->sgSonFuncAdd(sonFunc);
        emit this->sgSonFuncChanged(this);
        return true;
    }
    else
    {
        return false;
    }
}

bool XvFunc::delSonFunc(XvFunc *sonFunc)
{
    if(_lstSonFunc.contains(sonFunc))
    {
        bool bRet= _lstSonFunc.removeOne(sonFunc);
        if(bRet)
        {          
            if(sonFunc->existFatherFunc(this))//子连接算子存在本算子父连接算子,进行删除
            {
                sonFunc->delFatherFunc(this);
            }
            emit this->sgSonFuncDel(sonFunc);
            emit this->sgSonFuncChanged(this);
        }
        return bRet;
    }
    else
    {
        return false;
    }
}

bool XvFunc::existSonFunc(XvFunc *sonFunc)
{
    return _lstSonFunc.contains(sonFunc);
}

bool XvFunc::addFatherFunc(XvFunc *fatherFunc)
{
    if(fatherFunc==nullptr) return false;
    if(this->parFlow()!=fatherFunc->parFlow())//非同流程算子无法连接
    {
        return false;
    }
    if(!_lstFatherFunc.contains(fatherFunc))
    {
        _lstFatherFunc.append(fatherFunc);
        connect(fatherFunc,&XvFunc::sgXvFuncDestroyed,this,&XvFunc::onFatherFuncDestroyed);
        if(!fatherFunc->existSonFunc(this))//父连接算子不存在本算子子连接算子,进行添加
        {
            fatherFunc->addSonFunc(this);
        }
        emit this->sgFatherFuncAdd(fatherFunc);
        emit this->sgFatherFuncChanged(this);
        return true;
    }
    else
    {
        return false;
    }
}

bool XvFunc::delFatherFunc(XvFunc *fatherFunc)
{
    if(_lstFatherFunc.contains(fatherFunc))
    {
        bool bRet= _lstFatherFunc.removeOne(fatherFunc);
        if(bRet)
        {        
            if(fatherFunc->existSonFunc(this))//父连接算子不存在本算子子连接算子,进行删除
            {
                fatherFunc->delSonFunc(this);
            }
            emit this->sgFatherFuncDel(fatherFunc);
            emit this->sgFatherFuncChanged(this);
        }
        return bRet;
    }
    else
    {
        return false;
    }
}

bool XvFunc::existFatherFunc(XvFunc *fatherFunc)
{
    return _lstFatherFunc.contains(fatherFunc);
}

bool XvFunc::canConnectSelf()
{
    return false;
}

bool XvFunc::existAncestorFunc(XvFunc *ancestorFunc)
{
    QList<XvFunc*> lst;
    getAncestorFuncs(lst);
    return lst.contains(ancestorFunc);
}

bool XvFunc::existDescendantFunc(XvFunc *descendantFunc)
{
    QList<XvFunc*> lst;
    getDescendantFuncs(lst);
    return lst.contains(descendantFunc);
}

void XvFunc::getAncestorFuncs(QList<XvFunc *> &lst) const
{
    foreach (auto father, _lstFatherFunc)
    {
        if(!lst.contains(father))
        {
            lst.append(father);            
            father->getAncestorFuncs(lst);
        }
    }
}

void XvFunc::getDescendantFuncs(QList<XvFunc *> &lst) const
{
    foreach (auto son, _lstSonFunc)
    {
        if(!lst.contains(son))
        {
            lst.append(son);
            son->getDescendantFuncs(lst);
        }
    }
}




void XvFunc::onFatherFuncDestroyed(XvFunc* func)
{
    if(func)
    {
        delFatherFunc(func);
    }
}

void XvFunc::onSonFuncDestroyed(XvFunc* func)
{
    if(func)
    {
        delSonFunc(func);
    }
}

void XvFunc::onXvFlowLinkRefresh()
{
    onRefreshParamSubscribe();//刷新连接绑定
}

/**********************算子参数结果定义**********************/
bool XvFunc::updataParam(const QString &paramName, XObject *object)
{
    if(!object) return false;
    auto paramObj=getParamsByName(paramName);    
    if(!paramObj)
    {
        return false;
    }
    return paramObj->setData(object);
}

XObject *XvFunc::getParamsByName(const QString &objectName)
{
    auto param=getParam();
    if(param)
    {
        return param->childObject(objectName);
    }
    return nullptr;
}

XObject *XvFunc::getResultsByName(const QString &objectName)
{
    auto result=getResult();
    if(result)
    {
        return result->childObject(objectName);
    }
    return nullptr;
}

QList<XObject *> XvFunc::getParamsByType(const QString &typeName)
{
    auto param=getParam();
    if(param)
    {
        return param->childObjects(typeName);
    }
    return QList<XObject*>();
}

QList<XObject *> XvFunc::getResultsByType(const QString &typeName)
{
    auto result=getResult();
    if(result)
    {
        return result->childObjects(typeName);
    }
    return QList<XObject*>();;
}

QMap<XvFunc*, QList<XObject*>> XvFunc::getAncestorsResultByType(const QString &typeName)
{
    QMap<XvFunc*, QList<XObject*>>  map;
    QList<XvFunc*> lstAncestors;
    this->getAncestorFuncs(lstAncestors);
    lstAncestors.removeOne(this);//移除自己
    foreach (auto anctor, lstAncestors)
    {
        auto results=anctor->getResultsByType(typeName);
        if(results.count()>0)
        {
            map.insert(anctor,results);
        }
    }
    return map;
}

bool XvFunc::getParamSubscribe(const QString &paramName, SubscribeInfo &subscribeInfo)
{
    if(!isParamSubscribe(paramName))
    {
        return false;
    }
    subscribeInfo=_mapParamSubscribe[paramName];
    return true;
}




bool XvFunc::paramSubscribe(const QString &paramName, XvFunc *target, const QString &resultName)
{
    paramUnSubscribe(paramName);//先解绑
    if(!target) return false;
    if(!this->existAncestorFunc(target)) return false;
    auto paramObject=getParamsByName(paramName);
    if(!paramObject) return false;//不存在目标对象失败
    auto resultObject=target->getResultsByName(resultName);
    if(!resultObject) return false;//不存在结果对象失败
    if(!existParamSubscribe(target))
    {
        connect(target,&XvFunc::sgFuncRunEnd,this,&XvFunc::onSubscribeTargetRunEndUpdataParam,Qt::DirectConnection);
        connect(target,&XvFunc::sgXvFuncDestroyed,this,&XvFunc::onParamTargetDestroyed);
    }
    _mapParamSubscribe[paramName]=SubscribeInfo(target,resultName);
    return true;
}

bool XvFunc::paramUnSubscribe(const QString &paramName)
{
    auto paramObject=getParamsByName(paramName);
    if(!paramObject) return false;//不存在目标对象失败
    if(!_mapParamSubscribe.contains(paramName))
    {
        return false;
    }
    auto kv=_mapParamSubscribe[paramName];
    auto target=kv.first;
    if(!target) return false;
    _mapParamSubscribe.remove(paramName);
    if(!existParamSubscribe(target))
    {
        disconnect(target,&XvFunc::sgFuncRunEnd,this,&XvFunc::onSubscribeTargetRunEndUpdataParam);
        disconnect(target,&XvFunc::sgXvFuncDestroyed,this,&XvFunc::onParamTargetDestroyed);
    }
    return true;
}



bool XvFunc::existParamSubscribe(XvFunc *target)
{
    foreach (auto kv, _mapParamSubscribe)
    {
        if(kv.first==target)
        {
            return true;
        }
    }
    return false;
}

void XvFunc::onRefreshParamSubscribe()
{
    QList<XvFunc*> lstLoseLinkSubscriber;//丢失连接的订阅算子
    foreach (auto kv, _mapParamSubscribe)
    {
        if(!kv.first->existDescendantFunc(this))
        {
            lstLoseLinkSubscriber.append(kv.first);
        }
    }
    foreach (auto lostLinkSubscriber, lstLoseLinkSubscriber)
    {
         foreach (auto paramName, _mapParamSubscribe.keys())
         {
            auto kv=_mapParamSubscribe[paramName];
            if(kv.first==lostLinkSubscriber)
            {
                _mapParamSubscribe.remove(paramName);
            }
         }
         disconnect(lostLinkSubscriber,&XvFunc::sgFuncRunEnd,this,&XvFunc::onSubscribeTargetRunEndUpdataParam);
         disconnect(lostLinkSubscriber,&XvFunc::sgXvFuncDestroyed,this,&XvFunc::onParamTargetDestroyed);

    }

}

void XvFunc::onSubscribeTargetRunEndUpdataParam(XvFunc *target)
{
    foreach (auto paramName, _mapParamSubscribe.keys())
    {
        auto kv=_mapParamSubscribe[paramName];
        if(kv.first==target)
        {
            auto resultObject= target->getResultsByName(kv.second);
            this->updataParam(paramName,resultObject);
        }
    }
}



void XvFunc::onParamTargetDestroyed(XvFunc *target)
{
    if(!target)
    {
        return;
    }
    foreach (auto paramName, _mapParamSubscribe.keys())
    {
        auto kv=_mapParamSubscribe[paramName];
        if(kv.first==target)
        {
            _mapParamSubscribe.remove(paramName);
        }
    }
    if(!existParamSubscribe(target))
    {
      disconnect(target,&XvFunc::sgFuncRunEnd,this,&XvFunc::onSubscribeTargetRunEndUpdataParam);
      disconnect(target,&XvFunc::sgXvFuncDestroyed,this,&XvFunc::onParamTargetDestroyed);
    }

}

/**********************算子运行操作及其状态更新**********************/
EXvFuncRunStatus XvFunc::runXvFunc()
{
    _runInfo.runIdx++;
    setRunStatus(EXvFuncRunStatus::Running);
    emit sgFuncRunStart(this);
    QElapsedTimer timer;
    timer.start();  
    auto runStatus=run();
    setRunStatus(runStatus);
    setRunElapsed((timer.nsecsElapsed()*1.0)/1000/1000);
    emit sgFuncRunEnd(this);
    return _runInfo.runStatus;
}

void XvFunc::setRunElapsed(const double &time)
{
    _runInfo.runElapsed=time;
}

void XvFunc::setRunMsg(const QString &msg)
{
    _runInfo.runMsg=msg;
}

void XvFunc::setRunStatus(const EXvFuncRunStatus &status)
{
    _runInfo.runStatus=status;
}




bool XvFunc::release()
{
    if(getXvFuncRunStatus()==EXvFuncRunStatus::Running)
    {
        return false;
    }
    else
    {
        return true;
    }
}
