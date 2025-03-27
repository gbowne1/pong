#include "GameObjects.h"
#include <iostream>
#include <random>

// Constructor for Platform object
Platform::Platform(const int &x, const int &y, const int &w, const int &h) {
    _velocity.x = 0;
    _velocity.y = 0;
    setSpeed(7);
    _curX = x;
    _curY = y;
    _boundingBox.x = x;
    _boundingBox.y = y;
    _boundingBox.w = w;
    _boundingBox.h = h;
}

// Constructor for Ball object
Ball::Ball(const int &x, const int &y, const int &r) {
    setSpeed(8);
    _curX = x;
    _curY = y;
    _boundingBox.r = r;
    _boundingBox.x = x + r;
    _boundingBox.y = y + r;
}

// Sets a random y velocity going towards left or right.
void Ball::setRandomVelocity() {
    std::uniform_int_distribution<int> dist(0, 1);
    if (dist(_mt) == 1)
        _velocity.x = _speed;
    else
        _velocity.x = -_speed;

    std::uniform_int_distribution<int> dist2(-3, 3);
    _velocity.y = dist2(_mt);
}

// Renders the ball
void Ball::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0XFF, 0XFF);
    SDL_Rect newPos = {_curX, _curY, 15, 15};
    SDL_RenderCopy(renderer, _texture, NULL, &newPos);
}

// Renders the platform
void Platform::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0XFF, 0XFF);
    SDL_Rect newPos = {_curX, _curY, 13, 73};
    SDL_RenderCopy(renderer, _texture, NULL, &newPos);
}

// Moves the platform up
void Platform::moveUp() {
    setVelocity(Vect_2D{0, -_speed});
}

// Moves the platform down
void Platform::moveDown() {
    setVelocity(Vect_2D{0, _speed});
}

// Stops the platform
void Platform::stop() {
    setVelocity(Vect_2D{0, 0});
}

// Updates bounding box for Circle objects
template <>
void GameObjects<Circle>::updateBoundingBox() {
    _boundingBox.x = _curX + _boundingBox.r;
    _boundingBox.y = _curY + _boundingBox.r;
}

// Updates bounding box for SDL_Rect objects
template <>
void GameObjects<SDL_Rect>::updateBoundingBox() {
    _boundingBox.x = _curX;
    _boundingBox.y = _curY;
}
