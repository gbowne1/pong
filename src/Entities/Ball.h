#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include <SDL_image.h>

class Ball {
public:
    Ball(int startX, int startY, int width, int height);
    ~Ball();

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void resetPosition(int x, int y);
    
    void setVelocity(float x, float y);
    SDL_Rect getRect() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    float velocityX;
    float velocityY;
};

#endif // BALL_H
