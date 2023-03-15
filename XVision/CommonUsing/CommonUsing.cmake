﻿set(COMMON_USING_BUILD_TYPE Debug)
#set(COMMON_USING_BUILD_TYPE Release)

#include_dir:

set(AdsDocking_Inc CommonUsing/Project/AdsDocking/include)
set(XGraphics_Inc CommonUsing/Project/XGraphics/include)
set(XLanguage_Inc CommonUsing/Project/XLanguage/include)
set(XLog_Inc CommonUsing/Project/XLog/include)
set(XWidget_Inc CommonUsing/Project/XWidget/XWidget/include)


#link_dir:

if (NOT MSVC)
    set(OUTPUT_DIR mingw)
else()
    set(OUTPUT_DIR msvc)
endif()

if("${COMMON_USING_BUILD_TYPE}" STREQUAL "Debug") #debug lib目录为LibD
    set(COMMON_USING_LINK_DIR  CommonUsing/LibD/${OUTPUT_DIR})
 else() #release lib目录为Lib
    set(COMMON_USING_LINK_DIR  CommonUsing/Lib/${OUTPUT_DIR})
 endif()