#pragma once

#include <stack>
#include <memory>

#include "engine/board/GameBoardIntf.hpp"
#include "engine/board/Types.hpp"
#include "engine/board/GameBoardMove.hpp"

namespace engine
{

namespace board
{

// Encapsulates a current board state
// Note that this class does not do the resource checking; that should be done before
// each resource call
// --------------------------------------------------------
class GameBoard_t : public GameBoardIntf_t {
// --------------------------------------------------------

// --------------------------------------------------------
public: // TYPES
// --------------------------------------------------------

using BoardArray1D_t = std::unique_ptr< BoardCellState_t >[];
using BoardArray2D_t = std::unique_ptr< BoardArray1D_t >[];

GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY );

// --------------------------------------------------------
public: // GameBoardIntf_t overrides
// --------------------------------------------------------

const BoardArray2D_t& GetBoardState() const override;
std::vector< MoveResult_t > RunMoves( std::vector< engine::board::GameBoardMove_t > aMoves ) override;
bool UndoMove() override;

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

void AllocateBoard( std::size_t aBoardSizeX, std::size_t aBoardSizeY );

MoveResult_t AddResource( engine::board::GameBoardMove_t aMoves );
MoveResult_t RemoveResource( engine::board::GameBoardMove_t aMoves );

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

    // We want to make sure ONLY this class can make copy to the "real" version of the board
    BoardArray2D_t mBoard;
    std::stack< std::vector< engine::board::GameBoardMove_t > > mPreviousMoves;
};

} //ENDOF board
} //ENDOF engine