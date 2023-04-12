cmake_minimum_required(VERSION 3.5)

project(XVision VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENABLE_BREAKPAD ON)#使能软件崩溃生成dump文件

include (../CommonCMake/CommonProjectOutputSet.cmake)
include (../CommonUsing/CommonUsing.cmake)


#寻找QT库
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Xml Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml Concurrent)

set(XVAPPLICATION_CLASS QApplication)
add_subdirectory(SingleApplication)
if(ENABLE_BREAKPAD)
    add_subdirectory(QBreakpad)
endif()



#[[**************添加链接库**************]]

#添加QT库
list(APPEND APP_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Concurrent
)
if(ENABLE_BREAKPAD)
    list(APPEND APP_LIBS QBreakpad)
endif()

#添加工程库
list(APPEND APP_LIBS
    SingleApplication
    XvCore #核心库
    XvTokenMsg #Token消息库
    XvUtils #工具库
)
#添加公共库
list(APPEND APP_LIBS
    XWidget         #控件库
    XLog            #日志库
    XLanguage       #多语言库
    AdsDocking      #悬浮窗口库
    XGraphics       #流程绘图库
    XConcurrent     #多线程管理库
)



#[[**************添加包含目录**************]]
if(ENABLE_BREAKPAD)
    list(APPEND APP_INCLUDE_DIR QBreakpad/handler)
endif()
#添加工程包含目录
list(APPEND APP_INCLUDE_DIR
    ../SingleApplication
    ../XvCore/include
    ../XvTokenMsg/include
    ../XvUtils/include
)
#添加第三方库
list(APPEND APP_INCLUDE_DIR
    ../${XWidget_Inc}
    ../${XLog_Inc}
    ../${XLanguage_Inc}
    ../${AdsDocking_Inc}
    ../${XGraphics_Inc}
    ../${XConcurrent_Inc}

)


#[[**************添加连接库文件路径**************]]

if (NOT MSVC)
    set(LINK_3RDLIB_DIR mingw)
else()
    set(LINK_3RDLIB_DIR msvc)
endif()

#添加依赖库目录
list(APPEND APP_LINK_DIR
    ../${COMMON_USING_LINK_DIR}
)
link_directories(${APP_LINK_DIR})

#[[**************添加工程文件**************]]

file(GLOB MODEL      Model/*.*)
file(GLOB CORE       Core/*.*)
file(GLOB DEF        Def/*.*)
file(GLOB UTILS      Utils/*.*)

file(GLOB UIMAIN     UiMain/*.*)
file(GLOB UICORE     UiCore/*.*)
file(GLOB UIWORK     UiWork/*.*)
file(GLOB UIWORK_UIXVFUNC     UiWork/UiXvFunc/*.*)
file(GLOB UIOUTPUT   UIOutput/*.*)



set(PROJECT_RES
    Res/AppRes.qrc
)


set(PROJECT_SOURCES
    main.cpp
    ${MODEL}
    ${CORE}
    ${DEF}
    ${UTILS}

    ${UIMAIN}
    ${UICORE}
    ${UIWORK}
    ${UIWORK_UIXVFLOW}
    ${UIWORK_UIXVFUNC}
    ${UIOUTPUT}
)

#生成可执行文件
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_RES}
)

#添加当前工程包含
list(APPEND APP_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Def
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils

    ${CMAKE_CURRENT_SOURCE_DIR}/UiMain
    ${CMAKE_CURRENT_SOURCE_DIR}/UiCore
    ${CMAKE_CURRENT_SOURCE_DIR}/UiWork
    ${CMAKE_CURRENT_SOURCE_DIR}/UiWork/UiXvFunc
    ${CMAKE_CURRENT_SOURCE_DIR}/UIOutput 

)



#[[**************链接-包含**************]]

#包含目录
include_directories(${APP_INCLUDE_DIR})
#连接[第三方库/内部库] 动态
target_link_libraries(${PROJECT_NAME} PRIVATE ${APP_LIBS})
#[[**************生成设置**************]]

#set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)
if(ENABLE_BREAKPAD)
    target_compile_definitions(XVision PRIVATE QBREAKPAD_ENABLE)
endif()

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(XVision)
endif()



add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
