#ifndef LANGDEF_H
#define LANGDEF_H
#include "XLanguage.h"
#include "XLogger.h"

#define Core_Plg_InitFail               "Core_Plg_InitFail"                     ///插件初始化失败
#define Core_XvFunc_RegFail            "Core_XvFunc_RegFail"                  ///算子注册失败
#define Core_XvFunc_RegSuccess         "Core_XvFunc_RegSuccess"               ///算子注册成功

#define Core_XvFuncType_Null                                "Core_XvFuncType_Null"                      ///无
#define Core_XvFuncType_ImageAcquisition                    "Core_XvFuncType_ImageAcquisition"          ///图像采集
#define Core_XvFuncType_Calibration                         "Core_XvFuncType_Calibration"               ///校正标定
#define Core_XvFuncType_Contraposition                      "Core_XvFuncType_Contraposition"            ///对位
#define Core_XvFuncType_Location                            "Core_XvFuncType_Location"                  ///定位
#define Core_XvFuncType_ImageProcessing                     "Core_XvFuncType_ImageProcessing"           ///图像处理
#define Core_XvFuncType_Measurement                         "Core_XvFuncType_Measurement"               ///测量
#define Core_XvFuncType_DefectDetection                     "Core_XvFuncType_DefectDetection"           ///检测
#define Core_XvFuncType_Recognition                         "Core_XvFuncType_Recognition"               ///识别
#define Core_XvFuncType_Communication                       "Core_XvFuncType_Communication"             ///通讯
#define Core_XvFuncType_MachineLearning                     "Core_XvFuncType_MachineLearning"           ///机器学习
#define Core_XvFuncType_DataProcessing                      "Core_XvFuncType_DataProcessing"            ///数据处理
#define Core_XvFuncType_Logic                               "Core_XvFuncType_Logic"                     ///逻辑
#define Core_XvFuncType_Special                             "Core_XvFuncType_Special"                   ///特殊
#define Core_XvFuncType_Other                               "Core_XvFuncType_Other"                     ///其他
#define Core_XvFuncType_User                                "Core_XvFuncType_User"                      ///用户


#endif // LANGDEF_H
