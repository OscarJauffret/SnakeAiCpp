cmake_minimum_required(VERSION 3.28)
project(SnakeAI)
set(PROJECT_NAME SnakeAI)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE source_files
    "src/*.cpp"
)
set(SOURCES ${source_files}
        src/Engine/engine.cpp
        src/Engine/headers/engine.hpp
        src/Render/renderer.cpp
        src/Render/headers/renderer.hpp
        src/config.hpp
        src/Engine/snake.cpp
        src/Engine/headers/snake.hpp
        src/Engine/input.cpp
        src/Render/snakerenderer.cpp
        src/Render/headers/snakerenderer.hpp
        src/Engine/headers/snakepart.hpp
        src/Engine/rng.cpp
        src/Network/genetic.cpp
        src/Network/genome.cpp
        src/Render/networkrenderer.cpp
        src/Render/headers/card.hpp
        src/Render/statsrenderer.cpp
        src/Render/headers/statsrenderer.hpp
        src/Render/headers/textutils.hpp
        src/Render/trainingrenderer.cpp
        src/Render/headers/trainingrenderer.hpp
        src/Render/headers/traininginfo.hpp
        src/Engine/headers/statstracker.hpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})


set(CMAKE_PREFIX_PATH "C:/SFML-2.6.1")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)