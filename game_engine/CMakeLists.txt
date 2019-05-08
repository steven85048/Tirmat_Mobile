# Top level library for the entire engine; compiles the necessary libraries
# and creates the exposed header implementation

#--
# SET THESE VARIABLES SPECIFIC TO PLATFORM
#--

cmake_minimum_required(VERSION 3.5)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(game_engine)

# Expose the libraries
add_subdirectory(engine/board/build)

add_executable(game_engine "engine/board/BoardTest.cpp")

# Link the libraries
target_link_libraries(game_engine engine::board)

set_target_properties(game_engine 
    PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

install(TARGETS game_engine DESTINATION bin)