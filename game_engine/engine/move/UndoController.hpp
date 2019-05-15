#pragma once

#include <optional>
#include <stack>

#include "engine/board/Types.hpp"

namespace engine
{

namespace move
{

// Creates and processes the undoes; returns the set of equivalent
// undo operations.
class UndoController_t
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

UndoController_t();

void AddUndoMoveBatch( const engine::board::GameBoardMoveBatch_t& aMoveBatch );
std::optional< engine::board::GameBoardMoveBatch_t > PopUndoMove();

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

engine::board::GameBoardMove_t CreateEquivalentUndo( const engine::board::GameBoardMove_t& aPreviousMove );


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::stack< engine::board::GameBoardMoveBatch_t > mUndoMoves;

};

} // ENDOF move
} // ENDOF engine