#include "Game.h"
#include "../Collision/Collision.h"

Game::Game() : gWindow(nullptr), gRenderer(nullptr), isRunning(false) {
    ball = new Ball(400, 300, 20, 20); // Example position and size
    playerPaddle = new Paddle(50, 250, 10, 100); // Example position and size
    inputHandler = new InputHandler();
}

Game::~Game() {
    clean();
    delete ball;
    delete playerPaddle;
    delete inputHandler;
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

    ball->loadBallTexture("/assets/images/ball.png", gRenderer);

     // Try loading the ball texture
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
    inputHandler->update();
    playerPaddle->handleInput(inputHandler->getCurrentKeyStates());
    ball->update(1.0f / 60.0f); // Assuming 60 FPS for simplicity

    // Handle collisions
    Collision::handleBallPaddleCollision(ball->getRect(), ball->getVelocityX(), ball->getVelocityY(), playerPaddle->getRect());
    Collision::handleBallWallCollision(ball->getRect(), ball->getVelocityY(), 600);
}

void Game::render() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Black color
    SDL_RenderClear(gRenderer);

    ball->render(gRenderer);
    playerPaddle->render(gRenderer);

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
