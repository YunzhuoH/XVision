cmake_minimum_required(VERSION 3.14)

project(XVFuncSystem LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../../CommonCMake/CommonXvFuncOutputSet.cmake)



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(XVFuncSystem SHARED
  XVFuncSystem_global.h
  xvfuncsystem.cpp
  xvfuncsystem.h
)

target_link_libraries(XVFuncSystem PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(XVFuncSystem PRIVATE XVFUNCSYSTEM_LIBRARY)


add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
