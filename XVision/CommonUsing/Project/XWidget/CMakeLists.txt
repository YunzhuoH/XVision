cmake_minimum_required(VERSION 3.5)

project(XWidgetProject VERSION 0.1 LANGUAGES CXX)
set(BUILD_PLUGIN OFF)

add_subdirectory(XWidget)

if(BUILD_PLUGIN)
add_subdirectory(XWidgetDesignerPlugin)
endif()
