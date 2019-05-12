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

    engine::board::GameBoardMove_t move4( engine::board::MoveType_t::ADDRESOURCE, 0, 2 );
    move4.Resource = engine::board::ResourceType_t::L1;
    
    engine::board::GameBoardMove_t move5( engine::board::MoveType_t::ADDRESOURCE, 1, 2 );
    move5.Resource = engine::board::ResourceType_t::L2;

    engine::board::GameBoardMove_t move6( engine::board::MoveType_t::ADDRESOURCE, 2, 2 );
    move6.Resource = engine::board::ResourceType_t::L3;

    engine::board::GameBoardMove_t move7( engine::board::MoveType_t::ADDRESOURCE, 2, 1 );
    move7.Resource = engine::board::ResourceType_t::L6;

    engine::board::GameBoardMove_t move9( engine::board::MoveType_t::ADDRESOURCE, 1, 1 );
    move9.Resource = engine::board::ResourceType_t::L6;

    engine::board::GameBoardMove_t move8( engine::board::MoveType_t::REMOVERESOURCE, 2, 1 );

    std::vector< engine::board::GameBoardMove_t > moveSet;

    moveSet.push_back(move1);
    moveSet.push_back(move2);
    moveSet.push_back(move3);
    moveSet.push_back(move4);
    moveSet.push_back(move5);
    moveSet.push_back(move6);
    moveSet.push_back(move7);
    moveSet.push_back(move9);

    std::vector< engine::board::GameBoardMove_t > moveSet2;
    moveSet2.push_back(move8);

    theShapeSetManager->ExecuteMoves( moveSet );
    theBoard->PrintBoard();

    theShapeSetManager->ExecuteMoves( moveSet2 );
    theBoard->PrintBoard();

    return 0;
}
