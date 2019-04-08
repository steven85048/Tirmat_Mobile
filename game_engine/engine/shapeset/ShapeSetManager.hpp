#include <memory>

#include "engine/board/GameBoardIntf.hpp"

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

ShapeSetManager_t();

// Execute a set of moves
void ExecuteMoves( std::vector< engine::board::GameBoardMove_t > aMoves );

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

void AddResource( int xPos, int yPos, engine::board::ResourceType_t aResource );
void RemoveResource( int xPos, int yPos );

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::board::GameBoardIntf_t > mGameBoard; 

};

} // ENDOF shapeset
} // ENDOF engine