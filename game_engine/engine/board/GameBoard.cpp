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