#pragma once

#include <memory>

#include "engine/board/GameBoard.hpp"
#include "engine/board/Types.hpp"

namespace engine
{

namespace state
{

// This class has shared pointers to state variables of the game
// Can be used to easily obtain state changes and relay them to the user interface.
class UserStateContainer_t
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

UserStateContainer_t( std::shared_ptr< engine::board::GameBoard_t > aGameBoard,
                      std::shared_ptr< std::unordered_map< engine::board::ResourceType_t, int > > aUserResources,
                      std::shared_ptr< std::vector< engine::board::BoardCellState_t > > aGeneratingLocations );

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::board::GameBoard_t > mGameBoard;
std::shared_ptr< std::unordered_map< engine::board::ResourceType_t, int > > mUserResources;
std::shared_ptr< std::vector< engine::board::BoardCellState_t > > mGeneratingLocations;

};

} // ENDOF ruleset
} // ENDOF engine