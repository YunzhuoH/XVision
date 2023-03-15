cmake_minimum_required(VERSION 3.14)

project(XLog LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB INCLUDE include/*)
file(GLOB SRC Src/*.*)

file(GLOB spdlog 3rdparty/spdlog/*.*)
file(GLOB spdlog_cfg 3rdparty/spdlog/cfg/*.*)
file(GLOB spdlog_details 3rdparty/spdlog/details/*.*)
file(GLOB spdlog_sinks 3rdparty/spdlog/sinks/*.*)
file(GLOB spdlog_fmt 3rdparty/spdlog/fmt/*.*)
file(GLOB spdlog_fmt_bundled 3rdparty/spdlog/fmt/bundled/*.*)

add_library(XLog SHARED
    ${INCLUDE}
    ${SRC}

    ${spdlog}
    ${spdlog_cfg}
    ${spdlog_details}
    ${spdlog_sinks}
    ${spdlog_fmt}
    ${spdlog_fmt_bundled}

)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_link_libraries(XLog PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(XLog PRIVATE XLOG_LIBRARY)


if (NOT MSVC)
    set(OUTPUT_DIR mingw)
else()
    set(OUTPUT_DIR msvc)
    target_compile_definitions(XLog PRIVATE XLOG_COMPILE_MSVC)
endif()

set(LIB_OUT_DIR_D ${CMAKE_CURRENT_SOURCE_DIR}/../../LibD/${OUTPUT_DIR})
set(LIB_OUT_DIR_R ${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${OUTPUT_DIR})


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
