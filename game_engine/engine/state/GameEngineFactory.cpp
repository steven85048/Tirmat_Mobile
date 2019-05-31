#include "engine/initialization/GameBoardFactory.hpp"
#include "engine/state/GameEngineFactory.hpp"
#include "djinni/GameEngineFactoryIntf.hpp"

std::shared_ptr< djinni::GameEngineFactoryIntf > djinni::GameEngineFactoryIntf::Create() {
    return std::make_shared< engine::state::GameEngineFactory_t >();
}

engine::state::GameEngineFactory_t::GameEngineFactory_t() {
    
    engine::initialization::GameBoardFactory_t theInitializationFactory;
    auto theInitializedEngine = theInitializationFactory.InitializeDefault();

    mStateContainer = std::move( theInitializedEngine.mStateContainer );
    mGameActionInteractor = std::make_shared< engine::state::GameActionInteractor_t >( std::move( theInitializedEngine.mMoveManager ) );

}

// Adds another listener that can receive events from the engine
void engine::state::GameEngineFactory_t::AddEngineStateListener( const std::shared_ptr< djinni::GameStateListenerIntf > & aListener  ) {
    
}

// Retrieve the object that can be used to interact with the engine
std::shared_ptr< djinni::GameInteractorIntf > engine::state::GameEngineFactory_t::GetGameInteractor() {
    return mGameActionInteractor;
}