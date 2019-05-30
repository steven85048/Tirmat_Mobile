# Top level library for the entire engine; compiles the necessary libraries
# and creates the exposed header implementation

cmake_minimum_required(VERSION 3.8.0)

# Global output directories; may want to make this target specific!
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Declare our project
project(game_engine)

# Expose the libraries recursively
add_subdirectory("../engine/build" lib)

# To change the test file, just change the executable file (cpp with main)
#add_executable(game_engine "../engine/shapeset/ShapeSetTest.cpp")
add_executable(game_engine "../engine/EngineTest.cpp")

# The rest of the engine is compiled as a library 
target_link_libraries(game_engine engine)

set_target_properties(game_engine 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# All non-external library includes are relative to the base directory; grouped by namespace
target_include_directories(game_engine
    PUBLIC
        "../"
)


install(TARGETS game_engine DESTINATION bin)