#include "engine/move/UndoController.hpp"

engine::move::UndoController_t::UndoController_t()
{
}

void engine::move::UndoController_t::AddUndoMoveBatch( const engine::board::GameBoardMoveBatch_t& aMoveBatch ) {
    
    if( aMoveBatch.IsUndo ) {
        return;
    }
    
    engine::board::GameBoardMoveBatch_t theUndoMoveBatch;
    theUndoMoveBatch.IsUndo = true;

    // initialize the resources (just the inverse of the original)
    for( auto theResourceItr = aMoveBatch.ResourceUsage.begin(); theResourceItr != aMoveBatch.ResourceUsage.end(); theResourceItr++ ) {
        auto theResourceType = theResourceItr->first;
        auto theResourceCount = theResourceItr->second;

        theUndoMoveBatch.ResourceUsage[theResourceType] = (-1) * theResourceCount;
    }

    // initialize the moves with the equivalent reverse
    for( auto& thePreviousMove : aMoveBatch.Moves ) {
        theUndoMoveBatch.Moves.push_back( CreateEquivalentUndo( thePreviousMove ) );
    }

    mUndoMoves.push( theUndoMoveBatch );
}

engine::board::GameBoardMove_t engine::move::UndoController_t::CreateEquivalentUndo( const engine::board::GameBoardMove_t& aPreviousMove ) {
    engine::board::MoveType_t theUndoMoveType;
    djinni::ResourceType theUndoResourceType = djinni::ResourceType::EMPTY;
    
    if( aPreviousMove.MoveType == engine::board::MoveType_t::ADDRESOURCE ) {
        if( aPreviousMove.PreviousResource.has_value() && *aPreviousMove.PreviousResource == djinni::ResourceType::EMPTY ) {
            theUndoMoveType = engine::board::MoveType_t::REMOVERESOURCE;
        } else {
            // This was just an update to an existing colored cell
            theUndoMoveType = engine::board::MoveType_t::ADDRESOURCE;
            theUndoResourceType = *aPreviousMove.PreviousResource;
        }
    } else if( aPreviousMove.MoveType == engine::board::MoveType_t::REMOVERESOURCE ) {
        theUndoMoveType = engine::board::MoveType_t::ADDRESOURCE;
        theUndoResourceType = *aPreviousMove.PreviousResource;
    }

    engine::board::GameBoardMove_t theUndoMove( theUndoMoveType, aPreviousMove.MoveIndexX, aPreviousMove.MoveIndexY, theUndoResourceType );
    return theUndoMove;
}

std::optional< engine::board::GameBoardMoveBatch_t > engine::move::UndoController_t::PopUndoMove() {
    if( !mUndoMoves.empty() ) {
        auto theTopBatch = mUndoMoves.top();
        mUndoMoves.pop();
        return theTopBatch;
    }

    return std::nullopt;
}