#include <memory>

#include "djinni/ResourceType.hpp"
#include "djinni/PointLocation.hpp"
#include "djinni/BoardCellState.hpp"

namespace engine
{

namespace board
{

struct BoardElementsFactory_t {

// Djinni records do not allow constructors, so we move it to a static create
static std::shared_ptr< djinni::BoardCellState > CreateCellState( int aIndexX, int aIndexY ) {

    djinni::PointLocation theLocation( aIndexX, aIndexY );
    auto theCellState = std::make_shared< djinni::BoardCellState >( theLocation, djinni::ResourceType::EMPTY, false );

    return theCellState;
}

};

}
}