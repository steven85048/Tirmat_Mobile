#include <memory>

#include "engine/MoveManager.hpp"

engine::MoveManager_t::MoveManager_t(  std::unique_ptr< engine::ruleset::RuleDFA_t > aRuleDFA, 
                        std::unique_ptr< engine::shapeset::ShapeSetManager_t > aShapeSetManager,
                        std::unique_ptr< engine::board::UserResources_t > aUserResources )
:
mRuleDFA( std::move( aRuleDFA ) ),
mShapeSetManager( std::move( aShapeSetManager ) ),
mUserResources( std::move( aUserResources ) )
{
}

void engine::MoveManager_t::ExecuteMoves( engine::board::GameBoardMoveBatch_t& aMoveBatch ) {
    if( !mUserResources ) {
        return;
    }

    if( !mShapeSetManager ) {
        return;
    }

    if( !mRuleDFA ) {
        return;
    }

    // Validate we have enough resources for these moves
    if( mUserResources->ValidateResources( aMoveBatch.ResourceUsage ) ) {
        return;
    }

    // If the move is a generating, we need to first initialize our moves
    

    mShapeSetManager->ExecuteMoves( aMoveBatch.Moves );
}