cmake_minimum_required(VERSION 3.14)

project(XvCore LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../CommonCMake/CommonProjectOutputSet.cmake)
include (../CommonUsing/CommonUsing.cmake)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets XML Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets XML Concurrent)




#[[**************添加包含目录**************]]

#添加依赖库包含目录
list(APPEND CORE_INCLUDE_DIR
  ../XvData/include
  ../XvTokenMsg/include
  ../${XLog_Inc}
  ../${XLanguage_Inc}
  ../${XConcurrent_Inc}
)

#添加工程包含目录
list(APPEND CORE_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Plugin
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Def

)
#[[**************添加链接库**************]]

#添加工程库
list(APPEND CORE_LIBS
    XvTokenMsg
    XvData
    XLog        #日志库
    XLanguage   #多语言库
    XConcurrent     #多线程管理库
)

#添加QT库
list(APPEND CORE_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Concurrent
)

#[[**************添加连接库文件路径**************]]

#添加依赖库目录
list(APPEND CORE_LINK_DIR
    ../${COMMON_USING_LINK_DIR}
)
link_directories(${CORE_LINK_DIR})


#[[**************添加工程文件**************]]

file(GLOB INCLUDE include/*.*)
file(GLOB PLUGIN Plugin/*.*)
file(GLOB CORE Core/*.*)
file(GLOB DEF Def/*.*)

#设置工程文件
set(PROJECT_SOURCES
    ${INCLUDE}
    ${DEF}
    ${PLUGIN}
    ${CORE}
)
set(PROJECT_RES
    res/Res.qrc
)
#添加工程文件
add_library(${PROJECT_NAME} SHARED
   ${PROJECT_SOURCES}
   ${PROJECT_RES}
)

#设置包含目录
include_directories(${CORE_INCLUDE_DIR})



target_link_libraries(${PROJECT_NAME} PRIVATE ${CORE_LIBS})

target_compile_definitions(${PROJECT_NAME} PRIVATE XVCORE_LIBRARY)



#set_target_properties(${PROJECT_NAME} PROPERTIES
#    AUTOMOC ON
#    AUTORCC ON
#    CXX_EXTENSIONS OFF
#    EXPORT_NAME ${PROJECT_NAME}
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
