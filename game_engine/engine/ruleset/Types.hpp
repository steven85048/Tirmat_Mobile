#pragma once

#include <vector>
#include <map>
#include <memory>

#include "djinni/PointLocation.hpp"
#include "djinni/ResourceType.hpp"
#include "djinni/BoardCellState.hpp"
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
    std::vector< std::shared_ptr< djinni::BoardCellState > > GeneratingPoints;
    djinni::PointLocation LeftTopCorner = djinni::PointLocation(0,0);
};

struct LanguageInputCharacter_t {
    LanguageDirection_t Direction;
    djinni::ResourceType Resource;
};

struct PointBounds_t {
    djinni::PointLocation LeftTopCorner = djinni::PointLocation(0,0);
    int recWidth;
    int recHeight;
};

struct DFANode_t {
    bool IsLevelCompletionNode = false;
    bool IsAcceptingNode = false;
    std::map< std::pair< LanguageDirection_t, djinni::ResourceType >, std::shared_ptr< DFANode_t > > Transition;
    std::vector< std::shared_ptr< djinni::BoardCellState > > Generating;
};

struct Rule_t{
    bool IsLevelCompletionRule = false;
    std::vector< std::shared_ptr< djinni::BoardCellState > > RulePoints;
    std::vector< std::shared_ptr< djinni::BoardCellState > > GeneratePoints;
};

} // ENDOF ruleset
} // ENDOF engine