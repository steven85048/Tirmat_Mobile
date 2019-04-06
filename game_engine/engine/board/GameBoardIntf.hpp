#include <vector>

#include "engine/board/Types.hpp"

namespace engine
{

namespace board
{

class GameBoardIntf_t
{
    const std::vector< std::vector< ResourceType_t > > GetBoardState() const;

    bool AddResource( engine::board::ResourceType_t aResourceType, int xPosition, int yPosition);
    bool RemoveResource( engine::board::ResourceType_t aResourceType, int xPosition, int yPosition);

    std::vector< std::vector < ResourceType_t > > UndoMove();
};

} // ENDOF board
} // ENDOF engine