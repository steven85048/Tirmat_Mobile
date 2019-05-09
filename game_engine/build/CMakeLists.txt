# Top level library for the entire engine; compiles the necessary libraries
# and creates the exposed header implementation

cmake_minimum_required(VERSION 3.5)

# Global output directories; may want to make this target specific!
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Declare our project
project(game_engine)

# Expose the libraries recursively
add_subdirectory("../engine/build" lib)

add_executable(game_engine "../engine/shapeset/ShapeSetTest.cpp")

# Link the libraries
target_link_libraries(game_engine engine)

set_target_properties(game_engine 
    PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

target_include_directories(game_engine
    PUBLIC
        "../"
)


install(TARGETS game_engine DESTINATION bin)