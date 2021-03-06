#include <iostream>
#include <memory>

#include "engine/move/MoveManager.hpp"

engine::move::MoveManager_t::MoveManager_t(  std::unique_ptr< engine::ruleset::RuleDFA_t > aRuleDFA, 
                                             std::unique_ptr< engine::shapeset::ShapeSetManager_t > aShapeSetManager,
                                             std::unique_ptr< engine::board::UserResources_t > aUserResources )
:
mRuleDFA( std::move( aRuleDFA ) ),
mShapeSetManager( std::move( aShapeSetManager ) ),
mUserResources( std::move( aUserResources ) ),
mUndoController( std::make_unique< engine::move::UndoController_t >() )
{
}

void engine::move::MoveManager_t::ExecuteMoves( engine::board::GameBoardMoveBatch_t& aMoveBatch ) {
    
    if( !mUserResources ) {
        return;
    }

    if( !mShapeSetManager ) {
        return;
    }

    if( !mRuleDFA ) {
        return;
    }

    aMoveBatch.UpdateResourceUsage();

    // Validate we have enough resources for these moves
    if( !mUserResources->ValidateResources( aMoveBatch.ResourceUsage ) ) {
        std::cout << "Insufficient Resources for this move! " << std::endl;
        return;
    }

    // If the move is a generating, we need to first initialize our moves
    if( aMoveBatch.IsGenerating ) {
        auto theGeneratingPoints = mRuleDFA->GetGeneratingLocations();

        if( !theGeneratingPoints ) {
            return;
        }

        for( auto& theGeneratingPoint : *theGeneratingPoints ) {
            engine::board::GameBoardMove_t theNewMove( engine::board::MoveType_t::ADDRESOURCE, theGeneratingPoint.Location.xPos, theGeneratingPoint.Location.yPos );
            theNewMove.Resource = theGeneratingPoint.Resource;

            aMoveBatch.Moves.push_back( theNewMove );
        }
    }

    auto theMovesSucceeded = mShapeSetManager->ExecuteMoves( aMoveBatch.Moves );

    if( theMovesSucceeded ) {
        // Now we update the rule DFA with our updated points
        auto theUpdatedPointSets = mShapeSetManager->GetPointSets();
        mRuleDFA->PointSetsUpdated( theUpdatedPointSets );
        
        // We also process possible resource returns here and update our resource usage
        aMoveBatch.ProcessRefunds();
        mUserResources->UpdateResources( aMoveBatch.ResourceUsage );

        // Create and push the equivalent undo move
        mUndoController->AddUndoMoveBatch( aMoveBatch );
    }

}

void engine::move::MoveManager_t::PopUndoMoves() {
    if( mUndoController ) {
        auto theUndoMoveBatch = mUndoController->PopUndoMove();

        // if optional is nullopt, there is no undo to process
        if( theUndoMoveBatch ) {
            ExecuteMoves( *theUndoMoveBatch );
        }
    }
}