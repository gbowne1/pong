#include "Ball.h"
#include "TextureManager.h"

Ball::Ball(int startX, int startY, int width, int height)
    : velocityX(100.0f), velocityY(100.0f) // Set initial velocity
{
    positionX = startX;
    positionY = startY;
    rect.w = width;
    rect.h = height;
}

Ball::~Ball() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Ball::loadBallTexture(const std::string& filename, SDL_Renderer* gRenderer) {
    // Destroy old texture if already loaded
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    texture = TextureManager::loadTexture(filename, gRenderer);
    if (!texture) {
        SDL_Log("Failed to load ball texture from %s: %s", filename.c_str(), SDL_GetError());
    }
}

void Ball::update(float deltaTime) {
    // Update the ball's position based on its velocity
    positionX += velocityX * deltaTime;
    positionY += velocityY * deltaTime;
    rect.x = static_cast<int>(positionX);
    rect.y = static_cast<int>(positionY);
}

void Ball::render(SDL_Renderer* renderer) {
    // Render the ball texture
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Ball::resetPosition(int x, int y) {
    positionX = x;
    positionY = y;
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
