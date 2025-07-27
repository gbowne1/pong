#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    void update();
    bool isKeyPressed(SDL_Scancode key);
    bool isKeyReleased(SDL_Scancode key);
    bool isKeyDown(SDL_Scancode key);
    void reset();

    const Uint8* getCurrentKeyStates() const;

private:
    const Uint8* currentKeyStates;
    Uint8 previousKeyStates[SDL_NUM_SCANCODES];
};

#endif // INPUTHANDLER_H
