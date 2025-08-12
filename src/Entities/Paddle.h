#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Paddle {
public:
    Paddle(int x, int y, int width, int height);
    ~Paddle();

    void handleInput(const Uint8* keystates, SDL_Scancode up, SDL_Scancode down);
    void update();
    void render(SDL_Renderer* renderer);

    SDL_Rect getRect() const;

private:
    SDL_Rect paddleRect;
    int speed;
};

#endif // PADDLE_H
