cmake_minimum_required(VERSION 3.14)

project(VFuncTest_A LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (../../CommonCMake/CommonXvFuncOutputSet.cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_library(VFuncTest_A SHARED
  VFuncTest_A_global.h
  VFuncTest_A_FactoryPlugin.h VFuncTest_A_FactoryPlugin.cpp
  VFunc_T1.h VFunc_T1.cpp
  VFunc_T2.h VFunc_T2.cpp
  XvFuncTest.h XvFuncTest.cpp
  VTest1.h VTest1.cpp
)

include_directories(
    ../../XvCore/include
    ../../XvTokenMsg/include
)


target_link_libraries(VFuncTest_A PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets
    XvCore
    XvTokenMsg)

target_compile_definitions(VFuncTest_A PRIVATE VFUNCTEST_A_LIBRARY)


add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
