cmake_minimum_required(VERSION 3.5)

project(XVision VERSION 0.1 LANGUAGES CXX)



add_subdirectory(XVision)
add_subdirectory(XvCore)
add_subdirectory(XvData)
add_subdirectory(XvUtils)
add_subdirectory(XvTokenMsg)


add_subdirectory(XvFuncCollection/VFuncTest_A)
add_subdirectory(XvFuncCollection/XvFuncSystem)


set(COM_USEING_BULID ON)

if(COM_USEING_BULID)
    add_subdirectory(CommonUsing)
endif()


