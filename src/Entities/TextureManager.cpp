#include "TextureManager.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> TextureManager::textureMap;

SDL_Texture* TextureManager::loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
    // Load the texture from the specified file
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, filePath.c_str());
    if (newTexture == nullptr) {
        std::cerr << "Failed to load texture: " << filePath << " SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Store the texture in the map with the file path as the key
    textureMap[filePath] = newTexture;
    return newTexture;
}

void TextureManager::freeTexture(const std::string& textureID) {
    // Find the texture in the map
    auto it = textureMap.find(textureID);
    if (it != textureMap.end()) {
        SDL_DestroyTexture(it->second); // Free the texture
        textureMap.erase(it); // Remove from the map
    }
}

SDL_Texture* TextureManager::getTexture(const std::string& textureID) {
    // Retrieve the texture from the map
    auto it = textureMap.find(textureID);
    if (it != textureMap.end()) {
        return it->second;
    }
    return nullptr; // Return nullptr if not found
}
