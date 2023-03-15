cmake_minimum_required(VERSION 3.14)

project(XvCommon LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../CommonCMake/CommonProjectOutputSet.cmake)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core XML)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core XML)

#[[**************添加包含目录**************]]

#添加工程包含目录
list(APPEND INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)

#[[**************添加链接库**************]]

#添加QT库
list(APPEND LINK_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Xml
)


add_library(XvCommon SHARED
  include/XvCommonGlobal.h
  include/XmlSerializable.h
  src/XmlSerializable.cpp
)

#设置包含目录
include_directories(${INCLUDE_DIR})

target_link_libraries(XvCommon PRIVATE ${LINK_LIBS})

target_compile_definitions(XvCommon PRIVATE XVCOMMON_LIBRARY)
