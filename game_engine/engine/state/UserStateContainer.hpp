#pragma once

#include <memory>

#include "djinni/ResourceType.hpp"
#include "djinni/BoardCellState.hpp"
#include "engine/board/GameBoard.hpp"
#include "engine/board/Types.hpp"

namespace engine
{

namespace state
{

// This class has shared pointers to state variables of the game
// Can be used to easily obtain state changes and relay them to the user interface.
// It is important that this class can only READ from the state variables.
class UserStateContainer_t
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

UserStateContainer_t( std::shared_ptr< engine::board::GameBoard_t > aGameBoard,
                      std::shared_ptr< std::unordered_map< djinni::ResourceType, int > > aUserResources,
                      std::shared_ptr< std::vector< djinni::BoardCellState > > aGeneratingLocations );

void PrintState();

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< const engine::board::GameBoard_t > mGameBoard;
std::shared_ptr< const std::unordered_map< djinni::ResourceType, int > > mUserResources;
std::shared_ptr< const std::vector< djinni::BoardCellState > > mGeneratingLocations;

};

} // ENDOF ruleset
} // ENDOF engine