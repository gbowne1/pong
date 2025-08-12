#include "Collision.h"
#include <cmath>

bool Collision::checkRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    return SDL_HasIntersection(&rectA, &rectB);
}

void Collision::handleBallPaddleCollision(Ball& ball, const SDL_Rect paddleRect) {
    SDL_Rect ballRect = ball.getRect();

    if (checkRectCollision(ballRect, paddleRect)) {
        // Reverse X velocity to bounce the ball back
        ball.setVelocityX(-ball.getVelocityX());

        // Calculate relative position of hit on the paddle
        int paddleCenter = paddleRect.y + paddleRect.h / 2;
        int ballCenter = ballRect.y + ballRect.h / 2;
        int relativeIntersectY = paddleCenter - ballCenter;

        // Normalize to get a vertical speed modifier
        float normalized = static_cast<float>(relativeIntersectY) / (paddleRect.h / 2.0f);

        // Change Y velocity based on collision point
        // ball.setVelocityY(-normalized * std::abs(ball.getVelocityY()));
        ball.setVelocityY(-normalized * 120);

        /*
        // Adjust ball's position to prevent sticking
        if (ballRect.y < paddleRect.y) {
            ballRect.y = paddleRect.y - ballRect.h;
        } else {
            ballRect.y = paddleRect.y + paddleRect.h;
        }
        */
    }
}

void Collision::handleBallWallCollision(Ball& ball, int screenHeight) {
    SDL_Rect ballRect = ball.getRect();

    if (ballRect.y <= 0 || (ballRect.y + ballRect.h) >= screenHeight) {
        // Reverse the ball's Y velocity
        ball.setVelocityY(-ball.getVelocityY());

        /*
        // Adjust the ball's position to prevent it from sticking to the wall
        if (ballRect.y <= 0) {
            ballRect.y = 0; // Ball is at the top
        } else {
            ballRect.y = screenHeight - ballRect.h; // Ball is at the bottom
        }
        */
    }
}
