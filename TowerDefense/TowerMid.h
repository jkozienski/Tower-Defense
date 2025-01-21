#pragma once
#include "Tower.h"
class TowerMid : public Tower {
public:
    // Konstruktor
    TowerMid( float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager,WaveManager* waveManager, Player* player, int towerDamage, int towerRange, int towerCost);
        
    ~TowerMid();
    
    void displayInfo() const override;
    void updateMousePos(sf::RenderWindow* window) override;
};



