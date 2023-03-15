﻿#设置工程生成目录
set(OUTPUT_DIR_BIN_DEBUG "${CMAKE_BINARY_DIR}/BinD")
set(OUTPUT_DIR_LIB_DEBUG "${CMAKE_BINARY_DIR}/LibD")
set(OUTPUT_DIR_BIN_RELEASE "${CMAKE_BINARY_DIR}/Bin")
set(OUTPUT_DIR_LIB_RELEASE "${CMAKE_BINARY_DIR}/Lib")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR_BIN_DEBUG}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR_LIB_DEBUG}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR_LIB_DEBUG}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR_BIN_RELEASE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR_LIB_RELEASE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR_LIB_RELEASE}")