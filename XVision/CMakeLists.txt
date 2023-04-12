cmake_minimum_required(VERSION 3.5)

project(XVision VERSION 0.1 LANGUAGES CXX)



add_subdirectory(XVision) #App主工程
add_subdirectory(XvCore)  #核心库工程
add_subdirectory(XvData)  #项目数据库工程
add_subdirectory(XvUtils) #项目工具库工程
add_subdirectory(XvTokenMsg)  #项目Token消息工程


add_subdirectory(XvFuncCollection/VFuncTest_A)
add_subdirectory(XvFuncCollection/XvFuncSystem) #系统工具库


set(COM_USEING_BULID ON) #项目公共库

if(COM_USEING_BULID)
    add_subdirectory(CommonUsing)
endif()


