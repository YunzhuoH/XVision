cmake_minimum_required(VERSION 3.5)
set(VERSION_SHORT 1)

project(AdsDocking LANGUAGES CXX VERSION ${VERSION_SHORT})
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)
if (UNIX AND NOT APPLE)
    include_directories(${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS})
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(BUILD_STATIC)
    set(CMAKE_STATIC_LIBRARY_SUFFIX "_static${CMAKE_STATIC_LIBRARY_SUFFIX}")
endif()
set(ads_SRCS
    src/ads_globals.cpp
    src/DockAreaTabBar.cpp
    src/DockAreaTitleBar.cpp
    src/DockAreaWidget.cpp
    src/DockContainerWidget.cpp
    src/DockManager.cpp
    src/DockOverlay.cpp
    src/DockSplitter.cpp
    src/DockWidget.cpp
    src/DockWidgetTab.cpp
    src/DockingStateReader.cpp
    src/DockFocusController.cpp
    src/ElidingLabel.cpp
    src/FloatingDockContainer.cpp
    src/FloatingDragPreview.cpp
    src/IconProvider.cpp
    src/DockComponentsFactory.cpp
    
    ads.qrc
)
set(ads_HEADERS
    include/ads_globals.h
    include/DockAreaTabBar.h
    include/DockAreaTitleBar.h
    include/DockAreaTitleBar_p.h
    include/DockAreaWidget.h
    include/DockContainerWidget.h
    include/DockManager.h
    include/DockOverlay.h
    include/DockSplitter.h
    include/DockWidget.h
    include/DockWidgetTab.h
    include/DockingStateReader.h
    include/DockFocusController.h
    include/ElidingLabel.h
    include/FloatingDockContainer.h
    include/FloatingDragPreview.h
    include/IconProvider.h
    include/DockComponentsFactory.h
)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} "include" )

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if (UNIX AND NOT APPLE)
    set(ads_SRCS linux/FloatingWidgetTitleBar.cpp ${ads_SRCS})
    set(ads_HEADERS linux/FloatingWidgetTitleBar.h ${ads_HEADERS})
endif()

if(BUILD_STATIC)
    add_library(AdsDocking STATIC ${ads_SRCS} ${ads_HEADERS})
    target_compile_definitions(AdsDocking PUBLIC ADS_STATIC)
else()
    add_library(AdsDocking SHARED ${ads_SRCS} ${ads_HEADERS})
    target_compile_definitions(AdsDocking PRIVATE ADS_SHARED_EXPORT)
endif()

add_library(ads::AdsDocking ALIAS AdsDocking)

target_link_libraries(AdsDocking PUBLIC Qt${QT_VERSION_MAJOR}::Core
                                               Qt${QT_VERSION_MAJOR}::Gui 
                                               Qt${QT_VERSION_MAJOR}::Widgets)

if (UNIX AND NOT APPLE)
  target_link_libraries(AdsDocking PUBLIC xcb)
endif()

if (NOT MSVC)
    set(OUTPUT_DIR mingw)
else()
    set(OUTPUT_DIR msvc)
endif()

set(LIB_OUT_DIR_D ${CMAKE_CURRENT_SOURCE_DIR}/../../LibD/${OUTPUT_DIR})
set(LIB_OUT_DIR_R ${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${OUTPUT_DIR})


set_target_properties(AdsDocking PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    CXX_EXTENSIONS OFF
    VERSION ${VERSION_SHORT}
    EXPORT_NAME "AdsDocking"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LIB_OUT_DIR_D}"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LIB_OUT_DIR_R}"

    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${LIB_OUT_DIR_D}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${LIB_OUT_DIR_R}"

    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${LIB_OUT_DIR_D}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${LIB_OUT_DIR_R}"
)
if(QT_VERSION_MAJOR STREQUAL "5")
    set_target_properties(AdsDocking PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
elseif(QT_VERSION_MAJOR STREQUAL "6")
    set_target_properties(AdsDocking PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "AdsDockingConfigVersion.cmake"
    VERSION ${VERSION_SHORT}
    COMPATIBILITY SameMajorVersion
)
install(FILES ${ads_HEADERS}
    DESTINATION include
    COMPONENT headers
)
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE"
    "${CMAKE_CURRENT_SOURCE_DIR}/../gnu-lgpl-v2.1.md"
    DESTINATION license/ads
    COMPONENT license
)
install(TARGETS AdsDocking
    EXPORT adsTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(EXPORT adsTargets
    FILE adsTargets.cmake
    NAMESPACE ads::
    DESTINATION lib/cmake/AdsDocking
)
install(FILES AdsDockingConfig.cmake "${CMAKE_CURRENT_BINARY_DIR}/qtadvanceddockingConfigVersion.cmake"
    DESTINATION lib/cmake/AdsDocking
)



target_include_directories(AdsDocking PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
