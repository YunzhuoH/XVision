cmake_minimum_required(VERSION 3.14)

project(XvFuncSystem LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../../CommonCMake/CommonXvFuncOutputSet.cmake)
include (../../CommonUsing/CommonUsing.cmake)


#寻找QT库
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

#[[**************添加链接库**************]]
#添加QT库
list(APPEND _LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)
#添加工程库
list(APPEND _LIBS
    XvCore #核心库
    XvData #数据库
    XvTokenMsg #Token消息库
    XvUtils #工具库
)

#添加公共库
list(APPEND _LIBS
    XWidget         #控件库
    XLog            #日志库
    XLanguage       #多语言库
    XConcurrent     #多线程管理库
)
#[[**************添加包含目录**************]]

#添加工程包含目录
list(APPEND _INCLUDE_DIR
    ../../XvCore/include
    ../../XvTokenMsg/include
    ../../XvUtils/include
    ../../XvData/include
)
#添加第三方库
list(APPEND _INCLUDE_DIR
    ../../${XWidget_Inc}
    ../../${XLog_Inc}
    ../../${XLanguage_Inc}
    ../../${XConcurrent_Inc}

)

#[[**************添加连接库文件路径**************]]

#添加依赖库目录
list(APPEND _LINK_DIR
    ../../${COMMON_USING_LINK_DIR}
)
link_directories(${_LINK_DIR})


#[[**************添加工程文件**************]]
file(GLOB INCLUDE include/*.*)
file(GLOB SRC src/*.*)
file(GLOB Model Model/*.*)
file(GLOB Helper Helper/*.*)

file(GLOB ImageAcquisition ImageAcquisition/*.*)
file(GLOB DataProcessing DataProcessing/*.*)
file(GLOB User User/*.*)
file(GLOB Logic Logic/*.*)
file(GLOB Other Other/*.*)


#设置工程文件
set(PROJECT_SOURCES
    ${INCLUDE}
    ${SRC}

    ${Model}
    ${Helper}

    ${DataProcessing}
    ${ImageAcquisition}
    ${User}
    ${Logic}
    ${Other}

)
set(PROJECT_RES
    res/Res.qrc
)
add_library(XvFuncSystem SHARED
    ${PROJECT_SOURCES}
    ${PROJECT_RES}
)

#添加当前工程包含
list(APPEND _INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Helper

    ${CMAKE_CURRENT_SOURCE_DIR}/ImageAcquisition
    ${CMAKE_CURRENT_SOURCE_DIR}/DataProcessing
    ${CMAKE_CURRENT_SOURCE_DIR}/User
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic
    ${CMAKE_CURRENT_SOURCE_DIR}/Other
)

#[[**************链接-包含**************]]

#包含目录
include_directories(${_INCLUDE_DIR})
#连接[第三方库/内部库] 动态
target_link_libraries(${PROJECT_NAME} PRIVATE ${_LIBS})


target_compile_definitions(XvFuncSystem PRIVATE XVFUNCSYSTEM_LIBRARY)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
