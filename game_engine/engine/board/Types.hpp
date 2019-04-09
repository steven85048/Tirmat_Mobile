#pragma once

#include <optional>

namespace engine
{

namespace board
{

enum class MoveType_t {
    ADDRESOURCE,
    REMOVERESOURCE
};

enum class ResourceType_t {
    EMPTY,
    IGNORE,
    L1,
    L2,
    L3,
    L4,
    L5,
    L6
};

enum class MoveResult_t {
    SUCCESS,
    OUTOFBOUNDS,
    UNKNOWNMOVE,
    LOCKED,
    RESOURCEUNSET
};

struct PointLocation_t {
    int xPos;
    int yPos;
};

struct BoardCellState_t {
    PointLocation_t Location;
    ResourceType_t Resource = ResourceType_t::EMPTY;
    bool Locked = false;

    BoardCellState_t( int xPos, int yPos ) {
        Location.xPos = xPos;
        Location.yPos = yPos;
    }
};

// Note that Resource MUST be set if you are adding a resource!
struct GameBoardMove_t {

    GameBoardMove_t( MoveType_t aMoveType, int aMoveIndexX, int aMoveIndexY )
    :
    MoveType( aMoveType ),
    MoveIndexX( aMoveIndexX ),
    MoveIndexY( aMoveIndexY )
    {
    }

    MoveType_t MoveType;
    int MoveIndexX;
    int MoveIndexY;
    std::optional< engine::board::ResourceType_t > Resource = std::nullopt;
};

} // ENDOF board
} // ENDOF engine