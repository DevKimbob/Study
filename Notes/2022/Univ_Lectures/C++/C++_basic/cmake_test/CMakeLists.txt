get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
string(APPEND ProjectId "_Project")
project(${ProjectID} C CXX)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.c *.cpp *.h)

add_executable(${PROJECT_NAME} ${SOURCES})