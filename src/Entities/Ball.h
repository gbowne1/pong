#ifndef BALL_H
#define BALL_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Ball {
public:
    Ball(int startX, int startY, int width, int height);
    ~Ball();

    void loadBallTexture(const std::string& filename, SDL_Renderer* gRenderer);

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    void resetPosition(int x, int y);

    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }
    void setVelocity(float x, float y);
    SDL_Rect getRect() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    float velocityX;
    float velocityY;

    float positionX;
    float positionY;
};

#endif // BALL_H
