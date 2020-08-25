cmake_minimum_required(VERSION 3.1...3.16)

project(NES
    VERSION 1.0
    DESCRIPTION "NES emulator written in C++."
    LANGUAGES CXX)

set(SOURCE_LIST
    main.cpp)

# Easiest way to add ImGui to a project is to simply compile the files with the project itself
set(IMGUI_FILES
    _deps/imgui/imgui.cpp
    _deps/imgui/imgui_draw.cpp
    _deps/imgui/imgui_widgets.cpp
    _deps/imgui-sfml/imgui-SFML.cpp)

add_executable(NES ${SOURCE_LIST} ${IMGUI_FILES})

# Configure SFML
set(BUILD_SHARED_LIBS FALSE)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_SYSTEM FALSE)
add_subdirectory(_deps/SFML)
target_link_libraries(NES PRIVATE sfml-graphics sfml-window)
target_include_directories(NES PRIVATE _deps/SFML/include)

# Configure ImGui and ImGui SFML bindings
target_include_directories(NES PRIVATE _deps/imgui _deps/imgui-sfml)

# Directory structure in IDEs that support it
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST} ${IMGUI_FILES})
