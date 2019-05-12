#include "engine/board/GameBoard.hpp"
#include "engine/board/Types.hpp"
#include <iostream>

// Testing suite for GameBoard functionality

int main()
{
    auto theBoard = std::make_shared< engine::board::GameBoard_t >( 5, 5 );
    theBoard->PrintBoard();
    
    engine::board::GameBoardMove_t move1( engine::board::MoveType_t::ADDRESOURCE, 3, 2 );
    engine::board::GameBoardMove_t move2( engine::board::MoveType_t::ADDRESOURCE, 1, 1 );
    engine::board::GameBoardMove_t move4( engine::board::MoveType_t::ADDRESOURCE, 25, 25 );

    move1.Resource = engine::board::ResourceType_t::L1;
    move2.Resource = engine::board::ResourceType_t::L3;
    move4.Resource = engine::board::ResourceType_t::L5;

    std::vector< engine::board::GameBoardMove_t > theMoves;
    theMoves.push_back(move1);
    theMoves.push_back(move2);
    theMoves.push_back(move4);
    
    std::cout << "running moves 1" << std::endl;
    theBoard->RunMoves( theMoves );
    
    theBoard->PrintBoard();
    
    engine::board::GameBoardMove_t move3( engine::board::MoveType_t::REMOVERESOURCE, 3, 2 );
    std::vector< engine::board::GameBoardMove_t > theDeleteMoves;
    theDeleteMoves.push_back( move3 );
    
    std::cout << "running moves 2" << std::endl;
    theBoard->RunMoves( theDeleteMoves );
    
    theBoard->PrintBoard();
    
    return 0;
}
