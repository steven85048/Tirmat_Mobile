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
    REFUND,
    GENERATING,
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
    bool IsUndo;

    // Updates the resource usage map with the resource usages specified in Moves
    void UpdateResourceUsage() {
        // The undo resources should already be set, so we shouldn't need to do anything
        if( IsUndo ) {
            return;
        }

        for( auto& theMove : Moves ) {
            if( theMove.MoveType == engine::board::MoveType_t::ADDRESOURCE ) {
                if( theMove.Resource ) { 
                    ResourceUsage[*theMove.Resource] -= 1;
                }
            } else if( theMove.MoveType == engine::board::MoveType_t::REMOVERESOURCE ) {
                ResourceUsage[ResourceType_t::REFUND] -=1 ;
            }
        }
    }

    // After the moves are processed, this method reupdates ResourceUsages with the
    // refunds on removing a resource
    void ProcessRefunds() {
        if( IsUndo ) {
            return;
        }

        for( auto& theMove : Moves ) {
            if( theMove.MoveType == engine::board::MoveType_t::REMOVERESOURCE ) {
                if( theMove.PreviousResource ) {
                    ResourceUsage[*theMove.PreviousResource] +=1;
                }
            }
        }
    }
};

} // ENDOF board
} // ENDOF engine