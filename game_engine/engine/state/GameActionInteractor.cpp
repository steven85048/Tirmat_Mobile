#include "engine/state/GameActionInteractor.hpp"

engine::state::GameActionInteractor_t::GameActionInteractor_t( std::shared_ptr< engine::move::MoveManager_t > aMoveManager ) 
:
mMoveManager( std::move( aMoveManager ) )
{
}

void engine::state::GameActionInteractor_t::AddResource(int32_t aIndexX, int32_t aIndexY, djinni::ResourceType aResourceType) {

}

void engine::state::GameActionInteractor_t::RemoveResource(int32_t aIndexX, int32_t aIndexY) {

}