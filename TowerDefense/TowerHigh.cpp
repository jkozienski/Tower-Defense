#include "TowerHigh.h"

TowerHigh::TowerHigh( float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager, WaveManager* waveManager, Player* player, int towerDamage, int towerRange, int towerCost)
    : Tower(projectileSpeed, textureManager, soundManager,waveManager,player, towerDamage, towerRange, towerCost) {
    this->sprite.setTexture(this->textureManager->getTexture("TurretLVL3"));
    
    this->rangeCoverage.setRadius(towerRange);
    sf::Color rangeColor = sf::Color::Red;
    rangeColor.a = 32;
    this->rangeCoverage.setFillColor(rangeColor);
    this->fireInterval = sf::milliseconds(200);
}

TowerHigh::~TowerHigh() = default;

void TowerHigh::displayInfo() const
{

    std::cout << "Damage: " << damage << std::endl;
    std::cout << "Range: " << range << std::endl;
    std::cout << "Cost: " << cost << std::endl;

}

void TowerHigh::updateMousePos(sf::RenderWindow* window)
{
    this->TEMPmousePos = sf::Mouse::getPosition(*window);
    this->mousePos.x = TEMPmousePos.x;
    this->mousePos.y = TEMPmousePos.y;
}

