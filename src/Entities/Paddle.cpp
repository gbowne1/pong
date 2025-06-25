#include "Paddle.h"

Paddle::Paddle(int x, int y, int width, int height) 
    : speed(5) // Set the speed of the paddle
{
    paddleRect.x = x;
    paddleRect.y = y;
    paddleRect.w = width;
    paddleRect.h = height;
}

Paddle::~Paddle() {
    // Cleanup if necessary
}

void Paddle::handleInput(const Uint8* keystates) {
    // Move the paddle based on input
    if (keystates[SDL_SCANCODE_UP] && paddleRect.y > 0) {
        paddleRect.y -= speed; // Move up
    }
    if (keystates[SDL_SCANCODE_DOWN] && paddleRect.y < 600 - paddleRect.h) {
        paddleRect.y += speed; // Move down
    }
}

void Paddle::update() {
    // Update paddle logic if needed (e.g., AI movement)
}

void Paddle::render(SDL_Renderer* renderer) {
    // Set paddle color (e.g., white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleRect); // Render the paddle
}

SDL_Rect Paddle::getRect() const {
    return paddleRect; // Return the paddle's rectangle
}
