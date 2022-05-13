set(CMAKE_CXX_STANDARD 11)

add_library(Render2D SHARED "./sources/Render2D.cpp")

target_include_directories(Render2D PUBLIC "./include")

target_link_libraries(Render2D QuadTree)