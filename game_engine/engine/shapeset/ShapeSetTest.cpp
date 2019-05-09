#include <iostream>
#include <vector>

#include "engine/board/GameBoard.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"
#include "engine/board/Types.hpp"

// Testing suite for shapeset functionality

int main()
{
    auto theBoard = std::make_shared< engine::board::GameBoard_t >( 5, 5 );
    
    auto theShapeSetManager = std::make_shared< engine::shapeset::ShapeSetManager_t >( theBoard );

    engine::board::GameBoardMove_t move1( engine::board::MoveType_t::ADDRESOURCE, 0, 0 );
    move1.Resource = engine::board::ResourceType_t::L1;
    
    engine::board::GameBoardMove_t move2( engine::board::MoveType_t::ADDRESOURCE, 1, 0 );
    move2.Resource = engine::board::ResourceType_t::L2;

    engine::board::GameBoardMove_t move3( engine::board::MoveType_t::ADDRESOURCE, 2, 0 );
    move3.Resource = engine::board::ResourceType_t::L3;

    std::vector< engine::board::GameBoardMove_t > moveSet;

    moveSet.push_back(move1);
    moveSet.push_back(move2);
    moveSet.push_back(move3);

    theShapeSetManager->ExecuteMoves( moveSet );
    theBoard->PrintBoard();

    return 0;
}
