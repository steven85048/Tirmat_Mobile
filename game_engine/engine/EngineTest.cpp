#include <iostream>
#include <vector>

#include "engine/initialization/GameBoardFactory.hpp"

// Testing suite for shapeset functionality

int main()
{
    engine::initialization::GameBoardFactory_t theFactory;
    theFactory.InitializeForTesting();

    return 0;
}
