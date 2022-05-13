set(CMAKE_CXX_STANDARD 11)

add_library(QuadTree SHARED "./sources/QuadTree.cpp")

target_include_directories(QuadTree PUBLIC "./include")

target_link_libraries(QuadTree Shapes)