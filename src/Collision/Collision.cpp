#include "Collision.h"

bool Collision::checkRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    return SDL_HasIntersection(&rectA, &rectB);
}

void Collision::handleBallPaddleCollision(SDL_Rect ballRect, float ballVelocityX, float ballVelocityY, const SDL_Rect paddleRect) {
    if (checkRectCollision(ballRect, paddleRect)) {
        // Reverse the ball's X velocity
        ballVelocityX = -ballVelocityX;

        // Adjust the ball's position to prevent it from sticking to the paddle
        if (ballRect.y < paddleRect.y) {
            ballRect.y = paddleRect.y - ballRect.h; // Ball is above the paddle
        } else {
            ballRect.y = paddleRect.y + paddleRect.h; // Ball is below the paddle
        }
    }
}

void Collision::handleBallWallCollision(SDL_Rect ballRect, float ballVelocityY, int screenHeight) {
    if (ballRect.y <= 0 || ballRect.y + ballRect.h >= screenHeight) {
        // Reverse the ball's Y velocity
        ballVelocityY = -ballVelocityY;

        // Adjust the ball's position to prevent it from sticking to the wall
        if (ballRect.y <= 0) {
            ballRect.y = 0; // Ball is at the top
        } else {
            ballRect.y = screenHeight - ballRect.h; // Ball is at the bottom
        }
    }
}
