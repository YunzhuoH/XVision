#ifndef XVFUNCDEF_H
#define XVFUNCDEF_H

#include "XvCoreGlobal.h"
#include <qglobal.h>
#include <qmetaobject.h>
#include <QPixmap>

#include "XvError.h"

/*-----------------------------算子预定义-----------------------------*/
/*算子5种状态:
1.未运行:Init
2.正在运行:Running
3.运行成功:Ok
4.运行失败:Fail
5.运行错误:Error
*/
#define XvFuncRunStatus_Init       0
#define XvFuncRunStatus_Running    1
#define XvFuncRunStatus_Ok         2
#define XvFuncRunStatus_Fail       3
#define XvFuncRunStatus_Error      4

#define XvFuncRunStatus_Init_Str       "Init"
#define XvFuncRunStatus_Running_Str    "Running"
#define XvFuncRunStatus_Ok_Str         "Ok"
#define XvFuncRunStatus_Fail_Str       "Fail"
#define XvFuncRunStatus_Error_Str      "Error"

/*-----------------------------流程预定义-----------------------------*/

/*流程5种状态:
1.未运行:Init
2.正在运行:Running
3.运行成功:Ok
4.运行失败:Fail
5.运行错误:Error
*/
#define XvFlowRunStatus_Init       0
#define XvFlowRunStatus_Running    1
#define XvFlowRunStatus_Ok         2
#define XvFlowRunStatus_Fail       3
#define XvFlowRunStatus_Error      4

#define XvFlowRunStatus_Init_Str       "Init"
#define XvFlowRunStatus_Running_Str    "Running"
#define XvFlowRunStatus_Ok_Str         "Ok"
#define XvFlowRunStatus_Fail_Str       "Fail"
#define XvFlowRunStatus_Error_Str      "Error"

/*-----------------------------*********-----------------------------*/
namespace XvCore
{
Q_NAMESPACE_EXPORT(XVCORE_EXPORT)

/*-----------------------------算子定义-----------------------------*/
///算子类型
typedef enum class E_XvFunc_Type
{
    Null=0x0000,//无:默认类型,无效算子
    ImageAcquisition=0x0001,//图像采集
    Calibration=0x0002,//校正标定
    Contraposition=0x0003,//对位
    Location=0x0004,//定位
    ImageProcessing=0x0005,//图像处理
    Measurement=0x0006,//测量:圆线点
    DefectDetection=0x0007,//检测
    Recognition=0x0008,//识别:条码/二维码/OCR
    Communication=0x0009,//通讯
    MachineLearning=0x000A,//机器学习
    DataProcessing=0x000B,//数据处理


    Logic=0x000F, //逻辑:判断/循环等特殊算子
    Special=0x0010,//特殊:特殊用途算子
    Other=0x0100,//其他:其他类型算子
    User=0xFFFF,//用户:用户自定义算子
}EXvFuncType,*PEXvFuncType;
Q_ENUM_NS(E_XvFunc_Type)


///算子类型信息
typedef struct S_XVFUNC_TYPE_INFO
{
    S_XVFUNC_TYPE_INFO()
    {
        type=XvCore::EXvFuncType::Null;
    }
    S_XVFUNC_TYPE_INFO(const XvCore::EXvFuncType& _type,
                       const QString& _name,
                       const QPixmap& _icon):
        type(_type), name(_name), icon(_icon)
    {

    }
    ///是否有效
    bool isValid()
    {
        return type!=XvCore::EXvFuncType::Null;//NULL类型无效
    }
    XvCore::EXvFuncType type;//算子类型
    QString name;  //算子类型名称
    QPixmap icon;  //算子类型图标

}XvFuncTypeInfo,*PXvFuncTypeInfo;

///算子基本信息
typedef struct S_XVFUNC_INFO
{
    S_XVFUNC_INFO()
    {

    }
    S_XVFUNC_INFO(const QString& _role,
                       const XvCore::EXvFuncType& _type,
                       const QString& _name,
                       const QPixmap& _icon,
                       const QMetaObject& _meta):
        role(_role),type(_type), name(_name), icon(_icon), meta(_meta)
    {

    }
    ///是否有效
    bool isValid()
    {
        return !role.isEmpty();//role为空无效
    }
    QString role;  //算子功能
    XvCore::EXvFuncType type;//算子分类
    QString name;  //算子名称
    QPixmap icon;  //算子图标
    QMetaObject meta;//算子元数据
}XvFuncInfo,*PXvFuncInfo;


///算子状态
typedef enum class E_XvFunc_Run_Status
{
    Init=XvFuncRunStatus_Init,//初始状态 未运行
    Running=XvFuncRunStatus_Running,//正在运行
    Ok=XvFuncRunStatus_Ok, //运行成功    运行成功返回
    Fail=XvFuncRunStatus_Fail, //运行失败  运行存在错误
    Error=XvFuncRunStatus_Error,//运行错误  中断强制退出运行
}EXvFuncRunStatus,*PEXvFuncRunStatus;
Q_ENUM_NS(E_XvFunc_Run_Status)


///算子运行信息
typedef struct S_XVFUNC_RUN_INFO
{
    S_XVFUNC_RUN_INFO()
    {
        runStatus=EXvFuncRunStatus::Init;
        runMsg="";
        runElapsed=0.0;
    }
    ///算子运行结果
    EXvFuncRunStatus runStatus;
    ///运行消息
    QString runMsg;
    ///运行耗时
    double runElapsed;
}XvFuncRunInfo,*PXvFuncRunInfo;

/*-----------------------------流程定义-----------------------------*/
///流程状态
typedef enum class E_XvFlow_Run_Status
{
    Init=XvFuncRunStatus_Init,//初始状态 未运行
    Running=XvFuncRunStatus_Running,//正在运行
    Ok=XvFuncRunStatus_Ok, //运行成功    运行成功返回
    Fail=XvFuncRunStatus_Fail, //运行失败  运行存在错误
    Error=XvFuncRunStatus_Error,//运行错误  中断强制退出运行
}EXvFlowRunStatus,*PEXvFlowRunStatus;
Q_ENUM_NS(E_XvFlow_Run_Status)

///流程运行信息
typedef struct S_XVFLOW_RUN_INFO
{
    S_XVFLOW_RUN_INFO()
    {
        runStatus=EXvFlowRunStatus::Init;
        runCode=RET_XV_SUCCESS;
        runMsg="";
        runElapsed=0.0;
    }
    ///最后算子运行结果
    EXvFlowRunStatus runStatus;
    ///最后运行代码 成功为0 失败非0
    RetXv runCode;
    ///最后运行消息
    QString runMsg;
    ///最后运行耗时
    double runElapsed;
}XvFlowRunInfo,*PXvFlowRunInfo;


}



#endif // XVFUNCDEF_H
