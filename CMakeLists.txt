cmake_minimum_required(VERSION 2.8)

project(Mag_2_course_1_Lab)

#set(SOURCES ooo.cpp)
#add_library(Output INTERFACE)
#target_sources(Output INTERFACE Output.hpp)
set(HEADER_FILE_ONLY "Output.hpp" "lab1.h")
set(SOURCES "main.cpp" "lab1.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER_FILE_ONLY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++14 -Wall")

#target_link_libraries(${PROJECT_NAME} output)
