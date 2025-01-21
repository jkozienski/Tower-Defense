#pragma once
#include "Tower.h"
class TowerLow : public Tower {
public:
    // Konstruktor
    TowerLow( float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager, WaveManager* waveManager, Player* player, int towerDamage, int towerRange, int towerCost);
    ~TowerLow();
    // Implementacja wirtualnej metody displayInfo dla klasy TowerLow
    
    
   
    void displayInfo() const override;
    void updateMousePos(sf::RenderWindow* window) override;

};



