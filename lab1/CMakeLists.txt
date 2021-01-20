cmake_minimum_required(VERSION 2.8)

project(lab1)
set(SPEC_HEADER "main_lab1.hpp")
set(SOURCES "lab1.cpp")
set(HEADERS "lab1.h")
add_library(lab1 ${SPEC_HEADER} ${SOURCES} ${HEADERS})
target_include_directories(lab1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})