#include "Gameboard.hpp"

engine::board::GameBoard_t::GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY ){
    AllocateBoard( aBoardSizeX, aBoardSizeY );
}

engine::board::GameBoard_t::AllocateBoard( std::size_t aBoardSizeX, std::size_t aBoardSizeY ) {
    mBoard = std::make_unique< BoardArray2D_t >( aBoardSizeX );
    for( int i = 0; i < aBoardSizeX; i++ ) {
        mBoard[i] = std::make_unique< BoardArray1D_t >( aBoardSizeY );
    }
}

std::vector< MoveError_t > engine::board::GameBoard_t::RunMoves( std::vector< game::engine::GameBoardMove_t > aMoves ) {
    for( auto& aMove : aMoves ) {
        if( aMove.MoveType == engine::board::MoveType_t::ADDRESOURCE ) {
            AddResource( aMove );
        } else if ( aMove.MoveType == engine::board::MoveType_t::REMOVERESOURCE ) {
            RemoveResource( aMove );
        } else {
            // unknown move type
        }
    }
}

MoveError_t engine::board::GameBoard_t::AddResource( game::engine::GameBoardMove_t aMove  ) {
    auto moveX = aMove.MoveIndexX;
    auto moveY = aMove.MoveIndexY;

    mBoard[ aMove.MoveIndexX ][ aMove.MoveIndexY ] = aResource;
}

bool engine::board::GameBoard_t::RemoveResource( game::engine::GameBoardMove_t aMove ) {
    mBoard[ aMove.MoveIndexX ][ aMove.MoveIndexY ] = ResourceType_t::EMPTY:
}


