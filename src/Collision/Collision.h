#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include "../Entities/Ball.h"

class Collision {
public:
    static bool checkRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static void handleBallPaddleCollision(Ball& ball, const SDL_Rect paddleRect);
    static void handleBallWallCollision(Ball& ball, int screenHeight);
};

#endif // COLLISION_H
