#include "Gameboard.hpp"

#include "engine/board/Types.hpp"

engine::board::GameBoard_t::GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY )
:
mBoard{},
mStagedBoard{}
{
    AllocateBoard( aBoardSizeX, aBoardSizeY );
}

void engine::board::GameBoard_t::AllocateBoard( std::size_t aBoardSizeX, std::size_t aBoardSizeY ) {
    mBoard = std::make_shared< BoardArray2D_t >( aBoardSizeX );
    for( int i = 0; i < aBoardSizeX; i++ ) {
        mBoard[i] = std::make_shared< BoardArray1D_t >( aBoardSizeY );
    }
}

std::shared_ptr< engine::board::BoardCellState_t > engine::board::GameBoard_t::GetCellState( int xPos, int yPos ) const {    
    if(!IsValidPosition( xPos, yPos ) || !mBoard ) {
        return nullptr;
    }

    return mBoard[xPos][yPos];
}

std::shared_ptr< engine::board::BoardCellState_t > engine::board::GameBoard_t::GetCellStateStaged( int xPos, int yPos ) const {    
    if(!IsValidPosition( xPos, yPos ) || !mStagedBoard ) {
        return nullptr;
    }

    return mStagedBoard[xPos][yPos];
}

std::vector< engine::board::MoveResult_t > engine::board::GameBoard_t::RunMoves( const std::vector< engine::board::GameBoardMove_t >& aMoves ) {        
    std::vector< engine::board::MoveResult_t > moveResults;

    // We stage an instance of the board and make that instance the real one
    // if everything proceeds successfully
    mStagedBoard = std::make_shared< BoardArray2D_t >( *mBoard );

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

    if( mBoard[ moveX ][ moveY ].Locked ) {
        return engine::board::MoveResult_t::LOCKED;
    }

    mStagedBoard[ moveX ][ moveY ].Resource = aMove.Resource;
    return engine::board::MoveResult_t::SUCCESS;
}

engine::board::MoveResult_t engine::board::GameBoard_t::RemoveResource( engine::board::GameBoardMove_t aMove ) {
    auto moveX = aMove.MoveIndexX;
    auto moveY = aMove.MoveIndexY;
    
    if( !IsValidPosition( moveX, moveY ) ){
        return engine::board::MoveResult_t::OUTOFBOUNDS;
    }

    if( mBoard[ moveX ][ moveY ].Locked ) {
        return engine::board::MoveResult_t::LOCKED;
    }
    
    mStagedBoard[ moveX ][ moveY ].Resource = ResourceType_t::EMPTY;
    return engine::board::MoveResult_t::SUCCESS;
}

bool engine::board::GameBoard_t::IsValidPosition( int moveX, int moveY ) const {
    return moveX >= mBoard.size() || moveX < 0 || moveY >= mBoard.at(0).size() || moveY < 0;
}
