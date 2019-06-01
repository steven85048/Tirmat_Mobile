#include "engine/initialization/GameBoardFactory.hpp"

#include <iostream>
#include <vector>

#include "djinni/ResourceType.hpp"
#include "djinni/BoardCellState.hpp"
#include "engine/board/GameBoard.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"
#include "engine/board/Types.hpp"
#include "engine/ruleset/RuleDFA.hpp"
#include "engine/ruleset/Types.hpp"
#include "engine/state/UserStateContainer.hpp"
#include "engine/move/MoveManager.hpp"
#include "engine/board/UserResources.hpp"
#include "engine/board/BoardElementsFactory.hpp"

engine::initialization::GameInteractorContainer engine::initialization::GameBoardFactory_t::InitializeDefault() {

    engine::initialization::GameInteractorContainer theInteractorContainer;

    // Shared state variables
    auto theBoard = std::make_shared< engine::board::GameBoard_t >( 7, 6 ); 
    auto theResourcesMap = std::make_shared< std::unordered_map< djinni::ResourceType, int > >();
    auto theGeneratingLocations = std::make_shared< std::vector< djinni::BoardCellState > >();

    // transfer ownership
    auto theGameStateContainer = std::make_shared< engine::state::UserStateContainer_t >( theBoard, theResourcesMap, theGeneratingLocations );
    theInteractorContainer.mStateContainer = theGameStateContainer;

    // shapeset manager init
    auto theShapeSetManager = std::make_unique< engine::shapeset::ShapeSetManager_t >( theBoard );

    // Rule DFA init
    auto theRuleDFA = std::make_unique< engine::ruleset::RuleDFA_t >( theGeneratingLocations );

    engine::ruleset::Rule_t theRule;

    auto point1 = engine::board::BoardElementsFactory_t::CreateCellState(0,0);
    point1->Resource = djinni::ResourceType::L1;

    auto point2 = engine::board::BoardElementsFactory_t::CreateCellState(1,0);
    point2->Resource = djinni::ResourceType::L2;

    auto point3 = engine::board::BoardElementsFactory_t::CreateCellState(1,1);
    point3->Resource = djinni::ResourceType::L3;

    theRule.RulePoints.push_back(point1);
    theRule.RulePoints.push_back(point2);

    theRule.GeneratePoints.push_back(point3);

    theRuleDFA->AddRuleToDFA( theRule );

    // User Resources init
    auto theUserResources = std::make_unique< engine::board::UserResources_t >( theResourcesMap );

    std::unordered_map< djinni::ResourceType, int > theResources;
    theResources[ djinni::ResourceType::L1 ] = 5;
    theResources[ djinni::ResourceType::L2 ] = 5;

    theUserResources->UpdateResources(theResources);

    // Move Manager init
    auto theMoveManager = std::make_shared< engine::move::MoveManager_t >( std::move( theRuleDFA ), std::move( theShapeSetManager ), std::move( theUserResources ) );
    theInteractorContainer.mMoveManager = theMoveManager;

    return theInteractorContainer;
}