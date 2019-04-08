#pragma once

#include <vector>
#include <map>
#include <memory>

#include "engine/board/Types.hpp"

namespace engine
{
namespace ruleset
{

// Technically, only use EAST and SOUTH but we can get more
// lines in Github with 4
enum class LanguageDirection_t {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct DFAPassResponse_t {
    DFAResponseType_t ResponseType = DFAResponseType_t::UNKNOWN;
    std::vector< engine::board::BoardCellState_t > GeneratingPoints;
};

enum class DFAResponseType_t {
    NOMATCH,
    GENERATING,
    LEVELCOMPLETION,
    UNKNOWN
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
    std::map< std::pair< LanguageDirection_t, engine::board::ResourceType_t >, std::unique_ptr< DFANode_t > > Transition;
    std::vector< engine::board::BoardCellState_t > Generating;
};

struct Rule_t{
    bool IsLevelCompletionRule = false;
    std::vector< engine::board::BoardCellState_t > RulePoints;
    std::vector< engine::board::BoardCellState_t > GeneratePoints;
};

} // ENDOF ruleset
} // ENDOF engine