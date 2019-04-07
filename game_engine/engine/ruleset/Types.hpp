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

struct DFANode_t {
    bool IsLevelCompletionNode;
    bool IsAcceptingNode;
    std::map< LanguageDirection_t, engine::board::ResourceType_t > Transition;
    std::vector< Point_t > Generating;
};

struct Point_t
{
    int xPos;
    int yPos;
    engine::board::ResourceType_t Resource;
};

struct Rule_t
{
    std::vector< Point_t > RulePoints;
    std::vector< Point_t > GeneratePoints;
};

} // ENDOF ruleset
} // ENDOF engine