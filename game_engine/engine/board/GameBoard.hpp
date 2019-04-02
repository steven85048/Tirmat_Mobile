#pragma once

#include "engine/board/GameBoardIntf.hpp"

namespace engine
{

namespace board
{

enum class ResourceType_t {
    EMPTY,
    L1,
    L2,
    L3,
    L4,
    L5,
    L6
}

// Encapsulates a current board state
// Note that this class does not do the resource checking; that should be done before
// each resource call
// --------------------------------------------------------
class GameBoard_t : public GameBoardIntf_t {
// --------------------------------------------------------

GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY );

// --------------------------------------------------------
public: // GameBoardIntf_t overrides
// --------------------------------------------------------

const BoardArray_t& GetBoardState() const override;

bool AddResource( ResourceTypes aResourceType, int xPosition, int yPosition) override;
bool RemoveResource( ResourceTypes aResourceType, int xPosition, int yPosition) override;

int UndoMove() override;

// --------------------------------------------------------
public: // TYPES
// --------------------------------------------------------

using BoardArray1D_t = std::unique_ptr< ResourceType_t >[];
using BoardArray2D_t = std::unique_ptr< BoardArray1D_t >[] >;

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

AllocateBoard( int aBoardSizeX, int aBoardSizeY );

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

    // We want to make sure ONLY this class can make copy to the "real" version of the board
    BoardArray_t mBoard;

};

} //ENDOF board
} //ENDOF engine