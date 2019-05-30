#pragma once

#include "GameInteractor.hpp"

namespace engine
{

namespace state
{

// This class features the main talking point for the UI to interact
// with the engine
class GameActionInteractor_t : public engine::GameInteractor
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

    GameActionInteractor_t();

// --------------------------------------------------------
public: // GameInteractor OVERRIDES
// --------------------------------------------------------

    std::string Test() override;
};

}

}