cmake_minimum_required(VERSION 3.0.0)
project(simplexsdl VERSION 1.0.0)

find_package(SDL2 REQUIRED)

set(SubDirectories
    simplextk
    )

foreach(SubDirectory IN LISTS SubDirectories)
    if(NOT TARGET ${SubDirectory})
        add_subdirectory("../${SubDirectory}" ${SubDirectory})
    endif()
endforeach()

include_directories("include")
include_directories("..")
include_directories(${SDL2_INCLUDE_DIRS})

set(SourceFiles
    src/CMYColor.cpp
    src/Event.cpp
    src/Framework.cpp
    src/Font.cpp
    src/MouseEvent.cpp
    src/Rectangle.cpp
    src/Renderer.cpp
    src/RGBColor.cpp
    src/Surface.cpp
    src/Texture.cpp
    src/Window.cpp
    src/WindowEvent.cpp
    )

if(NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} SHARED ${SourceFiles})
    target_link_libraries(${PROJECT_NAME} simplextk ${SDL2_LIBRARIES} "-lSDL2_ttf")
endif()