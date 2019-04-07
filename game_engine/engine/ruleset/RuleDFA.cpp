#include <memory>
#include <map>

#include "engine/ruleset/RuleDFA.hpp"

engine::ruleset::RuleDFA_t::RuleDFA_t()
:
mDFAStartNode( std::make_unique< engine::ruleset::DFANode_t >() )
{  
}

void engine::ruleset::RuleDFA_t::AddRuleToDFA( const engine::ruleset::Rule_t& aRule ) {

}

std::vector< engine::ruleset::LanguageInputCharacter_t > engine::ruleset::RuleDFA_t::ConvertPointsToLanguage( std::vector< engine::ruleset::Point_t >& aRulePoints ) {
    std::vector< engine::ruleset::LanguageInputCharacter_t > inputString;
    
    if( aRulePoints.size() == 0 ) {
        return inputString;
    }
    
    engine::ruleset::PointBounds_t pointBounds = GetBoundsFromPoints( aRulePoints );

    std::map< std::pair< int, int >, engine::board::ResourceType_t > pointLocationToResourceMap {};
    for( auto& point : aRulePoints ) {
        pointLocationToResourceMap[{ point.Location.xPos, point.Location.yPos }] = point.Resource;
    }

    for( int i = pointBounds.LeftTopCorner.xPos; i < pointBounds.LeftTopCorner.xPos + pointBounds.recWidth; i++ ) {
        auto direction = engine::ruleset::LanguageDirection_t::EAST;

        for( int j = pointBounds.LeftTopCorner.yPos; j < pointBounds.LeftTopCorner.yPos + pointBounds.recHeight; j++) {
            engine::ruleset::LanguageInputCharacter_t newCharacter{};
            newCharacter.Direction = direction;

            // Three cases are checked here:
            // (a) The point has a resource; must match exactly
            // (b) The point cardinal-direction neighbor is filled; must be an empty space
            // (c) The point is empty and neighbors are empty; can be any resource type
            // This solves the issue of L shapes!
            if( pointLocationToResourceMap.find({i, j}) != pointLocationToResourceMap.end() ) {
                newCharacter.Resource = pointLocationToResourceMap[{i, j}];
            } else if ( ( pointLocationToResourceMap.find({i, j}) != pointLocationToResourceMap.end() ) ||
                        ( pointLocationToResourceMap.find({i, j}) != pointLocationToResourceMap.end() ) ||
                        ( pointLocationToResourceMap.find({i, j}) != pointLocationToResourceMap.end() ) ||
                        ( pointLocationToResourceMap.find({i, j}) != pointLocationToResourceMap.end() ) ) {
                newCharacter.Resource = engine::board::ResourceType_t::EMPTY;
            } else {
                newCharacter.Resource = engine::board::ResourceType_t::IGNORE;
            }

            direction = engine::ruleset::LanguageDirection_t::SOUTH;

            inputString.push_back( newCharacter );
        }
    }

    return inputString;
}

engine::ruleset::PointBounds_t engine::ruleset::RuleDFA_t::GetBoundsFromPoints( std::vector< engine::ruleset::Point_t >& aRulePoints ) {

    engine::ruleset::PointBounds_t theBounds {};

    int xLowCorner;
    int yLowCorner;
    int xHighCorner;
    int yHighCorner;

    bool hasSetCorner = false;

    // First, obtain the range of the points
    // note lower means higher in the board in the user's perspective
    for( auto& point : aRulePoints) {
        if( point.Location.xPos < xLowCorner || !hasSetCorner ) {
            xLowCorner = point.Location.xPos;
        }

        if( point.Location.yPos < yLowCorner || !hasSetCorner ) {
            yLowCorner = point.Location.yPos;
        }

        if( point.Location.xPos > xHighCorner || !hasSetCorner ) {
            xHighCorner = point.Location.xPos;
        }

        if( point.Location.yPos > yHighCorner || !hasSetCorner ) {
            yHighCorner = point.Location.xPos;
        }
    }

    theBounds.LeftTopCorner = engine::ruleset::PointLocation_t{ xLowCorner, yLowCorner };
    theBounds.recWidth = xHighCorner - xLowCorner;
    theBounds.recHeight = yHighCorner - yLowCorner;

    return theBounds;
}