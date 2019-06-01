#pragma once

#include <map>
#include <memory>
#include <unordered_set>

#include "djinni/BoardCellState.hpp"
#include "engine/board/Types.hpp"
#include "engine/ruleset/Types.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"

namespace engine
{

namespace ruleset
{

// Handles rule-matching functionality, allowing the creation
// of new rules and matching of shapes with existing rules
class RuleDFA_t
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

RuleDFA_t( std::shared_ptr< std::vector< djinni::BoardCellState > > aGeneratingLocations );

// Note that DFA generation rules must have a LeftTop coordinate of (0,0)
// This is important for the generating points to work correctly
void AddRuleToDFA( const engine::ruleset::Rule_t& aRule );

// Runs the point sets through the DFA again, and updates the game state variables
void PointSetsUpdated( const std::unordered_set< engine::shapeset::ShapeSetManager_t::PointSet_t >& aPointSets );

// Getter for the generating points
const std::shared_ptr< std::vector< djinni::BoardCellState > >& GetGeneratingLocations() {
    return mGeneratingLocations;
}

// Reset the DFA state
void Reset();

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// Passes the input points through the DFA and outputs whether or not the shape matches successfully
engine::ruleset::DFAPassResponse_t PassShapeThroughDFA( const std::vector< std::shared_ptr< djinni::BoardCellState > >& aRulePoints );

// Generate the input string from the points;
// It traverses the point space in a zig-zag format
std::vector< engine::ruleset::LanguageInputCharacter_t > ConvertPointsToLanguage( const std::vector< std::shared_ptr< djinni::BoardCellState > >& aRulePoints,
                                                                                  const engine::ruleset::PointBounds_t& aPointBounds );
// Obtains the bounds of a set of points; used to create the input string
engine::ruleset::PointBounds_t GetBoundsFromPoints( const std::vector< std::shared_ptr< djinni::BoardCellState > >& aRulePoints );


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::ruleset::DFANode_t > mDFAStartNode;
std::shared_ptr< std::vector< djinni::BoardCellState > > mGeneratingLocations;

};

} // ENDOF ruleset
} // ENDOF engine