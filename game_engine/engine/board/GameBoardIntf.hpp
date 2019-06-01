#pragma once

#include <memory>
#include <vector>

#include "djinni/BoardCellState.hpp"
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
    
    virtual bool RunMoves( std::vector< engine::board::GameBoardMove_t >& aMoves ) = 0;    
    virtual std::vector<std::vector<djinni::BoardCellState>> CloneBoardDereferenced() const = 0;
    virtual std::shared_ptr< djinni::BoardCellState > GetCellState( int xPos, int yPos ) const = 0;
};

} // ENDOF board
} // ENDOF engine