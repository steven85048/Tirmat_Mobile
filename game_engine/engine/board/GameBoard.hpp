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

enum class MoveError_t {
    SUCCESS,
    OUTOFBOUNDS
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

const BoardArray2D_t& GetBoardState() const override;
std::vector< MoveError_t > RunMoves( std::vector< game::engine::GameBoardMove_t > aMoves ) override;
bool UndoMove() override;

// --------------------------------------------------------
public: // TYPES
// --------------------------------------------------------

using BoardArray1D_t = std::unique_ptr< ResourceType_t >[];
using BoardArray2D_t = std::unique_ptr< BoardArray1D_t >[] >;

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

AllocateBoard( int aBoardSizeX, int aBoardSizeY );

MoveError_t AddResource( std::vector< game::engine::GameBoardMove_t > aMoves ) override;
MoveError_t RemoveResource( std::vector< game::engine::GameBoardMove_t > aMoves ) override;

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

    // We want to make sure ONLY this class can make copy to the "real" version of the board
    BoardArray_t mBoard;
    std::stack< std::vector< game::engine::GameBoardMove_t > > mPreviousMoves;
};

} //ENDOF board
} //ENDOF engine