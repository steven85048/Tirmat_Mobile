#include <iostream>

#include "engine/board/UserResources.hpp"

engine::board::UserResources_t::UserResources_t( std::shared_ptr< std::unordered_map< djinni::ResourceType, int > > aResources )
:
mResources( std::move( aResources ) )
{
}
    
void engine::board::UserResources_t::UpdateResources( std::unordered_map< djinni::ResourceType, int >& aResources ) {
    if( !mResources ) {
        return;
    }
    
    for( auto theResourceIterator : aResources ) {
        auto theUseResourceType = theResourceIterator.first;
        auto theUseResourceCount = theResourceIterator.second;

        (*mResources)[theUseResourceType] += theUseResourceCount;
    }
}

bool engine::board::UserResources_t::ValidateResources( std::unordered_map< djinni::ResourceType, int >& aResources ) {
    
    if( !mResources ) {
        return false;
    }
    
    for( auto theResourceIterator : aResources ) {
        auto theUseResourceType = theResourceIterator.first;
        auto theUseResourceCount = theResourceIterator.second;

        if( theUseResourceCount == 0 ) {
            continue;
        }

        // If we don't have any of the resource, then invalid
        if( mResources->find( theUseResourceType ) == mResources->end() ) {
            return false;
        }

        // If the amount of resource we have is less than what we need
        auto theHaveResourceCount = (*mResources)[theUseResourceType];

        if( theHaveResourceCount + theUseResourceCount < 0 ) {
            return false;
        }
    }

    return true;
}