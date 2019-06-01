#include <string>

#include "djinni/ResourceType.hpp"
#include "djinni/MoveResult.hpp"
#include "engine/board/Types.hpp"

namespace engine
{

namespace utilities
{

// enum classes are strongly typed, so we do this if we want a pretty print format
struct EnumStrings_t {
    static std::string ResourceToString( djinni::ResourceType theType ) {
        switch( theType ) {
            case djinni::ResourceType::EMPTY:
                return "0";
            case djinni::ResourceType::IGNORE: 
                return "-1";
            case djinni::ResourceType::L1: 
                return "1";
            case djinni::ResourceType::L2: 
                return "2";
            case djinni::ResourceType::L3: 
                return "3";
            case djinni::ResourceType::L4: 
                return "4";
            case djinni::ResourceType::L5: 
                return "5";
            case djinni::ResourceType::L6: 
                return "6"; 
            case djinni::ResourceType::L7:
                return "7";
            case djinni::ResourceType::REFUND:
                return "R";
            case djinni::ResourceType::GENERATING:
                return "G";
        }

        return "UNKNOWN";
    }

    static std::string MoveResultToString( djinni::MoveResult theResult ) {
        switch( theResult ) {
            case djinni::MoveResult::LOCKED:
                return "LOCKED";
            case djinni::MoveResult::OUTOFBOUNDS:
                return "OUTOFBOUNDS";
            case djinni::MoveResult::RESOURCEUNSET:
                return "RESOURCEUNSET";
            case djinni::MoveResult::SUCCESS:
                return "SUCCESS";
            case djinni::MoveResult::DELETEFROMEMPTY:
                return "DELETEFROMEMPTY";
            case djinni::MoveResult::MOVEUNCHECKED:
                return "MOVEUNCHECKED";
        }

        return "UNKNOWN";
    }
};

} // ENDOF utilities
} // ENDOF engine