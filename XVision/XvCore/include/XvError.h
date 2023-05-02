#ifndef XVERROR_H
#define XVERROR_H


typedef int RetXv;
/*---------------------------错误码---------------------------*/
#define Ret_Xv_Success              0x00000000    //成功
#define Ret_Xv_FuncNoRun            0x00000001    //算子未运行
#define Ret_Xv_FuncRunning          0x00000002    //算子正在运行

#define Ret_Xv_FlowIllegal          0x00000003    //流程不合法
#define Ret_Xv_FlowNoRun            0x00000004    //流程未运行
#define Ret_Xv_FlowRunning          0x00000005    //流程正在运行
#define Ret_Xv_FlowTimeOut          0x00000007    //流程超时
#define Ret_Xv_FlowWaitTimeOut      0x00000008    //流程等待超时

#endif // XVERROR_H
