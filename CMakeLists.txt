cmake_minimum_required(VERSION 3.10) 
project(WinAPIHelloWorld) 

set(CMAKE_CXX_STANDARD 23)               
set(CMAKE_CXX_STANDARD_REQUIRED True)    

add_subdirectory(code)

#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")