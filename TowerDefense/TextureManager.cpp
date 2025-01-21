#include "TextureManager.h"

namespace fs = std::filesystem;

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

TextureManager::TextureManager() {
}
TextureManager::~TextureManager() {
    this->textures.clear();
}
//Filesystem
void TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    //TODO:Filesystem
    if (fs::exists(filename)) { // Sprawdü, czy plik istnieje
        if (texture.loadFromFile(filename)) {
            textures[name] = texture;
            //std::cout << "Zaladowano: " << filename << std::endl;
        }
        else {
            std::cerr << "Nie zaladowano tekstury: " << filename << std::endl;
        }
    }
    else {
        std::cerr << "Nie znaleziono pliku: " << filename << std::endl;
    }
}

sf::Texture& TextureManager::getTexture(const std::string& name) {
    return textures.at(name);
}


