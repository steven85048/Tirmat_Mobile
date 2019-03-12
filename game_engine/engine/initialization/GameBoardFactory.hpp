#pragma once
#include "engine/board/GameBoardIntf.hpp"

namespace engine
{

namespace initialization
{

class GameBoardFactory_t
{
    
public:

    GameBoardIntf_t InitializeBoardWithFile();

};

} // ENDOF initialization
} // ENDOF engine