cmake_minimum_required(VERSION 3.5)

project(ascii_cpp)

find_package(OpenCV REQUIRED)

add_executable(ascii main.cpp)
target_link_libraries(ascii PRIVATE ${OpenCV_LIBS})

