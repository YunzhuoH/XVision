cmake_minimum_required(VERSION 3.14)

project(XvData LANGUAGES CXX)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/Data

)

#[[**************添加链接库**************]]

#添加QT库
list(APPEND LINK_LIBS
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Xml
)

file(GLOB INCLUDE     include/*)
file(GLOB SRC     src/*.*)
file(GLOB DATA     Data/*.*)
file(GLOB XOBJECT     XObject/*.*)

add_library(XvData SHARED
    ${INCLUDE}
    ${SRC}
    ${DATA}
    ${XOBJECT}
)

#设置包含目录
include_directories(${INCLUDE_DIR})

target_link_libraries(XvData PRIVATE ${LINK_LIBS})

target_compile_definitions(XvData PRIVATE XVDATA_LIBRARY)
