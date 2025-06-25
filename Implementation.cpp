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

// SDL Initialization and Cleanup
SDL_Init();
SDL_WaitInit();
SDL_Quit();

// Creating Windows and Renderers
SDL_Window();
SDL_CreateWindow();
SDL_CreateRenderer();

// Event Handling
SDL_Event();
SDL_PollEvent();

// Rendering Functions
SDL_SetRenderDrawColor();
SDL_Renderer();
SDL_RenderClear();
SDL_RenderCopy();
SDL_RenderPresent();
SDL_RenderFillRect();

// Texture Loading
SDL_Texture();
IMG_Load();
SDL_CreateTexture();
SDL_CreateTextureFromSurface();
SDL_DestroyTexture();
SDL_QueryTexture();

// Font Rendering
TTF_Init();
TTF_OpenFont();
TTF_RenderText_Blended();
TTF_CloseFont();
TTF_Quit();

// Timing Functions
SDL_GetTicks();

// Error Handling
SDL_GetError();

SDL_Rect();
SDL_Color();
SDL_FreeSurface();
SDL_Surface();
SDL_BlitSurface();
SDL_Delay();
SDL_Flip();
SDL_GetMouseState();
SDL_GetKeyboardState();
SDL_GetTicks();
