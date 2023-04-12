#通用工程目录
set(ADSD_BULID ON) #AdsDocking     浮动窗口库
set(XGPH_BULID ON)  #XGraphics      流程绘制库
set(XLNG_BULID ON) #XLanguage      多语言库
set(XLOG_BULID ON) #XLog           日志库
set(XWDG_BULID ON) #XWidget        自定义控件库
set(XCON_BULID ON)  #XConcurrent    多线程统一管理

if(ADSD_BULID)
    add_subdirectory(Project/AdsDocking)
endif()

if(XGPH_BULID)
    add_subdirectory(Project/XGraphics)
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

