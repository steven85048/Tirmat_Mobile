#include "engine/board/Types.hpp"
#include "engine/state/GameActionInteractor.hpp"

engine::state::GameActionInteractor_t::GameActionInteractor_t( std::shared_ptr< engine::move::MoveManager_t > aMoveManager ) 
:
mMoveManager( std::move( aMoveManager ) )
{
}

void engine::state::GameActionInteractor_t::AddResource(int32_t aIndexX, int32_t aIndexY, djinni::ResourceType aResourceType) {
    engine::board::GameBoardMoveBatch_t theMoveBatch;

    engine::board::GameBoardMove_t theMove( engine::board::MoveType_t::ADDRESOURCE, aIndexX, aIndexY, engine::board::ResourceType_t::L1 );
    theMoveBatch.Moves.push_back( theMove );

    mMoveManager->ExecuteMoves( theMoveBatch );
}

void engine::state::GameActionInteractor_t::RemoveResource(int32_t aIndexX, int32_t aIndexY) {
    engine::board::GameBoardMoveBatch_t theMoveBatch;

    engine::board::GameBoardMove_t theMove( engine::board::MoveType_t::REMOVERESOURCE, aIndexX, aIndexY, std::nullopt );
    theMoveBatch.Moves.push_back( theMove );

    mMoveManager->ExecuteMoves( theMoveBatch );
}