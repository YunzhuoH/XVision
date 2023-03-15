cmake_minimum_required(VERSION 3.14)

project(XWidgetDesignerPlugin LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core UiPlugin Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core UiPlugin Widgets)

qt_add_plugin(XWidgetDesignerPlugin)

file(GLOB BUTTON Button/*.*)
file(GLOB INPUT Input/*.*)
file(GLOB PROGRESS Progress/*.*)
file(GLOB DISPLAY Display/*.*)


target_sources(XWidgetDesignerPlugin PRIVATE
  Res/Plg.qrc
  XWidgetPlugins.h XWidgetPlugins.cpp
  ${BUTTON}
  ${INPUT}
  ${DISPLAY}
  ${PROGRESS}

)

set_target_properties(XWidgetDesignerPlugin PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../XWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/../XWidget/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Button
    ${CMAKE_CURRENT_SOURCE_DIR}/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Display
    ${CMAKE_CURRENT_SOURCE_DIR}/Progress

)

target_link_libraries(XWidgetDesignerPlugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::UiPlugin
    Qt::Widgets
    XWidget
)


if (NOT MSVC)
    set(OUTPUT_DIR mingw)
else()
    set(OUTPUT_DIR msvc)
endif()

set(LIB_OUT_DIR_D ${CMAKE_CURRENT_SOURCE_DIR}/../../../LibD/${OUTPUT_DIR})
set(LIB_OUT_DIR_R ${CMAKE_CURRENT_SOURCE_DIR}/../../../Lib/${OUTPUT_DIR})


set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    CXX_EXTENSIONS OFF
    EXPORT_NAME ${PROJECT_NAME}

    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LIB_OUT_DIR_D}"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LIB_OUT_DIR_R}"

    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${LIB_OUT_DIR_D}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${LIB_OUT_DIR_R}"

    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${LIB_OUT_DIR_D}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${LIB_OUT_DIR_R}"
)

