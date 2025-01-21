#pragma once
#include "Tower.h"
class TowerHigh : public Tower {
public:
    // Konstruktor
    TowerHigh(float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager,WaveManager* waveManager,Player* player, int towerDamage, int towerRange, int towerCost);
    ~TowerHigh();

    void displayInfo() const override;
    void updateMousePos(sf::RenderWindow* window) override;
   
};



