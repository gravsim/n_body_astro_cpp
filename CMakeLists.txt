cmake_minimum_required(VERSION 3.20)

project(n_body_astro_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(yaml-cpp CONFIG REQUIRED)

add_executable(n_body_astro_cpp
        main.cpp
        src/body.cpp
        src/vec2.cpp
        src/simulation.cpp
)

target_link_libraries(n_body_astro_cpp PRIVATE yaml-cpp::yaml-cpp)