#include "djinni/ResourceType.hpp"
#include "engine/board/Types.hpp"
#include "engine/state/GameActionInteractor.hpp"

engine::state::GameActionInteractor_t::GameActionInteractor_t( std::shared_ptr< engine::move::MoveManager_t > aMoveManager,
                                                               std::shared_ptr< engine::state::UserStateContainer_t > aUserStateContainer)
:
mMoveManager( std::move( aMoveManager ) ),
mUserStateContainer( std::move( aUserStateContainer ) )
{
}

void engine::state::GameActionInteractor_t::AddObserver( const std::shared_ptr< djinni::GameStateListenerIntf >& aStateListener ) {
    mStateListener = aStateListener;
}

void engine::state::GameActionInteractor_t::AddResource(int32_t aIndexX, int32_t aIndexY, djinni::ResourceType aResourceType) {
    engine::board::GameBoardMoveBatch_t theMoveBatch;

    engine::board::GameBoardMove_t theMove( engine::board::MoveType_t::ADDRESOURCE, aIndexX, aIndexY, aResourceType );
    theMoveBatch.Moves.push_back( theMove );

    mMoveManager->ExecuteMoves( theMoveBatch );

    if( mStateListener != nullptr && mUserStateContainer != nullptr ) {
        mStateListener->GetState( mUserStateContainer->GetState() );
    }
}

void engine::state::GameActionInteractor_t::RemoveResource(int32_t aIndexX, int32_t aIndexY) {
    engine::board::GameBoardMoveBatch_t theMoveBatch;

    engine::board::GameBoardMove_t theMove( engine::board::MoveType_t::REMOVERESOURCE, aIndexX, aIndexY, std::nullopt );
    theMoveBatch.Moves.push_back( theMove );

    mMoveManager->ExecuteMoves( theMoveBatch );

    if( mStateListener != nullptr && mUserStateContainer != nullptr ) {
        mStateListener->GetState( mUserStateContainer->GetState() );
    }
}