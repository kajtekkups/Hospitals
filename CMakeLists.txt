cmake_minimum_required(VERSION 3.10)
project(Hospitals)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")


# add include folder path
include_directories(${PROJECT_SOURCE_DIR}/include)

# add all source files
file(GLOB SRC_FILES ./src/*.cpp)

# add json library
add_subdirectory(./libraries/json)
include_directories(./libraries/json/include)

add_executable(Hospitals main.cpp ${SRC_FILES})

