# Creates a shared library for just board functionality
# Allows us to easily test just this library

cmake_minimum_required(VERSION 3.5)

# Define the source and header files in our project
SET(target_src_files 
        "../GameBoard.cpp"
)

SET(target_header_files
        "../GameBoard.hpp"
        "../GameBoardInteractorIntf.hpp"
        "../GameBoardIntf.hpp"
        "../Types.hpp"
)

# Define our library
project(lib_board VERSION 1.0 LANGUAGES CXX)
add_library(board SHARED ${target_src_files})
add_library(engine::board ALIAS board)

# Set library compilation features
target_compile_features(board
    PRIVATE
        cxx_variable_templates
)

set_target_properties(board 
    PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Set library headers; public headers are visible to those who
# include this library; private is not
target_include_directories(board
    PUBLIC
        "../../../"
)

install(TARGETS board DESTINATION lib)
