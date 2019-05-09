#pragma once

#include <vector>

#include "engine/board/Types.hpp"

namespace engine
{

namespace board
{

class GameBoardIntf_t
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------
    
    virtual std::vector< engine::board::MoveResult_t > RunMoves( const std::vector< engine::board::GameBoardMove_t >& aMoves ) = 0;
    virtual void CommitStagedBoard() = 0;
    
    virtual std::shared_ptr< engine::board::BoardCellState_t > GetCellState( int xPos, int yPos ) const = 0;
    virtual std::shared_ptr< engine::board::BoardCellState_t > GetCellStateStaged( int xPos, int yPos ) const = 0;
};

} // ENDOF board
} // ENDOF engine