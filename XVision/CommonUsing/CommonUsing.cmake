#当前构建模式:Debug-No Release-Off
set(CurBuildType_IsDebug ON)


#include_dir:

set(AdsDocking_Inc CommonUsing/Project/AdsDocking/include)
set(XFlowGraphics_Inc CommonUsing/Project/XFlowGraphics/include)
set(XLanguage_Inc CommonUsing/Project/XLanguage/include)
set(XLog_Inc CommonUsing/Project/XLog/include)
set(XWidget_Inc CommonUsing/Project/XWidget/XWidget/include)
set(XConcurrent_Inc CommonUsing/Project/XConcurrent/include)


#link_dir:

if (NOT MSVC)
    set(OUTPUT_DIR mingw)
else()
    set(OUTPUT_DIR msvc)
endif()


if(CurBuildType_IsDebug) #debug lib目录为LibD
   set(COMMON_USING_LINK_DIR  CommonUsing/LibD/${OUTPUT_DIR})
else() #release lib目录为Lib
   set(COMMON_USING_LINK_DIR  CommonUsing/Lib/${OUTPUT_DIR})
endif()
