#通用工程目录
set(ADSD_BULID OFF)
set(XGPH_BULID OFF)
set(XLNG_BULID OFF)
set(XLOG_BULID OFF)
set(XWDG_BULID OFF)

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


