cmake_minimum_required(VERSION 3.14)
project(SuperMarioBros)

set(CMAKE_CXX_STANDARD 17)

if (DRAW_HITBOX)
    add_definitions(-DDRAW_HITBOX)
endif ()

include(FetchContent)
set(SFML_VERSION "2.5.1")
FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG "${SFML_VERSION}"
)

FetchContent_GetProperties(sfml)
if (NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif ()

enable_testing()

add_library(MarioLib Animation.cpp file_util.cpp Entity.cpp Entity.h SpriteMaker.cpp SpriteMaker.h Utils.cpp Utils.h Hitbox.cpp Hitbox.h Timer.cpp Timer.h entities/Pipe.cpp entities/Pipe.h
        entities/Mario.cpp entities/Goomba.cpp Level.cpp Level.h entities/Block.cpp entities/Block.h)
target_include_directories(MarioLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(MarioLib PRIVATE -Wall -Wextra -Werror)
target_link_libraries(MarioLib sfml-window sfml-graphics)
target_include_directories(MarioLib PRIVATE ${sfml_INCLUDE_DIR})

add_executable(SuperMarioBros main.cpp)
target_link_libraries(SuperMarioBros sfml-window sfml-graphics MarioLib)
target_include_directories(SuperMarioBros PRIVATE ${sfml_INCLUDE_DIR})


add_subdirectory(unittests)
