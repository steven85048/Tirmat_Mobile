# Creates a shared library with all library functionality
# Allows us to easily test just this library

cmake_minimum_required(VERSION 3.5)

# Define the source files in our project
SET(board_src_files 
        "../board/GameBoard.cpp"
        "../board/UserResources.cpp"
)

SET(initialization_src_files 
        "../initialization/GameBoardFactory.cpp"
)

SET(ruleset_src_files 
        "../ruleset/RuleDFA.cpp"
)

SET(shapeset_src_files 
        "../shapeset/ShapeSetManager.cpp"
)

SET(state_src_files 
        "../state/UserStateContainer.cpp"
)

SET(engine_src_files 
        "../move/MoveManager.cpp"
)

# Define our library
project(lib_engine VERSION 1.0 LANGUAGES CXX)
add_library(engine SHARED ${board_src_files} 
                          ${initialization_src_files} 
                          ${ruleset_src_files} 
                          ${shapeset_src_files}  
                          ${state_src_files}
                          ${engine_src_files} )

# Set library compilation features
target_compile_features(engine
    PRIVATE
        cxx_variable_templates
)

set_target_properties(engine 
    PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
)

# All app specific includes are relative to the game-engine/ directory
target_include_directories(engine
    PUBLIC
        "../../"
)

install(TARGETS engine DESTINATION lib)