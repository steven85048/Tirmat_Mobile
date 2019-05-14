#include <iostream>
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
    std::cout << "MoveManager::ExecuteMoves" << std::endl;

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
    if( !mUserResources->ValidateResources( aMoveBatch.ResourceUsage ) ) {
        return;
    }

    std::cout << "Resources Validated! " << std::endl;

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

    mShapeSetManager->ExecuteMoves( aMoveBatch.Moves );

    std::cout << "MoveManager updating point sets" << std::endl;
    // Now we update the rule DFA with our updated points
    auto theUpdatedPointSets = mShapeSetManager->GetPointSets();
    mRuleDFA->PointSetsUpdated( theUpdatedPointSets );

    mUserResources->UpdateResources( aMoveBatch.ResourceUsage );
}