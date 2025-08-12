#include "Game.h"
#include "../Collision/Collision.h"

Game::Game() : gWindow(nullptr), gRenderer(nullptr), isRunning(false) {
    ball = new Ball(400, 300, 20, 20); // Example position and size
    playerPaddle1 = new Paddle(50, 250, 10, 100); // Example position and size
    playerPaddle2 = new Paddle(750, 250, 10, 100);
    inputHandler = new InputHandler();
}

Game::~Game() {
    clean();
    delete ball;
    delete playerPaddle1;
    delete playerPaddle2;
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

    // Try loading the ball texture
    ball->loadBallTexture("./assets/images/ball.png", gRenderer);

    isRunning = true;
    return true;
}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();

        // Tiny tiny delay
        SDL_Delay(5);
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
    playerPaddle1->handleInput(inputHandler->getCurrentKeyStates(), SDL_SCANCODE_A, SDL_SCANCODE_Z);
    playerPaddle2->handleInput(inputHandler->getCurrentKeyStates(), SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
    ball->update(1.0f / 60.0f); // Assuming 60 FPS for simplicity

    // Handle collisions
    Collision::handleBallPaddleCollision(*ball, playerPaddle1->getRect());
    Collision::handleBallPaddleCollision(*ball, playerPaddle2->getRect());
    Collision::handleBallWallCollision(*ball, 600);
}

void Game::render() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Black color
    SDL_RenderClear(gRenderer);

    ball->render(gRenderer);
    playerPaddle1->render(gRenderer);
    playerPaddle2->render(gRenderer);

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
