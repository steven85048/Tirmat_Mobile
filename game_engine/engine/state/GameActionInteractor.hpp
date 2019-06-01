#pragma once

#include "djinni/GameInteractorIntf.hpp"
#include "djinni/GameStateListenerIntf.hpp"
#include "djinni/ResourceType.hpp"
#include "engine/move/MoveManager.hpp"
#include "engine/state/UserStateContainer.hpp"

namespace engine
{

namespace state
{

// This class features the main talking point for the UI to interact
// with the engine
class GameActionInteractor_t : public djinni::GameInteractorIntf
{

// --------------------------------------------------------
public: // FUNCTIONS
// --------------------------------------------------------

GameActionInteractor_t( std::shared_ptr< engine::move::MoveManager_t > aMoveManager, 
                        std::shared_ptr< engine::state::UserStateContainer_t > aUserStateContainer );

void AddObserver( const std::shared_ptr< djinni::GameStateListenerIntf >& aStateListener );

// --------------------------------------------------------
public: // GameInteractor OVERRIDES
// --------------------------------------------------------

void AddResource(int32_t aIndexX, int32_t aIndexY, djinni::ResourceType aResourceType) override;
void RemoveResource(int32_t aIndexX, int32_t aIndexY) override;

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::move::MoveManager_t > mMoveManager;
std::shared_ptr< engine::state::UserStateContainer_t > mUserStateContainer;
std::shared_ptr< djinni::GameStateListenerIntf > mStateListener;
 

};

} // ENDOF state

} // ENDOF engine