#include "engine/state/UserStateContainer.hpp"
#include "engine/utilities/Logging.hpp"

#include <iostream>

engine::state::UserStateContainer_t::UserStateContainer_t( std::shared_ptr< engine::board::GameBoard_t > aGameBoard,
                                                           std::shared_ptr< std::unordered_map< djinni::ResourceType, int > > aUserResources,
                                                           std::shared_ptr< std::vector< djinni::BoardCellState > > aGeneratingLocations )
:
mGameBoard( std::move(aGameBoard) ),
mUserResources( std::move(aUserResources) ),
mGeneratingLocations( std::move(aGeneratingLocations) )
{
}

void engine::state::UserStateContainer_t::PrintState() {

    mGameBoard->PrintBoard();
    std::cout << std::endl;

    for( auto theResourceItr = mUserResources->begin(); theResourceItr != mUserResources->end(); theResourceItr++ ) {
        std::cout << engine::utilities::EnumStrings_t::ResourceToString( theResourceItr->first ) << ": " << theResourceItr->second << " | ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}