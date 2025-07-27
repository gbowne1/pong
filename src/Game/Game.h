#include "../Entities/Ball.h"
#include "../Entities/Paddle.h"
#include "../Input/InputHandler.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool isRunning;

    Ball* ball; // Pointer to the ball
    Paddle* playerPaddle; // Pointer to the player's paddle
    InputHandler* inputHandler; // Input handler
};
