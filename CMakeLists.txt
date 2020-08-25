cmake_minimum_required(VERSION 3.1...3.16)

project(NES
    VERSION 1.0
    DESCRIPTION "NES emulator written in C++."
    LANGUAGES CXX)

set(SOURCE_LIST
    main.cpp)

add_executable(NES ${SOURCE_LIST})

# Configure SFML
set(BUILD_SHARED_LIBS FALSE)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_SYSTEM FALSE)
add_subdirectory(_deps/SFML)
target_link_libraries(NES PRIVATE sfml-graphics sfml-window)
target_include_directories(NES PRIVATE _deps/SFML/include)

# Directory structure in IDEs that support it
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
