#pragma once
#include "Enemy.h"
#include "EnemyEasy.h"
#include "EnemyMedium.h"
#include "EnemyHard.h"
#include "Player.h"
//#include "Map.h"

#include <vector>
#include <algorithm>
#include <ranges>
#include <iostream>
#include <windows.h>
#include <random>
#include <thread>
#include <mutex>

class WaveManager {
private:
    std::vector<std::vector<Enemy*>> waves; // Kolekcja fal przeciwników
    std::vector<Enemy*> enemiesInWave;
    TextureManager* textureManager;
    Map* map;
    Player* player;
    bool waveExists;
    int currentWaveNumber = 0;


public:
    // Konstruktor
    WaveManager(Map* map, Player* player);

    ~WaveManager();

    const bool& getWaveExists() const;
   
    void generateWave(int minEasy, int maxEasy, int minMedium, int maxMedium, int minHard, int maxHard);

    const std::vector<std::vector<Enemy*>>& getWaves() const;
    const std::vector<Enemy*>& getEnemies() const;
    
    // Metoda do rozpoczêcia nowej fali
    const int getWaveNumber();
    void startNewWave();

    // Metoda do aktualizowania stanu fali (np. sprawdzanie, czy fala zosta³a pokonana
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};

