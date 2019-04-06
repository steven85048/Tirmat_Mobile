#include "engine/board/Types.hpp"

namespace engine
{

namespace board
{

// --------------------------------------------------------
class GameBoardMove_t {
// --------------------------------------------------------

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

GameBoardMove_t( MoveType_t aMoveType, int aMoveIndexX, int aMoveIndexY )
:
MoveType( aMoveType ),
MoveIndexX( aMoveIndexX ),
MoveIndexY( aMoveIndexY )
{
}

// --------------------------------------------------------
public: // DATA
// --------------------------------------------------------

MoveType_t MoveType;
int MoveIndexX;
int MoveIndexY;
engine::board::ResourceType_t Resource;

};

} // END of board
} // END of engine