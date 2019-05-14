#pragma once

#include <vector>
#include <optional>
#include <unordered_map>

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
    LOCKED,
    RESOURCEUNSET,
    DELETEFROMEMPTY,
    MOVEUNCHECKED
};

struct PointLocation_t {
    int xPos;
    int yPos;

    friend bool operator==(const PointLocation_t& aLeftLocation, const PointLocation_t& aRightLocation) {
        return aLeftLocation.xPos == aRightLocation.xPos && aLeftLocation.yPos == aRightLocation.yPos;
    }
};

struct BoardCellState_t {
    PointLocation_t Location;
    ResourceType_t Resource = ResourceType_t::EMPTY;
    bool Locked = false;

    BoardCellState_t( int xPos, int yPos ) {
        Location.xPos = xPos;
        Location.yPos = yPos;
    }

    friend bool operator==(const BoardCellState_t& aLeftState, const BoardCellState_t& aRightState) {
        return aLeftState.Location == aRightState.Location && aLeftState.Resource == aRightState.Resource && aLeftState.Locked == aRightState.Locked; 
    }
};

struct GameBoardMove_t {

    MoveType_t MoveType;
    MoveResult_t MoveResult = MoveResult_t::MOVEUNCHECKED;

    int MoveIndexX;
    int MoveIndexY;
    
    // Previous resource is used to extract the equivalent Undo of this move
    std::optional< engine::board::ResourceType_t > PreviousResource = std::nullopt; 
    std::optional< engine::board::ResourceType_t > Resource = std::nullopt;

    GameBoardMove_t( MoveType_t aMoveType, int aMoveIndexX, int aMoveIndexY, std::optional< engine::board::ResourceType_t > aResource = std::nullopt )
    :
    MoveType( aMoveType ),
    MoveIndexX( aMoveIndexX ),
    MoveIndexY( aMoveIndexY ),
    Resource( aResource )
    {
    }
};

struct GameBoardMoveBatch_t {
    std::vector< GameBoardMove_t > Moves;
    std::unordered_map< ResourceType_t, int > ResourceUsage;
    bool IsGenerating;

    // TODO: function that obtains the necessary resources for batch
};

} // ENDOF board
} // ENDOF engine