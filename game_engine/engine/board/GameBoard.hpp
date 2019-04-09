#pragma once

#include <stack>
#include <memory>
#include <vector>

#include "engine/board/GameBoardIntf.hpp"
#include "engine/board/Types.hpp"

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

// We store shared pointers since we store these cell states elsewhere, notably in the shapesetmanager
using BoardArray1D_t = std::vector< std::shared_ptr< engine::board::BoardCellState_t > >;
using BoardArray2D_t = std::vector< BoardArray1D_t >;

GameBoard_t( std::size_t aBoardSizeX, std::size_t aBoardSizeY );

// --------------------------------------------------------
public: // GameBoardIntf_t overrides
// --------------------------------------------------------

std::vector< MoveResult_t > RunMoves( const std::vector< engine::board::GameBoardMove_t >& aMoves ) override;
void CommitStagedBoard() override;

std::shared_ptr< engine::board::BoardCellState_t > GetCellState( int xPos, int yPos ) const override;
std::shared_ptr< engine::board::BoardCellState_t > GetCellStateStaged( int xPos, int yPos ) const override;

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// Allocates heap memory for the board
BoardArray2D_t AllocateBoard();

MoveResult_t AddResource( engine::board::GameBoardMove_t aMoves );
MoveResult_t RemoveResource( engine::board::GameBoardMove_t aMoves );

bool IsValidPosition( int moveX, int moveY ) const;

// For Testing
void PrintBoard();

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

    std::size_t mBoardWidth;
    std::size_t mBoardHeight;

    // We want to make sure ONLY this class can make copy to the "real" version of the board
    BoardArray2D_t mBoard;
    BoardArray2D_t mStagedBoard;

    std::stack< std::vector< engine::board::GameBoardMove_t > > mPreviousMoves;
};

} //ENDOF board
} //ENDOF engine