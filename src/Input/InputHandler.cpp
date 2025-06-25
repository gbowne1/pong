#include "InputHandler.h"

InputHandler::InputHandler() {
    currentKeyStates = SDL_GetKeyboardState(nullptr);
    std::fill(std::begin(previousKeyStates), std::end(previousKeyStates), 0);
}

InputHandler::~InputHandler() {
    // No dynamic memory to clean up
}

void InputHandler::update() {
    // Store the current key states as previous key states
    std::copy(currentKeyStates, currentKeyStates + SDL_NUM_SCANCODES, previousKeyStates);
    currentKeyStates = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::isKeyPressed(SDL_Scancode key) {
    return currentKeyStates[key] == 1 && previousKeyStates[key] == 0;
}

bool InputHandler::isKeyReleased(SDL_Scancode key) {
    return currentKeyStates[key] == 0 && previousKeyStates[key] == 1;
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    return currentKeyStates[key] == 1;
}

void InputHandler::reset() {
    // Reset the previous key states
    std::fill(std::begin(previousKeyStates), std::end(previousKeyStates), 0);
}
