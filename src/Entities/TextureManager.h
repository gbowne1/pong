#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    // Load a texture from a file
    static SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer);

    // Free a texture
    static void freeTexture(const std::string& textureID);

    // Get a texture by ID
    static SDL_Texture* getTexture(const std::string& textureID);

private:
    // Store textures in a map
    static std::unordered_map<std::string, SDL_Texture*> textureMap;
};

#endif // TEXTUREMANAGER_H
