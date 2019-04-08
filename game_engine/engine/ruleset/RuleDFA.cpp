#include <memory>
#include <map>

#include "engine/ruleset/RuleDFA.hpp"

engine::ruleset::RuleDFA_t::RuleDFA_t()
:
mDFAStartNode( std::make_unique< engine::ruleset::DFANode_t >() )
{  
}

engine::ruleset::DFAPassResponse_t engine::ruleset::RuleDFA_t::PassShapeThroughDFA( const std::vector< engine::board::BoardCellState_t >& aShapePoints ) {
    auto& theCurrentState = *mDFAStartNode;

    engine::ruleset::DFAPassResponse_t theResponse{};

    auto theInputString = ConvertPointsToLanguage( aShapePoints );
    for( auto& theInputCharacter : theInputString ) {
        std::pair< LanguageDirection_t, engine::board::ResourceType_t > inputCharacterPair = { theInputCharacter.Direction, theInputCharacter.Resource };
        if( theCurrentState.Transition.find( inputCharacterPair ) == theCurrentState.Transition.end() ) {
            theResponse.ResponseType = engine::ruleset::DFAResponseType_t::NOMATCH;
            return theResponse;
        }

        theCurrentState = *theCurrentState.Transition[inputCharacterPair];
    }

    if( !theCurrentState.IsAcceptingNode ) {
        theResponse.ResponseType = engine::ruleset::DFAResponseType_t::NOMATCH;
        return theResponse;
    }

    theResponse.GeneratingPoints = theCurrentState.Generating;
    if( theCurrentState.IsLevelCompletionNode ) {
        theResponse.ResponseType = engine::ruleset::DFAResponseType_t::LEVELCOMPLETION;
    } else if ( theCurrentState.IsAcceptingNode ) {
        theResponse.ResponseType = engine::ruleset::DFAResponseType_t::GENERATING;
    }

    return theResponse;
}

void engine::ruleset::RuleDFA_t::AddRuleToDFA( const engine::ruleset::Rule_t& aRule ) {
    auto& theCurrentState = *mDFAStartNode;

    auto theInputString = ConvertPointsToLanguage( aRule.RulePoints );
    for( auto& theInputCharacter : theInputString ) {
        // Using structs as keys are annoying, so we just use a pair
        std::pair< LanguageDirection_t, engine::board::ResourceType_t > inputCharacterPair = { theInputCharacter.Direction, theInputCharacter.Resource };

        // Similar to Trie! We continue the tree traversal if the transition exists, and create a new node if it doesn't
        if( theCurrentState.Transition.find( inputCharacterPair ) == theCurrentState.Transition.end() ) {
            auto theNewNode = std::make_unique< engine::ruleset::DFANode_t >();
            theCurrentState.Transition[inputCharacterPair] = std::move( theNewNode );
        }

        theCurrentState = *theCurrentState.Transition[inputCharacterPair];
    }

    if( theCurrentState.IsAcceptingNode ) {
        // ERROR! There is a duplicate rule in the set.
    }

    theCurrentState.IsAcceptingNode = true;
    theCurrentState.IsLevelCompletionNode = aRule.IsLevelCompletionRule;
    theCurrentState.Generating = aRule.GeneratePoints;
}

std::vector< engine::ruleset::LanguageInputCharacter_t > engine::ruleset::RuleDFA_t::ConvertPointsToLanguage( const std::vector< engine::board::BoardCellState_t >& aRulePoints ) {
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

engine::ruleset::PointBounds_t engine::ruleset::RuleDFA_t::GetBoundsFromPoints( const std::vector< engine::board::BoardCellState_t >& aRulePoints ) {

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

    theBounds.LeftTopCorner = engine::board::PointLocation_t{ xLowCorner, yLowCorner };
    theBounds.recWidth = xHighCorner - xLowCorner;
    theBounds.recHeight = yHighCorner - yLowCorner;

    return theBounds;
}