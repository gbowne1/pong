#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool isRunning;

    // Game objects (e.g., paddles, ball) can be added here
};

#endif // GAME_H
