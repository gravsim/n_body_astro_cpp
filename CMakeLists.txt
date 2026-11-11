
cmake_minimum_required(VERSION 3.20)

project(n_body_astro_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)


include(FetchContent)

set(YAML_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(YAML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(YAML_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(yaml-cpp)


add_executable(n_body_astro_cpp
        main.cpp
        src/body.cpp
        src/vec2.cpp
        src/simulation.cpp
        src/methods.hpp
        src/methods.cpp
)
set_target_properties(n_body_astro_cpp PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
target_link_options(n_body_astro_cpp  PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
)
target_link_libraries(n_body_astro_cpp
        PRIVATE
        yaml-cpp::yaml-cpp
)
