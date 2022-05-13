set(CMAKE_CXX_STANDARD 11)

add_library(Application STATIC "./sources/Application.cpp")

target_include_directories(Application PUBLIC "./include")

target_link_libraries(Application Render2D)