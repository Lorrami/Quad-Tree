set(CMAKE_CXX_STANDARD 11)

add_library(Shapes SHARED "./sources/FieldShape.cpp"
							"./sources/CircleShape.cpp"
							"./sources/RectangleShape.cpp"
							"./sources/DefaultShape.cpp"
							"./sources/ShapesFactory.cpp")

target_include_directories(Shapes PUBLIC "./include")
target_link_libraries(Shapes sfml-graphics sfml-audio sfml-window)