#pragma once

#ifndef LANGDEF_H
#define LANGDEF_H
#include <XLanguage>
#include <XLogger.h>
///App语言定义文件
/*App公共*/
#define App_Common_RunStart         "App_Common_RunStart"       //软件开始运行
#define App_Common_RunEnd           "App_Common_RunEnd"         //软件运行结束
#define App_Common_Loading          "App_Common_Loading"        //正在加载
#define App_Common_InitFinish       "App_Common_InitFinish"     //系统初始化完成
#define App_Common_Open             "App_Common_Open"          //打开
#define App_Common_Close            "App_Common_Close"         //关闭

#define App_LogType_Trace       "App_LogType_Trace"     //追踪
#define App_LogType_Debug       "App_LogType_Debug"     //调试
#define App_LogType_Info        "App_LogType_Info"      //信息
#define App_LogType_Event       "App_LogType_Event"     //事件
#define App_LogType_Warn        "App_LogType_Warn"      //警告
#define App_LogType_Error       "App_LogType_Error"     //错误
#define App_LogType_Critical    "App_LogType_Critical"  //致命




/*App核心*/
#define App_XvWorkMgr_CreateProjectError1 "App_XvWorkMgr_CreateProjectError1" //创建项目%1失败

#define App_XvWorkMgr_XvFlowDefaultName     "App_XvWorkMgr_XvFlowDefaultName"   //流程1

#define App_XvWorkMgr_XvProjectIsNull "App_XvWorkMgr_XvProjectIsNull" //项目为空
#define App_XvWorkMgr_XvFlowIsNull "App_XvWorkMgr_XvFlowIsNull" //流程为空

#define App_XvWorkMgr_CreateXvFlow "App_XvWorkMgr_CreateXvFlow" //创建流程
#define App_XvWorkMgr_CreateXvFlowError1 "App_XvWorkMgr_CreateXvFlowError1" //创建流程失败,当前无项目
#define App_XvWorkMgr_CreateXvFlowError2 "App_XvWorkMgr_CreateXvFlowError2" //创建流程失败,当前流程界面管理器为空
#define App_XvWorkMgr_CreateXvFlowError3 "App_XvWorkMgr_CreateXvFlowError3" //当前流程界面为空

#define App_XvWorkMgr_RemoveXvFlow "App_XvWorkMgr_RemoveXvFlow" //删除流程
#define App_XvWorkMgr_RemoveXvFlowError1 "App_XvWorkMgr_RemoveXvFlowError1" //删除流程失败,当前无项目
#define App_XvWorkMgr_RemoveXvFlowError2 "App_XvWorkMgr_RemoveXvFlowError2" //删除流程失败,无法删除唯一一个流程
#define App_XvWorkMgr_RemoveXvFlowError3 "App_XvWorkMgr_RemoveXvFlowError3" //创删除流程失败,当前流程界面管理器为空

#define App_XvWorkMgr_OnceRunXvFlowError1 "App_XvWorkMgr_OnceRunXvFlowError1" //单次运行流程失败,错误码
#define App_XvWorkMgr_LoopRunXvFlowError1 "App_XvWorkMgr_LoopRunXvFlowError1" //重复运行流程失败,错误码
#define App_XvWorkMgr_StopRunXvFlowError1 "App_XvWorkMgr_StopRunXvFlowError1" //停止运行流程失败,错误码


#define App_MainDockIsNull  "App_MainDockIsNull" //MainDock为空
#define App_XvFlowDockIsNull  "App_XvFlowDockIsNull" //XvFlowDock为空
#define App_XvFlowStatusBarIsNull  "App_XvFlowStatusBarIsNull" //XvFlow状态栏为空


/*[UI]*/
/*UiCommon*/
#define App_UiCommon_Info   "App_UiCommon_Info"   //信息
#define App_UiCommon_Event   "App_UiCommon_Event"   //事件
#define App_UiCommon_Warning   "App_UiCommon_Warning"   //警告
#define App_UiCommon_Error   "App_UiCommon_Error"   //错误
#define App_UiCommon_Critical   "App_UiCommon_Critical"   //致命

#define App_UiCommon_Save   "App_UiCommon_Save"   //保存
#define App_UiCommon_SaveAll   "App_UiCommon_SaveAll"   //保存所有
#define App_UiCommon_Open   "App_UiCommon_Open"   //打开
#define App_UiCommon_Close   "App_UiCommon_Close"   //关闭
#define App_UiCommon_Yes   "App_UiCommon_Yes"   //是
#define App_UiCommon_YesToAll   "App_UiCommon_YesToAll"   //全是
#define App_UiCommon_No   "App_UiCommon_No"   //否
#define App_UiCommon_NoToAll   "App_UiCommon_NoToAll"   //全否
#define App_UiCommon_Abort   "App_UiCommon_Abort"   //中断
#define App_UiCommon_Retry   "App_UiCommon_Retry"   //重试
#define App_UiCommon_Ignore   "App_UiCommon_Ignore"   //忽略
#define App_UiCommon_Confirm   "App_UiCommon_Confirm"   //确定
#define App_UiCommon_Cancel     "App_UiCommon_Cancel"   //取消
#define App_UiCommon_Discard     "App_UiCommon_Discard"   //废弃
#define App_UiCommon_Help     "App_UiCommon_Help"   //帮助
#define App_UiCommon_Apply     "App_UiCommon_Apply"   //引用
#define App_UiCommon_Reset     "App_UiCommon_Reset"   //重置
#define App_UiCommon_Reset     "App_UiCommon_Reset"   //重置
#define App_UiCommon_RestoreDefaults     "App_UiCommon_RestoreDefaults"   //恢复默认

/*AppMainWindow*/
//标题栏
#define App_AppMainWindow_File          "App_AppMainWindow_File" //文件
#define App_AppMainWindow_Setting          "App_AppMainWindow_Setting" //设置
#define App_AppMainWindow_System          "App_AppMainWindow_System" //系统
#define App_AppMainWindow_Tool          "App_AppMainWindow_Tool" //工具
#define App_AppMainWindow_Help          "App_AppMainWindow_Help" //帮助
//标题栏-文件
#define App_AppMainWindow_NewProject    "App_AppMainWindow_NewProject" //新建项目
#define App_AppMainWindow_OpenProject    "App_AppMainWindow_OpenProject" //打开项目
#define App_AppMainWindow_SaveProject    "App_AppMainWindow_SaveProject" //保存项目
//标题栏-设置
#define App_AppMainWindow_SystemSetting    "App_AppMainWindow_SystemSetting" //系统设置
#define App_AppMainWindow_ProjectSetting    "App_AppMainWindow_ProjectSetting" //项目设置
//标题栏-帮助
#define App_AppMainWindow_Language   "App_AppMainWindow_Language" //语言
#define App_AppMainWindow_HelpDoc    "App_AppMainWindow_HelpDoc" //帮助文档
#define App_AppMainWindow_About      "App_AppMainWindow_About" //关于
//工具栏
#define App_AppMainWindow_ProjectOnceRun      "App_AppMainWindow_ProjectOnceRun" //项目单次运行
#define App_AppMainWindow_ProjectLoopRun      "App_AppMainWindow_ProjectLoopRun" //项目重复运行
#define App_AppMainWindow_ProjectStop         "App_AppMainWindow_ProjectStop" //项目停止运行
//Msg
#define App_AppMainWindow_MsgSwitchLangError  "App_AppMainWindow_MsgSwitchLangError" //切换语言失败
#define App_AppMainWindow_MsgSwitchLangSuccess  "App_AppMainWindow_MsgSwitchLangSuccess" //切换语言成功，请重启软件

/*Frm*/
#define App_Ui_FrmLogShow           "App_Ui_FrmLogShow"     //日志显示
#define App_Ui_FrmLogShowClearLog       "App_Ui_FrmLogShowClearLog"     //清除日志
#define App_Ui_FrmLogOpenLogDir         "App_Ui_FrmLogOpenLogDir"     //打开日志目录

#define App_Ui_FrmThreadMonitor     "App_Ui_FrmThreadMonitor"   //线程监控
#define App_Ui_FrmThreadMonitorThreadId     "App_Ui_FrmThreadMonitorThreadId"   //线程Id
#define App_Ui_FrmThreadMonitorThreadGroup     "App_Ui_FrmThreadMonitorThreadGroup"   //线程组
#define App_Ui_FrmThreadMonitorThreadName     "App_Ui_FrmThreadMonitorThreadName"   //线程名
#define App_Ui_FrmThreadMonitorThreadPriority     "App_Ui_FrmThreadMonitorThreadPriority"   //线程优先权
#define App_Ui_FrmThreadMonitorThreadRunElapsed     "App_Ui_FrmThreadMonitorThreadRunElapsed"   //线程运行耗时
#define App_Ui_FrmThreadMonitorThreadRunState     "App_Ui_FrmThreadMonitorThreadRunState"   //线程运行状态
#define App_Ui_FrmThreadMonitorThreadRuning     "App_Ui_FrmThreadMonitorThreadRuning"   //线程运行
#define App_Ui_FrmThreadMonitorThreadStop     "App_Ui_FrmThreadMonitorThreadStop"   //线程停止
#define App_Ui_FrmThreadMonitorThreadMsg     "App_Ui_FrmThreadMonitorThreadMsg"   //线程消息

#define App_Ui_FrmVisionImage    "App_Ui_FrmVisionImage" //图像
#define App_Ui_FrmVisionWork     "App_Ui_FrmVisionWork"  //视觉流程

#define App_Ui_FrmXvFuncAsmUp         "App_Ui_FrmXvFuncAsmUp"      //向上滚动
#define App_Ui_FrmXvFuncAsmDown       "App_Ui_FrmXvFuncAsmDown"      //向下滚动
#define App_Ui_FrmXvFuncAsmExpand     "App_Ui_FrmXvFuncAsmExpand"        //展开
#define App_Ui_FrmXvFuncAsmCollapse   "App_Ui_FrmXvFuncAsmCollapse"      //折叠

#define App_Ui_FrmAbout                 "App_Ui_FrmAbout" //关于
/*UiXvWorkMgr*/
//流程
#define App_UiXvWorkMgr_FlowId          "App_UiXvWorkMgr_FlowId"   //流程ID
#define App_UiXvWorkMgr_FlowName          "App_UiXvWorkMgr_FlowName"   //流程名
#define App_UiXvWorkMgr_FlowRunStatus       "App_UiXvWorkMgr_FlowRunStatus"   //运行结果
#define App_UiXvWorkMgr_FlowRunMsg          "App_UiXvWorkMgr_FlowRunMsg"   //运行信息
#define App_UiXvWorkMgr_FlowRunElapsed      "App_UiXvWorkMgr_FlowRunElapsed"   //运行耗时

#define App_UiXvWorkMgr_FlowAdd          "App_UiXvWorkMgr_FlowAdd"   //流程添加
#define App_UiXvWorkMgr_FlowRename          "App_UiXvWorkMgr_FlowRename"   //流程重命名
#define App_UiXvWorkMgr_FlowDel          "App_UiXvWorkMgr_FlowDel"   //流程删除
#define App_UiXvWorkMgr_FlowIsDel          "App_UiXvWorkMgr_FlowIsDel"   //是否删除流程

#define App_UiXvWorkMgr_FlowOnceRun      "App_UiXvWorkMgr_FlowOnceRun"   //流程单次运行
#define App_UiXvWorkMgr_FlowLoopRun      "App_UiXvWorkMgr_FlowLoopRun"   //流程重复运行
#define App_UiXvWorkMgr_FlowStop         "App_UiXvWorkMgr_FlowStop"      //流程停止运行
#define App_UiXvWorkMgr_FlowProp         "App_UiXvWorkMgr_FlowProp"      //流程属性

//算子
#define App_UiXvWorkMgr_FuncRename          "App_UiXvWorkMgr_FuncRename"   //算子重命名
#define App_UiXvWorkMgr_FuncShow            "App_UiXvWorkMgr_FuncShow"   //显示界面
#define App_UiXvWorkMgr_FuncId              "App_UiXvWorkMgr_FuncId"       //算子ID
#define App_UiXvWorkMgr_FuncRole            "App_UiXvWorkMgr_FuncRole"   //算子标识符
#define App_UiXvWorkMgr_FuncRunStatus       "App_UiXvWorkMgr_FuncRunStatus"   //运行结果
#define App_UiXvWorkMgr_FuncRunMsg          "App_UiXvWorkMgr_FuncRunMsg"   //运行信息
#define App_UiXvWorkMgr_FuncRunElapsed      "App_UiXvWorkMgr_FuncRunElapsed"   //运行耗时

#define App_UiXvWorkMgr_SceneAddXvFunc   "App_UiXvWorkMgr_SceneAddXvFunc"   //添加算子
#define App_UiXvWorkMgr_SceneZoomToFit   "App_UiXvWorkMgr_SceneZoomToFit"   //缩放到合适范围

#define App_UiXvWorkMgr_XvFlowRunStart "App_UiXvWorkMgr_XvFlowRunStart" //流程<%1>开始运行
#define App_UiXvWorkMgr_XvFlowRunEnd "App_UiXvWorkMgr_XvFlowRunEnd" //流程<%1>运行结束
#define App_UiXvWorkMgr_XvFlowRunStop "App_UiXvWorkMgr_XvFlowRunStop" //流程<%1>运行停止

#endif // LANGDEF_H
