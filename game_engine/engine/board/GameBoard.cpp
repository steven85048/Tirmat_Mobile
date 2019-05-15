#include <memory>
#include <iostream>

#include "GameBoard.hpp"

#include "engine/board/Types.hpp"
#include "engine/utilities/Logging.hpp"

engine::board::GameBoard_t::GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY )
:
mBoardWidth( aBoardSizeX ),
mBoardHeight( aBoardSizeY ),
mBoard( AllocateBoard() )
{
}

engine::board::GameBoard_t::BoardArray2D_t engine::board::GameBoard_t::AllocateBoard() {
    
    BoardArray2D_t theBoard{};

    for( int i = 0 ; i < mBoardWidth; i++ ) {
        BoardArray1D_t theColumn{};

        for( int j = 0 ; j < mBoardHeight; j++ ) {
            auto theCell = std::make_shared< engine::board::BoardCellState_t >( i, j );
            theColumn.push_back( theCell );
        }

        theBoard.push_back( theColumn );
    }

    return theBoard;
}

std::shared_ptr< engine::board::BoardCellState_t > engine::board::GameBoard_t::GetCellState( int xPos, int yPos ) const {    
    if(!IsValidPosition( xPos, yPos ) ) {
        return nullptr;
    }

    return mBoard[xPos][yPos];
}

bool engine::board::GameBoard_t::RunMoves( std::vector< engine::board::GameBoardMove_t >& aMoves ) {        
    // First, we need to verify if the batch of moves that we have is valid
    for( auto& theMove : aMoves ) {
        auto theMoveResult = VerifyMove( theMove );
        theMove.MoveResult = theMoveResult;


        // We just don't run this batch of moves if one or more of them is successful
        if( theMoveResult != engine::board::MoveResult_t::SUCCESS ) {
            std::cout << "Game Board Move ERROR: " << engine::utilities::EnumStrings_t::MoveResultToString( theMoveResult ) << std::endl;
            return false;
        }
    }

    // If all of the moves are successful, then run them and execute board changes
    for( auto& theMove : aMoves ) {
        RunMove( theMove );
    }

    return true;
}

engine::board::MoveResult_t engine::board::GameBoard_t::VerifyMove( engine::board::GameBoardMove_t& aMove ) {
    auto moveX = aMove.MoveIndexX;
    auto moveY = aMove.MoveIndexY;

    //TODO: Handle edge case where a move is added and deleted in a batch (does nothing)
    // Pretty low priority; shouldn't happen

    if( !IsValidPosition( moveX, moveY ) ){
        return engine::board::MoveResult_t::OUTOFBOUNDS;
    }

    if( mBoard[ moveX ][ moveY ]->Locked ) {
        return engine::board::MoveResult_t::LOCKED;
    }

    // Add specific checks
    if( aMove.MoveType == engine::board::MoveType_t::ADDRESOURCE ) {
        // To add a tile, the resource in the move must be set
        if( !aMove.Resource ) {
            return engine::board::MoveResult_t::RESOURCEUNSET;
        }        
    }
    else if( aMove.MoveType == engine::board::MoveType_t::REMOVERESOURCE ) {
        if( mBoard[moveX][moveY]->Resource == engine::board::ResourceType_t::EMPTY ) {
            return engine::board::MoveResult_t::DELETEFROMEMPTY;
        }
    }

    return engine::board::MoveResult_t::SUCCESS;
}

void engine::board::GameBoard_t::RunMove( engine::board::GameBoardMove_t& aMove ) {
    switch( aMove.MoveType ) {
        case engine::board::MoveType_t::ADDRESOURCE:
            AddResource( aMove );
            break;
        case engine::board::MoveType_t::REMOVERESOURCE:
            RemoveResource( aMove );
            break;
        default:
            throw;
    }
}

void engine::board::GameBoard_t::AddResource( engine::board::GameBoardMove_t& aMove  ) {
    if( aMove.MoveResult != engine::board::MoveResult_t::SUCCESS ) {
        return;
    }

    aMove.PreviousResource = mBoard[ aMove.MoveIndexX ][ aMove.MoveIndexX ]->Resource;
    mBoard[ aMove.MoveIndexX ][ aMove.MoveIndexY ]->Resource = *aMove.Resource;
}

void engine::board::GameBoard_t::RemoveResource( engine::board::GameBoardMove_t& aMove ) {
    if( aMove.MoveResult != engine::board::MoveResult_t::SUCCESS ) {
        return;
    }
    
    aMove.PreviousResource = mBoard[ aMove.MoveIndexX ][ aMove.MoveIndexX ]->Resource;
    mBoard[ aMove.MoveIndexX ][ aMove.MoveIndexY ]->Resource = ResourceType_t::EMPTY;
}

bool engine::board::GameBoard_t::IsValidPosition( int moveX, int moveY ) const {
    return moveX < mBoardWidth && moveX >= 0 && moveY < mBoardHeight && moveY >= 0;
}

void engine::board::GameBoard_t::PrintBoard() const {
    std::cout << std::endl;
    static const std::string ResourceTypeString[8] = { "EMPTY", "IGNORE", "L1", "L2", "L3", "L4", "L5", "L6" };

    for( int j = 0; j < mBoardHeight; j++ ) {
        for( int i = 0 ; i < mBoardWidth; i++ ) {
            std::cout << engine::utilities::EnumStrings_t::ResourceToString( mBoard[i][j]->Resource ) << " ";
        } 

        std::cout << std::endl;
    }
}