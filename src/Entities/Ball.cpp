#include "Ball.h"
#include "TextureManager.h" // Assuming you have a TextureManager for loading textures

Ball::Ball(int startX, int startY, int width, int height)
    : velocityX(300.0f), velocityY(300.0f) // Set initial velocity
{
    rect.x = startX;
    rect.y = startY;
    rect.w = width;
    rect.h = height;

    // Load the ball texture (make sure to adjust the path as necessary)
    texture = TextureManager::loadTexture("assets/images/ball.png");
}

Ball::~Ball() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Ball::update(float deltaTime) {
    // Update the ball's position based on its velocity
    rect.x += static_cast<int>(velocityX * deltaTime);
    rect.y += static_cast<int>(velocityY * deltaTime);
}

void Ball::render(SDL_Renderer* renderer) {
    // Render the ball texture
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Ball::resetPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Ball::setVelocity(float x, float y) {
    velocityX = x;
    velocityY = y;
}

SDL_Rect Ball::getRect() const {
    return rect;
}
