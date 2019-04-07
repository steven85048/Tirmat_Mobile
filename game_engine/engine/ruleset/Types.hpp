#pragma once

#include <vector>
#include <map>

#include "engine/board/Types.hpp"

namespace engine
{
namespace ruleset
{

enum class LanguageDirection_t {
    EAST,
    SOUTH,
    WEST
};

struct LanguageInputCharacter_t {
    LanguageDirection_t Direction;
    engine::board::ResourceType_t Resource;
};

struct PointBounds {
    PointLocation_t LeftTopCorner;
    int recWidth;
    int recHeight;
};

struct DFANode_t {
    bool IsLevelCompletionNode = false;
    bool IsAcceptingNode = false;
    std::map< LanguageDirection_t, engine::board::ResourceType_t > Transition;
    std::vector< Point_t > Generating;
};

struct PointLocation_t {
    int xPos;
    int yPos;
};

struct Point_t{
    PointLocation_t Location;
    engine::board::ResourceType_t Resource;
};

struct Rule_t{
    bool IsLevelCompletionRule = false;
    std::vector< Point_t > RulePoints;
    std::vector< Point_t > GeneratePoints;
};

} // ENDOF ruleset
} // ENDOF engine