cmake_minimum_required(VERSION 3.14)

project(XvTokenMsg  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../CommonCMake/CommonProjectOutputSet.cmake)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(XvTokenMsg SHARED
  include/XvTokenMsgGlobal.h
  include/XvTokenMsg.h
  include/XvTokenMsgMgr.h src/XvTokenMsgMgr.cpp
  include/IXvTokenMsgable.h src/IXvTokenMsgable.cpp
)

#[[**************添加包含目录**************]]

#添加依赖库包含目录
list(APPEND INCLUDE_DIR
)

#添加工程包含目录
list(APPEND INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)

#设置包含目录
include_directories(${INCLUDE_DIR})

target_link_libraries(XvTokenMsg PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(XvTokenMsg PRIVATE XVTOKENMSG_LIBRARY)

