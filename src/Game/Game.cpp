#include "Game.h"

Game::Game() : gWindow(nullptr), gRenderer(nullptr), isRunning(false) {}

Game::~Game() {
    clean();
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void Game::update() {
    // Update game logic here (e.g., move paddles, update ball position)
}

void Game::render() {
    // Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Black color
    SDL_RenderClear(gRenderer);

    // Render game objects here (e.g., paddles, ball)

    // Update the screen
    SDL_RenderPresent(gRenderer);
}

void Game::clean() {
    // Destroy renderer
    if (gRenderer != nullptr) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = nullptr;
    }

    // Destroy window
    if (gWindow != nullptr) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    // Quit SDL subsystems
    SDL_Quit();
}
