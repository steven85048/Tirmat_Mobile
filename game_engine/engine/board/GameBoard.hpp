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
class GameBoard_t : public GameBoardIntf_t 
// --------------------------------------------------------
{

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

// Runs the set of moves in aMoves; note that aMoves WILL be modified after execution
bool RunMoves( std::vector< engine::board::GameBoardMove_t >& aMoves ) override;

std::shared_ptr< engine::board::BoardCellState_t > GetCellState( int xPos, int yPos ) const override;

// For Testing
void PrintBoard();

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// Allocates heap memory for the board
BoardArray2D_t AllocateBoard();

// Determine if move is possible according to current board conditions
engine::board::MoveResult_t VerifyMove( engine::board::GameBoardMove_t& aMove );

// Run the move according to the type; will throw if the movetype is unidentified
void RunMove( engine::board::GameBoardMove_t& aMove );

// It is important that verify move is used on the move BEFORE these functions are run
void AddResource( engine::board::GameBoardMove_t& aMove );
void RemoveResource( engine::board::GameBoardMove_t& aMove );

bool IsValidPosition( int moveX, int moveY ) const;

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

    std::size_t mBoardWidth;
    std::size_t mBoardHeight;

    BoardArray2D_t mBoard;
};

} //ENDOF board
} //ENDOF engine