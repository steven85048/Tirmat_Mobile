#include <map>
#include <memory>

#include "engine/board/Types.hpp"
#include "engine/ruleset/Types.hpp"

namespace engine
{
namespace ruleset
{

class RuleDFA_t
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

RuleDFA_t();

// Note that DFA generation rules must have a LeftTop coordinate of (0,0)
// This is important for the generating points to work correctly
void AddRuleToDFA( const engine::ruleset::Rule_t& aRule );

// Passes the input points through the DFA and outputs whether or not the shape matches successfully
engine::ruleset::DFAPassResponse_t PassShapeThroughDFA( const std::vector< engine::board::BoardCellState_t >& aRulePoints );

// Reset the DFA state
void Reset();

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

// Generate the input string from the points;
// It traverses the point space in a zig-zag format
std::vector< engine::ruleset::LanguageInputCharacter_t > ConvertPointsToLanguage( const std::vector< engine::board::BoardCellState_t >& aRulePoints );

// Obtains the bounds of a set of points; used to create the input string
engine::ruleset::PointBounds_t GetBoundsFromPoints( const std::vector< engine::board::BoardCellState_t >& aRulePoints );


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::unique_ptr< engine::ruleset::DFANode_t > mDFAStartNode;

};

} // ENDOF ruleset
} // ENDOF engine