#include <vector>

#include "engine/board/GameBoard.hpp"
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

    virtual const engine::board::GameBoard_t::BoardArray2D_t& GetBoardState() const = 0;
    
    virtual std::vector< engine::board::MoveResult_t > RunMoves( const std::vector< engine::board::GameBoardMove_t >& aMoves ) = 0;
    virtual void CommitStagedBoard() = 0;
    
    virtual bool UndoMove() = 0; 

    virtual std::shared_ptr< engine::board::BoardCellState_t > GetCellState( int xPos, int yPos ) const = 0;
    virtual std::shared_ptr< engine::board::BoardCellState_t > GetCellStateStaged( int xPos, int yPos ) const = 0;
};

} // ENDOF board
} // ENDOF engine