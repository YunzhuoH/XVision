#ifndef XVFUNCDEF_H
#define XVFUNCDEF_H

#include <QObject>

///算子类型
typedef enum class E_XvFunc_Type
{
    Null=0x0000,//通用无
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


    Logic=0x000F, //逻辑
    Special=0x0010,//特殊
    Other=0x0100,//其他
    User=0xFFFF,//用户
}EXvFuncType,*PEXvFuncType;



#endif // XVFUNCDEF_H
