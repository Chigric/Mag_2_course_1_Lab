cmake_minimum_required(VERSION 2.8)

project(Mag_2_course_1_Lab)

#set(SOURCES ooo.cpp)
#add_library(Output INTERFACE)
#target_sources(Output INTERFACE Output.hpp)
set(SPEC_HEADER "main_lab1.hpp" "main_lab2.hpp" "main_lab3.hpp")
add_executable(${PROJECT_NAME}
	"main.cpp"
	"lab1.cpp" "lab1.h"
	"lab2.cpp" "lab2.h"
	"lab3.cpp" "lab3.h"
	"Output.hpp"
	${SPEC_HEADER})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++14 -Wall")

#target_link_libraries(${PROJECT_NAME} output)
