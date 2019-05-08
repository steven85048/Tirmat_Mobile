# Top level library for the entire engine; compiles the necessary libraries
# and creates the exposed header implementation

cmake_minimum_required(VERSION 3.5)

set (CMAKE_CXX_STANDARD 17)

project(game_engine)

# Expose the libraries
add_subdirectory(engine/board/build)

add_executable(game_engine "engine/board/BoardTest.cpp")

# Link the libraries
target_link_libraries(game_engine engine::board)

install(TARGETS game_engine DESTINATION bin)