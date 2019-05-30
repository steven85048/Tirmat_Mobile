#pragma once

#include "engine/state/GameActionInteractor.hpp"
#include "djinni/GameEngineFactoryIntf.hpp"
#include "engine/state/UserStateContainer.hpp"

namespace engine
{

namespace state
{

// Starting point for the game engine; initializes dependencies and
// provides/starts the communication channel with the UI
class GameEngineFactory_t : public djinni::GameEngineFactoryIntf
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

GameEngineFactory_t();

// --------------------------------------------------------
public: // GameInteractor OVERRIDES
// --------------------------------------------------------

// Adds another listener that can receive events from the engine
void AddEngineStateListener( const std::shared_ptr< djinni::GameStateListenerIntf > & aListener  ) override;

// Retrieve the object that can be used to interact with the engine
std::shared_ptr< djinni::GameInteractorIntf > GetGameInteractor() override;

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::state::UserStateContainer_t > mStateContainer;
std::shared_ptr< engine::state::GameActionInteractor_t > mGameActionInteractor;

};

}

}