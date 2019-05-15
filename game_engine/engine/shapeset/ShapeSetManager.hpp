#pragma once

#include <map>
#include <memory>
#include <unordered_set>

#include "engine/board/GameBoardIntf.hpp"
#include "engine/ruleset/Types.hpp"

namespace engine
{
namespace shapeset
{

// Manages the shapes that are active on the board through a set of disjoint set operations
// A shape are all cells connected through cardinal directions.
// --------------------------------------------------------
class ShapeSetManager_t 
// --------------------------------------------------------
{

// --------------------------------------------------------
public: // TYPES
// --------------------------------------------------------

using PointSet_t = std::shared_ptr< std::vector< std::shared_ptr< engine::board::BoardCellState_t > > >;

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

ShapeSetManager_t( std::shared_ptr< engine::board::GameBoardIntf_t > aGameBoard );

void ExecuteMoves( std::vector< engine::board::GameBoardMove_t >& aMoves );
std::unordered_set< PointSet_t >& GetPointSets(){ return mPointSets; }

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

void AddResource( int xPos, int yPos );
void RemoveResource( int xPos, int yPos );

// Also removes all neighbor sets from mPointSets; assumes that these will be readded as part of the
// add and remove operations
PointSet_t GetNeighborSets( int xPos, int yPos );
std::vector< engine::board::PointLocation_t > GetValidNeighbors( int xPos, int yPos );

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::board::GameBoardIntf_t > mGameBoard; 

// Map from the location to the reference of the state stored in the board itself
std::map< std::pair< int, int >, PointSet_t > mLocationToPointSetMap;

// Store all the current point sets on the board
std::unordered_set< PointSet_t > mPointSets;

};

} // ENDOF shapeset
} // ENDOF engine