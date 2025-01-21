#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem>
#include <SFML/Audio.hpp>

class SoundManager
{
private:
    static std::unordered_map<std::string, sf::Sound> sounds;
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
public:


    static void loadSound(const std::string& name, const std::string& filename);
    static sf::Sound& getSound(const std::string& name);
    std::unordered_map<std::string, sf::Sound>& getSounds();

    SoundManager();
    ~SoundManager();


};