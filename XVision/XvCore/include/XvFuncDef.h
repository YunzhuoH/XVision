#ifndef XVFUNCDEF_H
#define XVFUNCDEF_H

#include "XvCoreGlobal.h"
#include <qglobal.h>
#include <qmetaobject.h>
#include <QPixmap>

namespace XvCore
{
Q_NAMESPACE_EXPORT(XVCORE_EXPORT)

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
typedef struct S_XVFUNC_BASE_INFO
{
    S_XVFUNC_BASE_INFO()
    {

    }
    S_XVFUNC_BASE_INFO(const QString& _role,
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
}XvFuncBaseInfo,*PXvFuncBaseInfo;



}



#endif // XVFUNCDEF_H
