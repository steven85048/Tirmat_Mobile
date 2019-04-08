#include "engine/shapeset/ShapeSetManager.hpp"
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

        // TODO: Handle possible errors in the results here
        for( auto& theMove : aMoves ) {
            
        }
    }
}

void engine::shapeset::ShapeSetManager_t::AddResource( int xPos, int yPos, engine::board::ResourceType_t aResource ) {

}

void engine::shapeset::ShapeSetManager_t::RemoveResource( int xPos, int yPos ) {

}


