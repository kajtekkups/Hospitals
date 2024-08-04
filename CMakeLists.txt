cmake_minimum_required(VERSION 3.1)
project(Hospitals)

set(CMAKE_CXX_STANDARD 17)

# Dodaj wszystkie pliki źródłowe z folderu 'src'
file(GLOB SRC_FILES src/*.cpp)

# Dodaj wszystkie pliki nagłówkowe z folderu 'include'
file(GLOB HEADER_FILES include/*.hpp)

# Dodaj biblioteke obslugujaca pliki json
add_subdirectory(json)
include_directories(./json/include)

# Dodaj pliki źródłowe i nagłówkowe do projektu
add_executable(Hospitals main.cpp include/tabu.hpp scr/tabu.cpp include/structures.hpp
        scr/structures.cpp include/window.hpp scr/window.cpp
        main.cpp
)

# Dodaj ścieżki do folderów include
target_include_directories(Hospitals PRIVATE include)

