#include <iostream>

#include "engine/board/GameBoard.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"

// Testing suite for shapeset functionality

int main()
{
    auto theBoard = std::make_shared< engine::board::GameBoard_t >( 5, 5 );
    theBoard->PrintBoard();
    
    auto theShapeSetManager = std::make_shared< engine::shapeset::ShapeSetManager_t >( std::move( theBoard ) );

    return 0;
}
