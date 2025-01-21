#include "SoundManager.h"

std::unordered_map<std::string, sf::Sound> SoundManager::sounds;
std::unordered_map<std::string, sf::SoundBuffer> SoundManager::soundBuffers;

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {
    sounds.clear();
    soundBuffers.clear();
}

void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    if (soundBuffers.find(name) == soundBuffers.end()) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(filename)) {
            soundBuffers[name] = buffer;
            sounds[name].setBuffer(soundBuffers[name]);
            //std::cout << "Zaladowano dzwiek: " << filename << std::endl;

        }
        else {
            std::cerr << "Nie znaleziono pliku: " << filename << std::endl;
        }
    }
}

sf::Sound& SoundManager::getSound(const std::string& name) {
    return sounds.at(name);
}

std::unordered_map<std::string, sf::Sound>& SoundManager::getSounds() {
    return this->sounds;
}
