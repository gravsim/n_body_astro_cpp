
cmake_minimum_required(VERSION 3.20)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
)

FetchContent_MakeAvailable(yaml-cpp)

add_executable(MyProject main.cpp)

target_link_libraries(MyProject PRIVATE yaml-cpp::yaml-cpp)
