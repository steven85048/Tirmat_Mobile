#include "engine/initialization/GameBoardFactory.hpp"

#include <iostream>
#include <vector>

#include "engine/board/GameBoard.hpp"
#include "engine/shapeset/ShapeSetManager.hpp"
#include "engine/board/Types.hpp"
#include "engine/ruleset/RuleDFA.hpp"
#include "engine/ruleset/Types.hpp"
#include "engine/state/UserStateContainer.hpp"
#include "engine/move/MoveManager.hpp"
#include "engine/board/UserResources.hpp"

void engine::initialization::GameBoardFactory_t::InitializeForTesting() {

    // Shared state variables
    auto theBoard = std::make_shared< engine::board::GameBoard_t >( 5, 5 ); 
    auto theResourcesMap = std::make_shared< std::unordered_map< engine::board::ResourceType_t, int > >();
    auto theGeneratingLocations = std::make_shared< std::vector< engine::board::BoardCellState_t > >();

    // transfer ownership
    auto theGameStateContainer = engine::state::UserStateContainer_t( theBoard, theResourcesMap, theGeneratingLocations );

    // shapeset manager init
    auto theShapeSetManager = std::make_unique< engine::shapeset::ShapeSetManager_t >( theBoard );

    // Rule DFA init
    auto theRuleDFA = std::make_unique< engine::ruleset::RuleDFA_t >( theGeneratingLocations );

    engine::ruleset::Rule_t theRule;

    auto point1 = std::make_shared< engine::board::BoardCellState_t >(0,0);
    point1->Resource = engine::board::ResourceType_t::L1;

    auto point2 = std::make_shared< engine::board::BoardCellState_t >(1,0);
    point2->Resource = engine::board::ResourceType_t::L2;

    auto point3 = std::make_shared< engine::board::BoardCellState_t >(1,1);
    point3->Resource = engine::board::ResourceType_t::L3;

    theRule.RulePoints.push_back(point1);
    theRule.RulePoints.push_back(point2);

    theRule.GeneratePoints.push_back(point3);

    theRuleDFA->AddRuleToDFA( theRule );

    // User Resources init
    auto theUserResources = std::make_unique< engine::board::UserResources_t >( theResourcesMap );

    std::unordered_map< engine::board::ResourceType_t, int > theResources;
    theResources[ engine::board::ResourceType_t::L1 ] = 5;
    theResources[ engine::board::ResourceType_t::L2 ] = 5;

    theUserResources->UpdateResources(theResources);

    // Move Manager init
    auto theMoveManager = std::make_shared< engine::move::MoveManager_t >( std::move( theRuleDFA ), std::move( theShapeSetManager ), std::move( theUserResources ) );

    engine::board::GameBoardMoveBatch_t theMoveBatch;

    engine::board::GameBoardMove_t move1(engine::board::MoveType_t::ADDRESOURCE, 3,3, engine::board::ResourceType_t::L1);
    engine::board::GameBoardMove_t move2(engine::board::MoveType_t::ADDRESOURCE, 4,3, engine::board::ResourceType_t::L2);

    theMoveBatch.Moves.push_back(move1);
    theMoveBatch.Moves.push_back(move2);

    theGameStateContainer.PrintState();

    theMoveManager->ExecuteMoves( theMoveBatch );
    theGameStateContainer.PrintState();

    engine::board::GameBoardMoveBatch_t theMoveBatchGenerate;
    theMoveBatchGenerate.IsGenerating = true;
    theMoveManager->ExecuteMoves( theMoveBatchGenerate );
    theGameStateContainer.PrintState();

    theMoveManager->PopUndoMoves();
    theGameStateContainer.PrintState();

    theMoveManager->PopUndoMoves();
    theGameStateContainer.PrintState();
}