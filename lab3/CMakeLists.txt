cmake_minimum_required(VERSION 2.8)

project(lab3)
set(SPEC_HEADER "main_lab3.hpp")
set(SOURCES "lab3.cpp")
set(HEADERS "lab3.h")
add_library(lab3 ${SPEC_HEADER} ${SOURCES} ${HEADERS})
target_include_directories(lab3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
