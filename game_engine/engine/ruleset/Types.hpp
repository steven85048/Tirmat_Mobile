#pragma once

#include <vector>
#include <map>
#include <memory>

#include "engine/board/Types.hpp"

namespace engine
{
namespace ruleset
{

enum class LanguageDirection_t {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum class DFAResponseType_t {
    NOMATCH,
    GENERATING,
    LEVELCOMPLETION,
    UNKNOWN
};

struct DFAPassResponse_t {
    DFAResponseType_t ResponseType = DFAResponseType_t::UNKNOWN;

    // Generating points are relative to the LCornerX/Y
    std::vector< std::shared_ptr< engine::board::BoardCellState_t > > GeneratingPoints;
    engine::board::PointLocation_t LeftTopCorner;
};

struct LanguageInputCharacter_t {
    LanguageDirection_t Direction;
    engine::board::ResourceType_t Resource;
};

struct PointBounds_t {
    engine::board::PointLocation_t LeftTopCorner;
    int recWidth;
    int recHeight;
};

struct DFANode_t {
    bool IsLevelCompletionNode = false;
    bool IsAcceptingNode = false;
    std::map< std::pair< LanguageDirection_t, engine::board::ResourceType_t >, std::shared_ptr< DFANode_t > > Transition;
    std::vector< std::shared_ptr< engine::board::BoardCellState_t > > Generating;
};

struct Rule_t{
    bool IsLevelCompletionRule = false;
    std::vector< std::shared_ptr< engine::board::BoardCellState_t > > RulePoints;
    std::vector< std::shared_ptr< engine::board::BoardCellState_t > > GeneratePoints;
};

} // ENDOF ruleset
} // ENDOF engine