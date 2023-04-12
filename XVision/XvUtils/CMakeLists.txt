cmake_minimum_required(VERSION 3.14)

project(XvUtils LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../CommonCMake/CommonProjectOutputSet.cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB INCLUDE include/*.*)
file(GLOB SRC src/*.*)

add_library(XvUtils SHARED
  ${INCLUDE}
  ${SRC}
)

#添加工程包含目录
list(APPEND INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)


include_directories(${INCLUDE_DIR})

target_link_libraries(XvUtils PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(XvUtils PRIVATE XVUTILS_LIBRARY)
