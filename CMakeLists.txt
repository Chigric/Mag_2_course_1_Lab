cmake_minimum_required(VERSION 2.8)

project(Mag_2_course_1_Lab)

# MAIN_PROJECT && COMMON_FILES
include_directories("common/")
set(COMMON_FILES "common/Output.hpp"
	"common/cubatureRules.cpp" "common/cubatureRules.h")
set(MAIN_PROJECT_SRC_LIST "main.cpp" ${COMMON_FILES})

# Build && flags (keys)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++14 -Wall")
add_executable(${PROJECT_NAME}
	${MAIN_PROJECT_SRC_LIST})

# Subdirectorys
add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)
target_link_libraries(${PROJECT_NAME} lab1 lab2 lab3)
