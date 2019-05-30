#pragma once

#include <memory>

#include "engine/state/UserStateContainer.hpp"
#include "engine/move/MoveManager.hpp"

namespace engine
{

namespace initialization
{

struct GameInteractorContainer {
    std::shared_ptr< engine::state::UserStateContainer_t > mStateContainer;
    std::shared_ptr< engine::move::MoveManager_t > mMoveManager;
};

// Initializes the game with a variety of different options
class GameBoardFactory_t
{
    
// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

GameInteractorContainer InitializeDefault();

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

};

} // ENDOF initialization
} // ENDOF engine