#include "Game.h"
#include <iostream>

int main(int argc, char *argv[])
{
    // Create the game object
    Game game;

    // Execute the game and check for errors
    int result = game.execute();
    if (result != 0) {
        std::cerr << "Game execution failed with error code: " << result << std::endl;
        return result;
    }

    return 0;
}
