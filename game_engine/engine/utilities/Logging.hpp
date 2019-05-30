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
            case engine::board::ResourceType_t::REFUND:
                return "R";
            case engine::board::ResourceType_t::GENERATING:
                return "G";
        }

        return "UNKNOWN";
    }

    static std::string MoveResultToString( engine::board::MoveResult_t theResult ) {
        switch( theResult ) {
            case engine::board::MoveResult_t::LOCKED:
                return "LOCKED";
            case engine::board::MoveResult_t::OUTOFBOUNDS:
                return "OUTOFBOUNDS";
            case engine::board::MoveResult_t::RESOURCEUNSET:
                return "RESOURCEUNSET";
            case engine::board::MoveResult_t::SUCCESS:
                return "SUCCESS";
            case engine::board::MoveResult_t::DELETEFROMEMPTY:
                return "DELETEFROMEMPTY";
            case engine::board::MoveResult_t::MOVEUNCHECKED:
                return "MOVEUNCHECKED";
        }

        return "UNKNOWN";
    }
};

} // ENDOF utilities
} // ENDOF engine