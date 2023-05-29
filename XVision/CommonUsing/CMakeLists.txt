#通用工程目录
set(ADSD_BULID OFF) #AdsDocking     浮动窗口库
set(XFGP_BULID OFF) #XFlowGraphics   流程绘制库
set(XLNG_BULID OFF) #XLanguage      多语言库
set(XLOG_BULID OFF) #XLog           日志库
set(XWDG_BULID OFF) #XWidget        自定义控件库
set(XCON_BULID OFF) #XConcurrent    多线程统一管理

if(ADSD_BULID)
    add_subdirectory(Project/AdsDocking)
endif()

if(XFGP_BULID)
    add_subdirectory(Project/XFlowGraphics)
endif()

if(XLNG_BULID)
    add_subdirectory(Project/XLanguage)
endif()

if(XLOG_BULID)
    add_subdirectory(Project/XLog)
endif()

if(XWDG_BULID)
    add_subdirectory(Project/XWidget)
endif()

if(XCON_BULID)
    add_subdirectory(Project/XConcurrent)
endif()

