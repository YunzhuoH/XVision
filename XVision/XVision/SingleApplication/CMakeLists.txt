cmake_minimum_required(VERSION 3.12.0)

project(SingleApplication LANGUAGES CXX DESCRIPTION "Replacement for QtSingleApplication")

set(CMAKE_AUTOMOC ON)


add_library(${PROJECT_NAME}  STATIC
    singleapplication.cpp
    singleapplication_p.cpp
)



list(APPEND QT_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
list(APPEND QT_FINDS Core Network)

if(XVAPPLICATION_CLASS STREQUAL QApplication)
    list(APPEND QT_LIBRARIES Qt${QT_VERSION_MAJOR}::Widgets)
    list(APPEND QT_FINDS Widgets)
elseif(XVAPPLICATION_CLASS STREQUAL QGuiApplication)
    list(APPEND QT_LIBRARIES Qt${QT_VERSION_MAJOR}::Gui)
    list(APPEND QT_FINDS Gui)
else()
    set(XVAPPLICATION_CLASS QCoreApplication)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS  ${QT_FINDS})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_FINDS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBRARIES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE advapi32)
endif()



target_compile_definitions(${PROJECT_NAME} PUBLIC QAPPLICATION_CLASS=${XVAPPLICATION_CLASS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_NO_CAST_TO_ASCII
    QT_NO_CAST_FROM_ASCII
    QT_NO_URL_CAST_FROM_STRING
    QT_NO_CAST_FROM_BYTEARRAY
    QT_USE_QSTRINGBUILDER
    QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
    QT_NO_KEYWORDS
    QT_NO_FOREACH
)

