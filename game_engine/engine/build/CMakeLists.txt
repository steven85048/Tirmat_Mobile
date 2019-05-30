# Creates a shared library with all library functionality
# Allows us to easily test just this library

cmake_minimum_required(VERSION 3.8.0)

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

SET(move_src_files 
        "../move/MoveManager.cpp"
        "../move/UndoController.cpp"
)

# Djinni compiles

# The JNI files are the files directly interactable from Java
file( GLOB_RECURSE jni_src_files
        "../../generated/jni/*.cpp"
        "../../generated/cpp/*.cpp")

# Djinni has some files we need to compile; just glob them
file( GLOB djinni_src_files
        "../../../dependencies/djinni/support-lib/jni/*.cpp")

# Define our library
project(lib_engine VERSION 1.0 LANGUAGES CXX)
add_library(engine SHARED ${board_src_files} 
                          ${initialization_src_files} 
                          ${ruleset_src_files} 
                          ${shapeset_src_files}  
                          ${state_src_files}
                          ${move_src_files}
                          ${jni_src_files}
                          ${djinni_src_files} )

# Set library compilation features
target_compile_features(engine
    PRIVATE
        cxx_variable_templates
)

set_target_properties(engine 
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

SET( generated_headers 
        "../../generated/cpp/engine/state"
        "../../generated/jni/engine/state")

# All app specific includes are relative to the game-engine/ directory
target_include_directories(engine
    PUBLIC
        "../../"
        ${generated_headers}
        "../../../dependencies/djinni/support-lib/"
        "../../../dependencies/djinni/support-lib/jni/"
)

install(TARGETS engine DESTINATION lib)