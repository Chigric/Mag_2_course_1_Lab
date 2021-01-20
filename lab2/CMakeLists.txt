cmake_minimum_required(VERSION 2.8)

project(lab2)
set(SPEC_HEADER "main_lab2.hpp")
set(SOURCES "lab2.cpp")
set(HEADERS "lab2.h")
add_library(lab2 ${SPEC_HEADER} ${SOURCES} ${HEADERS})
target_include_directories(lab2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
