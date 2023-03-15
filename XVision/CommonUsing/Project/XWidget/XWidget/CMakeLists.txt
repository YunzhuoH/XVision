cmake_minimum_required(VERSION 3.14)

project(XWidget LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core StateMachine UiPlugin)
if(${QT_VERSION_MAJOR} EQUAL 5)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Network WinExtras REQUIRED StateMachine)
else(${QT_VERSION_MAJOR} EQUAL 5)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Network REQUIRED StateMachine)
endif(${QT_VERSION_MAJOR} EQUAL 5)

file(GLOB INCLUDE include/*.*)
file(GLOB INTERNAL Internal/*.*)
file(GLOB WIDGET Widget/*.*)
file(GLOB BUTTON Button/*.*)
file(GLOB INPUT Input/*.*)
file(GLOB DISPLAY Display/*.*)
file(GLOB PROGRESS Progress/*.*)
file(GLOB TEST Test/*.*)



add_library(XWidget SHARED
  Res/XWidget.qrc
  ${INCLUDE}
  ${INTERNAL}
  ${WIDGET}
  ${BUTTON}
  ${INPUT}
  ${DISPLAY}
  ${PROGRESS}
  ${TEST}
)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Internal
    ${CMAKE_CURRENT_SOURCE_DIR}/Private
)


if(WIN32)
    if(${QT_VERSION_MAJOR} EQUAL 5)
        target_link_libraries(XWidget PUBLIC dwmapi PRIVATE
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Network
            Qt${QT_VERSION_MAJOR}::WinExtras
            Qt${QT_VERSION_MAJOR}::WidgetsPrivate
            Qt${QT_VERSION_MAJOR}::StateMachine
        )
    else(${QT_VERSION_MAJOR} EQUAL 5)
        target_link_libraries(XWidget PUBLIC dwmapi PRIVATE
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Network
            Qt${QT_VERSION_MAJOR}::WidgetsPrivate
            Qt${QT_VERSION_MAJOR}::StateMachine
        )
    endif(${QT_VERSION_MAJOR} EQUAL 5)
else ()
    target_link_libraries(XWidget PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::WidgetsPrivate
        Qt${QT_VERSION_MAJOR}::StateMachine
    )
endif(WIN32)

target_compile_definitions(XWidget PRIVATE XWIDGET_LIBRARY)

if (NOT MSVC)
    set(OUTPUT_DIR mingw)
    target_compile_definitions(XWidget PRIVATE XWIDGET_COMPILE_NOT_MSVC)
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
