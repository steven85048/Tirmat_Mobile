#pragma once

#include <memory>

#include "engine/board/Types.hpp"
#include "engine/board/UserResources.hpp"
#include "engine/ruleset/RuleDFA.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"

namespace engine
{

namespace move
{

// The brains of each move; tells the respective manageres to perform their operations
class MoveManager_t
{
// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

MoveManager_t(  std::unique_ptr< engine::ruleset::RuleDFA_t > aRuleDFA, 
                std::unique_ptr< engine::shapeset::ShapeSetManager_t > aShapeSetManager, 
                std::unique_ptr< engine::board::UserResources_t > aUserResources );

void ExecuteMoves( engine::board::GameBoardMoveBatch_t& aMoveBatch );

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

    std::unique_ptr< engine::ruleset::RuleDFA_t > mRuleDFA;
    std::unique_ptr< engine::shapeset::ShapeSetManager_t > mShapeSetManager;
    std::unique_ptr< engine::board::UserResources_t > mUserResources;
};

} // ENDOF move
} // ENDOF engine