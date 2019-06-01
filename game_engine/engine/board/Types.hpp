#pragma once

#include <vector>
#include <optional>
#include <unordered_map>

#include "djinni/MoveResult.hpp"
#include "djinni/PointLocation.hpp"
#include "djinni/ResourceType.hpp"

namespace engine
{

namespace board
{

enum class MoveType_t {
    ADDRESOURCE,
    REMOVERESOURCE
};

struct GameBoardMove_t {

    MoveType_t MoveType;
    djinni::MoveResult MoveResult = djinni::MoveResult::MOVEUNCHECKED;

    int MoveIndexX;
    int MoveIndexY;
    
    // Previous resource is used to extract the equivalent Undo of this move
    std::optional< djinni::ResourceType > PreviousResource = std::nullopt; 
    std::optional< djinni::ResourceType > Resource = std::nullopt;

    GameBoardMove_t( MoveType_t aMoveType, int aMoveIndexX, int aMoveIndexY, std::optional< djinni::ResourceType > aResource = std::nullopt )
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
    std::unordered_map< djinni::ResourceType, int > ResourceUsage;
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
                ResourceUsage[ djinni::ResourceType::REFUND ] -=1 ;
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