#include "TowerLow.h"

TowerLow::TowerLow( float projectileSpeed, TextureManager* textureManager,SoundManager* soundManager, WaveManager* waveManager, Player* player, int towerDamage, int towerRange, int towerCost)
    : Tower(projectileSpeed, textureManager, soundManager, waveManager, player, towerDamage, towerRange, towerCost) {
    
    this->sprite.setTexture(this->textureManager->getTexture("TurretLVL1"));
   
    this->rangeCoverage.setRadius(towerRange);
    sf::Color rangeColor = sf::Color::Green;
    rangeColor.a = 32;
    this->rangeCoverage.setFillColor(rangeColor);
    this->fireInterval = sf::milliseconds(600);
}

TowerLow::~TowerLow() = default;

void TowerLow::displayInfo() const
{
    std::cout << "Damage: " << damage << std::endl;
    std::cout << "Range: " << range << std::endl;
    std::cout << "Cost: " << cost << std::endl;
}

void TowerLow::updateMousePos(sf::RenderWindow* window)
{
    this->TEMPmousePos = sf::Mouse::getPosition(*window);
    this->mousePos.x = TEMPmousePos.x;
    this->mousePos.y = TEMPmousePos.y;
   // std::cout << mousePos.x << " " << mousePos.y << "\n";
}



