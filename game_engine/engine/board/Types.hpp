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

struct EnumStrings_t {
    static std::string ResourceToString( ResourceType_t theType ) {
        switch( theType ) {
            case ResourceType_t::EMPTY:
                return "0";
            case ResourceType_t::IGNORE: 
                return "-1";
            case ResourceType_t::L1: 
                return "1";
            case ResourceType_t::L2: 
                return "2";
            case ResourceType_t::L3: 
                return "3";
            case ResourceType_t::L4: 
                return "4";
            case ResourceType_t::L5: 
                return "5";
            case ResourceType_t::L6: 
                return "6";   
        }

        return "UNKNOWN";
    }
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