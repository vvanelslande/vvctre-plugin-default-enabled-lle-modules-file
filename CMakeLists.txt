cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0003 NEW)

project(vvctre-plugin-enable-lle-modules-in-file-when-starting)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>)

add_library(whereami STATIC
    whereami/src/whereami.c
    whereami/src/whereami.h
)
target_include_directories(whereami PUBLIC ./whereami/src)

add_library(vvctre-plugin-enable-lle-modules-in-file-when-starting SHARED plugin.cpp string_util.cpp string_util.h)
target_link_libraries(vvctre-plugin-enable-lle-modules-in-file-when-starting PRIVATE whereami)

set_target_properties(vvctre-plugin-enable-lle-modules-in-file-when-starting PROPERTIES PREFIX "" OUTPUT_NAME enable-lle-modules-in-file-when-starting)
