#pragma once

#include "djinni/GameInteractorIntf.hpp"
#include "djinni/ResourceType.hpp"
#include "engine/move/MoveManager.hpp"

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

GameActionInteractor_t( std::shared_ptr< engine::move::MoveManager_t > aMoveManager );

// --------------------------------------------------------
public: // GameInteractor OVERRIDES
// --------------------------------------------------------

void AddResource(int32_t aIndexX, int32_t aIndexY, djinni::ResourceType aResourceType) override;
void RemoveResource(int32_t aIndexX, int32_t aIndexY) override;

// --------------------------------------------------------
private: // DATA
// --------------------------------------------------------

std::shared_ptr< engine::move::MoveManager_t > mMoveManager;

};

} // ENDOF state

} // ENDOF engine