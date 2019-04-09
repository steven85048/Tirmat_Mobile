#include <memory>
#include <iostream>

#include "GameBoard.hpp"

#include "engine/board/Types.hpp"
#include "engine/utilities/Logging.hpp"

engine::board::GameBoard_t::GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY )
:
mBoardWidth( aBoardSizeX ),
mBoardHeight( aBoardSizeY ),
mBoard( AllocateBoard() ),
mStagedBoard( AllocateBoard() )
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

std::shared_ptr< engine::board::BoardCellState_t > engine::board::GameBoard_t::GetCellStateStaged( int xPos, int yPos ) const {    
    if(!IsValidPosition( xPos, yPos ) ) {
        return nullptr;
    }

    return mStagedBoard[xPos][yPos];
}

std::vector< engine::board::MoveResult_t > engine::board::GameBoard_t::RunMoves( const std::vector< engine::board::GameBoardMove_t >& aMoves ) {        
    std::vector< engine::board::MoveResult_t > moveResults;

    // We stage an instance of the board and make that instance the real one
    // if everything proceeds successfully; deep copies it
    mStagedBoard = mBoard;

    for( auto& aMove : aMoves ) {
        if( aMove.MoveType == engine::board::MoveType_t::ADDRESOURCE ) {
            moveResults.push_back( AddResource( aMove ) );
        } else if ( aMove.MoveType == engine::board::MoveType_t::REMOVERESOURCE ) {
            moveResults.push_back( RemoveResource( aMove ) );
        } else {
            moveResults.push_back( engine::board::MoveResult_t::UNKNOWNMOVE );
        }
    }

    return moveResults;
}

void engine::board::GameBoard_t::CommitStagedBoard() {
    mBoard = std::move( mStagedBoard );
}

engine::board::MoveResult_t engine::board::GameBoard_t::AddResource( engine::board::GameBoardMove_t aMove  ) {
    auto moveX = aMove.MoveIndexX;
    auto moveY = aMove.MoveIndexY;

    if( !IsValidPosition( moveX, moveY ) ){
        return engine::board::MoveResult_t::OUTOFBOUNDS;
    }

    if( mBoard[ moveX ][ moveY ]->Locked ) {
        return engine::board::MoveResult_t::LOCKED;
    }

    if( !aMove.Resource ) {
        return engine::board::MoveResult_t::RESOURCEUNSET;
    }

    mStagedBoard[ moveX ][ moveY ]->Resource = *aMove.Resource;
    return engine::board::MoveResult_t::SUCCESS;
}

engine::board::MoveResult_t engine::board::GameBoard_t::RemoveResource( engine::board::GameBoardMove_t aMove ) {
    auto moveX = aMove.MoveIndexX;
    auto moveY = aMove.MoveIndexY;
    
    if( !IsValidPosition( moveX, moveY ) ){
        return engine::board::MoveResult_t::OUTOFBOUNDS;
    }

    if( mBoard[ moveX ][ moveY ]->Locked ) {
        return engine::board::MoveResult_t::LOCKED;
    }
    
    mStagedBoard[ moveX ][ moveY ]->Resource = ResourceType_t::EMPTY;
    return engine::board::MoveResult_t::SUCCESS;
}

bool engine::board::GameBoard_t::IsValidPosition( int moveX, int moveY ) const {
    return moveX < mBoardWidth && moveX >= 0 && moveY < mBoardHeight && moveY >= 0;
}

void engine::board::GameBoard_t::PrintBoard() {
    std::cout << std::endl;
    static const std::string ResourceTypeString[8] = { "EMPTY", "IGNORE", "L1", "L2", "L3", "L4", "L5", "L6" };

    for( int j = 0; j < mBoardHeight; j++ ) {
        for( int i = 0 ; i < mBoardWidth; i++ ) {
            std::cout << engine::utilities::EnumStrings_t::ResourceToString( mBoard[i][j]->Resource ) << " ";
        } 

        std::cout << std::endl;
    }
}