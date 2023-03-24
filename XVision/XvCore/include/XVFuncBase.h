#ifndef VFUNCBASE_H
#define VFUNCBASE_H

#include "XvCoreGlobal.h"
#include <QObject>
#include "XvFuncDef.h"
#include "IXvTokenMsgable.h"

/*算子4种状态:
1.未运行:Init
2.运行成功:Ok
3.运行失败:Fail
4.运行错误:Error
*/
#define XvFuncStatus_Init   0
#define XvFuncStatus_Ok     1
#define XvFuncStatus_Fail   2
#define XvFuncStatus_Error  3

#define XvFuncStatus_Init_Str   "Init"
#define XvFuncStatus_Ok_Str     "Ok"
#define XvFuncStatus_Fail_Str   "Fail"
#define XvFuncStatus_Error_Str  "Error"

#define XvFuncStatusStrs { XvFuncStatus_Init_Str,XvFuncStatus_Ok_Str,XvFuncStatus_Fail_Str,XvFuncStatus_Error_Str }

namespace XvCore
{

class XVCORE_EXPORT XvFuncBase:public QObject,public IXvTokenMsgable
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit XvFuncBase(QObject *parent = nullptr);
    ~XvFuncBase();

/**********************字段/属性定义**********************/
//算子基本定义属性 序列号/功能/归类/名称/提示/ 归属的流程序列号
/********************************************************/
public:
    ///算子ID
    QString VFuncId () const
    {
        return _VFuncId;
    }
    ///算子功能
    QString VFuncRole () const
    {
        return _VFuncRole;
    }
    ///算子类型
    EXvFuncType VFuncType () const
    {
        return _VFuncType;
    }
    ///算子名称
    QString VFuncName () const
    {
        return _VFuncName;
    }
    ///算子自定义名称
    QString VFuncCustomName;

    ///算子图标
    virtual QPixmap VFuncIcon();

    ///TokenMsgAble
    QString tokenMsgId() override { return VFuncId();}
protected:
    ///算子唯一ID
    QString _VFuncId;

    ///算子功能标识符
    QString _VFuncRole;

    ///算子类型
    EXvFuncType _VFuncType;

    ///设置名称
    void setVFuncName(const QString &name)
    {
        _VFuncName=name;
        VFuncCustomName=name;
    }
    ///算子名称
    QString _VFuncName;


/********************************************************/


/**********************算子运行操作及其状态更新**********************/
public:
    enum EVFucRunStatus
    {
        Init=XvFuncStatus_Init,//初始状态 未运行
        OK=XvFuncStatus_Ok, //运行成功    运行成功返回
        Fail=XvFuncStatus_Fail, //运行失败  运行存在错误
        Error=XvFuncStatus_Error,//运行错误  中断强制退出运行
    };
    Q_ENUMS(EVFucRunStatus)
    ///算子运行接口
    virtual EVFucRunStatus runVFunc();


    ///获取算子运行状态
    EVFucRunStatus getVFuncRunStatus() const
    {
        return VFuncRunStatus;
    }
    ///获取算子最后运行信息
    QString getLastInfo() const
    {
        return VFuncLastInfo;
    }
    ///获取最后运行耗时
    double getLastRunTime() const
    {
        return LastRunTime;
    }
signals:
    ///算子运行开始
    void sgVFuncRunStart();
    ///算子运行结束
    void sgVFuncRunEnd();
protected:
    ///算子运行虚接口
    virtual EVFucRunStatus run()
    {
        return EVFucRunStatus::Fail;
    }
protected:
    ///算子运行结果
    EVFucRunStatus VFuncRunStatus=EVFucRunStatus::Init;
    ///最后运行信息
    QString VFuncLastInfo="";
    ///最后一次运行耗时
    double LastRunTime=0.0;
/****************************************************************/


};
}
#endif // VFUNCBASE_H
