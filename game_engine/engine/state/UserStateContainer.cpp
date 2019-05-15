#include "engine/state/UserStateContainer.hpp"

engine::state::UserStateContainer_t::UserStateContainer_t( std::shared_ptr< engine::board::GameBoard_t > aGameBoard,
                                                           std::shared_ptr< std::unordered_map< engine::board::ResourceType_t, int > > aUserResources,
                                                           std::shared_ptr< std::vector< engine::board::BoardCellState_t > > aGeneratingLocations )
:
mGameBoard( std::move(aGameBoard) ),
mUserResources( std::move(aUserResources) ),
mGeneratingLocations( std::move(aGeneratingLocations) )
{
}