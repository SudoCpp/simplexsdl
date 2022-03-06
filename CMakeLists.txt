cmake_minimum_required(VERSION 3.0.0)
project(simplexsdl VERSION 1.0.0)

#Debian Packages required
# libsdl2-dev
# libsdl2-ttf-dev

set(Packages
    SDL2
    )

set(SubProjects
    simplextk
    ) 

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

        include_directories("include")
        foreach(Package IN LISTS Packages)
            find_package(${Package} REQUIRED)
            include_directories(${${Package}_INCLUDE_DIRS})
            target_link_libraries(${PROJECT_NAME} ${${Package}_LIBRARIES})
        endforeach()

        foreach(Project IN LISTS SubProjects)
            if(NOT TARGET ${Project})
                add_subdirectory("../${Project}")
            endif()
            include_directories("../${Project}")
            target_link_libraries(${PROJECT_NAME} ${Project})
        endforeach()
    endif()

target_link_libraries(${PROJECT_NAME} "-lSDL2_ttf")