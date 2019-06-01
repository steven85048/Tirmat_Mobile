#pragma once

#include "djinni/ResourceType.hpp"
#include "engine/board/Types.hpp"
#include "engine/ruleset/RuleDFA.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"

namespace engine
{

namespace board
{

// Handles the validation and update of user resources; contains the shared
// resource state
class UserResources_t
{
// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

UserResources_t( std::shared_ptr< std::unordered_map< djinni::ResourceType, int > > aResources );
    
// Assumes that ValidateResources() is called before this
void UpdateResources( std::unordered_map< djinni::ResourceType, int >& aResources );

bool ValidateResources( std::unordered_map< djinni::ResourceType, int >& aResources );

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< std::unordered_map< djinni::ResourceType, int > > mResources;

};

} //END of board
} //END of engine