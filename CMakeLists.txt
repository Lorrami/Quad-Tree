cmake_minimum_required(VERSION 3.22)
project(quad_tree)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(SFML)
add_subdirectory(Application)
add_subdirectory(Shapes)
add_subdirectory(QuadTree)
add_subdirectory(Render2D)

add_executable(quad_tree main.cpp)
target_link_libraries(quad_tree Application)
