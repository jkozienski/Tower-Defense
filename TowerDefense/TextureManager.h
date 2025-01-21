#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem>

class TextureManager {
public:
    static void loadTexture(const std::string& name, const std::string& filename);
    static sf::Texture& getTexture(const std::string& name);
    
    TextureManager();
    ~TextureManager();

private:
    static std::unordered_map<std::string, sf::Texture> textures;
};