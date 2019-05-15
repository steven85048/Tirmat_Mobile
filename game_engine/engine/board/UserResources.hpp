#pragma once

#include "engine/board/Types.hpp"
#include "engine/ruleset/RuleDFA.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"

namespace engine
{

namespace board
{

class UserResources_t
{
// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

UserResources_t( std::shared_ptr< std::unordered_map< engine::board::ResourceType_t, int > > aResources );
    
// Assumes that ValidateResources() is called before this
void UpdateResources( std::unordered_map< engine::board::ResourceType_t, int >& aResources );

bool ValidateResources( std::unordered_map< engine::board::ResourceType_t, int >& aResources );

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< std::unordered_map< engine::board::ResourceType_t, int > > mResources;

};

} //END of board
} //END of engine