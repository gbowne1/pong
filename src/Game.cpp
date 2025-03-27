#include "Game.h"
#include "CollisionDetection.h"

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Game::Game() {
    std::cout << "Game object initialized." << std::endl;

    _state = GameState::kMainMenu;
    _scoresVector = { 0, 0 };

    _ball = std::make_unique<Ball>(GAME_WIDTH / 2, GAME_HEIGHT / 2, 8);
    _leftPlatform = std::make_unique<Platform>(7, 150, 13, 73);
    _rightPlatform = std::make_unique<Platform>(580, 150, 13, 73);

    _running = true;
    _gameStarted = false;
    _frames = 0;
}

int Game::execute() {
    std::cout << "Launching game." << std::endl;

    if (!init()) {
        return -1;
    }

    SDL_Event e;
    std::cout << "Starting game..." << std::endl;
    while (_running) {
        while (SDL_PollEvent(&e)) {
            onEvents(&e);
        }
        gameLoop();
        render();
    }

    cleanUp();
    return 0;
}

void checkSDLInit(int result, const std::string& errorMsg) {
    if (result < 0) {
        throw std::runtime_error(errorMsg + " SDL_Error: " + SDL_GetError());
    }
}

bool Game::init() {
    std::cout << "Initializing game." << "\n" << std::flush;

    try {
        checkSDLInit(SDL_Init(SDL_INIT_EVERYTHING), "SDL couldn't initialize!");
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    _mainWindow = SDL_CreateWindow("Pong by Can", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);
    if (_mainWindow == nullptr) {
        return false;
    }

    _renderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        std::cout << "Renderer could not be created. SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "Failed to initialise SDL_ttf. SDL_ttf error: " << TTF_GetError() << "\n";
        return false;
    }

    if (!loadMedia()) {
        return false;
    }

    _timeAtLaunch = SDL_GetTicks();

    return true;
}

bool Game::loadMedia() {
    _ball->setTexture(loadTexture("Resources/ball.png"));
    _leftPlatform->setTexture(loadTexture("Resources/plank.bmp"));
    _rightPlatform->setTexture(loadTexture("Resources/plank2.bmp"));

    _fonts.push_back(TTF_OpenFont("Resources/ARLRDBD.TTF", 28));
    if (_fonts[0] == nullptr) {
        std::cout << "Failed to load 28 ARIAL ROUNDED font. SDL_ttf error: " << TTF_GetError() << "\n";
        return false;
    }

    _fonts.push_back(TTF_OpenFont("Resources/ARLRDBD.TTF", 14));
    if (_fonts[1] == nullptr) {
        std::cout << "Failed to load 14 ARIAL ROUNDED font. SDL_ttf error: " << TTF_GetError() << "\n";
        return false;
    }

    return true;
}

SDL_Texture* Game::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font) {
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cout << "Unable to render text surface. SDL_ttf error: " << TTF_GetError() << "\n";
    } else {
        newTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from rendered text. SDL_ttf error: " << TTF_GetError() << "\n";
        }
        SDL_FreeSurface(textSurface);
    }
    return newTexture;
}

SDL_Texture* Game::loadTexture(std::string path) {
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path << ". SDL_image error: " << IMG_GetError() << "\n";
    } else {
        newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << path << ". SDL Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Game::handleKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP: _rightPlatform->moveUp(); break;
        case SDLK_DOWN: _rightPlatform->moveDown(); break;
        case SDLK_w: _leftPlatform->moveUp(); break;
        case SDLK_s: _leftPlatform->moveDown(); break;
        case SDLK_SPACE:
            if (_state == GameState::kScoreScreen || _state == GameState::kMainMenu) _state = GameState::kPreStart;
            break;
        default: break;
    }
}

void Game::handleKeyRelease(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP: _rightPlatform->stop(); break;
        case SDLK_DOWN: _rightPlatform->stop(); break;
        case SDLK_w: _leftPlatform->stop(); break;
        case SDLK_s: _leftPlatform->stop(); break;
        default: break;
    }
}

void Game::onEvents(SDL_Event* event) {
    if (event->type == SDL_QUIT) {
        _running = false;
    } else if (event->type == SDL_KEYDOWN) {
        handleKeyPress(event->key.keysym.sym);
    } else if (event->type == SDL_KEYUP) {
        handleKeyRelease(event->key.keysym.sym);
    }
}

void bounceBall(int x, int y, Platform* platform, Ball* ball) {
    int platformLeft = platform->boundingBox().x;
    int platformRight = platform->boundingBox().x + platform->boundingBox().w;
    int platformTop = platform->boundingBox().y;
    int platformBottom = platform->boundingBox().y + platform->boundingBox().h;

    int rectCenterX = (platformLeft + platformRight) / 2;
    int rectCenterY = (platformBottom + platformTop) / 2;

    int newX = ball->curX() - ball->velocity().x;
    int newY = ball->curY() - ball->velocity().y;

    ball->curX(newX);
    ball->curY(newY);

    int diffX = x - rectCenterX;
    int diffY = y - rectCenterY;
    int y_magnitude = abs(diffY / diffX);

    int y_dir_ball = ball->velocity().y < 0 ? -1 : 1;
    int direction_multiplierY = 1;

    if (y - ball->velocity().y >= platformBottom || y - ball->velocity().y <= platformTop) {
        direction_multiplierY = -1;
    }

    int yVel = y_magnitude * y_dir_ball * direction_multiplierY;
    int xVel = ball->velocity().x * -1;

    ball->setVelocity({ xVel, yVel });
}

void Game::checkAndReactToPlatformCollisions() {
    if (_leftPlatform->curY() < 0) {
        _leftPlatform->curY(0);
        _leftPlatform->stop();
    }
    if ((_leftPlatform->curY() + _leftPlatform->boundingBox().h) > (GAME_HEIGHT)) {
        _leftPlatform->curY(GAME_HEIGHT - _leftPlatform->boundingBox().h);
        _leftPlatform->stop();
    }

    if (_rightPlatform->curY() < 0) {
        _rightPlatform->curY(0);
        _rightPlatform->stop();
    }
    if ((_rightPlatform->curY() + _rightPlatform->boundingBox().h) > (GAME_HEIGHT)) {
        _rightPlatform->curY(GAME_HEIGHT - _rightPlatform->boundingBox().h);
        _rightPlatform->stop();
    }
}

void Game::checkAndReactToBallCollisions(int& winner) {
    winner = -1;

    int ballDiameter = 2 * _ball->boundingBox().r;

    if (_ball->curX() < 0) {
        winner = 1;
    } else if (_ball->curX() > GAME_WIDTH - ballDiameter) {
        winner = 0;
    } else if (_ball->curY() < 0) {
        int yVel = _ball->velocity().y;
        int xVel = _ball->velocity().x;

        _ball->setVelocity({ xVel, -yVel });
        _ball->curY(0);
    } else if (_ball->curY() > GAME_HEIGHT - ballDiameter) {
        int yVel = _ball->velocity().y;
        int xVel = _ball->velocity().x;

        _ball->setVelocity({ xVel, -yVel });
        _ball->curY(GAME_HEIGHT - ballDiameter);
    }

    int x = -1;
    int y = -1;
    CollisionDetection::detectCollision(_ball->boundingBox(), _leftPlatform->boundingBox(), x, y);
    if (x != -1 && y != -1) {
        bounceBall(x, y, _leftPlatform.get(), _ball.get());
    }

    CollisionDetection::detectCollision(_ball->boundingBox(), _rightPlatform->boundingBox(), x, y);
    if (x != -1 && y != -1) {
        bounceBall(x, y, _rightPlatform.get(), _ball.get());
    }
}

void Game::gameLoop() {
    int winner = -1;

    switch (_state) {
        case GameState::kMainMenu:
            _scoresVector = { 0, 0 };
            _leftPlatform->move();
            _rightPlatform->move();
            checkAndReactToPlatformCollisions();
            break;

        case GameState::kPreStart:
            _gameStarted = false;
            _ball->setVelocity({ 0, 0 });
            _ball->curX(GAME_WIDTH / 2);
            _ball->curY(GAME_HEIGHT / 2);
            _threadSafeTimer.start(std::chrono::milliseconds(1500));
            _state = GameState::kStart;
            break;

        case GameState::kStart:
            if (_threadSafeTimer.isCompleted() && !_gameStarted) {
                _ball->setRandomVelocity();
                _gameStarted = true;
            }

            _leftPlatform->move();
            _rightPlatform->move();
            checkAndReactToPlatformCollisions();
            _ball->move();
            checkAndReactToBallCollisions(winner);

            if (winner != -1) {
                _scoresVector[winner]++;
                _state = GameState::kScoreScreen;
            }
            break;

        case GameState::kScoreScreen:
            break;
    }
}

void Game::updateScoreTextTure() {
    std::ostringstream oss;
    oss << "Score: " << std::setw(5) << std::right << _scoresVector[0] << " - " << _scoresVector[1];
    SDL_Color white = { 255, 255, 255 };

    if (_scoresTexture != nullptr) {
        SDL_DestroyTexture(_scoresTexture);
    }
    _scoresTexture = loadFromRenderedText(oss.str().c_str(), white, _fonts[0]);

    if (_scoresTexture == nullptr) {
        std::cout << "Failed to change _scoresTexture texture \n";
    }
}

void Game::renderText(SDL_Texture* tt, int xpos, int ypos) {
    if (tt == nullptr) return;

    int w = 140;
    int h = 40;

    SDL_QueryTexture(tt, nullptr, nullptr, &w, &h);

    SDL_Rect newPos = { xpos, ypos, w, h };
    SDL_RenderCopy(_renderer, tt, nullptr, &newPos);
}

void print_FPS(uint32_t time_since_start, int frames) {
    int t = SDL_GetTicks();
    float fps = (static_cast<float>(frames) * 1000) / (t - time_since_start);
    std::cout << "Avg FPS: " << std::setprecision(2) << fps << "\n";
}

void Game::render() {
    SDL_Color white = { 255, 255, 255 };
    int t1 = SDL_GetTicks();
    int w = 0;
    int h = 0;

    SDL_RenderClear(_renderer);

    if (_state == GameState::kMainMenu) {
        _controlsTexture = loadFromRenderedText("W/S", white, _fonts[1]);
        renderText(_controlsTexture, 20, 20);

        _controlsTexture = loadFromRenderedText("UP/DOWN", white, _fonts[1]);
        SDL_QueryTexture(_controlsTexture, nullptr, nullptr, &w, nullptr);
        renderText(_controlsTexture, 580 - w, 20);

        _countdownTimer = loadFromRenderedText("Press SPACE to Start", white, _fonts[0]);
        SDL_QueryTexture(_countdownTimer, nullptr, nullptr, &w, nullptr);
        renderText(_countdownTimer, GAME_WIDTH / 2 - w / 2, 350);

        updateScoreTextTure();
    } else if (_state == GameState::kScoreScreen) {
        updateScoreTextTure();
        _countdownTimer = loadFromRenderedText("Press SPACE to re-match", white, _fonts[1]);
        SDL_QueryTexture(_countdownTimer, nullptr, nullptr, &w, nullptr);
        renderText(_countdownTimer, GAME_WIDTH / 2 - w / 2, 350);
    }

    _leftPlatform->render(_renderer);
    _rightPlatform->render(_renderer);
    _ball->render(_renderer);

    SDL_QueryTexture(_scoresTexture, nullptr, nullptr, &w, nullptr);
    renderText(_scoresTexture, GAME_WIDTH / 2 - w / 2, 20);

    SDL_SetRenderDrawColor(_renderer, 0x30, 0x30, 0x30, 0xFF);
    SDL_RenderPresent(_renderer);
    _frames++;

    int t2 = SDL_GetTicks() - t1;
    int ticks_per_frame = 1000 / 60;
    if (t2 < ticks_per_frame) {
        SDL_Delay(ticks_per_frame - t2);
    }
    print_FPS(_timeAtLaunch, _frames);
}

void Game::cleanUp() {
    std::cout << "End. Cleaning up..." << std::endl;

    for (auto& f : _fonts) {
        TTF_CloseFont(f);
        f = nullptr;
    }

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_mainWindow);

    _renderer = nullptr;
    _mainWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
