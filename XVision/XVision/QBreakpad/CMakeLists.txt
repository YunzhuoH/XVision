cmake_minimum_required(VERSION 3.12.0)

project(QBreakpad LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(BREAKPAD_PATH 3rdparty/breakpad/src)
list(APPEND SRC_LIST)

if(UNIX)
   list(APPEND SRC_LIST
   ${BREAKPAD_PATH}/client/minidump_file_writer.cc
   ${BREAKPAD_PATH}/common/convert_UTF.cc
   ${BREAKPAD_PATH}/common/md5.cc
   ${BREAKPAD_PATH}/common/string_conversion.cc
    )
endif()

if (UNIX AND NOT APPLE)
     list(APPEND SRC_LIST
        ${BREAKPAD_PATH}/client/linux/crash_generation/crash_generation_client.cc
        ${BREAKPAD_PATH}/client/linux/dump_writer_common/thread_info.cc
        ${BREAKPAD_PATH}/client/linux/dump_writer_common/ucontext_reader.cc
        ${BREAKPAD_PATH}/client/linux/handler/exception_handler.cc
        ${BREAKPAD_PATH}/client/linux/handler/minidump_descriptor.cc
        ${BREAKPAD_PATH}/client/linux/log/log.cc
        ${BREAKPAD_PATH}/client/linux/microdump_writer/microdump_writer.cc
        ${BREAKPAD_PATH}/client/linux/minidump_writer/linux_core_dumper.cc
        ${BREAKPAD_PATH}/client/linux/minidump_writer/linux_dumper.cc
        ${BREAKPAD_PATH}/client/linux/minidump_writer/linux_ptrace_dumper.cc
        ${BREAKPAD_PATH}/client/linux/minidump_writer/minidump_writer.cc
        ${BREAKPAD_PATH}/common/linux/breakpad_getcontext.S
        ${BREAKPAD_PATH}/common/linux/elfutils.cc
        ${BREAKPAD_PATH}/common/linux/file_id.cc
        ${BREAKPAD_PATH}/common/linux/guid_creator.cc
        ${BREAKPAD_PATH}/common/linux/linux_libc_support.cc
        ${BREAKPAD_PATH}/common/linux/memory_mapped_file.cc
        ${BREAKPAD_PATH}/common/linux/safe_readlink.cc
     )
elseif (WIN32)
     list(APPEND SRC_LIST
        ${BREAKPAD_PATH}/client/windows/crash_generation/crash_generation_client.cc
        ${BREAKPAD_PATH}/client/windows/handler/exception_handler.cc
        ${BREAKPAD_PATH}/common/windows/guid_string.cc
     )
elseif (APPLE)
   list(APPEND SRC_LIST
      ${BREAKPAD_PATH}/client/mac/zcrash_generation/crash_generation_client.cc
      ${BREAKPAD_PATH}/client/mac/handler/breakpad_nlist_64.cc
      ${BREAKPAD_PATH}/client/mac/handler/dynamic_images.cc
      ${BREAKPAD_PATH}/client/mac/handler/exception_handler.cc
      ${BREAKPAD_PATH}/client/mac/handler/minidump_generator.cc
      ${BREAKPAD_PATH}/common/mac/MachIPC.mm
      ${BREAKPAD_PATH}/common/mac/bootstrap_compat.cc
      ${BREAKPAD_PATH}/common/mac/file_id.cc
      ${BREAKPAD_PATH}/common/mac/macho_id.cc
      ${BREAKPAD_PATH}/common/mac/macho_utilities.cc
      ${BREAKPAD_PATH}/common/mac/macho_walker.cc
      ${BREAKPAD_PATH}/common/mac/string_utilities.cc
   )
endif ()

add_library(${PROJECT_NAME}  STATIC
    handler/QBreakpadHandler.h
    handler/QBreakpadHandler.cpp
    handler/QBreakpadHttpUploader.h
    handler/QBreakpadHttpUploader.cpp
    handler/singletone/singleton.h
    handler/singletone/call_once.h
    ${SRC_LIST}
)

include_directories(
    ${BREAKPAD_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)
