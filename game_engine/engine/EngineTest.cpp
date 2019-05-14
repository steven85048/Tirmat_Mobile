#include <iostream>
#include <vector>

#include "engine/board/GameBoard.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"
#include "engine/board/Types.hpp"
#include "engine/ruleset/RuleDFA.hpp"
#include "engine/ruleset/Types.hpp"
#include "engine/MoveManager.hpp"
#include "engine/board/UserResources.hpp"

// Testing suite for shapeset functionality

int main()
{
    auto theBoard = std::make_shared< engine::board::GameBoard_t >( 5, 5 );    
    auto theShapeSetManager = std::make_unique< engine::shapeset::ShapeSetManager_t >( theBoard );
    auto theRuleDFA = std::make_unique< engine::ruleset::RuleDFA_t >();

    engine::ruleset::Rule_t theRule;

    auto point1 = std::make_shared< engine::board::BoardCellState_t >(0,0);
    point1->Resource = engine::board::ResourceType_t::L1;

    auto point2 = std::make_shared< engine::board::BoardCellState_t >(1,0);
    point2->Resource = engine::board::ResourceType_t::L2;

    theRule.RulePoints.push_back(point1);
    theRule.RulePoints.push_back(point2);

    theRuleDFA->AddRuleToDFA( theRule );

    auto theUserResources = std::make_unique< engine::board::UserResources_t >();
    auto theMoveManager = std::make_shared< engine::MoveManager_t >( std::move( theRuleDFA ), std::move( theShapeSetManager ), std::move( theUserResources ) );

    engine::board::GameBoardMoveBatch_t theMoveBatch();


    return 0;
}
