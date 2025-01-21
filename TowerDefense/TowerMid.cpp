#include "TowerMid.h"

TowerMid::TowerMid( float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager, WaveManager* waveManager, Player* player, int towerDamage, int towerRange, int towerCost)
    : Tower( projectileSpeed, textureManager, soundManager, waveManager, player, towerDamage, towerRange, towerCost) {


    this->sprite.setTexture(this->textureManager->getTexture("TurretLVL2"));
    this->rangeCoverage.setRadius(towerRange);
    sf::Color rangeColor = sf::Color::Blue;
    rangeColor.a = 32;
    this->rangeCoverage.setFillColor(rangeColor);
    this->fireInterval = sf::milliseconds(500);

}

TowerMid::~TowerMid() = default;

void TowerMid::displayInfo() const
{

    std::cout << "Damage: " << damage << std::endl;
    std::cout << "Range: " << range << std::endl;
    std::cout << "Cost: " << cost << std::endl;

}

void TowerMid::updateMousePos(sf::RenderWindow* window)
{
    this->TEMPmousePos = sf::Mouse::getPosition(*window);
    this->mousePos.x = TEMPmousePos.x;
    this->mousePos.y = TEMPmousePos.y;
    // std::cout << mousePos.x << " " << mousePos.y << "\n";
}


