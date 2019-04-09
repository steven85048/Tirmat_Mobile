#pragma once

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
    LOCKED
};

struct PointLocation_t {
    int xPos;
    int yPos;
};

struct BoardCellState_t {
    PointLocation_t Location;
    ResourceType_t Resource;
    bool Locked = false;

    BoardCellState_t( int xPos, int yPos ) {
        Location.xPos = xPos;
        Location.yPos = yPos;
    }
};

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
    engine::board::ResourceType_t Resource;
};

} // ENDOF board
} // ENDOF engine