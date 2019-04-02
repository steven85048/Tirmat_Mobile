namespace engine
{

namespace board
{

class GameBoardIntf_t
{
    const std::vector< std::vector< ResourceType_t > > GetBoardState() const override;

    bool AddResource( ResourceTypes aResourceType, int xPosition, int yPosition) override;
    bool RemoveResource( ResourceTypes aResourceType, int xPosition, int yPosition) override;

    std::vector< std::vector < ResourceType_t > > UndoMove() override;
};

} // ENDOF board
} // ENDOF engine