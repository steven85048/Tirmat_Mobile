#include <map>
#include <memory>

#include "engine/board/Types.hpp";
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

// --------------------------------------------------------
private: // FUNCTIONS
// --------------------------------------------------------

void AddRuleToDFA( const engine::ruleset::Rule_t& aRule );
std::vector< engine::ruleset::LanguageInputCharacter_t > ConvertPointsToLanguage( const std::vector< engine::ruleset::Point_t >& aRulePoints );
engine::ruleset::PointBounds_t GetBoundsFromPoints( const std::vector< engine::ruleset::Point_t >& aRulePoints );


// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::unique_ptr< engine::ruleset::DFANode_t > mDFAStartNode;

};

} // ENDOF ruleset
} // ENDOF engine