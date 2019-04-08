#include <unordered_set>

#include "engine/shapeset/ShapeSetManager.hpp"
#include "engine/board/GameBoardIntf.hpp"
#include "engine/board/Types.hpp"
#include "engine/ruleset/Types.hpp"

engine::shapeset::ShapeSetManager_t::ShapeSetManager_t( std::shared_ptr< engine::board::GameBoardIntf_t > aGameBoard )
:
mGameBoard( std::move( aGameBoard ) ),
mLocationToPointSetMap()
{}

void engine::shapeset::ShapeSetManager_t::ExecuteMoves( const std::vector< engine::board::GameBoardMove_t > aMoves ) {
    if( mGameBoard ) {
        auto theMoveResults = mGameBoard->RunMoves( aMoves );
        
        // If there was a problem executing, we just leave for now; may want more robust handling later
        for( auto& theMoveResult : theMoveResults ) {
            if( theMoveResult != engine::board::MoveResult_t::SUCCESS ) {
                return;
            }
        }

        for( auto& theMove : aMoves ) {
            switch( theMove.MoveType ) {
                case engine::board::MoveType_t::ADDRESOURCE: {
                    AddResource( theMove.MoveIndexX, theMove.MoveIndexY );
                    break;  
                }
                case engine::board::MoveType_t::REMOVERESOURCE: {
                    RemoveResource( theMove.MoveIndexX, theMove.MoveIndexY );
                    break;
                }
            }
        }

        mGameBoard->CommitStagedBoard();
    }
}

void engine::shapeset::ShapeSetManager_t::AddResource( int xPos, int yPos ) {

    auto concatSet = GetNeighborSets( xPos, yPos );

    // Also insert our new point; NOTE that the staged board should be updated with the correct color at this point, so we just get it from there
    concatSet->push_back( mGameBoard->GetCellStateStaged( xPos, yPos ) );

    // Update the map so all points now reference this new set
    for( auto& thePoint : *mConcatSet ) {
        mLocationToPointSetMap[{thePoint.Location.xPos, thePoint.Location.yPos}] = mConcatSet;
    }
}

void engine::shapeset::ShapeSetManager_t::RemoveResource( int xPos, int yPos ) {

    // Should only be one set, but we use this for convenience
    auto concatSet = GetNeighborSets( xPos, yPos );

    // Remove all the cells and re-add them; this isn't the cleanest, but it works
    for( auto& thePoint : *mConcatSet ) {
        mLocationToPointSetMap[{thePoint.Location.xPos, thePoint.Location.yPos}] = nullptr;
    }

    // Readd them all EXCEPT the one to get removed
    for( auto& thePoint : *mConcatSet ) {
        if( !( thePoint.Location.xPos == xPos && thePoint.Location.yPos == yPos ) ) {
            AddResource( thePoint.Location.xPos, thePoint.Location.yPos );
        }
    }  
}

std::shared_ptr< std::vector< engine::board::BoardCellState_t > > engine::shapeset::ShapeSetManager_t::GetNeighborSets( int xPos, int yPos ) {
    auto theNeighbors = GetValidNeighbors( xPos, yPos );

    // If two neighbors are in the same set, we don't want to do duplicate ops
    std::unordered_set< std::shared_ptr< std::vector< engine::board::BoardCellState_t > > > pointSet;

    // get all unique sets of the neighbors
    for( auto theNeighbor : theNeighbors) {
        std::pair<int, int> theNeighborLocationPair = {theNeighbor.xPos, theNeighbor.yPos};

        if( mLocationToPointSetMap.find( theNeighborLocationPair ) != mLocationToPointSetMap.end() ) {
            pointSet.insert( mLocationToPointSetMap[ theNeighborLocationPair ] );
        }
    }

    // Create a new set that we will put all the neighboring points into
    auto concatSet = std::make_shared< std::vector< engine::board::BoardCellState_t > >();

    for( auto theSet : pointSet ) {
        if( theSet ) {
            concatSet->insert( concatSet->end(), theSet->begin(), theSet->end() );
        }
    }

    return concatSet;
}

std::vector< engine::ruleset::PointLocation_t > engine::shapeset::ShapeSetManager_t::GetValidNeighbors( int xPos, int yPos ) {
    int theDirections[4][2] = {{0, 1},{1,0},{-1,0},{0,-1}};

    std::vector< engine::ruleset::PointLocation_t > theNeighbors;

    for( auto& theDirection : theDirections ) {
        auto xNeighborPos = xPos + theDirection[0];
        auto yNeighborPos = yPos + theDirection[1];

        auto theCellState = mGameBoard->GetCellState( xNeighborPos, yNeighborPos );
        if( theCellState ) {
            engine::ruleset::PointLocation_t newPoint{};
            newPoint.xPos = xNeighborPos;
            newPoint.yPos = yNeighborPos;

            theNeighbors.push_back( newPoint );
        }
    }

    return theNeighbors;
}