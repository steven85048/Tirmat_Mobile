#include <string>

#include "engine/board/Types.hpp"

namespace engine
{

namespace utilities
{

// enum classes are strongly typed, so we do this if we want a pretty print format
struct EnumStrings_t {
    static std::string ResourceToString( engine::board::ResourceType_t theType ) {
        switch( theType ) {
            case engine::board::ResourceType_t::EMPTY:
                return "0";
            case engine::board::ResourceType_t::IGNORE: 
                return "-1";
            case engine::board::ResourceType_t::L1: 
                return "1";
            case engine::board::ResourceType_t::L2: 
                return "2";
            case engine::board::ResourceType_t::L3: 
                return "3";
            case engine::board::ResourceType_t::L4: 
                return "4";
            case engine::board::ResourceType_t::L5: 
                return "5";
            case engine::board::ResourceType_t::L6: 
                return "6";   
        }

        return "UNKNOWN";
    }
};

} // ENDOF utilities
} // ENDOF engine