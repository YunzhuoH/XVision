#pragma once

#ifndef LANGDEF_H
#define LANGDEF_H
#include <XLanguage>
#include <XLogger.h>
///App语言定义文件

#define App_RunStart         "App_RunStart"       //软件开始运行
#define App_RunEnd           "App_RunEnd"         //软件运行结束

#define App_Open             "App_Open"          //打开
#define App_Close            "App_Close"         //关闭

#define App_MainDockIsNull  "App_MainDockIsNull" //MainDock为空
#define App_XvFlowDockIsNull  "App_XvFlowDockIsNull" //XvFlowDock为空
#define App_XvFlowStatusBarIsNull  "App_XvFlowStatusBarIsNull" //XvFlow状态栏为空

#define App_LogType_Trace       "App_LogType_Trace"     //追踪
#define App_LogType_Debug       "App_LogType_Debug"     //调试
#define App_LogType_Info        "App_LogType_Info"      //信息
#define App_LogType_Event       "App_LogType_Event"     //事件
#define App_LogType_Warn        "App_LogType_Warn"      //警告
#define App_LogType_Error       "App_LogType_Error"     //错误
#define App_LogType_Critical    "App_LogType_Critical"  //致命

#define App_Ui_FrmLogShowTitle           "App_Ui_FrmLogShowTitle"     //日志显示
#define App_Ui_FrmLogShowClearLog       "App_Ui_FrmLogShowClearLog"     //清除日志
#define App_Ui_FrmLogOpenLogDir         "App_Ui_FrmLogOpenLogDir"     //打开日志目录


#define App_Ui_FrmVisionImageTitle    "App_Ui_FrmVisionImageTitle" //图像
#define App_Ui_FrmVisionWorkTitle     "App_Ui_FrmVisionWorkTitle"  //视觉流程

#define App_Ui_FrmXvFuncAsmUp         "App_Ui_FrmXvFuncAsmUp"      //向上滚动
#define App_Ui_FrmXvFuncAsmDown       "App_Ui_FrmXvFuncAsmDown"      //向下滚动
#define App_Ui_FrmXvFuncAsmExpand     "App_Ui_FrmXvFuncAsmExpand"        //展开
#define App_Ui_FrmXvFuncAsmCollapse   "App_Ui_FrmXvFuncAsmCollapse"      //折叠

#define App_UiCommon_FlowAdd          "App_UiCommon_FlowAdd"   //流程添加
#define App_UiCommon_FlowDel          "App_UiCommon_FlowDel"   //流程删除
#define App_UiCommon_FlowOnceRun      "App_UiCommon_FlowOnceRun"   //流程单次运行
#define App_UiCommon_FlowLoopRun      "App_UiCommon_FlowLoopRun"   //流程重复运行
#define App_UiCommon_FlowStop         "App_UiCommon_FlowStop"      //流程停止运行
#define App_UiCommon_FlowProp         "App_UiCommon_FlowProp"      //流程属性

#endif // LANGDEF_H
