#include <SDL.h>          // Core SDL functionality
#include <SDL_image.h>   // For image loading and handling
#include <SDL_ttf.h>     // For text rendering with TrueType fonts

#include <iostream>      // For input/output stream
#include <vector>        // For using std::vector
#include <string>        // For using std::string
#include <memory>        // For smart pointers (std::unique_ptr)
#include <random>        // For random number generation
#include <chrono>        // For time-related functions
#include <mutex>         // For mutexes in thread safety
#include <future>        // For futures in asynchronous programming
#include <sstream>       // For string stream operations
#include <iomanip>       // For input/output manipulators

// Function prototypes
bool init();
void close();

// Window and renderer
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

// Main function
int main(int argc, char* args[]) {
    // Initialize SDL
    if (!init()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    // Main game loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Black color
        SDL_RenderClear(gRenderer);

        // Render game objects here (e.g., paddles, ball)

        // Update the screen
        SDL_RenderPresent(gRenderer);
    }

    // Clean up and close SDL
    close();
    return 0;
}

// Initialize SDL
bool init() {
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

    return true;
}

// Clean up and close SDL
void close() {
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
