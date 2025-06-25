#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

class Collision {
public:
    static bool checkRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static void handleBallPaddleCollision(SDL_Rect& ballRect, float& ballVelocityX, float& ballVelocityY, const SDL_Rect& paddleRect);
    static void handleBallWallCollision(SDL_Rect& ballRect, float& ballVelocityY, int screenHeight);
};

#endif // COLLISION_H
