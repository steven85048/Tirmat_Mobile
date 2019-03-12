namespace engine
{

namespace board
{

class GameBoardInteractorIntf_t
{
    virtual void UpdateCell( int aXPosition, int aYPosition, int aToColor ) = 0;

    virtual void ConsumeGenerate() = 0;

    virtual bool IsGenerateAvailable() = 0;
};

} // ENDOF board
} // ENDOF engine