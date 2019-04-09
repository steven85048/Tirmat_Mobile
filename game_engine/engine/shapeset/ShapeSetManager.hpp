#pragma once

#include <map>
#include <memory>

#include "engine/board/GameBoardIntf.hpp"
#include "engine/ruleset/Types.hpp"

namespace engine
{
namespace shapeset
{

// Manages the shapes that are active on the board through a set of disjoint set operations
class ShapeSetManager_t 
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

ShapeSetManager_t( std::shared_ptr< engine::board::GameBoardIntf_t > aGameBoard );

// Execute a set of moves
void ExecuteMoves( std::vector< engine::board::GameBoardMove_t > aMoves );

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

void AddResource( int xPos, int yPos );
void RemoveResource( int xPos, int yPos );

std::shared_ptr< std::vector< std::shared_ptr< engine::board::BoardCellState_t > > > GetNeighborSets( int xPos, int yPos );
std::vector< engine::board::PointLocation_t > GetValidNeighbors( int xPos, int yPos );

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::board::GameBoardIntf_t > mGameBoard; 
std::map< std::pair< int, int >, std::shared_ptr< std::vector< std::shared_ptr< engine::board::BoardCellState_t > > > > mLocationToPointSetMap;

};

} // ENDOF shapeset
} // ENDOF engine