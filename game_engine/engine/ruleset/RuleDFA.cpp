#include <iostream>
#include <memory>
#include <map>

#include "engine/ruleset/RuleDFA.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"

engine::ruleset::RuleDFA_t::RuleDFA_t()
:
mDFAStartNode( std::make_shared< engine::ruleset::DFANode_t >() ),
mGeneratingLocations( std::make_shared< std::vector< engine::board::BoardCellState_t > >() )
{  
}

void engine::ruleset::RuleDFA_t::PointSetsUpdated( const std::unordered_set< engine::shapeset::ShapeSetManager_t::PointSet_t >& aPointSets ) {
    
    std::cout << "RuleDFA_T::PointSetsUpdated: " << aPointSets.size() << std::endl;

    mGeneratingLocations->clear();
    
    for( auto& thePointSet : aPointSets ) {
        auto thePassResponse = PassShapeThroughDFA( *thePointSet );
        
        if( thePassResponse.ResponseType == engine::ruleset::DFAResponseType_t::LEVELCOMPLETION ) {
            std::cout << "Reached Level Completion Node" << std::endl;
            // TODO: set some shared level completion variable
        } else if( thePassResponse.ResponseType == engine::ruleset::DFAResponseType_t::GENERATING ) {

            auto theShapeCorner = thePassResponse.LeftTopCorner;
            auto theShapeGeneratingPoints = thePassResponse.GeneratingPoints;

            // For each point, we create the new point with the absolute location
            // Corner + generating point(x,y)
            for( auto& thePoint : theShapeGeneratingPoints ) {
                engine::board::BoardCellState_t theGeneratingState( theShapeCorner.xPos + thePoint->Location.xPos, theShapeCorner.yPos + thePoint->Location.yPos );
                theGeneratingState.Resource = thePoint->Resource;
                theGeneratingState.Locked = thePoint->Locked;

                // TODO: Assumes there are no duplicate generating locations for now; we may want to add
                // the values in the case of duplicates

                mGeneratingLocations->push_back( theGeneratingState );
            }
        }
    }
}

engine::ruleset::DFAPassResponse_t engine::ruleset::RuleDFA_t::PassShapeThroughDFA( const std::vector< std::shared_ptr< engine::board::BoardCellState_t > >& aShapePoints ) {
    std::cout << "RuleDFA_T::PassShapeThroughDFA" << std::endl;
    
    auto theCurrentState = mDFAStartNode;

    engine::ruleset::DFAPassResponse_t theResponse{};

    auto thePointBounds = GetBoundsFromPoints( aShapePoints );
    auto theInputString = ConvertPointsToLanguage( aShapePoints, thePointBounds );

    // Used to get the absolute generating location
    theResponse.LeftTopCorner = thePointBounds.LeftTopCorner;

    for( auto& theInputCharacter : theInputString ) {
        std::cout << "Transitioning pass: " << theCurrentState->Transition.size() << std::endl;

        std::pair< LanguageDirection_t, engine::board::ResourceType_t > inputCharacterPair = { theInputCharacter.Direction, theInputCharacter.Resource };
        if( theCurrentState->Transition.find( inputCharacterPair ) == theCurrentState->Transition.end() ) {
            theResponse.ResponseType = engine::ruleset::DFAResponseType_t::NOMATCH;
            return theResponse;
        }

        theCurrentState = theCurrentState->Transition[inputCharacterPair];
    }

    if( !theCurrentState->IsAcceptingNode ) {
        theResponse.ResponseType = engine::ruleset::DFAResponseType_t::NOMATCH;
        return theResponse;
    }

    theResponse.GeneratingPoints = theCurrentState->Generating;
    if( theCurrentState->IsLevelCompletionNode ) {
        theResponse.ResponseType = engine::ruleset::DFAResponseType_t::LEVELCOMPLETION;
    } else if ( theCurrentState->IsAcceptingNode ) {
        theResponse.ResponseType = engine::ruleset::DFAResponseType_t::GENERATING;
    }

    return theResponse;
}

void engine::ruleset::RuleDFA_t::AddRuleToDFA( const engine::ruleset::Rule_t& aRule ) {
    auto theCurrentState = mDFAStartNode;

    auto thePointBounds = GetBoundsFromPoints( aRule.RulePoints );
    auto theInputString = ConvertPointsToLanguage( aRule.RulePoints, thePointBounds );

    for( auto& theInputCharacter : theInputString ) {
        std::cout << "Transitioning add rule" << std::endl;

        // Using structs as keys are annoying, so we just use a pair
        std::pair< LanguageDirection_t, engine::board::ResourceType_t > inputCharacterPair = { theInputCharacter.Direction, theInputCharacter.Resource };

        // Similar to Trie! We continue the tree traversal if the transition exists, and create a new node if it doesn't
        if( theCurrentState->Transition.find( inputCharacterPair ) == theCurrentState->Transition.end() ) {
            auto theNewNode = std::make_shared< engine::ruleset::DFANode_t >();
            theCurrentState->Transition[inputCharacterPair] = std::move( theNewNode );
        }

        theCurrentState = theCurrentState->Transition[inputCharacterPair];
    }

    if( theCurrentState->IsAcceptingNode ) {
        // Duplicate rule
    }

    theCurrentState->IsAcceptingNode = true;
    theCurrentState->IsLevelCompletionNode = aRule.IsLevelCompletionRule;
    theCurrentState->Generating = aRule.GeneratePoints;
}

std::vector< engine::ruleset::LanguageInputCharacter_t > engine::ruleset::RuleDFA_t::ConvertPointsToLanguage( const std::vector< std::shared_ptr< engine::board::BoardCellState_t > >& aRulePoints, 
                                                                                                              const engine::ruleset::PointBounds_t& aPointBounds ) {
    std::cout << "RuleDFA_t::ConvertPointsToLanguage" << std::endl;
    
    std::cout << "Point bounds width: " << aPointBounds.recWidth << " height: " << aPointBounds.recHeight << std::endl;
    std::cout << "Point bounds xCorn: " << aPointBounds.LeftTopCorner.xPos << " yCorn: " << aPointBounds.LeftTopCorner.yPos << std::endl;
 
    std::vector< engine::ruleset::LanguageInputCharacter_t > inputString;
    
    if( aRulePoints.size() == 0 ) {
        return inputString;
    }
    
    std::map< std::pair< int, int >, engine::board::ResourceType_t > pointLocationToResourceMap {};
    for( auto& point : aRulePoints ) {
        pointLocationToResourceMap[{ point->Location.xPos, point->Location.yPos }] = point->Resource;
    }

    for( int i = aPointBounds.LeftTopCorner.xPos; i <= aPointBounds.LeftTopCorner.xPos + aPointBounds.recWidth; i++ ) {
        auto direction = engine::ruleset::LanguageDirection_t::EAST;

        for( int j = aPointBounds.LeftTopCorner.yPos; j <= aPointBounds.LeftTopCorner.yPos + aPointBounds.recHeight; j++) {

            engine::ruleset::LanguageInputCharacter_t newCharacter{};
            newCharacter.Direction = direction;

            // Three cases are checked here:
            // (a) The point has a resource; must match exactly
            // (b) The point cardinal-direction neighbor is filled; must be an empty space
            // (c) The point is empty and neighbors are empty; can be any resource type
            // This solves the issue of L shapes!
            if( pointLocationToResourceMap.find({i, j}) != pointLocationToResourceMap.end() ) {
                newCharacter.Resource = pointLocationToResourceMap[{i, j}];
            } else if ( ( pointLocationToResourceMap.find({i+1, j}) != pointLocationToResourceMap.end() ) ||
                        ( pointLocationToResourceMap.find({i, j+1}) != pointLocationToResourceMap.end() ) ||
                        ( pointLocationToResourceMap.find({i-1, j}) != pointLocationToResourceMap.end() ) ||
                        ( pointLocationToResourceMap.find({i, j-1}) != pointLocationToResourceMap.end() ) ) {
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

engine::ruleset::PointBounds_t engine::ruleset::RuleDFA_t::GetBoundsFromPoints( const std::vector< std::shared_ptr< engine::board::BoardCellState_t > >& aRulePoints ) {

    engine::ruleset::PointBounds_t theBounds {};

    int xLowCorner;
    int yLowCorner;
    int xHighCorner;
    int yHighCorner;

    bool hasSetCorner = false;

    // First, obtain the range of the points
    // note lower means higher in the board in the user's perspective
    for( auto& point : aRulePoints) {
        if( point->Location.xPos < xLowCorner || !hasSetCorner ) {
            xLowCorner = point->Location.xPos;
        }

        if( point->Location.yPos < yLowCorner || !hasSetCorner ) {
            yLowCorner = point->Location.yPos;
        }

        if( point->Location.xPos > xHighCorner || !hasSetCorner ) {
            xHighCorner = point->Location.xPos;
        }

        if( point->Location.yPos > yHighCorner || !hasSetCorner ) {
            yHighCorner = point->Location.yPos;
        }

        hasSetCorner = true;
    }

    theBounds.LeftTopCorner = engine::board::PointLocation_t{ xLowCorner, yLowCorner };
    theBounds.recWidth = xHighCorner - xLowCorner;
    theBounds.recHeight = yHighCorner - yLowCorner;

    return theBounds;
}