cmake_minimum_required(VERSION 3.22)
project(quad_tree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    "Application.cpp"
    "Shapes/DefaultShape.cpp"
    "Shapes/RectangleShape.cpp"
    "Shapes/CircleShape.cpp"
    "Shapes/ShapesFactory.cpp"
    "Render2D.cpp"
    "QuadTree.cpp")

add_subdirectory(SFML)

add_executable(quad_tree ${SOURCES} main.cpp)
target_link_libraries(quad_tree sfml-graphics sfml-system sfml-window)
